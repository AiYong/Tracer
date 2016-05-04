#ifndef _TRACKER_POSITIONCOSTPERSISTER_H_
#define _TRACKER_POSITIONCOSTPERSISTER_H_

#include "Account.h"
#include "Instrument.h"
#include "PositionCost.h"
#include "ObjectPersister.h"

template<typename T>
class PositionCostAccessor
{
public:

    void Load(T const* pDep,QList<PositionCost*> &lObjs)
    {

    }

    void Remove(T const* pDep)
    {

    }
};

template<>
class PositionCostAccessor<Account>
{
public:

    void Load(Account const* pAccount,QList<PositionCost*> &lPositionCosts)
    {
        QString strQuery = "SELECT * FROM POSITION_COST WHERE ACCOUNT_ID = ?" ;
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        oQuery.prepare(strQuery);
        oQuery.bindValue(0,pAccount->GetId());
        if(oQuery.exec())
        {
            while(oQuery.next())
            {
                QString strInstrumentName = oQuery.value("INSTRUMENT_ID").toString();
                CommissionMode eCommissitionMode = (CommissionMode)(oQuery.value("COMMISSION_MODE").toInt());
                MarginMode eMarginMode = (MarginMode)(oQuery.value("MARGIN_MODE").toInt());
                double dLongOpenCommission = oQuery.value("LONG_OPEN_COMMISSION").toDouble();
                double dShortOpenCommission = oQuery.value("SHORT_OPEN_COMMISSION").toDouble();
                double dLongCloseCommission = oQuery.value("LONG_CLOSE_COMMISSION").toDouble();
                double dShortCloseCommission = oQuery.value("SHORT_CLOSE_COMMISSION").toDouble();
                double dLongMargin = oQuery.value("LONG_MARGIN").toDouble();
                double dShortMargin = oQuery.value("SHORT_MARGIN").toDouble();
                Instrument *pInstrument = pAccount->GetInstrument(strInstrument);
                PositionCost *pPositionCost = new PositionCost(pAccount,pInstrument,eCommissitionMode,dLongOpenCommission,
                                                               dShortOpenCommission,dLongCloseCommission,dShortCloseCommission,
                                                               eMarginMode,dLongMargin,dShortMargin);
                lPositionCosts.append(pPositionCost);
            };
        }
    }

    void Remove(Account const* pAccount)
    {
        QString strQuery = "DELETE FROM POSITION_COST WHERE ACCOUNT_ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        dbConn.transaction();
        QSqlQuery oQuery(dbConn);
        oQuery.prepare(strQuery);
        oQuery.bindValue(0,pAccount->GetId());
        oQuery.exec();
        dbConn.commit();
    }
};

template<>
class ObjectPersister<PositionCost>
{
public:

    template<typename D>
    void Load(D *pDep,QList<PositionCost*> &lObjs)
    {
        PositionCostAccessor<D> oAccessor;
        oAccessor.Load(pDep,lObjs);
    }

