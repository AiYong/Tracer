#ifndef _TRACKER_ACCOUNTTRACKERTRADEPROCESSOR_H_
#define _TRACKER_ACCOUNTTRACKERTRADEPROCESSOR_H_

#include <QMap>
#include <QList>

#include "OrderError.h"


class Order;
class Account;
class Position;
class Instrument;
class MarketData;
class Transaction;
class AccountTrackerSetting;
class AccountTrackerPosition;

enum OrderOperationType
{
    ootSubmit,
    ootCancel,
    ootNone
};

struct OrderOperation
{
    Order const*pOrder;
    OrderOperationType eOperation;
    OrderOperation()
    {
        eOperation = ootNone;
        pOrder = nullptr;
    }

    OrderOperation(OrderOperation const& from)
    {
        this->eOperation = from.eOperation;
        this->pOrder = from.pOrder;
    }

    OrderOperation& operator=(OrderOperation const& from)
    {
        this->eOperation = from.eOperation;
        this->pOrder = from.pOrder;
    }
};


class AccountTrackerTradeProcessor
{
public:

    /**
     * @brief AccountTrackerTradeProcessor
     * @param pAccountTrackerSetting
     */
    AccountTrackerTradeProcessor(AccountTrackerSetting const *pAccountTrackerSetting);

    /**
     *
     */
    ~AccountTrackerTradeProcessor();

public:

    /**
     * @brief IsTracking
     * @param pInstrument
     * @return
     */
    bool IsTracking(Instrument const* pInstrument);

    /**
     * @brief IsTracking
     * @param pOrder
     * @return
     */
    bool IsTracking(Order const* pOrder);


public:

    /**
     * @brief ProcessMarketData
     * @param pMarketData
     * @return
     */
     QList<OrderOperation> ProcessMarketData(Instrument const*pInstrumet,MarketData const* pMarketData);


    /**
     * @brief ProcessAccountSubmitOrder
     * @param pOrder
     * @return
     */
     OrderOperation  ProcessSubmit(Order const* pOrder);


    /**
     * @brief ProcessAccountQueued
     * @param pOrder
     * @return
     */
     OrderOperation  ProcessQueued(Order const* pOrder);

    /**
     * @brief ProcessAccountOrderTrade
     * @param pOrder
     * @param pPosition
     * @return
     */
     OrderOperation  ProcessOpen(Order const* pOrder, Position const *pPosition);

    /**
     * @brief ProcessAccountOrderTrade
     * @param pOrder
     * @param pTransaction
     * @return
     */
     OrderOperation ProcessClose(Order const* pOrder, Transaction const* pTransaction);

    /**
     * @brief ProcessCancelling
     * @param pOrder
     * @return
     */
     OrderOperation  ProcessCancelling(Order const* pOrder);

    /**
     * @brief ProcessCancelled
     * @param pOrder
     * @return
     */
     OrderOperation  ProcessCancelled(Order const* pOrder);

    /**
     * @brief ProcessError
     * @param pOrder
     * @return
     */
    OrderOperation ProcessError(Order const* pOrder,OrderError eError);

private:

    void Init();
    size_t GetAvailableOpenQuantity(Order const* pOrder) const;
    size_t GetAvailableCloseQuantity() const;

    AccountTrackerSetting const*m_pAccountTrackerSetting;
    bool m_bStopOrder;
    QList<Order const*> m_lOrders;
    QMap<Order const*,Order const*> m_hTrackToTrade;
    QList<AccountTrackerPosition*> m_lPositions;
    QMap<AccountTrackerPosition*,Order*> m_hCloseOrders;
    QMap<AccountTrackerPosition*,Order*> m_hStopWinInfo;
    QMap<AccountTrackerPosition*,Order*> m_hStopLossInfo;

};

#endif // ACCOUNTTRACKERTRADEPROCESSOR_H
