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
        QString strQuery = QString::fromLocal8Bit("SELECT * FROM BROKER");
        QSqlDatabase oConnection = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.exec(strQuery))
        {
			QString strError = oQuery.lastError().databaseText();
			bool bActive = oQuery.isActive();
			bool bSelect = oQuery.isSelect();
			//oQuery.first();
			bool bValid = oQuery.isValid();
			int nCount = oQuery.size();
			//if (oQuery.size() > 0)
			{
				while (oQuery.next())
				{
					QString strID = oQuery.value("ID").toString();
					QString strName = oQuery.value("NAME").toString();
					QString strTradeUrls = oQuery.value("TRADE_URLS").toString();
					QString strMarketDataUrls = oQuery.value("MARKETDATA_URLS").toString();
					QString strPlatform = oQuery.value("PLATFORM").toString();
					Broker *pBroker = new Broker(strID, strName, strTradeUrls.split("|"), strMarketDataUrls.split("|"), strPlatform);
					lObjs.append(pBroker);
				}
			}
        }
    }

    void Save(QList<Broker*> const&lObjs)
    {
        QString strQuery = "INSERT INTO BROKER VALUES(?,?,?,?,?)";
        QSqlDatabase oConnection = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            QVariantList lIDs;
            QVariantList lNames;
            QVariantList lMarketDataUrls;
            QVariantList lTradeUrls;
            QVariantList lPlatforms;
            for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
            {
                Broker* pBroker = lObjs[nCount];
                lIDs << pBroker->GetId();
                lNames<< pBroker->GetName();
                lMarketDataUrls<< pBroker->GetMarketDataUrl().join("|");
                lTradeUrls << pBroker->GetTradeUrl().join("|");
                lPlatforms << pBroker->GetPlatform();
            }
            oQuery.addBindValue(lIDs);
            oQuery.addBindValue(lNames);
            oQuery.addBindValue(lMarketDataUrls);
            oQuery.addBindValue(lTradeUrls);
            oQuery.addBindValue(lPlatforms);
            oConnection.transaction();
            oQuery.execBatch();
            oConnection.commit();
        }
    }

    void Save(Broker const* pBroker)
    {
        QString strQuery = "INSERT INTO BROKER VALUES(?,?,?,?,?)";
        QSqlDatabase oConnection = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            oQuery.bindValue(0,pBroker->GetId());
            oQuery.bindValue(1,pBroker->GetName());
            oQuery.bindValue(2,pBroker->GetTradeUrl().join("|"));
            oQuery.bindValue(3,pBroker->GetMarketDataUrl().join("|"));
            oQuery.bindValue(4,pBroker->GetPlatform());
            oConnection.transaction();
			bool b = oQuery.exec();
            oConnection.commit();
        }
    }

    void Update(QList<Broker*> const& lObjs)
    {
        QString strQuery = "UPDATE BROKER SET NAME = ?,MARKETDATA_URLS = ?,TRADE_URLS = ? ,PLATFORM = ? WHERE ID = ?";
        QSqlDatabase oConnection = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            QVariantList lIDs;
            QVariantList lNames;
            QVariantList lMarketDataUrls;
            QVariantList lTradeUrls;
             QVariantList lPlatforms;
            for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
            {
                Broker* pBroker = lObjs[nCount];
                lIDs << pBroker->GetId();
                lNames<< pBroker->GetName();
                lMarketDataUrls<< pBroker->GetMarketDataUrl().join("|");
                lTradeUrls << pBroker->GetTradeUrl().join("|");
                lPlatforms << pBroker->GetPlatform();
            }
            oQuery.addBindValue(lNames);
            oQuery.addBindValue(lMarketDataUrls);
            oQuery.addBindValue(lTradeUrls);
            oQuery.addBindValue(lPlatforms);
            oQuery.addBindValue(lIDs);
            oConnection.transaction();
            oQuery.execBatch();
            oConnection.commit();
        }
    }

    void Update(Broker const* pBroker)
    {
        QString strQuery = "UPDATE BROKER SET NAME = ?,MARKETDATA_URLS = ?,TRADE_URLS = ? ,PLATFORM = ? WHERE ID = ?";
        QSqlDatabase oConnection = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            oQuery.bindValue(0,pBroker->GetName());
            oQuery.bindValue(1,pBroker->GetTradeUrl().join("|"));
            oQuery.bindValue(2,pBroker->GetMarketDataUrl().join("|"));
            oQuery.bindValue(3,pBroker->GetPlatform());
            oQuery.bindValue(4,pBroker->GetId());
            oConnection.transaction();
            oQuery.exec();
            oConnection.commit();
        }
    }

    void Remove(QList<Broker*> const& lObjs)
    {
        QString strQuery = "DELETE FROM BROKER WHERE ID = ?";
        QSqlDatabase oConnection = DatabaseManager::GetInstance()->GetDatabase();
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
            oConnection.transaction();
            oQuery.execBatch();
            oConnection.commit();
        }
    }

    void Remove(Broker const* pBroker)
    {
        QString strQuery = "DELETE FROM BROKER WHERE ID = ?";
        QSqlDatabase oConnection = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(oConnection);
        if(oQuery.prepare(strQuery))
        {
            oQuery.bindValue(0,pBroker->GetId());
			oConnection.transaction();
            oQuery.exec();
            oConnection.commit();
        }
    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {
    }
};

#endif // _TRACKER_BROKERPERSISTER_H_
