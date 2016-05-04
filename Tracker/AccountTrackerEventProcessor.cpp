#include "AccountTrackerEventProcessor.h"
#include "AccountResourceManager.h"

TrackerEvent::TrackerEvent(EventType eType)
    :m_eType(eType)
{
}

TrackerEvent::~TrackerEvent()
{
}


EventType TrackerEvent::GetType() const
{
    return m_eType;
}

TrackerOrderEvent::TrackerOrderEvent(const Order *pOrder, EventType eType)
    :m_pOrder(pOrder),TrackerEvent(eType)
{

}

Order const* TrackerOrderEvent::GetOrder() const
{
    return m_pOrder;
}

TrackerOrderOpenEvent::TrackerOrderOpenEvent(const Position *pPosition, const Order *pOrder)
    :m_pPosition(pPosition),TrackerOrderEvent(pOrder,tOpen)
{

}

TrackerOrderOpenEvent::~TrackerOrderOpenEvent()
{
}

Position const* TrackerOrderOpenEvent::GetPosition() const
{
    return m_pPosition;
}


TrackerOrderCloseEvent::TrackerOrderCloseEvent(const Transaction *pTransaction, const Order *pOrder)
    :m_pTransaction(pTransaction),TrackerOrderEvent(pOrder,tClose)
{
}

TrackerOrderCloseEvent::~TrackerOrderCloseEvent()
{

}

Transaction const* TrackerOrderCloseEvent::GetTransaction() const
{
    return m_pTransaction;
}

TrackerOperationEvent::TrackerOperationEvent(AccountTrackerSetting *pTrackerSetting, EventType eType)
    :m_pTrackerSetting(pTrackerSetting),m_eType(eType)
{

}

TrackerOperationEvent::~TrackerOperationEvent()
{

}

AccountTrackerSetting const* TrackerOperationEvent::GetTrackerSetting() const
{
    return m_pTrackerSetting;
}

TrackerMarketDataEvent::TrackerMarketDataEvent(MarketData *pMarketData, Instrument *pInstrument)
    :m_pMarketData(pMarketData),m_pInstrument(pInstrument),TrackerEvent(tMarketData)
{

}

MarketData const* TrackerMarketDataEvent::GetInstrument() const
{
    return m_pMarketData;
}

Instrument const* TrackerMarketDataEvent::GetInstrument() const
{
    return m_pInstrument;
}


TrackerErrorEvent::TrackerErrorEvent(Order *pOrder, OrderError eError)
    :m_eError(eError),TrackerOrderEvent(pOrder,tError)
{

}

TrackerErrorEvent::~TrackerErrorEvent()
{

}

OrderError TrackerErrorEvent::GetError() const
{
    return m_eError;
}

void AccountTrackerEventProcessor::StartTrack(AccountTrackerSetting *pAccountTrackerSetting)
{
    QMutexLocker oLocker(m_lLock);
    TrackerOperationEvent *pEvent = new TrackerOperationEvent(pAccountTrackerSetting,tStartTrack);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}

void AccountTrackerEventProcessor::StopTrack(AccountTrackerSetting *pAccountTrackerSetting)
{
    QMutexLocker oLocker(m_lLock);
    TrackerOperationEvent *pEvent = new TrackerOperationEvent(pAccountTrackerSetting,tStopTrack);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}

void AccountTrackerEventProcessor::StopAllTrack()
{

}

void AccountTrackerEventProcessor::Stop()
{

}

void AccountTrackerEventProcessor::MarketDataUpdated(Instrument const* pInstrument,MarketData const* pMarketData) const
{
    QMutexLocker oLocker(m_lLock);
    TrackerMarketDataEvent *pEvent = new TrackerMarketDataEvent(pMarketData,pInstrument);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}

void AccountTrackerEventProcessor::OnSubmited(Order const* pOrder) const
{
    QMutexLocker oLocker(m_lLock);
    TrackerOrderEvent *pEvent = new TrackerOrderEvent(pOrder,tSubmit);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}

void AccountTrackerEventProcessor::OnQueued(Order const* pOrder) const
{
    QMutexLocker oLocker(m_lLock);
    TrackerOrderEvent *pEvent = new TrackerOrderEvent(pOrder,tQueued);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}

