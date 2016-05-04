#include "CTPOrderProcessor.h"
#include <cstring>

CTPOrder::CTPOrder(Order *pOrder,OrderListener *pOrderListener)
    :m_pOrder(pOrder),m_pOrderListener(pOrderListener)
{
    Init();
}

CTPOrder::~CTPOrder()
{
}

void CTPOrder::Init()
{
    strcpy(m_oInputOrder.InstrumentID,m_pOrder->GetInstrument()->GetID().toStdString().c_str());
    QString strOrderRef = m_pOrder->GetTimestamp().toString("yyyyMMdd");
    sprintf(m_oInputOrder.OrderRef,"%s%06ld",strOrderRef.toStdString().c_str(),m_pOrder->GetId());
    m_oInputOrder.ForceCloseReason =THOST_FTDC_FCC_NotForceClose;
    m_oInputOrder.IsAutoSuspend = false;
    m_oInputOrder.IsSwapOrder = false;
    m_oInputOrder.LimitPrice = closeRequest->getQuote();
    m_oInputOrder.VolumeTotalOriginal = closeRequest->getQuantity();
    m_oInputOrder.MinVolume = 1;
    m_oInputOrder.VolumeCondition = THOST_FTDC_VC_AV;
    m_oInputOrder.ContingentCondition = THOST_FTDC_CC_Immediately;
    if(m_pOrder->GetOperation() = opOpen)
    {
        m_oInputOrder.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    }
    else
    {
        m_oInputOrder.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
    }

    switch (m_pOrder->GetPriceMode())
    {
    case pmLimitPrice:
        m_oInputOrder.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        m_oInputOrder.TimeCondition = THOST_FTDC_TC_GFD;
        break;
    case pmMarketPrice:
        m_oInputOrder.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
        m_oInputOrder.TimeCondition = THOST_FTDC_TC_IOC;
    default:
        break;
    }
    switch (m_pOrder->GetDirection()) {
    case dLong:
        m_oInputOrder.Direction = THOST_FTDC_D_Sell;
        break;
    case dShort:
        m_oInputOrder.Direction = THOST_FTDC_D_Buy;
    default:
        break;
    }
    switch(m_pOrder->GetHedgeFlag())
    {
    case hfArbitrage:
        m_oInputOrder.CombHedgeFlag[0] = THOST_FTDC_HF_Arbitrage;
        break;
    case hfSpeculation:
        m_oInputOrder.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
        break;
    case hfHedge:
        m_oInputOrder.CombHedgeFlag[0] = THOST_FTDC_HF_Hedge;
        break;
    }
}

Order* CTPOrder::GetOrder() const
{
    return m_pOrder;
}

OrderListener* CTPOrder::GetOrderListener() const
{
    return m_pOrderListener;
}

CThostFtdcInputOrderField const& CTPOrder::GetInputOrder() const
{
    return m_oInputOrder;
}

CThostFtdcInputOrderActionField const& CTPOrder::GetInputOrderAction() const
{
    m_oInputOrderAction.ActionFlag = THOST_FTDC_AF_Delete;
    strcpy(m_oInputOrderAction.OrderRef,m_oOrderResponse.OrderRef);
    strcpy(m_oInputOrderAction.OrderSysID,m_oOrderResponse.OrderSysID);
    strcpy(m_oInputOrderAction.InstrumentID,m_oOrderResponse.InstrumentID);
    strcpy(m_oInputOrderAction.ExchangeID,m_oOrderResponse.ExchangeID);
    m_oInputOrderAction.FrontID = m_oOrderResponse.FrontID;
    m_oInputOrderAction.OrderActionRef = m_pOrder->GetId();
    m_oInputOrderAction.LimitPrice = m_oOrderResponse.LimitPrice;
    m_oInputOrderAction.VolumeChange = m_oOrderResponse.VolumeTotal;
    m_oInputOrderAction.SessionID = m_oOrderResponse.SessionID;
    return m_oInputOrderAction;
}

void CTPOrder::SetOrderResponse(CThostFtdcOrderField const& oOrderResponse)
{
    memcpy(&m_oOrderResponse,&oOrderResponse,sizeof(CThostFtdcOrderField));
}


CTPOrderProcessor::CTPOrderProcessor(Account *pAccount)
    :OrderProcessor(pAccount)
{

}


CTPOrderProcessor::~CTPOrderProcessor()
{

}

bool CTPOrderProcessor::Initialize()
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
    m_bConnected = false;
    m_pTradeApi->Init();
    std::unique_lock<std::mutex> oLocker(m_lLock);
    auto oWaitCondition = [&]()->bool {
        return m_bConnected == true;
    };
    if(m_cWaitCondition.wait_for(std::chrono::seconds(30),oWaitCondition))
    {
        return true;
    }
    m_pTradeApi->Release();
    m_pTradeApi = nullptr;
    return false;
}

void CTPOrderProcessor::Destroy()
{
    if(m_pTradeApi)
    {
        m_pTradeApi->RegisterSpi(nullptr);
        m_pTradeApi->Release();
        m_pTradeApi = nullptr;
    }
}

void CTPOrderProcessor::Submit(Order const* pOrder)
{
    std::unique_lock oLocker(m_lLock);
    CTPOrderOperation oOperation;
    oOperation.eType = ootSubmit;
    oOperation.pOrder = pOrder;
    m_qOrders.push_back(oOperation);
    m_cWaitCondition.notify_one();
}

