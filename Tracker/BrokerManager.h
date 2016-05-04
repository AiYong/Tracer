#ifndef _TRACKER_BROKERMANAGER_H_
#define _TRACKER_BROKERMANAGER_H_

#include <QString>
#include <QList>
#include "Broker.h"


class BrokerManager
{
public:

    BrokerManager();

    ~BrokerManager();

public:

    static BrokerManager* GetInstance();

public:

    QList<Broker*> GetBrokers() const;

    Broker* GetBroker(QString const& strBrokerID) const;

    Broker* Create(QString const& strName,QString const& strID,
                   QStringList const& strTradeUrl,QStringList const&strMarketDataUrl);

    void Update(Broker *pBroker);

    void Remove(Broker *pBroker);

    void RemoveAll();

private:

    QList<Broker*> m_lBrokers;

};

#endif // _TRACKER_BROKERMANAGER_H_
