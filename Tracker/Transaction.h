#ifndef _TRACKER_TRANSACTION_H_
#define _TRACKER_TRANSACTION_H_

#include <QObject>
#include <QList>

#include "Direction.h"
#include "Instrument.h"
#include "Operation.h"
#include "HedgeFlag.h"
#include "PriceMode.h"

class Order;
class Account;
class Position;
class Instrument;


class Transaction
{
public:

    /**
     * @brief Transaction
     * @param pAccount
     * @param pInstrument
     * @param eDirection
     * @param eHedgeFlag
     * @param nQuantity
     * @param dOpenPrice
     * @param dClosePrice
     * @param dCommission
     * @param dOpenCommission
     * @param dCloseCommission
     * @param dProfit
     */
    Transaction(
                Account const*pAccount,
                Instrument const*pInstrument,
                Direction eDirection,
                HedgeFlag eHedgeFlag,
                size_t nQuantity,
                double dOpenPrice,
                double dClosePrice,
                double dCommission,
                double dOpenCommission,
                double dCloseCommission,
                double dProfit,
                QDateTime const& oOpenTime,
                QDateTime const& oCloseTime
                );

    /**
    *
    */
    ~Transaction();

public:

    /**
     * @brief 交易事务账号
     * @return
     */
    Account const* GetAccount() const;

    /**
     * @brief 交易事务合约
     * @return
     */
    Instrument const* GetInstrument() const;

    /**
     * @brief 交易方向
     * @return
     */
    Direction GetDirection() const;

    /**
     * @brief 投机套保标志
     * @return
     */
    HedgeFlag GetHedgeFlag() const;

    /**
     * @brief 数量
     * @return
     */
    size_t GetQuantity() const;

    /**
     * @brief 返回开仓价格
     * @return
     */
    double GetOpenPrice() const;

    /**
     * @brief 返回开仓时间
     * @return
     */
    QDateTime const& GetOpenTime() const;

    /**
     * @brief 返回平仓价格
     * @return
     */
    double GetClosePrice() const;

    /**
     * @brief 返回平仓时间
     * @return
     */
    QDateTime const& GetCloseTime() const;

    /**
     * @brief 返回开仓费用
     * @return
     */
    double GetOpenCommission() const;

    /**
     * @brief 返回平仓费用
     * @return
     */
    double GetCloseCommission() const;

    /**
     * @brief 总费用
     * @return
     */
    double GetCommission() const;

    /**
     * @brief 盈利
     * @return
     */
    double GetProfit() const;

private:

    Account const*m_pAccount;
    Instrument const*m_pInstrument;
    Direction m_eDirection;
    HedgeFlag m_eHedgeFlag;
    size_t m_nQuantity;
    double m_dOpenPrice;
    double m_dClosePrice;
    double m_dCommission;
    double m_dOpenCommission;
    double m_dCloseCommission;
    double m_dProfit;
    QDateTime m_oOpenTime;
    QDateTime m_oCloseTime;
};

#endif // _TRACKER_TRANSACTION_H_
