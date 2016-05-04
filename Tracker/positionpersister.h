#ifndef _TRACKER_POSITIONPERSISTER_H_
#define _TRACKER_POSITIONPERSISTER_H_

#include "Account.h"
#include "Position.h"
#include "Instrument.h"
#include "ObjectPersister.h"
#include "DatabaseManager.h"

template<typename T>
class PositionAccessor
{
public:

    void Load(T const* pDep,QList<Position*> &lPositions)
    {

    }

    void Remove(T const* pDep)
    {

    }
};

template<>
class PositionAccessor<Account>
{
public:

    void Load(Account const* pAccount,QList<Position*> &lPositions)
    {
        QString strQuery = "SELECT * FROM POSITION WHERE ACCOUNT_ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        oQuery.prepare(strQuery);
        oQuery.bindValue(0,pAccount->GetId());
        if(oQuery.exec(strQuery))
        {
            while(oQuery.next())
            {
                QString strID = oQuery.value("ID").toString();
                QString strInstrumentID = oQuery.value("INSTRUMENT_ID").toString();
                size_t nQuantity = oQuery.value("QUANTITY").toUInt();
                double dPrice = oQuery.value("PRICE").toDouble();
                Direction eDirection = (Direction)(oQuery.value("DIRECTION").toInt());
                HedgeFlag eHedgeFlag = (HedgeFlag)(oQuery.value("HEDGE_FLAG").toInt());
                QDateTime oTimestamp = oQuery.value("TIMESTAMP").toDateTime();
                Instrument *pInstrument = pAccount->GetInstrument(strInstrumentID);
                PositionCost *pPositinCost = pAccount->GetPositionCost(pInstrument);
                Position *pPosition = new Position(strID,pAccount,pInstrument,pPositinCost,
                                                   oTimestamp,eDirection,eHedgeFlag,nQuantity,dPrice);
                lPositions.append(pPosition);
            }
        }
    }

    void Remove(Account const* pAccount)
    {
        QString strQuery = "DELETE FROM POSITION WHERE ACCOUNT_ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        dbConn.transaction();
        oQuery.prepare(strQuery);
        oQuery.bindValue(0,pAccount->GetId());
        oQuery.exec();
        dbConn.commit();
    }
};

template<>
class ObjectPersister<Position>
{
public:

    template<typename D>
    void Load(D *pDep,QList<Position*> &lObjs)
    {
        PositionAccessor<D> oAccessor;
        oAccessor.Load(pDep,lObjs);
    }

    void Save(QList<Position*> const&lObjs)
    {

    }

    void Save(Position const* pObj)
    {
        QString strQuery = "INSERT INTO POSITION VALUES(?,?,?,?,?,?,?,?)";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,pObj->GetID());
            oQuery.bindValue(1,pObj->GetAccount()->GetId());
            oQuery.bindValue(2,pObj->GetInstrument()->GetID());
            oQuery.bindValue(3,pObj->GetQuantity());
            oQuery.bindValue(4,pObj->GetPrice());
            oQuery.bindValue(5,(int)(pObj->GetDirection()));
            oQuery.bindValue(6,(int)(pObj->GetHedgeFlag()));
            oQuery.bindValue(7,pObj->GetTimestamp());
            oQuery.exec();
            dbConn.commit();
        }
    }

    void Update(QList<Position*> const& lOjbs)
    {

    }

    void Update(Position const* pObj)
    {
        QString strQuery = "UPDATE POSITION SET QUANTITY = ? WHERE ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,pObj->GetID());
            oQuery.bindValue(1,pObj->GetQuantity());
            oQuery.exec();
            dbConn.commit();
        }
    }

    void Remove(QList<Position*> const& lObjs)
    {

    }

    void Remove(Position const* pObjs)
    {
        QString strQuery = "DELETE FROM POSITION WHERE ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,pObj->GetID());
            oQuery.exec();
            dbConn.commit();
        }
    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {
        PositionAccessor<D> oAccessor;
        oAccessor.Remove(pDep);
    }
};

#endif // TRACKER_POSITIONPERSISTER_H_
