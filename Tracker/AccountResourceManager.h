#ifndef _TRACKER_ACCOUNTREOURCEMANAGER_H_
#define _TRACKER_ACCOUNTREOURCEMANAGER_H_

#include <QMap>
#include <QList>
#include <QString>

#include "PlatformFactory.h"

class Account;
class Instrument;
class PositionCost;

class AccountResourceManager
{
public:

    static AccountResourceManager* GetInstance();

public:

    /**
     * @brief GetAccountInfo
     * @return
     */
    shared_ptr<AccountInfo> GetAccountInfo();

    /**
     * @brief 返回指定账号的Order处理器
     * @param pAccount
     * @return
     */
    shared_ptr<OrderProcessor> GetOrderProcessor(Account *pAccount);

    /**
     * @brief 返回指定账号的行情订阅器
     * @param pAccount
     * @return
     */
    shared_ptr<MarketDataSubscriber> GetMarketDataSubscriber(Account *pAccount);

    /**
     * @brief 返回账号Order订阅器
     * @param pAccount
     * @return
     */
    shared_ptr<OrderSubscriber> GetOrderSubscriber(Account *pAccount);

    /**
     * @brief GetLastError
     * @return
     */
    QString const& GetLastError() const;

private:

    QMap<QString,shared_ptr<AccountInfo>> m_hAccountInfo;
    QMap<QString,shared_ptr<OrderProcessor>> m_hOrderProcessor;
    QMap<QString,shared_ptr<MarketDataSubscriber>> m_hMarketDaraSubscriber;
    QMap<QString,shared_ptr<OrderSubscriber>> m_hOrderSubscriber;

};

#endif // _TRACKER_ACCOUNTREOURCEMANAGER_H_