void CTPOrderProcessor::Cancel(Order const* pOrder)
{
    std::unique_lock oLocker(m_lLock);
    CTPOrderOperation oOperation;
    oOperation.eType = ootCancel;
    oOperation.pOrder = pOrder;
    m_qOrders.push_back(oOperation);
    m_cWaitCondition.notify_one();
}

void CTPOrderProcessor::operator()()
{
    while(true)
    {
        if(m_bStop)
        {
            return ;
        }
        std::unique_lock<std::mutex> oLocker(m_lLock);
        while(m_qOrders.isEmpty())
        {
            if(m_bStop)
            {
                return;
            }
            m_cWaitCondition.wait(oLocker);
        }
        CTPOrderOperation oOperation = m_qOrders.front();
        m_qOrders.pop_front();
        switch (oOperation.eType) {
        case ootSubmit:
        {
            CTPOrder *pCTPOrder = new CTPOrder(oOperation.pOrder,oOperation.pOrderListener);
            CThostFtdcInputOrderField const& oInputOrder = pCTPOrder->GetInputOrder();
            m_hOrders.insert(QString(oInputOrder.OrderRef),pCTPOrder);
            m_pTradeApi->ReqOrderInsert(const_cast<CThostFtdcInputOrderField*>(&oInputOrder),m_nRequestNumber++);
            pCTPOrder->GetOrderListener()->OnSubmited(oOperation.pOrder);
        }
            break;
        case ootCancel:
        {
            QString strOrderRef = "%1%1";  ;
            strOrderRef = strOrderRef.arg(oOperation.pOrder->GetTimestamp().toString("yyyyMMdd"))
                                     .arg(oOperation.pOrder->GetId(),6,"0");
            CTPOrder *pCTPOrder = m_hOrders[strOrderRef];
            if(pCTPOrder)
            {
                CThostFtdcInputOrderActionField const& oInputOrder = pCTPOrder->GetInputOrderAction();
                m_pTradeApi->ReqOrderAction(oInputOrder,m_nRequestNumber++);
                pCTPOrder->GetOrderListener()->OnCancelling(oOperation.pOrder);
            }
        }
            break;
        default:
            break;
        }
    }
}

void CTPOrderProcessor::OnFrontConnected()
{
    m_pTradeApi->ReqUserLogin(&m_oLoginInfo,m_nRequestNumber++);
}

void CTPOrderProcessor::OnFrontDisconnected(int nReason)
{
    m_bConnected = false;
}

void CTPOrderProcessor::OnHeartBeatWarning(int nTimeLapse)
{

}

void CTPOrderProcessor::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
    m_pTradeApi->ReqSettlementInfoConfirm(&m_oSettlementInfoConfirm,m_nRequestNumber++);
}

void CTPOrderProcessor::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{

}

void CTPOrderProcessor::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{

}

void CTPOrderProcessor::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{

}

void CTPOrderProcessor::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
    if(pRspInfo == nullptr || (pRspInfo != nullptr && pRspInfo->ErrorID == 0))
    {
        m_bConnected = true;
    }
}

void CTPOrderProcessor::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTPOrderProcessor::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
   QString strOrderRef(pOrder->OrderRef);
   CTPOrder *pCTPOrder = m_hOrders[strOrderRef];
   if(pCTPOrder)
   {
       pCTPOrder->SetOrderResponse(*pOrder);
       switch (pOrder->OrderStatus)
       {
       case THOST_FTDC_OST_Unknown:
       case THOST_FTDC_OST_NoTradeQueueing:
       {
           if(strlen(pOrder->OrderSysID))
           {
               pCTPOrder->GetOrderListener()->OnQueued(pCTPOrder->GetOrder());
           }
       }
       break;
       case THOST_FTDC_OST_AllTraded:
       case THOST_FTDC_OST_Touched:
       case THOST_FTDC_OST_NotTouched:
       case THOST_FTDC_OST_NoTradeNotQueueing:
       case THOST_FTDC_OST_PartTradedNotQueueing:
       case THOST_FTDC_OST_PartTradedQueueing:
       break;
       case THOST_FTDC_OST_Canceled:
       {
           pCTPOrder->GetOrderListener()->OnQueued(pCTPOrder->GetOrder());
       }
       break;
       default:
       break;
       }
   }
}

void CTPOrderProcessor::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    m_lLock.lock();
    QString strOrderRef(pOrder->OrderRef);
    CTPOrder *pCTPOrder = m_hOrders[strOrderRef];
    m_lLock.unlock();
    if(pCTPOrder)
    {
        QString strTradeTime(pTrade->TradeDate);
        strTradeTime.append(pTrade->TradeTime);
        QDateTime oTradeTime = QDateTime::fromString(strTradeTime,"yyyyMMddHH:mm:ss");
        size_t nQuantity = pTrade->Volume;
        double dPrice = pTrade->Price;
        if(pCTPOrder->GetOrder()->GetOperation() == opOpen)
        {
            Position *pPosition = m_pAccount->CreatePosition(pCTPOrder->GetOrder(),oTradeTime,nQuantity,dPrice);
            pCTPOrder->GetOrderListener()->OnOpen(pCTPOrder->GetOrder(),pPosition);
        }
        else
        {
            Transaction *pTransaction = m_pAccount->CreateTransaction(pCTPOrder->GetOrder(),oTradeTime,nQuantity,dPrice);
            pCTPOrder->GetOrderListener()->OnClose(pCTPOrder->GetOrder(),pTransaction);
        }

    }
}

void CTPOrderProcessor::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{

}

void CTPOrderProcessor::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{

}

void CTPOrderProcessor::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{

}

void CTPOrderProcessor::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{

}
