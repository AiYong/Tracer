#include "Platform.h"

AccountInfo::AccountInfo(double dAvailableMargin, const QList<Instrument *> &lInstrument, const QMap<QString, PositionCost *> &hPositionCost)
    :m_dAvailableMargin(dAvailableMargin),m_lInstrument(lInstrument),m_hPositionCost(hPositionCost)
{

}

AccountInfo::~AccountInfo()
{

}

double AccountInfo::GetAvailableMargin() const
{
    return m_dAvailableMargin;
}

QList<Instrument*> const& AccountInfo::GetInstruments() const
{
    return m_lInstrument;
}

QMap<QString,PositionCost*> const& AccountInfo::GetPositionCost() const
{
    return m_hPositionCost;
}

Platform::Platform()
{

}

Platform::~Platform()
{

}

shared_ptr<OrderProcessor> Platform::GetOrderProcessor(Account const*pAccount,bool bCreateIfNotExist)
{
   shared_ptr<OrderProcessor> pResult;
   if(m_mOrderProcessor.contains(pAccount->GetName()))
   {
       pResult = m_mOrderProcessor[pAccount->GetName()];
   }
   if(pResult == nullptr && bCreateIfNotExist)
   {
       pResult = CreateOrderProcessor(pAccount);
       m_mOrderProcessor.insert(pAccount->GetID(),pResult);
   }
   return pResult;
}

shared_ptr<OrderSubscriber> Platform::GetOrderSubscriber(Account const*pAccount,bool bCreateIfNotExist)
{
    shared_ptr<OrderSubscriber> pResult;
    if(m_mOrderSubscriber.contains(pAccount->GetID()))
    {
        pResult = m_mOrderSubscriber[pAccount->GetID()];
    }
    if(pResult == nullptr && bCreateIfNotExist)
    {
        pResult = CreateOrderSubsriber(pAccount);
        m_mOrderSubscriber.insert(pAccount->GetID(),pResult);
    }
    return pResult;
}

shared_ptr<MarketDataSubscriber> Platform::GetMarketDataSubscriber(Account const*pAccount,bool bCreateIfNotExist)
{
    shared_ptr<MarketDataSubscriber> pResult;
    if(m_mMarketDataSubscriber.contains(pAccount->GetID()))
    {
        pResult = m_mMarketDataSubscriber[pAccount->GetID()];
    }
    if(pResult == nullptr && bCreateIfNotExist)
    {
        pResult = CreateMarketDataSubscriber(pAccount);
        m_mMarketDataSubscriber.insert(pAccount->GetID(),pResult);
    }
    return pResult;
}


QString Platform::GetLastError() const
{
    return m_strError;
}
