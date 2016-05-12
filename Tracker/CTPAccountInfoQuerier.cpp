#include "CTPAccountInfoQuerier.h"
#include "Broker.h"
#include <thread>

CTPAccountInfoQuerier::CTPAccountInfoQuerier(Account const*pAccount)
	:m_pAccount(pAccount)
{

}

CTPAccountInfoQuerier::~CTPAccountInfoQuerier()
{

}

void CTPAccountInfoQuerier::OnFrontConnected()
{
    m_pTradeApi->ReqUserLogin(&m_oLoginInfo,m_nRequestNumber++);
}

void CTPAccountInfoQuerier::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
    if(pRspInfo == nullptr || pRspInfo != nullptr && pRspInfo->ErrorID == 0)
    {
        m_bCompleted = true;
        m_cWaitCondition.notify_one();
    }
}

void CTPAccountInfoQuerier::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if((pRspInfo == nullptr || pRspInfo != nullptr && pRspInfo->ErrorID == 0) && pInvestor != nullptr)
    {
        memcpy(&m_oInvestor,pInvestor,sizeof(CThostFtdcInvestorField));
        m_bCompleted = true;
        m_cWaitCondition.notify_one();
    }
}

void CTPAccountInfoQuerier::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if((pRspInfo == nullptr || pRspInfo != nullptr && pRspInfo->ErrorID == 0) && pInstrument != nullptr)
    {
        CThostFtdcInstrumentField *pNewInstrument = new CThostFtdcInstrumentField;
        memcpy(pNewInstrument,pInstrument,sizeof(CThostFtdcInstrumentField));
        m_lInstruments.append(pNewInstrument);
        if(bIsLast)
        {
            m_bCompleted = true;
            m_cWaitCondition.notify_one();
        }
    }
}

void CTPAccountInfoQuerier::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if((pRspInfo == nullptr || pRspInfo != nullptr && pRspInfo->ErrorID == 0) && pTradingAccount != nullptr)
    {
        memcpy(&m_oTradingAccount,pTradingAccount,sizeof(CThostFtdcTradingAccountField));
        m_bCompleted = true;
        m_cWaitCondition.notify_one();
    }
}

void CTPAccountInfoQuerier::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if( pInstrumentMarginRate != nullptr && (pRspInfo == nullptr || (pRspInfo!= nullptr && pRspInfo->ErrorID == 0 )) )
    {
        CThostFtdcInstrumentMarginRateField *pNewInstrumentMarginRate = new CThostFtdcInstrumentMarginRateField;
        memcpy(pNewInstrumentMarginRate,pInstrumentMarginRate,sizeof(CThostFtdcInstrumentMarginRateField));
        m_lInstrumentMarginRates.insert(pNewInstrumentMarginRate->InstrumentID,pNewInstrumentMarginRate);
        if(bIsLast)
        {
            m_bCompleted = true;
            m_cWaitCondition.notify_one();
        }
    }
}

void CTPAccountInfoQuerier::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if( pInstrumentCommissionRate != nullptr && (pRspInfo == nullptr || (pRspInfo!= nullptr && pRspInfo->ErrorID == 0 )) )
    {
        CThostFtdcInstrumentCommissionRateField *pNewInstrumentCommissionRate = new CThostFtdcInstrumentCommissionRateField;
        *pNewInstrumentCommissionRate= *pInstrumentCommissionRate;
        m_lInstrumentCommissionRates.insert(pNewInstrumentCommissionRate->InstrumentID,pNewInstrumentCommissionRate);
        if(bIsLast)
        {
            m_bCompleted = true;
            m_cWaitCondition.notify_one();
        }
    }
}

void CTPAccountInfoQuerier::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	
}

