#ifndef _TRACKER_ORDER_H_
#define _TRACKER_ORDER_H_

#include <QObject>
#include "Direction.h"
#include "Instrument.h"
#include "Operation.h"
#include "HedgeFlag.h"
#include "PriceMode.h"
#include "OrderStatus.h"
class Account;
class Position;
class PositionCost;
class OrderOperator;




class Order
{
public:

    Order(
          int nId,
          Account *pAccount,
          Instrument *pInstrument,
          PositionCost *pPositionCost,
          QDate const& oTradeDay,
          QTime const& oTradeTime,
          Operation eOperation,
          Direction eDirection,
          HedgeFlag eHedgeFlag,
          PriceMode ePriceMode,
          size_t nQuantity,
          double dQuote,
          OrderStatus eStatus,
          size_t nTradeVolume = 0
          );

public:

    /**
     * @brief 返回ID
     * @return
     */
    int GetId() const;

    /**
     * @brief 返回报单账号
     * @return
     */
    Account* GetAccount() const;

    /**
     * @brief 返回报单合约
     * @return
     */
    Instrument* GetInstrument() const;

    /**
     * @brief 返回持仓成本
     * @return
     */
    PositionCost* GetPositionCost() const;

    /**
     * @brief 返回报单时间
     * @return
     */
    QDate const& GetTradeDay() const;

    /**
     * @brief GetTradeTime
     * @return
     */
    QTime const& GetTradeTime() const;

    /**
     * @brief 返回仓位操作
     * @return
     */
    Operation GetOperation()const;

    /**
     * @brief 返回方向
     * @return
     */
    Direction GetDirection() const;

    /**
     * @brief 返回投机套保标志
     * @return
     */
    HedgeFlag GetHedgeFlag() const;

    /**
     * @brief 返回价格模式
     * @return
     */
    PriceMode GetPriceMode() const;

    /**
     * @brief 返回报单量
     * @return
     */
    size_t GetQuantity() const;

    /**
     * @brief 返回报单价格
     * @return
     */
    double GetQuote() const;

    /**
     * @brief 返回报单状态
     * @return
     */
    OrderStatus GetStatus() const;


    /**
     * @brief 返回占用保证金
     * @return
     */
    double GetFrezonMargin() const;

    /**
     * @brief 返回成交量
     * @return
     */
    size_t GetTradeVolume() const;

private:

    friend class OrderOperator;
    template<typename T>
    friend class ObjectPersister;

    int m_nId;
    Account *m_pAccount;
    Instrument *m_pInstrument;
    PositionCost *m_pPositionCost;
    QDate m_oTradeDay;
    QTime m_oTradeTime;
    Operation m_eOperation;
    Direction m_eDirection;
    HedgeFlag m_eHedgeFlag;
    PriceMode m_ePriceMode;
    size_t m_nQuantity;
    double m_dQuote;
    OrderStatus m_eStatus;
    size_t m_nTradeVolume;

};

#endif // _TRACKER_ORDER_H_
