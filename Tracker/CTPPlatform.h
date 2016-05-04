#ifndef _TRACKER_CTPPLATFORM_H_
#define _TRACKER_CTPPLATFORM_H_

#include "Platform.h"

class CTPPlatform : public Platform
{
public:

    CTPPlatform();

    ~CTPPlatform();

public:

    shared_ptr<AccountInfo> QueryAccountInfo(Account const*pAccount) ;

    shared_ptr<OrderProcessor> CreateOrderProcessor(Account const*pAccount);

    shared_ptr<OrderSubscriber> CreateOrderSubsriber(Account const*pAccount);

    shared_ptr<MarketDataSubscriber> CreateMarketDataSubscriber(Account const*pAccount);

private:

    shared_ptr<MarketDataSubscriber> m_pMarketDataSubscriber;

};

#endif // _TRACKER_CTPPLATFORM_H_
