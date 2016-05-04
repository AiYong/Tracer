#ifndef _TRACKER_POSITION_H_
#define _TRACKER_POSITION_H_

#include <QObject>
#include "Direction.h"
#include "HedgeFlag.h"

class Order;
class Account;
class Instrument;
class Transaction;
class PositionCost;
class Position
{
public:

    Position(
        QString const& strID,
        Account *pAccount,
        Instrument *pInstrument,
        PositionCost *pPositionCost,
        QDateTime const& oTimestamp,
        Direction eDirection,
        HedgeFlag eHedgeFlag,
        size_t nQuantity,
        double dPrice
        );

    ~Position();

public:

    QString const& GetID() const;

    /**
     * @brief 持仓所属账号
     * @return
     */
    Account* GetAccount() const;

    /**
     * @brief 持仓合约合约
     * @return
     */
    Instrument* GetInstrument() const;

    /**
     * @brief GetPositionCost
     * @return
     */
    PositionCost* GetPositionCost() const;

    /**
     * @brief 返回开仓时间
     * @return
     */
    QDateTime GetTimestamp() const;

    /**
     * @brief 开仓方向
     * @return
     */
    Direction GetDirection() const;

    /**
     * @brief 投机套保标志
     * @return
     */
    HedgeFlag GetHedgeFlag() const;

    /**
     * @brief 开仓数量
     * @return
     */
    size_t GetQuantity() const;

    /**
     * @brief 开仓价格
     * @return
     */
    double GetPrice() const;

public:

    /**
     * @brief 开仓手续费
     * @return
     */
    double GetCommission() const;

    /**
     * @brief 返回持仓占用保证金
     * @return
     */
    double GetFrezonMargin() const;


public:

    /**
     * @brief 当日盈亏
     * @return
     */
    double GetTradeDayProfit() const;

    /**
     * @brief 总盈亏
     * @return
     */
    double GetTotalProfit() const;

public:

    /**
     * @brief Close
     * @param oTimestamp
     * @param nQuantity
     * @param dPrice
     * @return
     */

    Transaction* Close(QDateTime const& oTimestamp,size_t nQuantity,double dPrice);


private:

    double GetCommission(double dPrice);

    QString m_strID;
    Account *m_pAccount;
    Instrument *m_pInstrument;
    PositionCost *m_pPositionCost;
    QDateTime m_oTimestamp;
    Direction m_eDirection;
    HedgeFlag m_eHedgeFlag;
    size_t m_nQuantity;
    double m_dPrice;
    double m_dCommission;

};

#endif // _TRACKER_POSITION_H_
