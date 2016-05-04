#ifndef _TRACKER_PLATFORM_H_
#define _TRACKER_PLATFORM_H_

#include <memory>

#include <QMap>
#include <QList>
#include <QString>
#include <QObject>

#include "Account.h"
#include "Instrument.h"
#include "PositionCost.h"
#include "OrderListener.h"
#include "OrderProcessor.h"
#include "OrderSubscriber.h"
#include "MarketDataSubscriber.h"

using namespace std;

class AccountInfo
{
public:

    AccountInfo(double dAvailableMargin,QList<Instrument*> const& lInstrument,QMap<QString,PositionCost*> const& hPositionCost);

    ~AccountInfo();

public:

   double GetAvailableMargin() const;

   QList<Instrument*> const& GetInstruments() const;

   QMap<QString,PositionCost*> const& GetPositionCost() const;

private:

    double m_dAvailableMargin;
    QList<Instrument*> m_lInstrument;
    QMap<QString,PositionCost*> m_hPositionCost;
};

class Platform
{
public:

    /**
     * @brief Platform
     * @param parent
     */
    Platform();

    /**
     * @brief ~Platform
     */
    virtual ~Platform();

public:

    /**
     * @brief QUeryMargin
     * @param pAccount
     * @return
     */
    virtual shared_ptr<AccountInfo> QueryAccountInfo(Account const*pAccount) = 0;

    /**
     * @brief 为指定账号创建交易处理器
     * @param pAccount
     * @return
     */
    virtual shared_ptr<OrderProcessor> CreateOrderProcessor(Account const*pAccount) = 0;

    /**
     * @brief CreateOrderSubsriber
     * @param pAccount
     * @return
     */
    virtual shared_ptr<OrderSubscriber> CreateOrderSubsriber(Account const* pAccount) = 0;

    /**
     * @brief 为指定账号创建行情订阅器
     * @param pAccount
     * @return
     */
    virtual shared_ptr<OrderSubscriber> CreateMarketDataSubscriber(Account const*pAccount) = 0;

public:

    /**
     * @brief 返回指定账号对应的交易处理器
     * 如果不存在指定账号的交易处理器，并且bCreateIfNotExist为true的话，该方法为创建指定的交易处理器
     * @param pAccount
     * @param bCreateIfNotExist
     * @return
     */
    shared_ptr<OrderProcessor> GetOrderProcessor(Account const*pAccount,bool bCreateIfNotExist = true);

    /**
     * @brief GetOrderSubscriber
     * @param pAccount
     * @param CreateIfNotExist
     * @return
     */
    shared_ptr<OrderSubscriber> GetOrderSubscriber(Account const*pAccount,bool CreateIfNotExist = true);
    /**
     * @brief 返回指定账号对应的行情订阅器
     * 如果不存在指定账号的行情订阅器，并且bCreateIfNotExist为true的话，该方法为创建指定的行情订阅器
     * @param pAccount
     * @param bCreateIfNotExist
     * @return
     */
    shared_ptr<OrderSubscriber> GetMarketDataSubscriber(Account const*pAccount,bool bCreateIfNotExist = true);

    /**
     * @brief 返回的错误信息
     * @return
     */
    QString GetLastError() const;

protected:

    QString m_strError;
    QMap<QString,shared_ptr<MarketDataSubscriber>> m_mMarketDataSubscriber;
    QMap<QString,shared_ptr<OrderProcessor>> m_mOrderProcessor;
    QMap<QString,shared_ptr<OrderSubscriber>> m_mOrderSubscriber;
};

#endif // _TRACKER_PLATFORM_H_
