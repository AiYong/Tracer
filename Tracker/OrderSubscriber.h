#ifndef _TRACKER_ORDERSUBSCRIBER_H_
#define _TRACKER_ORDERSUBSCRIBER_H_

#include <QList>
#include <QMutex>

#include "Order.h"
#include "Account.h"
#include "Position.h"
#include "Transaction.h"

#include "Instrument.h"
#include "OrderListener.h"

class SubscriberProcessor
{
public:

    void AddSubscriber(OrderListener *pOrderListener);

    void RemoveSubscriber(OrderListener *pOrderListener);

public:

    void PublishSubmit(Order *pOrder);

    void PublishCancelling(Order *pOrder);

    void PublishCancelled(Order *pOrder);

    void PublishError(Order *pOrder,OrderError eOrderError);

    void PublishOpen(Order *pOrder,Position *pPosition);

    void PublishClose(Order *pOrder,Transaction *pTransaction);

private:

    QMutex m_lLock;
    QList<OrderListener*> m_lListener;

};


class OrderSubscriber
{
public:

    OrderSubscriber(Account const*pAccount);

    virtual ~OrderSubscriber();

public:

    /**
     * @brief Subscribe
     * @param pInstrument
     * @param pOrderListener
     */
    virtual void Subscribe(Instrument *pInstrument , OrderListener *pOrderListener);

    /**
     * @brief UnSubscribe
     * @param pInstrument
     * @param pOrderListener
     */
    virtual void UnSubscribe(Instrument *pInstrument , OrderListener *pOrderListener);


protected:

    Account *m_pAccount;
    QMap<QString,SubscriberProcessor*> m_hProcessor;

private:

    void Init(QList<Instrument*> const& lInstrument);

};

#endif // _TRACKER_ORDERSUBSCRIBER_H_
