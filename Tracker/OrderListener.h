#ifndef _TRACKER_ORDERLISTENER_H_
#define _TRACKER_ORDERLISTENER_H_

#include <QObject>
#include "Order.h"
#include "Position.h"
#include "Transaction.h"
#include "OrderError.h"



class OrderListener
{
public:

    /**
     * @brief OrderListener
     * @param parent
     */
    OrderListener();

    /**
     * @brief ~OrderListener
     */
    virtual ~OrderListener();

public:

    /**
     * @brief 响应Order提交时间
     * 该方法被调用表示Order已经到达Broker
     * @param pOrder
     */
    virtual void OnSubmited(Order const* pOrder) const = 0;

    /**
     * @brief 响应Order排队事件
     * 该方法被调用表示Order到达交易所正在排队，等待撮合成交
     * @param pOrder
     */
    virtual void OnQueued(Order const* pOrder) const = 0;

    /**
     * @brief 响应Order成交事件
     */
    virtual void OnOpen(Order const* pOrder,Position const* pPosition) const = 0;

    /**
     * @brief OnClose
     * @param pOrder
     * @param pTransaction
     */
    virtual void OnClose(Order const* pOrder,Transaction const* pTransaction) const = 0;

    /**
     * @brief OnCancelling
     * @param pOrder
     */
    virtual void OnCancelling(Order const* pOrder) const = 0;

    /**
     * @brief 响应Order撤销事件
     * Order被撤销后该方法被调用
     * @param pOrder
     */
    virtual void OnCancelled(Order const* pOrder) const = 0;

    /**
     * @brief 响应Order错误事件
     * Order发生错误是调用该方法。
     * @param pOrder
     * @param strError
     */
    virtual void OnError(Order const* pOrder,OrderError eOrderError) const = 0;

};


#endif // _TRACKER_ORDERLISTENER_H_