void AccountTrackerEventProcessor::OnOpen(Order const* pOrder,Position const* pPosition) const
{
    QMutexLocker oLocker(m_lLock);
    TrackerOrderOpenEvent *pEvent = new TrackerOrderOpenEvent(pPosition,pOrder);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}

void AccountTrackerEventProcessor::OnClose(Order const* pOrder,Transaction const* pTransaction) const
{
    QMutexLocker oLocker(m_lLock);
    TrackerOrderCloseEvent *pEvent = new TrackerOrderCloseEvent(pTransaction,pOrder);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}

void AccountTrackerEventProcessor::OnCancelling(Order const* pOrder) const
{
    QMutexLocker oLocker(m_lLock);
    TrackerOrderEvent *pEvent = new TrackerOrderEvent(pOrder,tCancelling);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}

void AccountTrackerEventProcessor::OnCancelled(Order const* pOrder) const
{
    QMutexLocker oLocker(m_lLock);
    TrackerOrderEvent *pEvent = new TrackerOrderEvent(pOrder,tCancelled);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}

void AccountTrackerEventProcessor::OnError(Order const* pOrder,OrderError eError) const
{
    QMutexLocker oLocker(m_lLock);
    TrackerErrorEvent *pEvent = new TrackerErrorEvent(pOrder,eError);
    m_qEvents.push_back(pEvent);
    m_cWaitCondition.wakeOne();
}


