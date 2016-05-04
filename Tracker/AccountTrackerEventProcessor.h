#ifndef _TRACKER_ACCOUNTTRACKEREVENTPROCESSOR_H_
#define _TRACKER_ACCOUNTTRACKEREVENTPROCESSOR_H_

#include <memory>
#include <QQueue>
#include <QRunnable>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <QMetaMethod>

#include "OrderListener.h"
#include "MarketDataListener.h"
#include "AccountTrackerSetting.h"

#include "OrderProcessor.h"
#include "OrderSubscriber.h"
#include "MarketDataSubscriber.h"
#include "AccountTrackerTradeProcessor.h"

enum EventType
{
    tSubmit,
    tQueued,
    tOpen,
    tClose,
    tCancelling,
    tCancelled,
    tMarketData,
    tStartTrack,
    tStopTrack,
    tError
};

class TrackerEvent{
public:

    TrackerEvent(EventType eType);

    ~TrackerEvent();

public:

    EventType GetType() const;

private:

    EventType m_eType;

};

class TrackerOrderEvent : public TrackerEvent
{
public:

    TrackerOrderEvent(Order const*pOrder,EventType eType);

    ~TrackerOrderEvent();

public:

    Order* GetOrder() const;

private:

    Order const*m_pOrder;

};

class TrackerOrderOpenEvent : public TrackerOrderEvent
{
public:

    /**
     * @brief TrackerOrderOpenEvent
     * @param pPosition
     * @param pOrder
     * @param eType
     */
    TrackerOrderOpenEvent(Position const* pPosition,Order const* pOrder);

    /**
     *
     */
    ~TrackerOrderOpenEvent();

public:

    Position const* GetPosition() const;

private:

    Position *m_pPosition;

};

class TrackerOrderCloseEvent : public TrackerOrderEvent
{
public:

    /**
     * @brief TrackerOrderOpenEvent
     * @param pPosition
     * @param pOrder
     * @param eType
     */
    TrackerOrderCloseEvent(Transaction const* pTransaction,Order const* pOrder);

    /**
     *
     */
    ~TrackerOrderCloseEvent();


public:

    Transaction const* GetTransaction() const;

private:

    Transaction *m_pTransaction;

};

class TrackerOperationEvent : public TrackerEvent
{
public:

    TrackerOperationEvent(AccountTrackerSetting*,EventType eType);

    ~TrackerOperationEvent();

public:

    AccountTrackerSetting* GetTrackerSetting() const;

private:

    AccountTrackerSetting* m_pTrackerSetting;

};

class TrackerErrorEvent : public TrackerOrderEvent
{
public:

    TrackerErrorEvent(Order *pOrder,OrderError);

    ~TrackerErrorEvent();

public:

    OrderError GetError() const;

private:

    OrderError m_eError;
};





class TrackerMarketDataEvent : public TrackerEvent
{
public:

    TrackerMarketDataEvent(MarketData *pMarketData,Instrument *pInsrument);

    ~TrackerMarketDataEvent();

public:

    MarketData const* GetMarketData() const;


    Instrument const* GetInstrument() const;

private:

    MarketData const* m_pMarketData;
    Instrument const* m_pInstrument;

};


struct AccountTrackerTradeData
{
    std::shared_ptr<OrderProcessor> pOrderProcessor;
    std::shared_ptr<OrderSubscriber> pOrderSubscriber;
    std::shared_ptr<MarketDataSubscriber> pMarketDataSubscriber;
};


class AccountTracker;


class AccountTrackerEventProcessor : public QRunnable,public OrderListener,public MarketDataListener
{
public:

    AccountTrackerEventProcessor(AccountTracker *pAccountTracker);

    ~AccountTrackerEventProcessor();

public:

    /**
     * @brief StartTrack
     * @param pAccountTrackerSetting
     */
    void StartTrack(AccountTrackerSetting *pAccountTrackerSetting);

    /**
     * @brief StopTrack
     * @param pAccountTrackerSetting
     */
    void StopTrack(AccountTrackerSetting *pAccountTrackerSetting);

    /**
     * @brief Stop
     */
    void Stop();

public:

    void MarketDataUpdated(Instrument const* pInstrument,MarketData const* pMarketData) const;

public:

    void OnSubmited(Order const* pOrder) const;

    void OnQueued(Order const* pOrder) const;

    void OnOpen(Order const* pOrder,Position const* pPosition) const;

    void OnClose(Order const* pOrder,Transaction const* pTransaction) const;

    void OnCancelling(Order const* pOrder) const;

    void OnCancelled(Order const* pOrder) const;

    void OnError(Order const* pOrder,OrderError eError) const;

public:

    void run();

private:

    bool m_bStop;
    QMutex m_lLock;
    QWaitCondition m_cWaitCondition;
    QQueue<TrackerEvent*> m_qEvents;
    QMap<AccountTrackerSetting*,AccountTrackerTradeData> m_hTradeDatas;
    QMap<AccountTrackerSetting*,AccountTrackerTradeProcessor*> m_hTradeProcessors;

};

#endif // _TRACKER_ACCOUNTTRACKEREVENTPROCESSOR_H_
