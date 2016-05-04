#include "OrderSubscriber.h"
#include <algorithm>
#include <QMutexLocker>


SubscriberProcessor::AddSubscriber(OrderListener *pOrderListener)
{
    QMutexLocker oLocker(m_lLock);
    if(!m_lListener.contains(pOrderListener))
    {
        m_lListener.append(pOrderListener);
    }
}

SubscriberProcessor::RemoveSubscriber(OrderListener *pOrderListener)
{
    QMutexLocker oLocker(m_lLock);
    if(m_lListener.contains(pOrderListener))
    {
        m_lListener.removeAll(pOrderListener);
    }
}

void SubscriberProcessor::PublishSubmit(Order *pOrder)
{
    QMutexLocker oLocker(m_lLock);
    std::for_each(m_lListener.begin(),m_lListener.end(),[&](OrderListener *pOrderListener){
        pOrderListener->OnSubmited(pOrder);
    });
}

void SubscriberProcessor::PublishOpen(Order *pOrder, Position *pPosition)
{
    QMutexLocker oLocker(m_lLock);
    std::for_each(m_lListener.begin(),m_lListener.end(),[&](OrderListener *pOrderListener){
        pOrderListener->OnOpen(pOrder,pPosition);
    });
}

void SubscriberProcessor::PublishClose(Order *pOrder, Transaction *pTransaction)
{
    QMutexLocker oLocker(m_lLock);
    std::for_each(m_lListener.begin(),m_lListener.end(),[&](OrderListener *pOrderListener){
        pOrderListener->OnClose(pOrder,pTransaction);
    });
}

void SubscriberProcessor::PublishCancelling(Order *pOrder)
{
    QMutexLocker oLocker(m_lLock);
    std::for_each(m_lListener.begin(),m_lListener.end(),[&](OrderListener *pOrderListener){
        pOrderListener->OnCancelling(pOrder);
    });
}

void SubscriberProcessor::PublishCancelled(Order *pOrder)
{
    QMutexLocker oLocker(m_lLock);
    std::for_each(m_lListener.begin(),m_lListener.end(),[&](OrderListener *pOrderListener){
        pOrderListener->OnCancelled(pOrder);
    });
}

void SubscriberProcessor::PublishError(Order *pOrder, OrderError eOrderError)
{
    QMutexLocker oLocker(m_lLock);
    std::for_each(m_lListener.begin(),m_lListener.end(),[&](OrderListener *pOrderListener){
        pOrderListener->OnError(pOrder,eOrderError);
    });
}

OrderSubscriber::OrderSubscriber(Account *pAccount)
    :m_pAccount(pAccount)
{
    Init(pAccount->GetInstruments().values());
}

OrderSubscriber::~OrderSubscriber()
{

}

void OrderSubscriber::Subscribe(Instrument *pInstrument, OrderListener *pOrderListener)
{
    SubscriberProcessor *pProcessor = m_hProcessor[pInstrument->GetID()];
    pProcessor->AddSubscriber(pOrderListener);
}

void OrderSubscriber::UnSubscribe(Instrument *pInstrument, OrderListener *pOrderListener)
{
    SubscriberProcessor *pProcessor = m_hProcessor[pInstrument->GetID()];
    pProcessor->RemoveSubscriber(pOrderListener);
}

void OrderSubscriber::Init(QList<Instrument*> const& lInstrument)
{
    std::for_each(lInstrument.begin(),lInstrument.end(),[&](Instrument const* pInstrument){
       SubscriberProcessor *pProcessor = new SubscriberProcessor();
       m_hProcessor.insert(pInstrument->GetID(),pProcessor);
    });
}
