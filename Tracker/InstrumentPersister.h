#ifndef _TRACKER_INSTRUMENTPERSISTER_H_
#define _TRACKER_INSTRUMENTPERSISTER_H_

#include "Order.h"
#include "Account.h"
#include "ObjectPersister.h"
#include "DatabaseManager.h"

template<>
class ObjectPersister<Instrument>
{
public:

    template<typename D>
    void Load(D *pDep,QList<Instrument*> &lObjs)
    {
        QString strQuery = "SELECT * FROM INSTRUMENT";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.exec(strQuery))
        {
            while(oQuery.next())
            {
                QString strID = oQuery.value("ID").toString();
                QString strName = oQuery.value("NAME").toString();
                double  dPriceMultiple = oQuery.value("PRICE_MULTIPLE").toDouble();
                QTime oCloseTime = oQuery.value("CLOSE_TIME").toTime();
                QTime oLastTradeDayCloseTime = oQuery.value("LAST_TRADE_DAY_CLOSE_TIME").toTime();
                QString strVariety = oQuery.value("VARIETY").toString();
                QString strExchange = oQuery.value("EXCHANGE").toString();
                QDate oLastTradeDay = oQuery.value("LAST_TRADE_DAY").toDate();
                Instrument *pInstrument = new Instrument(strID,strName,strVariety,strExchange,
                                                         dPriceMultiple,oLastTradeDay,oCloseTime,oLastTradeDayCloseTime);
                lObjs.append(pInstrument);
            }
        }
    }

    void Save(QList<Instrument*> const&lObjs)
    {
        QString strQuery = "INSERT INTO INSTRUMENT VALUES(?,?,?,?,?,?,?,?)";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            QVariantList lIDs;
            QVariantList lNames;
            QVariantList lPriceMultiples;
            QVariantList lCloseTimes;
            QVariantList lLastTradeDayCloseTimes;
            QVariantList lExchanges;
            QVariantList lVarieties;
            QVariantList lLastTradeDays;
            for(int nCount = 0 ; nCount < lObjs.size() ; nCount++)
            {
                Instrument *pInstrument = lObjs[nCount];
                lIDs << pInstrument->GetID();
                lNames << pInstrument->GetName();
                lPriceMultiples << pInstrument->GetPriceMultiple();
                lCloseTimes << pInstrument->GetCloseTime();
                lLastTradeDayCloseTimes << pInstrument->GetLastTradeDayCloseTime();
                lExchanges << pInstrument->GetExchange();
                lVarieties << pInstrument->GetVariety();
                lLastTradeDays << pInstrument->GetLastTradeDay();
            }
            dbConn.transaction();
            oQuery.addBindValue(lIDs);
            oQuery.addBindValue(lNames);
            oQuery.addBindValue(lPriceMultiples);
            oQuery.addBindValue(lCloseTimes);
            oQuery.addBindValue(lLastTradeDayCloseTimes);
            oQuery.addBindValue(lExchanges);
            oQuery.addBindValue(lVarieties);
            oQuery.addBindValue(lLastTradeDays);
            oQuery.execBatch();
            dbConn.commit();
        }
    }

    void Save(Instrument const* pObj)
    {

    }

    void Update(QList<Instrument*> const& lOjbs)
    {

    }

    void Update(Instrument const* pObj)
    {

    }

    void Remove(QList<Instrument*> const& lObjs)
    {

    }

    void Remove(Instrument const* pObjs)
    {

    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {

    }
};

#endif // _TRACKER_INSTRUMENTPERSISTER_H_
