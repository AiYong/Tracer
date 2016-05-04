#ifndef _TRACKER_ACCOUNT_H_
#define _TRACKER_ACCOUNT_H_

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QMutex>
#include <QMutexLocker>
#include "Direction.h"
#include "Hedgeflag.h"
#include "Operation.h"
#include "PriceMode.h"
#include "OrderStatus.h"


class Order;
class Broker;
class Position;
class Instrument;
class Transaction;
class PositionCost;
class AccountManager;
class AccountAccessor;
class TradeResourceManager;

class Account
{
public:

    /**
     * @brief 构造函数
     * @param parent
     */
    Account(QString const& strId,QString const& strName,
            QString const& strPassword,Broker *pBroker);

    ~Account();

public:

    /**
     * @brief Initlize
     */
    bool Initlize();

    /**
     * @brief Destory
     */
    void Destory();

public:

    /**
     * @brief 返回Id
     * @return
     */
    QString const& GetID() const;

    /**
     * @brief  返回账号名称
     * @return
     */
    QString const& GetName() const;

    /**
     * @brief 返回账号密码
     * @return
     */
    QString const& GetPassword() const;

    /**
     * @brief 返回经纪商
     * @return
     */
    Broker* GetBroker() const;

public:

    /**
     * @brief 返回动态保证金数量
     * @return
     */
    double GetDynamicMargin() const;

    /**
     * @brief 返回静态保证金
     * @return
     */
    double GetStaticMargin() const;

    /**
     * @brief 返回账号可用保证金
     * @return
     */
    double GetAvailableMargin() const;

    /**
     * @brief 返回当前冻结保证金
     * @return
     */
    double GetFrezonMargin() const;

    /**
     * @brief 返回账号动态盈亏
     * @return
     */
    double GetPositionProfit() const;

    /**
     * @brief GetTradeDayProfit
     * @return
     */
    double GetTradeDayProfit() const;

    /**
     * @brief GetTotalProfit
     * @return
     */
    double GetTotalProfit() const;

public:

    /**
     * @brief 返回指定在当前账号的最大开仓数量
     * 该方法返回的最大开仓数量是以最近成交价计算的。
     * @param pInstrument
     * @return
     */
    size_t GetAvailableQuantity(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag) const;

    /**
     * @brief 返回指定在当前账号的最大开仓数量
     * @param pInstrument
     * @return
     */
    size_t GetAvailableQuantity(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag,double dQuote) const;


    /**
     * @brief 返回指定在当前账号的最大开仓数量
     * 该方法返回的最大开仓数量是以最近成交价计算的。
     * @param pInstrument
     * @return
     */
    size_t GetAvailableQuantityWithMargin(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag,double dMargin) const;

    /**
     * @brief 返回指定在当前账号的最大开仓数量
     * @param pInstrument
     * @return
     */
    size_t GetAvailableQuantityWithMargin(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag,double dMargin,double dQuote) const;

    /**
     * @brief 返回合约持仓数量
     * @param pInstrument
     * @param eDirection
     * @return
     */
    size_t GetPositionQuantity(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag) const;


public:

    /**
     * @brief 返回合约列表
     * @return
     */
    QMap<QString,Instrument*> const& GetInstruments() const;

    /**
     * @brief GetInstrument
     * @param strInstrumentName
     * @return 
     */
    Instrument* GetInstrument(QString const& strInstrumentName) const;
    
public:

    /**
     * @brief 返回指定合约的持仓成本
     * @param pInstrument
     * @return
     */
    PositionCost* GetPositionCost(Instrument *pInstrument) const;

    /**
     * @brief 返回所有合约的持仓成本
     * @return
     */
    QMap<Instrument*,PositionCost*> GetPositionCosts() const;


public:

    /**
     * @brief 创建报单
     * @param pInstrument
     * @param eDirection
     * @param eOperation
     * @param eHedgeFlag
     * @param ePriceMode
     * @param nQantity
     * @param dQuote
     * @return
     */
    Order* CreateOrder(
            Instrument const* pInstrument,Direction eDirection,Operation eOperation,
            HedgeFlag eHedgeFlag,PriceMode ePriceMode,size_t nQantity,double dQuote = 0
            );

    /**
     * @brief 创建仓位对象
     * @param pOrder
     * @param oTimestamp
     * @param nQuantity
     * @param dPrice
     * @return
     */
    Position* CreatePosition(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);

    /**
     * @brief 创建交易事务对象
     * @param pOrder
     * @param oTimestamp
     * @param nQuantity
     * @param dPrice
     * @return
     */
    Transaction* CreateTransaction(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice);

    /**
     * @brief 设置Order状态
     * @param pOrder
     * @param eStatus
     */
    void SetOrderStatus(Order *pOrder,OrderStatus eStatus);

public:

    /**
     * @brief 返回当前正在执行的Order
     * @return
     */
    QMap<Instrument*,QList<Order*>> GetRunningOrders();

    /**
     * @brief 返回指定合约正在执行的Order
     * @param pInstrument
     * @return
     */
    QList<Order*> GetRunningOrders(Instrument* pInstrument);


    /**
     * @brief 返回所有Order
     * @return
     */
    QMap<Instrument*,QList<Order*>> GetOrders() const;

    /**
     * @brief 返回指定合约所有Order
     * @param pInstrument
     * @return
     */
    QList<Order*> GetOrders(Instrument *pInstrument) const;


    /**
     * @brief GetTradeDayOrders
     * @return
     */
    QMap<Instrument*,QList<Order*>> GetTradeDayOrders() const;

    /**
     * @brief GetTradeDayOrders
     * @param pInstrument
     * @return
     */
    QList<Order*> GetTradeDayOrders(Instrument *pInstrument) const;


public:

    /**
     * @brief 返回所有持仓
     * @return
     */
    QMap<Instrument*,QList<Position*>> GetPositions() const;

    /**
     * @brief 返回指定合约的持仓
     * @param pInstrument
     * @return
     */
    QList<Position*> GetPositions(Instrument *pInstrument) const;


public:

    /**
     * @brief 返回指定合约交易事务
     * @param pInstrument
     * @return
     */
    QList<Transaction*> GetTransactions(Instrument *pInstrument) const;

    /**
     * @brief 返回交易事务
     * @return
     */
    QMap<Instrument*,QList<Transaction*>> GetTransactions() const;

    /**
     * @brief 返回交易日指定合约交易事务
     * @param pInstrument
     * @return
     */
    QList<Transaction*> GetTradeDayTransactions(Instrument *pInstrument)const;

    /**
     * @brief 返回交易日交易事务
     * @return
     */
    QMap<Instrument*,QList<Transaction*>> GetTradeDayTransactions() const;


public:

    /**
     * @brief GenOrderID
     * @return
     */
    QString GenOrderID();
    
    /**
     * @brief GenPositionID
     * @return
     */
    QString GenPositionID();


private:

    QString m_strId;
    QString m_strName;
    QString m_strPassword;
    Broker *m_pBroker;
    double  m_dStaticMargin;
    QMutex m_mMutex;

    QMap<Instrument*,PositionCost*> m_mCosts;
    QList<Instrument*> m_lInstrument;
    QMap<QString,Instrument*> m_mInstrument;
    QMap<Instrument*,TradeResourceManager*> m_mTradeResources;

};

#endif // _TRACKER_ACCOUNT_H_
