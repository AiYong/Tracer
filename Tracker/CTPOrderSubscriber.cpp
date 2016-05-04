#include "CTPOrderSubscriber.h"

CTPOrderSubscriber::CTPOrderSubscriber(Account *pAccount)
    :OrderSubscriber(pAccount)
{

}

CTPOrderSubscriber::~CTPOrderSubscriber()
{

}

bool CTPOrderSubscriber::Initialize()
{
    m_nRequestNumber = 1;
    strcpy(m_oLoginInfo.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oLoginInfo.UserID,m_pAccount->GetId().toStdString().c_str());
    strcpy(m_oLoginInfo.Password,m_pAccount->GetPassword().toStdString().c_str());
    m_pTradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
    m_pTradeApi->SubscribePrivateTopic(THOST_TERT_QUICK);
    m_pTradeApi->SubscribePublicTopic(THOST_TERT_QUICK);
    m_pTradeApi->RegisterSpi(this);
    QStringList lTradeUrls = m_pAccount->GetBroker()->GetTradeUrl();
    for(auto iPos = lTradeUrls.begin(); iPos != lTradeUrls.end();iPos++)
    {
        QString strUrl = *iPos;
        m_pTradeApi->RegisterFront(const_cast<char*>(strUrl.toStdString().c_str()));
    }
    strcpy(m_oSettlementInfoConfirm.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oSettlementInfoConfirm.InvestorID,m_pAccount->GetId().toStdString().c_str());
    m_pTradeApi->Init();
}

void CTPOrderSubscriber::Destroy()
{

}


void CTPOrderSubscriber::OnFrontConnected()
{
    m_pTradeApi->ReqUserLogin(&m_oLoginInfo,m_nRequestNumber++);
}

void CTPOrderSubscriber::OnFrontDisconnected(int nReason)
{

}

void CTPOrderSubscriber::OnHeartBeatWarning(int nTimeLapse)
{

}

void CTPOrderSubscriber::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
    m_pTradeApi->ReqSettlementInfoConfirm(&m_oSettlementInfoConfirm,m_nRequestNumber++);
}

void CTPOrderSubscriber::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{

}

void CTPOrderSubscriber::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
    if(pInputOrder && (pRspInfo == nullptr || pRspInfo !=nullptr && pRspInfo->ErrorID == 0 ) && bIsLast )
    {
        Order *pOrder = EnsureOrder(pInputOrder);
        if(pOrder)
        {
            SubscriberProcessor *pProcessor = m_hProcessor[pOrder->GetInstrument()->GetID()];
            pProcessor->PublishSubmit(pOrder);
        }
    }
}


void CTPOrderSubscriber::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
    if(pInputOrderAction && (pRspInfo == nullptr || pRspInfo !=nullptr && pRspInfo->ErrorID == 0 ) && bIsLast)
    {
        QString strOrderRef(pInputOrderAction->OrderRef);
        Order *pOrder = m_hOrders[strOrderRef];
        if(pOrder)
        {
            switch (pInputOrderAction->ActionFlag) {
            case THOST_FTDC_AF_Delete:
            {
                m_pAccount->SetOrderStatus(pOrder,osCancelling);
                SubscriberProcessor *pProcessor = m_hProcessor[pOrder->GetInstrument()->GetID()];
                pProcessor->PublishCancelling(pOrder);
            }
                break;
            case THOST_FTDC_AF_Modify:

                break;
            default:
                break;
            }
        }
    }
}

void CTPOrderSubscriber::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{

}

void CTPOrderSubscriber::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTPOrderSubscriber::OnRtnOrder(CThostFtdcOrderField *pInputOrder)
{
    QString strOrderRef(pInputOrder->OrderRef);
    Order pOrder = m_hOrders[strOrderRef];
    if(pOrder)
    {
        switch (pInputOrder->OrderStatus) {
        case THOST_FTDC_OST_Canceled:
        {
            SubscriberProcessor *pProcessor = m_hProcessor[pOrder->GetInstrument()->GetID()];
            pProcessor->PublishCancelled(pOrder);
        }
            break;
        default:
            break;
        }
    }
}

void CTPOrderSubscriber::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    QString strOrderRef(pTrade->OrderRef);
    Order *pOrder = m_hOrders[pTrade];
    if(pOrder)
    {
        QString strTradeTime(pTrade->TradeDate);
        strTradeTime.append(pTrade->TradeTime);
        QDateTime oTradeTime = QDateTime::fromString(strTradeTime,"yyyyMMddHH:mm:ss");
        size_t nQuantity = pTrade->Volume;
        double dPrice = pTrade->Price;
        SubscriberProcessor *pProcessor = m_hProcessor[pOrder->GetInstrument()->GetID()];
        if(pOrder->GetOperation() == opOpen)
        {
            Position *pPosition = m_pAccount->CreatePosition(pOrder,oTradeTime,nQuantity,dPrice);
            pProcessor->PublishOpen(pOrder,pPosition);
        }
        else
        {
            Transaction *pTransaction = m_pAccount->CreateTransaction(pOrder,oTradeTime,nQuantity,dPrice);
            pProcessor->PublishClose(pOrder,pTransaction);
        }
    }
}


void CTPOrderSubscriber::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{

}

void CTPOrderSubscriber::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{

}

Order* CTPOrderSubscriber::EnsureOrder(CThostFtdcInputOrderField *pInputOrder)
{
   Order *pResult = nullptr;
   QString strOrderRef(pInputOrder->OrderRef);
   if(m_hOrders.contains(strOrderRef))
   {
       pOrder = m_hOrders[strOrderRef];
   }
   else
   {
       Instrument *pInstrument = m_pAccount->GetInstrument(pInputOrder->InstrumentID);
       if(pInstrument == nullptr)
       {
           return pResult;
       }
       Direction eDirection = dLong;
       if(pInputOrder->Direction == THOST_FTDC_D_Sell)
       {
           eDirection = dShort;
       }
       HedgeFlag eHedgeFlag = hfSpeculation;
       if(pInputOrder->CombHedgeFlag[0] == THOST_FTDC_HF_Arbitrage)
       {
           eHedgeFlag = hfArbitrage;
       }
       else if(pInputOrder->CombHedgeFlag[0] == THOST_FTDC_HF_Hedge)
       {
           eHedgeFlag = hfHedge;
       }
       PriceMode ePriceMode = pmLimitPrice;
       if(pInputOrder->OrderPriceType == THOST_FTDC_OPT_AnyPrice)
       {
           ePriceMode = pmMarketPrice;
       }
       Operation eOperation = opClose;
       if(pInputOrder->CombOffsetFlag[0] == THOST_FTDC_OF_Open)
       {
           eOperation = opOpen;
       }
       pResult = m_pAccount->CreateOrder(pInstrument,eDirection,eOperation,eHedgeFlag,ePriceMode,
                                               pInputOrder->VolumeTotalOriginal,pInputOrder->LimitPrice);
       m_hOrders.insert(strOrderRef,pResult);
   }
   return pResult;
}