std::shared_ptr<AccountInfo> CTPAccountInfoQuerier::Query()
{
    std::shared_ptr<AccountInfo> oResult;
    m_nRequestNumber = 1;
    strcpy(m_oLoginInfo.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oLoginInfo.UserID,m_pAccount->GetID().toStdString().c_str());
    strcpy(m_oLoginInfo.Password,m_pAccount->GetPassword().toStdString().c_str());
    m_pTradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
    m_pTradeApi->SubscribePrivateTopic(THOST_TERT_QUICK);
    m_pTradeApi->SubscribePublicTopic(THOST_TERT_QUICK);
    m_pTradeApi->RegisterSpi(this);
    QStringList lTradeUrls = m_pAccount->GetBroker()->GetTradeUrl();
    for(auto iPos = lTradeUrls.begin(); iPos != lTradeUrls.end();iPos++)
    {
		std::string strUrl = (*iPos).toStdString();
        m_pTradeApi->RegisterFront(const_cast<char*>(strUrl.c_str()));
    }
    m_bCompleted = false;
    //初始化登录
    m_pTradeApi->Init();
    std::unique_lock<std::mutex> oLocker(m_lLock);
    auto oWaitCondition = [&]()->bool {
        return m_bCompleted == true;
    };
    if(!m_cWaitCondition.wait_for(oLocker,std::chrono::seconds(10),oWaitCondition))
    {
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //查询投资人信息
    memset(&m_oQryInvestor,0,sizeof(CThostFtdcQryInvestorField));
    strcpy(m_oQryInvestor.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oQryInvestor.InvestorID,m_pAccount->GetID().toStdString().c_str());
    m_bCompleted = false;
    m_pTradeApi->ReqQryInvestor(&m_oQryInvestor,m_nRequestNumber++);
    if(!m_cWaitCondition.wait_for(oLocker,std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //查询账户信息
    memset(&m_oQryTradingAccount,0,sizeof(CThostFtdcQryTradingAccountField));
    strcpy(m_oQryTradingAccount.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oQryTradingAccount.InvestorID,m_pAccount->GetID().toStdString().c_str());
    m_bCompleted = false;
    m_pTradeApi->ReqQryTradingAccount(&m_oQryTradingAccount,m_nRequestNumber++);
    if(!m_cWaitCondition.wait_for(oLocker,std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //查询合约
    m_bCompleted = false;
    memset(&m_oQryInstrument,0,sizeof(CThostFtdcQryInstrumentField));
    m_pTradeApi->ReqQryInstrument(&m_oQryInstrument,m_nRequestNumber++);
    if(!m_cWaitCondition.wait_for(oLocker,std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //查询费率
    memset(&m_oQryInstrumentCommissionRate,0,sizeof(CThostFtdcQryInstrumentCommissionRateField));
    strcpy(m_oQryInstrumentCommissionRate.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oQryInstrumentCommissionRate.InvestorID,m_pAccount->GetID().toStdString().c_str());
	//strcpy(m_oQryInstrumentCommissionRate.InstrumentID, "IF1605");
    m_pTradeApi->ReqQryInstrumentCommissionRate(&m_oQryInstrumentCommissionRate,m_nRequestNumber++);
    if(!m_cWaitCondition.wait_for(oLocker,std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
	m_bCompleted = false;
    //查询保证金率
    memset(&m_oQryInstrumentMarginRate,0,sizeof(CThostFtdcQryInstrumentMarginRateField));
    strcpy(m_oQryInstrumentMarginRate.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oQryInstrumentMarginRate.InvestorID,m_pAccount->GetID().toStdString().c_str());
	//strcpy(m_oQryInstrumentMarginRate.InstrumentID, "IF1605");
	m_oQryInstrumentMarginRate.HedgeFlag = THOST_FTDC_HF_Speculation;
	m_pTradeApi->ReqQryInstrumentMarginRate(&m_oQryInstrumentMarginRate, m_nRequestNumber++);
    if(!m_cWaitCondition.wait_for(oLocker,std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
	/*std::this_thread::sleep_for(std::chrono::seconds(1));
	m_bCompleted = false;
	CThostFtdcQryExchangeMarginRateField oQryExchangeMarginRateField;
	memset(&oQryExchangeMarginRateField, 0, sizeof(CThostFtdcQryExchangeMarginRateField));
	m_pTradeApi->ReqQryExchangeMarginRate(&oQryExchangeMarginRateField, m_nRequestNumber++);
	if (!m_cWaitCondition.wait_for(oLocker, std::chrono::seconds(10), oWaitCondition))
	{
		Clear();
		return oResult;
	}*/
    m_pTradeApi->RegisterSpi(nullptr);
    m_pTradeApi->Release();
    m_pTradeApi = nullptr;
    QList<Instrument*> lInstruments;
    for(int nCount = 0 ; nCount < m_lInstruments.size() ; nCount++)
    {
        CThostFtdcInstrumentField *pCtpInstrument = m_lInstruments[nCount];
        QString strInstrumentId(pCtpInstrument->InstrumentID);
        QString strInstrumentName = QString::fromLocal8Bit(pCtpInstrument->InstrumentName);
        QString strInstrumentVariety(pCtpInstrument->ProductID);
        QString strInstrumentExchange(pCtpInstrument->ExchangeID);
        double dPriceMultipler = pCtpInstrument->VolumeMultiple;
        double dPriceTick = pCtpInstrument->PriceTick;
        QDate oTradeDay = QDate::fromString(pCtpInstrument->ExpireDate,"yyyyMMdd");
        QTime oCloseTime = QTime::fromString("151500","hhmmss");
        QTime oLastTradeDayCloseTime = QTime::fromString("150000","hhmmss");

        Instrument *pInstrument = new Instrument(strInstrumentId,strInstrumentName,strInstrumentVariety,
                                                 strInstrumentExchange,dPriceMultipler,dPriceTick,oTradeDay,
                                                 oCloseTime,oLastTradeDayCloseTime);
        lInstruments.append(pInstrument);
        delete pCtpInstrument;
    }
    return oResult;
}

void CTPAccountInfoQuerier::Clear()
{

}
