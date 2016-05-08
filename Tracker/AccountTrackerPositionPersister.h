#ifndef _TRACKER_ACCOUNTTRACKERPOSITIONPERSISTER_H_
#define _TRACKER_ACCOUNTTRACKERPOSITIONPERSISTER_H_

#include "Account.h"
#include "ObjectPersister.h"
#include "DatabaseManager.h"
#include "AccountTrackerPosition.h"
#include "AccountTrackerSetting.h"

template<typename T>
class AccountTrackerPositionAccessor
{
public:

    void Load(T const*pDep,QList<AccountTrackerPosition*> &lPositions)
    {

    }

    void Remove(T const*pDep)
    {

    }
};


template<>
class AccountTrackerPositionAccessor<AccountTrackerSetting>
{
public:

    void Load(AccountTrackerSetting const*pSetting,QList<AccountTrackerPosition*> &lPositions)
    {
        QString strQuery = "SELECT * FROM ACCOUNT_TRACKER_POSITION WHERE ACCOUNT_TRACKER_SETTING_ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            oQuery.addBindValue(0,pSetting->GetID());
            if(oQuery.exec())
            {
                while(oQuery.next())
                {
                    double dPrice = oQuery.value("PRICE").toDouble();
                    size_t nQuantity = oQuery.value("QUANTITY").toUInt();
                    QDate oTradeDay = oQuery.value("TRADE_DAY").toDate();
                    QString strInstrumentID = oQuery.value("INSTRUMENT_ID").toString();
                    Direction eDirection = (Direction)(oQuery.value("DIRECTION").toInt());
                    HedgeFlag eHedgeFlag = (HedgeFlag)(oQuery.value("HEDGE_FLAG").toInt());
                    Instrument *pInstrument = pSetting->GetTradeAccount()->GetInstrument(strInstrumentID);
                    AccountTrackerPosition *pPosition = new AccountTrackerPosition(dPrice,nQuantity,oTradeDay,pInstrument,eDirection,eHedgeFlag);
                    lPositions.append(pPosition);
                }
            }
        }
    }

    void Remove(AccountTrackerSetting const*pSetting)
    {

    }
};

template<>
class ObjectPersister<AccountTrackerPosition>
{
public:

    template<typename D>
    void Load(D *pDep,QList<AccountTrackerPosition*> &lObjs)
    {
        AccountTrackerPositionAccessor<D> oAccessor;
        oAccessor.Load(pDep,lObjs);
    }

    void Save(QList<AccountTrackerPosition*> const&lObjs)
    {

    }

    void Save(AccountTrackerPosition const* pObj)
    {
        QString strQuery = "INSERT INTO ACCOUNT_TRACKER_POSITION (?,?,?,?,?,?)";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            oQuery.bindValue(0,pObj->GetPrice());
            oQuery.bindValue(1,pObj->GetQuantity());
            oQuery.bindValue(2,pObj->GetTradeDay());
            oQuery.bindValue(3,pObj->GetInstrument()->GetID());
            oQuery.bindValue(4,(int)(pObj->GetDirection()));
            oQuery.bindValue(5,(int)(pObj->GetHedgeFlag()));
            dbConn.transaction();
            oQuery.exec();
            dbConn.commit();
            pObj->SetID(oQuery.lastInsertId().toInt());
        }
    }

    void Update(QList<AccountTrackerPosition*> const& lOjbs)
    {

    }

    void Update(AccountTrackerPosition const* pObj)
    {
        QString strQuery = "UPDATE ACCOUNT_TRACKER_POSITION SET QUANTITY = ? WHERE ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            oQuery.bindValue(0,pObj->GetQuantity());
            oQuery.bindValue(1,pObj->GetID());
            dbConn.transaction();
            oQuery.exec();
            dbConn.commit();
        }
    }

    void Remove(QList<AccountTrackerPosition*> const& lObjs)
    {

    }

    void Remove(AccountTrackerPosition const* pObj)
    {
        QString strQuery = "DELETE FROM ACCOUNT_TRACKER_POSITIN WHERE ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,pObj->GetID());
            dbConn.commit();
        }
    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {

    }
};

#endif // _TRACKER_ACCOUNTTRACKERPOSITIONPERSISTER_H_
