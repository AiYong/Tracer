#include "AccountResourceManager.h"
#include "Broker.h"
#include "PlatformFactory.h"

AccountResourceManager* AccountResourceManager::GetInstance()
{
    static AccountResourceManager oInstance;
    return &oInstance;
}

std::shared_ptr<AccountInfo> AccountResourceManager::GetAccountInfo(Account const* pAccount)
{
    std::shared_ptr<AccountInfo> pResult;
    Platform *pPlatform = nullptr;
    if(!m_hPlatfroms.contains(pAccount->GetBroker()->GetPlatform()))
    {
        pPlatform = PlatformFactory::Create(pAccount->GetBroker()->GetPlatform());
        m_hPlatfroms.insert(pAccount->GetBroker()->GetPlatform(),pPlatform);
    }
    else
    {
        pPlatform = m_hPlatfroms[pAccount->GetBroker()->GetPlatform()];
    }
    if(pPlatform)
    {
        pResult = pPlatform->QueryAccountInfo(pAccount);
    }
    return pResult;
}


std::shared_ptr<OrderProcessor> AccountResourceManager::GetOrderProcessor(Account const* pAccount)
{ 
    if(m_hOrderProcessor.contains(pAccount->GetID()))
    {
        return m_hOrderProcessor[pAccount->GetID()];
    }
    std::shared_ptr<OrderProcessor> pResult;
    Platform *pPlatform = nullptr;
    if(!m_hPlatfroms.contains(pAccount->GetBroker()->GetPlatform()))
    {
        pPlatform = PlatformFactory::Create(pAccount->GetBroker()->GetPlatform());
        m_hPlatfroms.insert(pAccount->GetBroker()->GetPlatform(),pPlatform);
    }
    else
    {
        pPlatform = m_hPlatfroms[pAccount->GetBroker()->GetPlatform()];
    }
    if(pPlatform)
    {
        pResult = pPlatform->GetOrderProcessor(pAccount);
        if(pResult != nullptr)
        {
            m_hOrderProcessor.insert(pAccount->GetID(),pResult);
        }
    }
    return pResult;
}

std::shared_ptr<MarketDataSubscriber> AccountResourceManager::GetMarketDataSubscriber(Account const* pAccount)
{
    if(m_hMarketDaraSubscriber.contains(pAccount->GetID()))
    {
        return m_hMarketDaraSubscriber[pAccount->GetID()];
    }
    std::shared_ptr<MarketDataSubscriber> pResult;
    Platform *pPlatform = nullptr;
    if(!m_hPlatfroms.contains(pAccount->GetBroker()->GetPlatform()))
    {
        pPlatform = PlatformFactory::Create(pAccount->GetBroker()->GetPlatform());
        m_hPlatfroms.insert(pAccount->GetBroker()->GetPlatform(),pPlatform);
    }
    else
    {
        pPlatform = m_hPlatfroms[pAccount->GetBroker()->GetPlatform()];
    }
    if(pPlatform)
    {
        pResult = pPlatform->GetMarketDataSubscriber(pAccount);
        if(pResult != nullptr)
        {
            m_hMarketDaraSubscriber.insert(pAccount->GetID(),pResult);
        }
    }
    return pResult;
}

shared_ptr<OrderSubscriber> AccountResourceManager::GetOrderSubscriber(Account const* pAccount)
{
    if(m_hOrderSubscriber.contains(pAccount->GetID()))
    {
        return m_hOrderSubscriber[pAccount->GetID()];
    }
    std::shared_ptr<OrderSubscriber> pResult;
    Platform *pPlatform = nullptr;
    if(!m_hPlatfroms.contains(pAccount->GetBroker()->GetPlatform()))
    {
        pPlatform = PlatformFactory::Create(pAccount->GetBroker()->GetPlatform());
        m_hPlatfroms.insert(pAccount->GetBroker()->GetPlatform(),pPlatform);
    }
    else
    {
        pPlatform = m_hPlatfroms[pAccount->GetBroker()->GetPlatform()];
    }
    if(pPlatform)
    {
        pResult = pPlatform->GetOrderSubscriber(pAccount);
        if(pResult != nullptr)
        {
            m_hOrderSubscriber.insert(pAccount->GetID(),pResult);
        }
    }
    return pResult;
}

QString AccountResourceManager::GetLastError() const
{
    return "";
}
