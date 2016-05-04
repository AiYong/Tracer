#ifndef _TRACKER_MARKETDATASUBSCRIBER_H_
#define _TRACKER_MARKETDATASUBSCRIBER_H_

#include <QObject>

#include "Instrument.h"
#include "MarketDataListener.h"

/**
 * @brief 行情订阅器
 */
class MarketDataSubscriber : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief 构造函数
     * @param parent
     */
    explicit MarketDataSubscriber(QObject *parent = 0);

    /**
     * @brief 析构函数
     */
    virtual ~MarketDataSubscriber();


public:

    /**
     * @brief 订阅行情
     * @param pListener
     * @param lstInstrument
     */
    virtual void Subscribe(MarketDataListener *pListener, QList<Instrument*> const& lstInstrument) = 0;

    /**
     * @brief 取消订阅
     * @param pListener
     * @param lstInstrument
     */
    virtual void UnSubscribe(MarketDataListener *pListener,QList<Instrument*> const& lstInstrument) = 0;

};

#endif // _TRACKER_MARKETDATASUBSCRIBER_H_
