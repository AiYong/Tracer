#include "BrokerManager.h"
#include "ObjectPersistManager.h"
#include "BrokerPersister.h"

BrokerManager* BrokerManager::GetInstance()
{
    static BrokerManager oInstance;
    return &oInstance;
}

BrokerManager::BrokerManager()
{
    ObjectPersistManager::GetInstance()->Load(this,m_lBrokers);
}

BrokerManager::~BrokerManager()
{
    for(int nCount = 0 ; nCount < m_lBrokers.size() ; nCount++)
    {
        Broker *pBroker = m_lBrokers[nCount];
        delete pBroker;
    }
}

QList<Broker*> BrokerManager::GetBrokers() const
{
    return m_lBrokers;
}

Broker* BrokerManager::GetBroker(QString const& strBrokerID) const
{
	for(int nCount = 0 ; nCount < m_lBrokers.size() ; nCount++)
	{
		Broker *pBroker = m_lBrokers[nCount];
		if(pBroker->GetId() == strBrokerID)
		{
			return pBroker;
		}
	}
	return nullptr;
}

Broker* BrokerManager::Create(QString const& strName,QString const& strID,
                              QStringList const& lTradeUrl,
                              QStringList const& lMarketDataUrl,
                              QString const& strPlatform)
{
    Broker *pBroker = new Broker(strID,strName,lTradeUrl,lMarketDataUrl,strPlatform);
    m_lBrokers.append(pBroker);
    ObjectPersistManager::GetInstance()->Save(pBroker);
    return pBroker;
}

void BrokerManager::Update(Broker *pBroker)
{
    ObjectPersistManager::GetInstance()->Update(pBroker);
}

void BrokerManager::Remove(Broker *pBroker)
{
    ObjectPersistManager::GetInstance()->Remove(pBroker);
	m_lBrokers.removeOne(pBroker);
	delete pBroker;
}

void BrokerManager::RemoveAll()
{
    ObjectPersistManager::GetInstance()->RemoveAll(this);
}
