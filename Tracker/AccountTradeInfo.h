#ifndef _TRACKER_AccountTradeInfo_H_
#define _TRACKER_AccountTradeInfo_H_

#include <QList>
#include <QDate>
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>

#include "Direction.h"
#include "Hedgeflag.h"
#include "Operation.h"
#include "PriceMode.h"
#include "OrderStatus.h"

class Order;
class Account;
class Position;
class Instrument;
class Transaction;
class PositionCost;

class AccountTradeInfo
{
public:
    

    /**
     * @brief 构造函数
     * @param pInstrument
     * @param pPositionCost
     */
    AccountTradeInfo(Account *pAccount,Instrument *pInstrument,PositionCost *pPositionCost);
    

    /**
     * @brief 析构函数
     */
    ~AccountTradeInfo();
    

public:
    

    /**
     * @brief 初始化
     */
    void Initialize();
    

    /**
     * @brief 清理
     */
    void Destroy();
    

public:
    

    /**
     * @brief 返回账号
     * @return 
     */
    Account* GetAccount() const;
    

    /**
     * @brief 返回合约
     * @return 
     */
    Instrument* GetInstrument() const;
    

    /**
     * @brief 返回持仓成本
     * @return 
     */
    PositionCost* GetPositionCost() const;


    /**
     * @brief 返回指定在当前账号的最大开仓数量
     * @param pInstrument
     * @return
     */
    size_t GetAvailableQuantity(Direction eDirection,HedgeFlag eHedgeFlag,double dMargin,double dQuote) const;

    /**
     * @brief 返回合约持仓数量
     * @param pInstrument
     * @param eDirection
     * @return
     */
    size_t GetPositionQuantity(Direction eDirection,HedgeFlag eHedgeFlag) const;

    /**
     * @brief GetProfit
     * @return
     */
    double GetPositionProfit() const;

    /**
     * @brief GetTradeProfit
     * @return
     */
    double GetTradeDayProfit() const;

    /**
     * @brief GetTradeDayCommission
     * @return
     */
    double GetTradeDayCommission() const;

    /**
     * @brief GetFrezonMargin
     * @return
     */
    double GetFrezonMargin() const;

public:
    
    /**
     * @brief 创建Order
     * @param eDirection
     * @param eOperation
     * @param eHedgeFlag
     * @param ePriceMode
     * @param nQantity
     * @param dQuote
     * @return 
     */
    Order* CreateOrder(Direction eDirection,Operation eOperation,
                       HedgeFlag eHedgeFlag,PriceMode ePriceMode,size_t nQantity,double dQuote = 0);
    
    /**
     * @brief 开仓报单成交
     * @param pOrder
     * @param oTimestamp
     * @param nQuantity
     * @param dPrice
     * @return
     */
    Position* CreatePosition(Order const* pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);

    /**
     * @brief 平仓报单成交
     * @param pOrder
     * @param oTimestamp
     * @param nQuantity
     * @param dPrice
     * @return
     */
    QList<Transaction*> CreateTransaction(Order const *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);

    /**
     * @brief UpdateOrderStatus
     * @param pOrder
     * @param eStatus
     */
    void UpdateOrderStatus(Order const* pOrder,OrderStatus eStatus);
    
 
public:
    
    /**
     * @brief 返回所有Order
     * @return 
     */
    QList<Order*> GetOrders();
    
    /**
     * @brief 返回指定交易日Order
     * @param oTradeDay
     * @return 
     */
    QList<Order*> GetOrders(QDate const& oTradeDay);
    
    /**
     * @brief 返回当前交易日Order
     * @return 
     */
    QList<Order*> GetTradeDayOrders() const;
    
    /**
     * @brief 返回正在执行的Order
     * @return 
     */
    QList<Order*> GetRunningOrders() const;
    
    
public:
    
    /**
     * @brief 返回当前持仓
     * @return 
     */
    QList<Position*> GetPositions() const;


    /**
     * @brief 返回所有的交易事务
     * @return 
     */
    QList<Transaction*> GetTransactions();
    

    /**
     * @brief 返回交易日交易事务
     * @return 
     */
    QList<Transaction*> GetTradeDayTransactions() const;
    

    /**
     * @brief 返回指定交易日交易事务
     * @param oTradeDay
     * @return 
     */
    QList<Transaction*> GetTransactions(QDate const& oTradeDay) ;
    

private:
    
    void LoadOrders();
    void LoadPositions();
    void LoadTransactions();
    void LoadTradeDayOrders();
    void LoadTradeDayTransactions();

    void SaveOrder(Order *pOrder);
    void UpdateOrder(Order *pOrder);

    void SavePosition(Position *pPosition);
    void UpdatePosition(Position *pPosition);
    void RemovePosition(Position *pPosition);

    void SaveTransaction(QList<Transaction*> const& lTransactions);
    
public:
    
    Account *m_pAccount;
    Instrument *m_pInstrument;
    PositionCost *m_pPositionCost;
    QList<Order*> m_lRunningOrders;
    QList<Order*> m_lTradeDayOrders;
    QList<Order*> m_lOrders;
    QList<Position*> m_lPositions;
    QList<Transaction*> m_lTradeDayTransactions;
    QList<Transaction*> m_lTransactions;
    mutable QMutex m_mLock;
    bool m_bOrderLoaded;
    bool m_bPositionLoaded;
    bool m_bTransactionLoaded;
};

#endif // _TRACKER_AccountTradeInfo_H_