    void Save(QList<PositionCost*> const&lObjs)
    {
        QString strQuery = "INSERT INOT POSITION_COST VALUES(?,?,?,?,?,?,?,?,?,?)";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
           dbConn.transaction();
           QVariantList lAccountIDs;
           QVariantList lNames;
           QVariantList lCommissionModes;
           QVariantList lMarginModes;
           QVariantList lLongOpenCommissions;
           QVariantList lShortOpenCommissions;
           QVariantList lLongCloseCommissions;
           QVariantList lShortCloseCommissions;
           QVariantList lLongMargins;
           QVariantList lShortMargins;
           for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
           {
               PositionCost *pPositionCost = lObjs[nCount];
               lAccountIDs << pPositionCost->GetAccount()->GetId();
               lNames << pPositionCost->GetInstrument()->GetName();
               lCommissionModes << (int)(pPositionCost->GetCommissionMode());
               lMarginModes << (int)(pPositionCost->GetMarginMode());
               lLongOpenCommissions << pPositionCost->GetLongOpenCommission();
               lShortOpenCommissions << pPositionCost->GetShortOpenCommission();
               lLongCloseCommissions << pPositionCost->GetLongCloseCommission();
               lShortCloseCommissions << pPositionCost->GetShortCloseCommission();
               lLongMargins << pPositionCost->GetLongMargin();
               lShortMargins << pPositionCost->GetShortMargin();
           }
           oQuery.addBindValue(lAccountIDs);
           oQuery.addBindValue(lNames);
           oQuery.addBindValue(lCommissionModes);
           oQuery.addBindValue(lMarginModes);
           oQuery.addBindValue(lLongOpenCommissions);
           oQuery.addBindValue(lShortOpenCommissions);
           oQuery.addBindValue(lLongCloseCommissions);
           oQuery.addBindValue(lShortCloseCommissions);
           oQuery.addBindValue(lLongMargins);
           oQuery.addBindValue(lShortMargins);
           oQuery.execBatch();
           dbConn.commit();
        }

    }

    void Save(PositionCost const* pObj)
    {
        QString strQuery = "INSERT INOT POSITION_COST VALUES(?,?,?,?,?,?,?,?,?,?)";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,pObj->GetAccount()->GetId());
            oQuery.bindValue(1,pObj->GetInstrument()->GetName());
            oQuery.bindValue(2,(int)(pObj->GetCommissionMode()));
            oQuery.bindValue(3,(int)(pObj->GetMarginMode()));
            oQuery.bindValue(4,pObj->GetLongOpenCommission());
            oQuery.bindValue(5,pObj->GetShortOpenCommission());
            oQuery.bindValue(6,pObj->GetLongCloseCommission());
            oQuery.bindValue(7,pObj->GetShortCloseCommission());
            oQuery.bindValue(8,pObj->GetLongMargin());
            oQuery.bindValue(9,pObj->GetShortMargin());
            oQuery.exec();
            dbConn.commit();
        }
    }

    void Update(QList<PositionCost*> const& lOjbs)
    {
        QString strQuery = "UPDATE POSITION_COST SET COMMISSION = ? ,"
                           "MARGIN_MODE = ? ,LONG_OPEN_COMMISSION = ?, "
                           "SHORT_OPEN_COMMISSION = ? ,LONG_CLOSE_COMMISSION = ? ,"
                           "SHORT_CLOSE_COMMISSION = ?, LONG_MARGIN = ?, SHORT_MARGIN = ?,"
                           "WHERE ACCOUNT_ID = ? AND INSTRUMENT_NAME = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            QVariantList lAccountIDs;
            QVariantList lNames;
            QVariantList lCommissionModes;
            QVariantList lMarginModes;
            QVariantList lLongOpenCommissions;
            QVariantList lShortOpenCommissions;
            QVariantList lLongCloseCommissions;
            QVariantList lShortCloseCommissions;
            QVariantList lLongMargins;
            QVariantList lShortMargins;
            for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
            {
                PositionCost *pPositionCost = lObjs[nCount];
                lAccountIDs << pPositionCost->GetAccount()->GetId();
                lNames << pPositionCost->GetInstrument()->GetName();
                lCommissionModes << (int)(pPositionCost->GetCommissionMode());
                lMarginModes << (int)(pPositionCost->GetMarginMode());
                lLongOpenCommissions << pPositionCost->GetLongOpenCommission();
                lShortOpenCommissions << pPositionCost->GetShortOpenCommission();
                lLongCloseCommissions << pPositionCost->GetLongCloseCommission();
                lShortCloseCommissions << pPositionCost->GetShortCloseCommission();
                lLongMargins << pPositionCost->GetLongMargin();
                lShortMargins << pPositionCost->GetShortMargin();
            }
            oQuery.addBindValue(lCommissionModes);
            oQuery.addBindValue(lMarginModes);
            oQuery.addBindValue(lLongOpenCommissions);
            oQuery.addBindValue(lShortOpenCommissions);
            oQuery.addBindValue(lLongCloseCommissions);
            oQuery.addBindValue(lShortCloseCommissions);
            oQuery.addBindValue(lLongMargins);
            oQuery.addBindValue(lShortMargins);
            oQuery.addBindValue(lAccountIDs);
            oQuery.addBindValue(lNames);
            oQuery.execBatch();
            dbConn.commit();
        }
    }

    void Update(PositionCost const* pObj)
    {
        QString strQuery = "UPDATE POSITION_COST SET COMMISSION = ? "
                           "MARGIN_MODE = ? LONG_OPEN_COMMISSION = ? "
                           "SHORT_OPEN_COMMISSION = ? LONG_CLOSE_COMMISSION = ? "
                           "SHORT_CLOSE_COMMISSION = ? LONG_MARGIN = ? SHORT_MARGIN = ?"
                           "WHERE ACCOUNT_ID = ? AND INSTRUMENT_NAME = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,(int)(pObj->GetCommissionMode()));
            oQuery.bindValue(1,(int)(pObj->GetMarginMode()));
            oQuery.bindValue(2,pObj->GetLongOpenCommission());
            oQuery.bindValue(3,pObj->GetShortOpenCommission());
            oQuery.bindValue(4,pObj->GetLongCloseCommission());
            oQuery.bindValue(5,pObj->GetShortCloseCommission());
            oQuery.bindValue(6,pObj->GetLongMargin());
            oQuery.bindValue(7,pObj->GetShortMargin());
            oQuery.bindValue(8,pObj->GetAccount()->GetId());
            oQuery.bindValue(9,pObj->GetInstrument()->GetName());
            oQuery.exec();
            dbConn.commit();
        }
    }

    void Remove(QList<PositionCost*> const& lObjs)
    {
        QString strQuery = "DELETE FROM POSITION_COST WHERE ACCOUNT_ID = ? AND INSTRUMENT_NAME = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();

        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            QVariantList lAccountIDs;
            QVariantList lNames;
            for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
            {
                PositionCost *pPositionCost = lObjs[nCount];
                lAccountIDs << pPositionCost->GetAccount()->GetId();
            }
            oQuery.addBindValue(lAccountIDs);
            oQuery.addBindValue(lNames);
            oQuery.execBatch();
            dbConn.commit();
        }
    }

    void Remove(PositionCost const* pObjs)
    {
        QString strQuery = "DELETE FROM POSITION_COST WHERE ACCOUNT_ID = ? AND INSTRUMENT_NAME = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();

        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,pObjs->GetAccount()->GetId());
            oQuery.bindValue(1,pObjs->GetInstrument()->GetName());
            oQuery.exec();
            dbConn.commit();
        }
    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {
        PositionCostAccessor<D> oAccessor;
        oAccessor.Remove(pDep);
    }

};
#endif // _TRACKER_POSITIONCOSTPERSISTER_H_
