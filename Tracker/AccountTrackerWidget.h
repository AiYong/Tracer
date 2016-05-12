#ifndef ACCOUNTTRACKWIDGET_H
#define ACCOUNTTRACKWIDGET_H

#include <QWidget>

class AccountTrackWidget : public QWidget
{
    Q_OBJECT
public:

    AccountTrackWidget(QWidget *parent = 0);

    ~AccountTrackWidget();

//public slots:

//    void OnNewTrackSettings();

//public slots:

//    /**
//     * @brief 报单创建时该信号触发
//     * @param pOrder
//     */
//    void OnTradeAccountNew(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

//    /**
//     * @brief 报单提交到经纪商时该信号触发
//     * @param pOrder
//     */
//    void OnTradeAccountSubmitted(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

//    /**
//     * @brief 报单提交到交易所时该信号触发
//     * @param pOrder
//     */
//    void OnTradeAccountQueued(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

//    /**
//     * @brief 报单撤销是该信号触发
//     * @param pOrder
//     */
//    void OnTradeAccountCancelling(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

//    /**
//     * @brief 报单撤销完成时该信号触发
//     * @param pOrder
//     */
//    void OnTradeAccountCancelled(AccountTrackSettings *pAccountTrackSettings,Order *pOrder);

//    /**
//     * @brief 开仓单成交时该信号触发
//     * @param pOrder
//     * @param pPosition
//     */
//    void OnTradeAccountOpen(AccountTrackSettings *pAccountTrackSettings,Order *pOrder,Position *pPosition);

//    /**
//     * @brief 平仓单关闭时该信号触发
//     * @param pAccountTrackSettings
//     * @param pOrder
//     * @param pTransaction
//     */
//    void OnTradeAccountClose(AccountTrackSettings *pAccountTrackSettings,Order *pOrder,Transaction *pTransaction);


//    /**
//     * @brief 被跟踪的账号成交时，该信号触发。
//     * @param pAccountTrackSettings
//     * @param pPositin
//     */
//    void OnTrackAccountOpen(AccountTrackSettings *pAccountTrackSettings,Position *pPositin);

//    /**
//     * @brief 被跟踪的账号成交时，该信号触发。
//     * @param pAccountTrackSettings
//     * @param pPositin
//     */
//    void OnTrackAccountClose(AccountTrackSettings *pAccountTrackSettings,Transaction *pTransaction);

//    /**
//     * @brief OnTradeAccountPositionUpdated
//     * @param pAcccountTrackSettings
//     * @param pPosition
//     * @param dProfit
//     */
//    void OnTradeAccountPositionUpdated(AccountTrackSettings *pAcccountTrackSettings,Position *pPosition,double dProfit);
};

#endif // ACCOUNTTRACKWIDGET_H
