#ifndef _TRACKER_ACCOUNTPERSISTER_H_
#define _TRACKER_ACCOUNTPERSISTER_H_


#include "Order.h"
#include "Account.h"
#include "ObjectPersister.h"
#include "DatabaseManager.h"
#include "BrokerManager.h"

template<>
class ObjectPersister<Account>
{
public:

    template<typename D>
    void Load(D *pDep,QList<Account*> &lObjs)
    {
        QString strQuery = "SELECT * FROM ACCOUNT";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.exec(strQuery))
        {
            while(oQuery.next())
            {
                QString strID = oQuery.value("ID").toString();
                QString strName = oQuery.value("NAME").toString();
                QString strBrokerID = oQuery.value("BROKER_ID").toString();
                QString strPassword = oQuery.value("PASSWORD").toString();
                Broker *pBroker = BrokerManager::GetInstance()->GetBroker(strBrokerID);
                Account *pAccount = new Account(strID,strName,strPassword,pBroker);
                lObjs.append(pAccount);
            }
        }
    }

    void Save(QList<Account*> const&lObjs)
    {

    }

    void Save(Account const* pObj)
    {
        QString strQuery = "INSERT INTO ACCOUNT VALUES(?,?,?,?)";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,pObj->GetID());
            oQuery.bindValue(1,pObj->GetName());
            oQuery.bindValue(2,pObj->GetPassword());
            oQuery.bindValue(3,pObj->GetBroker()->GetId());
            oQuery.exec();
            dbConn.commit();
        }
    }

    void Update(QList<Account*> const& lOjbs)
    {

    }

    void Update(Account const* pObj)
    {
        QString strQuery = "UPDATE ACCOUNT SET NAME = ?,PASSWORD = ?,BROKER_ID = ? WHERE ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        dbConn.transaction();
        oQuery.prepare(strQuery);
        oQuery.bindValue(0,pObj->GetName());
        oQuery.bindValue(1,pObj->GetPassword());
        oQuery.bindValue(2,pObj->GetBroker()->GetId());
        oQuery.bindValue(3,pObj->GetID());
        oQuery.exec();
        dbConn.commit();
    }

    void Remove(QList<Account*> const& lObjs)
    {

    }

    void Remove(Account const* pObjs)
    {
        QString strQuery = "DELETE FROM ACCOUNT WHERE ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        oQuery.prepare(strQuery);
        dbConn.transaction();
        oQuery.bindValue(0,pObjs->GetID());
        oQuery.exec();
        dbConn.commit();
    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {

    }
};

#endif // _TRACKER_ACCOUNTPERSISTER_H_