void AccountTrackerEventProcessor::run()
{
    while(true)
    {
        if(m_bStop)
        {
            return;
        }
        if(m_qEvents.isEmpty())
        {
            if(m_bStop)
            {
                return ;
            }
            m_cWaitCondition.wait(&m_lLock);
        }
        else
        {
            TrackerEvent *pEvent = m_qEvents.front();
            switch (pEvent->GetType()) {
            case tSubmit:
            {
                TrackerOrderEvent *pOrderEvent = dynamic_cast<TrackerOrderEvent*>(pEvent);
                Order const* pOrder = pOrderEvent->GetOrder();
                for(auto iPos = m_hTradeProcessors.begin() ; iPos != m_hTradeProcessors.end() ; iPos++)
                {
                    AccountTrackerTradeProcessor *pTradeProcessor = iPos.value();
                    AccountTrackerTradeData oTradeData = m_hTradeDatas.value(iPos.key());
                    if(pTradeProcessor->IsTracking(pOrder))
                    {
                        OrderOperation oOperation = pTradeProcessor->ProcessSubmit(pOrder);
                        switch (oOperation.eOperation) {
                        case ootSubmit:
                            oTradeData.pOrderProcessor->Submit(oOperation.pOrder,this);
                            break;
                        case ootCancel:
                            oTradeData.pOrderProcessor->Cancel(oOperation.pOrder);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
                break;
            case tOpen:
            {
                TrackerOrderOpenEvent *pOrderEvent = dynamic_cast<TrackerOrderOpenEvent*>(pEvent);
                Order const* pOrder = pOrderEvent->GetOrder();
                Position const* pPosition = pOrderEvent->GetPosition();
                for(auto iPos = m_hTradeProcessors.begin() ; iPos != m_hTradeProcessors.end() ; iPos++)
                {
                    AccountTrackerTradeProcessor *pTradeProcessor = iPos.value();
                    AccountTrackerTradeData oTradeData = m_hTradeDatas.value(iPos.key());
                    if(pTradeProcessor->IsTracking(pOrder))
                    {
                        OrderOperation oOperation = pTradeProcessor->ProcessOpen(pOrder,pPosition);
                        switch (oOperation.eOperation) {
                        case ootSubmit:
                            oTradeData.pOrderProcessor->Submit(oOperation.pOrder,this);
                            break;
                        case ootCancel:
                            oTradeData.pOrderProcessor->Cancel(oOperation.pOrder);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
                break;
            case tClose:
            {
                TrackerOrderCloseEvent *pOrderEvent = dynamic_cast<TrackerOrderCloseEvent*>(pEvent);
                Order const* pOrder = pOrderEvent->GetOrder();
                Transaction const* pTransaction = pOrderEvent->GetTransaction();
                for(auto iPos = m_hTradeProcessors.begin() ; iPos != m_hTradeProcessors.end() ; iPos++)
                {
                    AccountTrackerTradeProcessor *pTradeProcessor = iPos.value();
                    AccountTrackerTradeData oTradeData = m_hTradeDatas.value(iPos.key());
                    if(pTradeProcessor->IsTracking(pOrder))
                    {
                        OrderOperation oOperation = pTradeProcessor->ProcessClose(pOrder,pTransaction);
                        switch (oOperation.eOperation) {
                        case ootSubmit:
                            oTradeData.pOrderProcessor->Submit(oOperation.pOrder,this);
                            break;
                        case ootCancel:
                            oTradeData.pOrderProcessor->Cancel(oOperation.pOrder);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
                break;
            case tCancelling:
            {
                TrackerOrderEvent *pOrderEvent = dynamic_cast<TrackerOrderEvent*>(pEvent);
                Order const* pOrder = pOrderEvent->GetOrder();
                for(auto iPos = m_hTradeProcessors.begin() ; iPos != m_hTradeProcessors.end() ; iPos++)
                {
                    AccountTrackerTradeProcessor *pTradeProcessor = iPos.value();
                    AccountTrackerTradeData oTradeData = m_hTradeDatas.value(iPos.key());
                    if(pTradeProcessor->IsTracking(pOrder))
                    {
                        OrderOperation oOperation = pTradeProcessor->ProcessCancelling(pOrder);
                        switch (oOperation.eOperation) {
                        case ootSubmit:
                            oTradeData.pOrderProcessor->Submit(oOperation.pOrder,this);
                            break;
                        case ootCancel:
                            oTradeData.pOrderProcessor->Cancel(oOperation.pOrder);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
                break;
            case tCancelled:
            {
                TrackerOrderEvent *pOrderEvent = dynamic_cast<TrackerOrderEvent*>(pEvent);
                Order const* pOrder = pOrderEvent->GetOrder();
                for(auto iPos = m_hTradeProcessors.begin() ; iPos != m_hTradeProcessors.end() ; iPos++)
                {
                    AccountTrackerTradeProcessor *pTradeProcessor = iPos.value();
                    AccountTrackerTradeData oTradeData = m_hTradeDatas.value(iPos.key());
                    if(pTradeProcessor->IsTracking(pOrder))
                    {
                        OrderOperation oOperation = pTradeProcessor->ProcesCancelled(pOrder);
                        switch (oOperation.eOperation) {
                        case ootSubmit:
                            oTradeData.pOrderProcessor->Submit(oOperation.pOrder,this);
                            break;
                        case ootCancel:
                            oTradeData.pOrderProcessor->Cancel(oOperation.pOrder);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
                break;
            case tQueued:
            {
                TrackerOrderEvent *pOrderEvent = dynamic_cast<TrackerOrderEvent*>(pEvent);
                Order const* pOrder = pOrderEvent->GetOrder();
                for(auto iPos = m_hTradeProcessors.begin() ; iPos != m_hTradeProcessors.end() ; iPos++)
                {
                    AccountTrackerTradeProcessor *pTradeProcessor = iPos.value();
                    AccountTrackerTradeData oTradeData = m_hTradeDatas.value(iPos.key());
                    if(pTradeProcessor->IsTracking(pOrder))
                    {
                        OrderOperation oOperation = pTradeProcessor->ProcessQueued(pOrder);
                        switch (oOperation.eOperation) {
                        case ootSubmit:
                            oTradeData.pOrderProcessor->Submit(oOperation.pOrder,this);
                            break;
                        case ootCancel:
                            oTradeData.pOrderProcessor->Cancel(oOperation.pOrder);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
                break;
            case tError:
            {
                TrackerErrorEvent *pOrderEvent = dynamic_cast<TrackerErrorEvent*>(pEvent);
                Order const* pOrder = pOrderEvent->GetOrder();
                OrderError eError = pOrderEvent->GetError();
                for(auto iPos = m_hTradeProcessors.begin() ; iPos != m_hTradeProcessors.end() ; iPos++)
                {
                    AccountTrackerTradeProcessor *pTradeProcessor = iPos.value();
                    AccountTrackerTradeData oTradeData = m_hTradeDatas.value(iPos.key());
                    if(pTradeProcessor->IsTracking(pOrder))
                    {
                        OrderOperation oOperation = pTradeProcessor->ProcessError(pOrder,eError);
                        switch (oOperation.eOperation) {
                        case ootSubmit:
                            oTradeData.pOrderProcessor->Submit(oOperation.pOrder,this);
                            break;
                        case ootCancel:
                            oTradeData.pOrderProcessor->Cancel(oOperation.pOrder);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
                break;
            case tMarketData:
            {
                TrackerMarketDataEvent *pMarketDataEvent = dynamic_cast<TrackerMarketDataEvent*>(pEvent);
                Instrument *pInstrument = pMarketDataEvent->GetInstrument();
                MarketData *pMarektData = pMarketDataEvent->GetMarketData();
                for(auto iPos = m_hTradeProcessors.begin() ; iPos != m_hTradeProcessors.end() ; iPos++)
                {
                    AccountTrackerTradeProcessor *pTradeProcessor = iPos.value();
                    AccountTrackerTradeData oTradeData = m_hTradeDatas.value(iPos.key());
                    if(pTradeProcessor->IsTracking(pOrder))
                    {
                        OrderOperation oOperation = pTradeProcessor->ProcessMarketData(pInstrument,pMarektData);
                        switch (oOperation.eOperation) {
                        case ootSubmit:
                            oTradeData.pOrderProcessor->Submit(oOperation.pOrder,this);
                            break;
                        case ootCancel:
                            oTradeData.pOrderProcessor->Cancel(oOperation.pOrder);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
                break;

            case tStartTrack:
            {
                TrackerOperationEvent *pOperationEvent = dynamic_cast<TrackerOperationEvent*>(pEvent);
                AccountTrackerTradeData oTradeData;
                AccountTrackerSetting *pTrackerSetting = pOperationEvent->GetTrackerSetting();
                Account *pTradeAccount = pTrackerSetting->GetTradeAccount();
                Account *pTrackAccount = pTrackerSetting->GetTrackAccount();
                oTradeData.pMarketDataSubscriber = AccountResourceManager::GetInstance()->GetMarketDataSubscriber(pTradeAccount);
                oTradeData.pOrderSubscriber = AccountResourceManager::GetInstance()->GetOrderSubscriber(pTrackAccount);
                oTradeData.pOrderProcessor = AccountResourceManager::GetInstance()->GetOrderProcessor(pTradeAccount);
                if(oTradeData.pMarketDataSubscriber == nullptr ||
                   oTradeData.pOrderProcessor == nullptr ||
                   oTradeData.pOrderSubscriber == nullptr )
                {

                }

                AccountTrackerTradeProcessor *pTradeProcessor = new AccountTrackerTradeProcessor(pTrackerSetting);
                m_hTradeProcessors.insert(pTrackerSetting,pTradeProcessor);
                m_hTradeDatas.insert(pTrackerSetting,oTradeData);
                QList<Instrument*> lInstruments;
                lInstruments.append(pTrackerSetting->GetInstrument());
                oTradeData.pMarketDataSubscriber->Subscribe(this,lInstruments);
                oTradeData.pOrderSubscriber->Subscribe(pTrackerSetting->GetInstrument(),this);
            }
                break;
            case tStopTrack:
            {
                TrackerOperationEvent *pOperationEvent = dynamic_cast<TrackerOperationEvent*>(pEvent);
                AccountTrackerSetting *pTrackerSetting = pOperationEvent->GetTrackerSetting();
                AccountTrackerTradeData oTradeData = m_hTradeDatas[pTrackerSetting];
                AccountTrackerTradeProcessor *pTradeProcessor = m_hTradeProcessors[pTrackerSetting];
                m_hTradeProcessors.remove(pTrackerSetting);
                m_hTradeDatas.remove(pTrackerSetting);
            }
                break;
            default:
                break;
            }
            delete pEvent;
        }
    }
}


void AccountTrackerEventProcessor::Stop()
{
    m_bStop = true;
    m_cWaitCondition.wakeOne();
}
