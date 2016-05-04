#ifndef _TRACKER_TRADERESOURCEMANAGER_H_
#define _TRACKER_TRADERESOURCEMANAGER_H_

#include <QList>
#include <QDate>
#include <QDateTime>
#include <QReadLocker>
#include <QWriteLocker>
#include <QReadWriteLock>

#include "Direction.h"
#include "Hedgeflag.h"
#include "Operation.h"
#include "PriceMode.h"

class Order;
class Account;
class Position;
class Instrument;
class Transaction;
class PositionCost;

class TradeResourceManager
{
public:
    
    /**
     * @brief 构造函数
     * @param pInstrument
     * @param pPositionCost
     */
    TradeResourceManager(Account *pAccount,Instrument *pInstrument,PositionCost *pPositionCost);
    
    /**
     * @brief 析构函数
     */
    ~TradeResourceManager();
    
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
    Position* OpenOrderHasTraded(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);

    /**
     * @brief 平仓报单成交
     * @param pOrder
     * @param oTimestamp
     * @param nQuantity
     * @param dPrice
     * @return
     */
    Transaction* CloseOrderHasTraded(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);

    /**
     * @brief Order撤销
     * @param pOrder
     */
    void OrderHasCancelled(Order *pOrder);
    
 
public:
    
    /**
     * @brief 返回所有Order
     * @return 
     */
    QList<Order*> GetOrders() const;
    
    /**
     * @brief 返回指定交易日Order
     * @param oTradeDay
     * @return 
     */
    QList<Order*> GetOrders(QDate const& oTradeDay) const;
    
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
    QList<Transaction*> GetTransactions() const;
    
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
    QList<Transaction*> GetTransactions(QDate const& oTradeDay) const;
    
    
private:
    
    void LoadOrders();
    void LoadPositions();
    void LoadTransactions();
    
    void SaveOrders();
    void SavePositions(); 
    void SaveOrder(Order *pOrder);
    void UpdateOrder(Order *pOrder);
    void SavePosition(Position *pPosition);
    void pdatePosition(Position *pPosition);
    void SaveTransaction(QList<Transaction*> const& lTransactions);   
    void RemovePosition(QList<Position*> const& lPositions);
    
    void Lock();
    void Unlock();

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
    QReadWriteLock m_mLock;
    bool m_bOrderLoaded;
    bool m_bPositionLoaded;
    bool m_bTransactionLoaded;
};

#endif // _TRACKER_TRADERESOURCEMANAGER_H_
