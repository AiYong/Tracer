#include "CTPMarketDataSubscriber.h"

CTPMarketDataSubscriber::CTPMarketDataSubscriber(Account const* pAccount)
{

}

CTPMarketDataSubscriber::~CTPMarketDataSubscriber()
{

}

bool CTPMarketDataSubscriber::Initialize()
{
    m_nRequestNumber++;
    mMdApi = CThostFtdcMdApi::CreateFtdcMdApi();
    QStringList lMarketDataUrl = m_pAccount->GetBroker()->GetMarketDataUrl();
    for(auto iPos = lMarketDataUrl.begin(); iPos != lMarketDataUrl.end(); iPos++)
    {
        QString strUrl = *iPos;
        mMdApi->RegisterFront(const_cast<char*>(strUrl.toStdString().c_str()));
    }
    m_pMdApi->RegisterSpi(this);
    strcpy(m_oLoginInfo.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oLoginInfo.UserID,m_pAccount->GetId().toStdString().c_str());
    strcpy(m_oLoginInfo.Password,m_pAccount->GetPassword().toStdString().c_str());
    m_pMdApi->Init();
    return true;
}

void CTPMarketDataSubscriber::Destroy()
{
    m_pMdApi->RegisterSpi(nullptr);
    m_pMdApi->Release();
}

void CTPMarketDataSubscriber::Subscribe(MarketDataListener *pListener, QList<Instrument*> const& lstInstrument)
{

}

void CTPMarketDataSubscriber::UnSubscribe(MarketDataListener *pListener,QList<Instrument*> const& lstInstrument)
{

}

void CTPMarketDataSubscriber::OnFrontConnected()
{
    m_pMdApi->ReqUserLogin(&m_oLoginInfo,m_nRequestNumber++);
}

void CTPMarketDataSubscriber::OnFrontDisconnected(int nReason)
{

}

void CTPMarketDataSubscriber::OnHeartBeatWarning(int nTimeLapse)
{

}

void CTPMarketDataSubscriber::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(pRspInfo == nullptr || pRspInfo != nullptr && pRspInfo->ErrorID == 0)
    {
        QList<Instrument*> lInstruments = m_pAccount->GetInstruments().values();
        char** strCodes = new char*[lInstruments.size()];
        for(int nCount = 0 ; nCount < lInstruments.size() ; nCount++)
        {
            Instrument *pInstrument = lInstruments[nCount];
            strCodes[nCount] = new char[10];
            strcpy(strCodes[nCount],pInstrument->GetID().toStdString().c_str());
        }
        m_pMdApi->SubscribeMarketData(strCodes,lInstruments.size());
        for(int nCount = 0 ; nCount < lInstruments.size(); nCount++)
        {
            delete[] strCodes[nCount];
        }
        delete[] strCodes;
    }
}

void CTPMarketDataSubscriber::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTPMarketDataSubscriber::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTPMarketDataSubscriber::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTPMarketDataSubscriber::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTPMarketDataSubscriber::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    QMutexLocker oLocker(m_mLock);
    QString strInstrumentID(pDepthMarketData->InstrumentID);
    Instrument *pInstrument = m_lInstruments[strInstrumentID];
    QString strTimestamp(pDepthMarketData->TradingDay);
    strTimestamp.append(".");
    strTimestamp.append(pDepthMarketData->UpdateTime);
    QDateTime oTimestamp = QDateTime::fromString(strTimestamp,"yyyyMMdd.HH:mm:ss");
    oTimestamp.addMSecs(pDepthMarketData->UpdateMillisec);
    bool bIsLevelTwo = false;
    MarketData *pMarektData = nullptr;
    if(
      pDepthMarketData->BidVolume2 == 0 &&
      pDepthMarketData->BidVolume3 == 0 &&
      pDepthMarketData->BidVolume4 == 0 &&
      pDepthMarketData->BidVolume5 == 0
      )
    {
       bIsLevelTwo = true;
    }
    if(bIsLevelTwo)
    {
        pMarektData = new MarketData(
                    oTimestamp,pDepthMarketData->LastPrice,pDepthMarketData->Volume - pInstrument->GetVolume(),
                    pDepthMarketData->Turnover - pInstrument->GetAmount(),pDepthMarketData->Turnover,
                    pDepthMarketData->Volume,pDepthMarketData->UpperLimitPrice,pDepthMarketData->LowerLimitPrice,
                    pDepthMarketData->OpenInterest,pDepthMarketData->PreOpenInterest,pDepthMarketData->OpenPrice,
                    pDepthMarketData->HighestPrice,pDepthMarketData->LowestPrice,pDepthMarketData->SettlementPrice,
                    pDepthMarketData->PreClosePrice,pDepthMarketData->PreSettlementPrice,pDepthMarketData->BidPrice1,
                    pDepthMarketData->BidVolume1,pDepthMarketData->AskPrice1,pDepthMarketData->AskVolume1,
                    pDepthMarketData->BidPrice2,pDepthMarketData->BidVolume2,pDepthMarketData->AskPrice2,
                    pDepthMarketData->AskVolume2,pDepthMarketData->BidPrice3,pDepthMarketData->BidVolume3,
                    pDepthMarketData->AskPrice3,pDepthMarketData->AskVolume3,pDepthMarketData->BidPrice4,
                    pDepthMarketData->BidVolume4,pDepthMarketData->AskPrice4,pDepthMarketData->AskVolume4,
                    pDepthMarketData->BidPrice5,pDepthMarketData->BidVolume5,pDepthMarketData->AskPrice5,
                    pDepthMarketData->AskVolume5
                    );
    }
    else
    {
        pMarektData = new MarketData(
                    oTimestamp,pDepthMarketData->LastPrice,pDepthMarketData->Volume - pInstrument->GetVolume(),
                    pDepthMarketData->Turnover - pInstrument->GetAmount(),pDepthMarketData->Turnover,
                    pDepthMarketData->Volume,pDepthMarketData->UpperLimitPrice,pDepthMarketData->LowerLimitPrice,
                    pDepthMarketData->OpenInterest,pDepthMarketData->PreOpenInterest,pDepthMarketData->OpenPrice,
                    pDepthMarketData->HighestPrice,pDepthMarketData->LowestPrice,pDepthMarketData->SettlementPrice,
                    pDepthMarketData->PreClosePrice,pDepthMarketData->PreSettlementPrice,pDepthMarketData->BidPrice1,
                    pDepthMarketData->BidVolume1,pDepthMarketData->AskPrice1,pDepthMarketData->AskVolume1
                    );
    }

    m_lMarketData.append(pMarektData);
    QList<MarketDataListener*> lMarketDataListener =  m_mMarketDataListener[strInstrumentID];
    for(int nCount = 0 ; nCount < lMarketDataListener.size() ; nCount++)
    {
        MarketDataListener *pMarketDataListener = lMarketDataListener[nCount];
        pMarketDataListener->MarketDataUpdated(pInstrument,pMarektData);
    }
}
