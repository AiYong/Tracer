#ifndef _TRACKER_TRACKMANAGER_H_
#define _TRACKER_TRACKMANAGER_H_

#include <QObject>

#include "Account.h"
#include "Position.h"
#include "TradeService.h"
#include "AccountTrackerSetting.h"

class AccountTracker;

class TrackManager : public QObject
{
    Q_OBJECT
public:

    explicit TrackManager(QObject *parent = 0);

public:

    /**
     * @brief GetAccount
     * @return
     */
    Account* GetAccount() const;

public:

    /**
     * @brief NewTrackSettings
     * @return
     */
    AccountTrackSettings *NewTrackSettings();

    /**
     * @brief 启动一个账号监听器
     * @param pAccountTrackSettings
     */
    void StartTrack(AccountTrackSettings *pAccountTrackSettings);

    /**
     * @brief 停止一个账号监听器
     * @param pAccountTrackSettings
     */
    void StopTrack(AccountTrackSettings *pAccountTrackSettings);

    /**
     * @brief 更新账号监听器
     * @param pAccountTrackSettings
     */
    void UpdateTrack(AccountTrackSettings *pAccountTrackSettings);

public:

    /**
     * @brief GetTrackSettingsList
     * @return
     */
    QList<AccountTrackSettings*> GetTrackSettingsList() const;

    /**
     * @brief GetRunningTrackSettingsList
     * @return
     */
    QList<AccountTrackSettings*> GetRunningTrackSettingsList() const;


signals:

    /**
     * @brief 报单创建时该信号触发
     * @param pOrder
     */
    void OnTradeAccountNew(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

    /**
     * @brief 报单提交到经纪商时该信号触发
     * @param pOrder
     */
    void OnTradeAccountSubmitted(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

    /**
     * @brief 报单提交到交易所时该信号触发
     * @param pOrder
     */
    void OnTradeAccountQueued(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

    /**
     * @brief 报单撤销是该信号触发
     * @param pOrder
     */
    void OnTradeAccountCancelling(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

    /**
     * @brief 报单撤销完成时该信号触发
     * @param pOrder
     */
    void OnTradeAccountCancelled(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

    /**
     * @brief 开仓单成交时该信号触发
     * @param pOrder
     * @param pPosition
     */
    void OnTradeAccountOpen(AccountTrackSettings *pAccountTrackSettings,Order *pOrder,Position *pPosition);

    /**
     * @brief 平仓单关闭时该信号触发
     * @param pAccountTrackSettings
     * @param pOrder
     * @param pTransaction
     */
    void OnTradeAccountClose(AccountTrackSettings *pAccountTrackSettings,Order *pOrder,Transaction *pTransaction);


    /**
     * @brief 被跟踪的账号成交时，该信号触发。
     * @param pAccountTrackSettings
     * @param pPositin
     */
    void OnTrackAccountOpen(AccountTrackSettings *pAccountTrackSettings,Position *pPositin);

    /**
     * @brief 被跟踪的账号成交时，该信号触发。
     * @param pAccountTrackSettings
     * @param pPositin
     */
    void OnTrackAccountClose(AccountTrackSettings *pAccountTrackSettings,Transaction *pTransaction);

    /**
     * @brief 仓位盈利发生变化是该信号触发
     * @param pAcccountTrackSettings
     * @param pPosition
     * @param dProfit
     */
    void OnTradeAccountPositionUpdated(AccountTrackSettings *pAcccountTrackSettings,Position *pPosition,double dProfit);

private:

    AccountTracker *m_pAccountTracker;

};

#endif // _TRACKER_TRACKMANAGER_H_
