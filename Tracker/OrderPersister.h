#ifndef _TRACKER_ORDERPERSISTER_H_
#define _TRACKER_ORDERPERSISTER_H_

#include "Order.h"
#include "Account.h"
#include "ObjectPersister.h"
#include "DatabaseManager.h"

template<typename T>
class OrderAccessor
{
public:

    void Load(T const*pDep,QList<Order*> &lOrders)
    {

    }

    void Remove(T const*pDep)
    {

    }
};

template<>
class OrderAccessor<Order>
{
public:

    void Load(Account const* pAccount,QList<Order*> &lOrders)
    {
        QString strQuery = "SELECT * FROM ORDER WHERE ACCOUNT_ID = ?" ;
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery sqlQuery(dbConn);
        if(sqlQuery.prepare(strQuery))
        {
            sqlQuery.bindValue(0,pAccount->GetID());
            if(sqlQuery.exec())
            {
                sqlQuery.first();
                while(sqlQuery.next())
                {
                    QString strId = sqlQuery.value("ID");
                    QString strInstrument = sqlQuery.value("INSTRUMENT_NAME").toString();
                    QDateTime oTimestamp = sqlQuery.value("TIMESTAMP").toString();
                    Operation eOperation = (Operation)(sqlQuery.value("OPERATION").toInt());
                    Direction eDirection = (Direction)(sqlQuery.value("DIRECTION").toInt());
                    HedgeFlag eHedgeFlag = (HedgeFlag)(sqlQuery.value("HEDGE_FLAG").toInt());
                    PriceMode ePriceMode = (PriceMode)(sqlQuery.value("PRICE_MODE").toInt());
                    size_t nQuantity = sqlQuery.value("QUANTITY").toUInt();
                    double dQuote = sqlQuery.value("QUOTE").toDouble();
                    OrderStatus eStatus = (OrderStatus)(sqlQuery.value("STATUS").toInt());
                    size_t nTradeVolume = sqlQuery.value("TRADE_VOLUME");
                    Instrument *pInstrument = pAccount->GetInstrument(strInstrument);
                    Order *pOrder = new Order(strId,pAccount,pInstrument,pAccount->GetPositionCost(pInstrument),
                                              oTimestamp,eOperation,eDirection,eHedgeFlag,ePriceMode,nQuantity,
                                              dQuote,eStatus,nTradeVolume);
                    lOrders.append(pOrder);
                }
            }
        }
    }

    void Remove(Account const* pAccount)
    {
        QString strQuery = "DELETE FROM ORDER WHERE ACCOUNT_ID = ? ";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        oQuery.prepare(strQuery);
        dbConn.transaction();
        oQuery.bindValue(0,pAccount->GetId());
        oQuery.exec();
        dbConn.commit();
    }
};

template<>
class ObjectPersister<Order>
{
public:

    template<typename D>
    void Load(D *pDep,QList<Order*> &lObjs)
    {
        OrderAccessor<D> oOrderAccessor;
        oOrderAccessor.Load(pDep,lObjs);
    }

    void Save(QList<Order*> const& lObjs)
    {

    }

    void Save(Order const* pOrder)
    {
        QString strQuery= "INSERT INTO ORDER VALUES(?,?,?,?,?,?,?,?,?,?,?,?)";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            dbConn.transaction();
            oQuery.bindValue(0,pOrder->GetId());
            oQuery.bindValue(1,pOrder->GetInstrument()->GetName());
            oQuery.bindValue(2,pOrder->GetAccount()->GetId());
            oQuery.bindValue(3,pOrder->GetTimestamp());
            oQuery.bindValue(4,(int)(pOrder->GetOperation()));
            oQuery.bindValue(5,(int)(pOrder->GetDirection()));
            oQuery.bindValue(6,(int)(pOrder->GetHedgeFlag()));
            oQuery.bindValue(7,(int)(pOrder->GetPriceMode()));
            oQuery.bindValue(8,(int)(pOrder->GetQuantity()));
            oQuery.bindValue(9,pOrder->GetQuote());
            oQuery.bindValue(10,(int)(pOrder->GetStatus()));
            oQuery.bindValue(11,(int)(pOrder->GetTradeVolume()));
            oQuery.exec();
            dbConn.commit();
        }
    }

    void Update(QList<Order*> const& lOjbs)
    {

    }

    void Update(Order const* pObj)
    {
        QString strUpdateOrder = "UPDATE ORDER SET STATUS = ?,TRADE_VOLUME= ? WHERE ID = ? ";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery sqlQuery(dbConn);
        sqlQuery.prepare(strUpdateOrder);
        dbConn.transaction();
        sqlQuery.bindValue(0,(int)(pObj->GetStatus()));
        sqlQuery.bindValue(1,(int)(pObj->GetTradeVolume()));
        sqlQuery.bindValue(2,pObj->GetId());
        sqlQuery.exec();
        dbConn.commit();
    }

    void Remove(QList<Order*> const& lObjs)
    {

    }

    void Remove(Order const* pObjs)
    {

    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {
        OrderAccessor<D> oOrderAccessor;
        oOrderAccessor.Remove(pDep);
    }
};

#endif // _TRACKER_ORDERPERSISTER_H_
