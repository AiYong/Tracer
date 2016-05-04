#ifndef _TRACKER_TRANSACTIONPERSISTER_H_
#define _TRACKER_TRANSACTIONPERSISTER_H_


#include "Account.h"
#include "Transaction.h"
#include "ObjectPersister.h"
#include "DatabaseManager.h"

template<typename T>
class TransactionAccessor
{
public:

    void Load(T const* pDep,QList<Transaction*> &lTransactions)
    {

    }

    void Remove(T const* pDep)
    {

    }
};

template<>
class TransactionAccessor<Account>
{
public:

    void Load(Account const* pAccount,QList<Transaction*> &lTransactions)
    {
        QString strQuery = "SELECT *FROM TRANSACTION";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.exec(strQuery))
        {
            while(oQuery.next())
            {
                QString strID = oQuery.value("INSTRUMENT_ID").toString();
                size_t nQuantity = oQuery.value("QUANTITY").toUInt();
                QDateTime oOpenTime = oQuery.value("OPEN_TIME").toDateTime();
                QDateTime oCloseTime = oQuery.value("CLOSE_TIME").toDateTime();
                double dOpenPrice = oQuery.value("OPEN_PRICE").toDouble();
                double dClosePrice = oQuery.value("CLOSE_PRICE").toDouble();
                double dCommission = oQuery.value("COMMISSION").toDouble();
                double dProfit = oQuery.value("PROFIT").toDouble();
                double dOpenCommission = oQuery.value("OPEN_COMMISSION").toDouble();
                double dCloseCommission = oQuery.value("CLOSE_COMMISSION").toDouble();
                Direction eDirection = (Direction)(oQuery.value("DIRECTION").toInt());
                HedgeFlag eHedgeFlag = (HedgeFlag)(oQuery.value("HEDGE_FLAG").toInt());
                Instrument *pInstrument = pAccount->GetInstrument(strID);
                Transaction *pTransaction = new Transaction(pAccount,pInstrument,eDirection,eHedgeFlag,nQuantity,dOpenPrice,
                                                            dClosePrice,dCommission,dOpenCommission,dCloseCommission,dProfit);
                lTransactions.append(pTransaction);
            }
        }
    }

    void Remove(Account const* pAccount)
    {
        QString strQuery = "DELETE FROM WHERE ACCOUNT_ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,pAccount->GetId());
            oQuery.exec();
            dbConn.commit();
        }
    }
};


template<>
class ObjectPersister<Transaction>
{
public:

    template<typename D>
    void Load(D *pDep,QList<Transaction*> &lObjs)
    {
        TransactionAccessor<D> oAccessor;
        oAccessor.Load(pDep,lObjs);
    }

    void Save(QList<Transaction*> const& lObjs)
    {
        QString strQuery = "INSERT INTO TRANSACTION VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?)";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            QVariantList lAccountIDs;
            QVariantList lInstrumentIDs;
            QVariantList lOpenTimes;
            QVariantList lCloseTimes;
            QVariantList lQuantitys;
            QVariantList lOpenPrices;
            QVariantList lClosePrices;
            QVariantList lCommissions;
            QVariantList lOpenCommissions;
            QVariantList lCloseCommissions;
            QVariantList lProfits;
            QVariantList lDirections;
            QVariantList lHedgeFlags;
            for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
            {
                Transaction *pTransaction = lObjs[nCount];
                lAccountIDs << pTransaction->GetAccount()->GetId();
                lInstrumentIDs << pTransaction->GetInstrument()->GetID();
                lOpenTimes << pTransaction->GetOpenTime();
                lCloseTimes << pTransaction->GetCloseTime();
                lQuantitys << pTransaction->GetQuantity();
                lOpenPrices << pTransaction->GetOpenPrice();
                lClosePrices << pTransaction->GetClosePrice();
                lCommissions << pTransaction->GetCommission();
                lOpenCommissions << pTransaction->GetOpenCommission();
                lCloseCommissions << pTransaction->GetCloseCommission();
                lProfits << pTransaction->GetProfit();
                lDirections << (int)(pTransaction->GetDirection());
                lHedgeFlags << (int)(pTransaction->GetHedgeFlag());
            }
            oQuery.addBindValue(lAccountIDs);
            oQuery.addBindValue(lInstrumentIDs);
            oQuery.addBindValue(lOpenTimes);
            oQuery.addBindValue(lCloseTimes);
            oQuery.addBindValue(lQuantitys);
            oQuery.addBindValue(lOpenPrices);
            oQuery.addBindValue(lClosePrices);
            oQuery.addBindValue(lCommissions);
            oQuery.addBindValue(lOpenCommissions);
            oQuery.addBindValue(lCloseCommissions);
            oQuery.addBindValue(lProfits);
            oQuery.addBindValue(lDirections);
            oQuery.addBindValue(lHedgeFlags);
            oQuery.execBatch();
            dbConn.commit();
        }
    }

    void Save(Transaction const* pObj)
    {

    }

    void Update(QList<Transaction*> const& lOjbs)
    {

    }

    void Update(Transaction const* pObj)
    {

    }

    void Remove(QList<Transaction*> const& lObjs)
    {

    }

    void Remove(Transaction const* pObjs)
    {

    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {
        TransactionAccessor<D> oAccessor;
        oAccessor.Remove(pDep);
    }
};

#endif // _TRACKER_TRANSACTIONPERSISTER_H_
