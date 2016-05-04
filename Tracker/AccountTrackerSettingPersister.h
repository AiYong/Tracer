#ifndef _TRACKER_ACCOUNTTRACKERSETTINGPERSISTER_H_
#define _TRACKER_ACCOUNTTRACKERSETTINGPERSISTER_H_

#include "Account.h"
#include "AccountManager.h"

#include "AccountTrackerSetting.h"

#include "DatabaseManager.h"

template<typename T>
class TrackerSettingAccessor
{
public:

    void Load(T const*pDep,QList<AccountTrackerSetting*> &lOrders)
    {

    }

    void Remove(T const*pDep)
    {

    }
};

template<>
class TrackerSettingAccessor<Account>
{
public:

    void Load(Account const*pAccount,QList<AccountTrackerSetting*> &lSettings)
    {
        QString strQuery = "SELECT * FROM ACCOUNT_TRACKER_SETTING WHERE TRADE_ACCOUNT_ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        if(oQuery.prepare(strQuery))
        {
            oQuery.bindValue(0,pAccount->GetID());
            if(oQuery.exec())
            {
                while(oQuery.next())
                {
                    AccountTrackerSetting *pTrackerSetting = new AccountTrackerSetting(pAccount);
                    QString strTrackAccountID = oQuery.value("TRACK_ACCOUNT_ID").toString();
                    bool bStopWin = oQuery.value("STOP_WIN").toBool();
                    StopWinPriceMode eStopWinPriceMode = (StopWinPriceMode)(oQuery.value("STOP_WIN_PRICE_MODE").toInt());
                    double dStopWinPrice = oQuery.value("STOP_WIN_PRICE").toDouble();
                    StopWinOrderType eStopWinOrderType = (StopWinOrderType)(oQuery.value("STOP_WIN_ORDER_TYPE").toInt());
                    StopWinOrderLimitPriceMode eStopWinOrderLimitPriceMode = (StopWinOrderLimitPriceMode)(oQuery.value("STOP_WIN_ORDER_LIMIT_PRICE_MODE").toInt());
                    double dStopWinOrderLimitPriceDelta = oQuery.value("STOP_WIN_ORDER_LIMIT_PRICE_DELTA").toDouble();
                    bool bStopLoss = oQuery.value("STOP_LOSS").toBool();
                    StopWinPriceMode eStopLossPriceMode = (StopWinPriceMode)(oQuery.value("STOP_LOSS_PRICE_MODE").toInt());
                    double dStopLossPrice = oQuery.value("STOP_LOSS_PRICE").toDouble();
                    StopWinOrderType eStopLossOrderType = (StopWinOrderType)(oQuery.value("STOP_LOSS_ORDER_TYPE").toInt());
                    StopWinOrderLimitPriceMode eStopLossOrderLimitPriceMode = (StopWinOrderLimitPriceMode)(oQuery.value("STOP_LOSS_ORDER_LIMIT_PRICE_MODE").toInt());
                    double dStopLossOrderLimitPriceDelta = oQuery.value("STOP_LOSS_ORDER_LIMIT_PRICE_DELTA").toDouble();
                    PositionLimitMode ePositionLimitMode = (PositionLimitMode)(oQuery.value("POSITION_LIMIT_MODE").toInt());
                    double dPositionLimit = oQuery.value("POSITION_LIMIT").toDouble();
                    BeyondPositionLimitProcessMode eBeyondPositionLimitProcessMode = (BeyondPositionLimitProcessMode)(oQuery.value("BEYOND_POSITION_LIMIT_PROCESS_MODE").toInt());
                    QString strInstrumentID = oQuery.value("INSTRUMENT_ID").toString();
                    OrderSubmitMode eOrderSubmitMode = (OrderSubmitMode)(oQuery.value("ORDER_SUBMIT_MODE").toString());
                    OpenPriceMode eOpenPriceMode = (OpenPriceMode)(oQuery.value("OPEN_PRICE_MODE").toInt());
                    OpenLimitPriceMode eOpenLimitPriceMode = (OpenLimitPriceMode)(oQuery.value("OPEN_LIMIT_PRICE_MODE").toString());
                    double dOpenLimitPriceDelta = oQuery.value("OPEN_LIMIT_PRICE_DELTA").toDouble();
                    ClosePriceMode eClosePriceMode = (ClosePriceMode)(oQuery.value("CLOSE_PRICE_MODE").toDouble());
                    CloseLimitPriceMode eCloseLimitPriceMode = (CloseLimitPriceMode)(oQuery.value("CLOSE_LIMIT_PRICE_MODE").toInt());
                    double dCloseLimitPriceDelta = oQuery.value("CLOSE_LIMIT_PRICE_DELTA").toDouble();

                    Account *pTrackAccount = AccountManager::GetInstance()->GetAccountWithID(strTrackAccountID);

                    pTrackerSetting->SetTrackAccount(pTrackAccount);
                    pTrackerSetting->SetStopWin(bStopWin);
                    pTrackerSetting->SetStopWinPriceMode(eStopWinPriceMode);
                    pTrackerSetting->SetStopWinPrice(dStopWinPrice);
                    pTrackerSetting->SetStopWinOrderType(eStopWinOrderType);
                    pTrackerSetting->SetStopWinOrderLimitPriceMode(eStopWinOrderLimitPriceMode);
                    pTrackerSetting->SetStopWinOrderLimitPriceDelta(dStopWinOrderLimitPriceDelta);
                    pTrackerSetting->SetStopLoss(bStopLoss);
                    pTrackerSetting->SetStopLossPriceMode(eStopLossPriceMode);
                    pTrackerSetting->SetStopLossPrice(dStopLossPrice);
                    pTrackerSetting->SetStopLossOrderType(eStopLossOrderType);
                    pTrackerSetting->SetStopLossOrderLimitPriceMode(eStopLossOrderLimitPriceMode);
                    pTrackerSetting->SetStopLossOrderLimitPriceDelta(dStopLossOrderLimitPriceDelta);
                    pTrackerSetting->SetPositionLimitMode(ePositionLimitMode);
                    pTrackerSetting->SetPositionLimit(dPositionLimit);
                    pTrackerSetting->SetBeyondPositionLimitProcessMode(eBeyondPositionLimitProcessMode);
                    pTrackerSetting->SetInstrument(pTrackAccount->GetInstrument(strInstrumentID));
                    pTrackerSetting->SetOrderSubmitMode(eOrderSubmitMode);
                    pTrackerSetting->SetOpenPriceMode(eOpenPriceMode);
                    pTrackerSetting->SetOpenLimitPriceMode(eOpenLimitPriceMode);
                    pTrackerSetting->SetOpenLimitPriceDelta(dOpenLimitPriceDelta);
                    pTrackerSetting->SetClosePriceMode(eClosePriceMode);
                    pTrackerSetting->SetCloseLimitPriceMode(eCloseLimitPriceMode);
                    pTrackerSetting->SetCloseLimitPriceDelta(dCloseLimitPriceDelta);
                    lSettings.append(pTrackerSetting);
                }
            }
        }
    }

