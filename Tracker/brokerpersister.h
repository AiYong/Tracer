#ifndef _TRACKER_BROKERPERSISTER_H_
#define _TRACKER_BROKERPERSISTER_H_

#include "Broker.h"
#include "ObjectPersister.h"
#include "DatabaseManager.h"
template<>
class ObjectPersister<Broker>
{
public:

    template<typename D>
    void Load(D *pDep,QList<Broker*> &lObjs)
    {
        QString strQuery = "SELECT * FROM BROKER";
        QSqlDatabase oConnection = DatabaseManager::GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.exec(strQuery))
        {
            while(oQuery.next());
            {
                QString strID = oQuery.value("ID").toString();
                QString strName = oQuery.value("NAME").toString();
                QString strTradeUrls = oQuery.value("TRADE_URLS").toString();
                QString strMarketDataUrls = oQuery.value("MARKETDATA_URLS").toString();
                Broker *pBroker = new Broker(strID,strName,strTradeUrls.split("|"),strMarketDataUrls.split("|"));
                lObjs.append(pBroker);
            }
        }
    }

    void Save(QList<Broker*> const&lObjs)
    {
        QString strQuery = "INSERT INTO BROKER VALUES(?,?,?,?)";
        QSqlDatabase oConnection = DatabaseManager::GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            QVariantList lIDs;
            QVariantList lNames;
            QVariantList lMarketDataUrls;
            QVariantList lTradeUrls;
            for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
            {
                Broker* pBroker = lObjs[nCount];
                lIDs << pBroker->GetId();
                lNames<< pBroker->GetName();
                lMarketDataUrls<< pBroker->GetMarketDataUrl().join("|");
                lTradeUrls << pBroker->GetTradeUrl().join("|");
            }
            oQuery.addBindValue(lIDs);
            oQuery.addBindValue(lNames);
            oQuery.addBindValue(lMarketDataUrls);
            oQuery.addBindValue(lTradeUrls);
            oQuery.execBatch();
        }
    }

    void Save(Broker const* pBroker)
    {
        QString strQuery = "INSERT INTO BROKER VALUES(?,?,?,?)";
        QSqlDatabase oConnection = DatabaseManager::GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            oQuery.bindValue(0,pBroker->GetId());
            oQuery.bindValue(1,pBroker->GetName());
            oQuery.bindValue(2,pBroker->GetTradeUrl().join("|"));
            oQuery.bindValue(3,pBroker->GetMarketDataUrl().join("|"));
            oQuery.exec();
        }
    }

    void Update(QList<Broker*> const& lObjs)
    {
        QString strQuery = "UPDATE BROKER SET NAME = ?,MARKETDATA_URLS = ?,TRADE_URLS = ? WHERE ID = ?";
        QSqlDatabase oConnection = DatabaseManager::GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            QVariantList lIDs;
            QVariantList lNames;
            QVariantList lMarketDataUrls;
            QVariantList lTradeUrls;
            for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
            {
                Broker* pBroker = lObjs[nCount];
                lIDs << pBroker->GetId();
                lNames<< pBroker->GetName();
                lMarketDataUrls<< pBroker->GetMarketDataUrl().join("|");
                lTradeUrls << pBroker->GetTradeUrl().join("|");
            }
            oQuery.addBindValue(lNames);
            oQuery.addBindValue(lMarketDataUrls);
            oQuery.addBindValue(lTradeUrls);
            oQuery.addBindValue(lIDs);
            oQuery.execBatch();
        }
    }

    void Update(Broker const* pBroker)
    {
        QString strQuery = "UPDATE BROKER SET NAME = ?,MARKETDATA_URLS = ?,TRADE_URLS = ? WHERE ID = ?";
        QSqlDatabase oConnection = DatabaseManager::GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            oQuery.bindValue(0,pBroker->GetName());
            oQuery.bindValue(1,pBroker->GetTradeUrl().join("|"));
            oQuery.bindValue(2,pBroker->GetMarketDataUrl().join("|"));
            oQuery.bindValue(3,pBroker->GetId());
            oQuery.exec();
        }
    }

    void Remove(QList<Broker*> const& lObjs)
    {
        QString strQuery = "DELETE FROM BROKER WHERE ID = ?";
        QSqlDatabase oConnection = DatabaseManager::GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            QVariantList lIDs;
            for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
            {
               Broker* pBroker = lObjs[nCount];
               lIDs << pBroker->GetId();
            }
            oQuery.addBindValue(lIDs);
            oQuery.execBatch();
        }
    }

    void Remove(Broker const* pBroker)
    {
        QString strQuery = "DELETE FROM BROKER WHERE ID = ?";
        QSqlDatabase oConnection = DatabaseManager::GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            oQuery.bindValue(0,pBroker->GetId());
            oQuery.exec();
        }
    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {
    }
};

#endif // _TRACKER_BROKERPERSISTER_H_