    void Remove(Account const*pDep)
    {
        QString strQuery = "DELETE FROM ACCOUNT_TRACKER_SETTING WHERE TRADE_ACCOUNT_ID = ?";
        QSqlDatabase dbConn = DatabaseManager::GetInstance()->GetDatabase();
        QSqlQuery oQuery(dbConn);
        dbConn.transaction();
        oQuery.prepare(strQuery);
        oQuery.exec();
        dbConn.commit();
    }
};


/**
 * @brief 对象持久化器主模板
 */
template<>
class ObjectPersister<AccountTrackerSetting>
{
public:

    template<typename D>
    void Load(D *pDep,QList<AccountTrackerSetting*> &lObjs)
    {
        TrackerSettingAccessor<D> oAccessor;
        oAccessor.Load(pDep,lObjs);
    }

    void Save(QList<AccountTrackerSetting*> const&lObjs)
    {

    }

    void Save(AccountTrackerSetting const* pObj)
    {

    }

    void Update(QList<AccountTrackerSetting*> const& lOjbs)
    {

    }

    void Update(AccountTrackerSetting const* pObj)
    {

    }

    void Remove(QList<AccountTrackerSetting*> const& lObjs)
    {

    }

    void Remove(AccountTrackerSetting const* pObjs)
    {

    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {
        TrackerSettingAccessor<D> oAccessor;
        oAccessor.Remove(pDep);
    }
};
#endif // ACCOUNTTRACKERSETTINGPERSISTER_H
