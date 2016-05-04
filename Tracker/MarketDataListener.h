#ifndef _TRACKER_MARKETDATALISTENER_H_
#define _TRACKER_MARKETDATALISTENER_H_

#include <QObject>

#include "MarketData.h"
#include "Instrument.h"

/**
 * @brief 行情监听器
 */
class MarketDataListener
{
public:

    /**
     * @brief 析构函数
     */
    virtual ~MarketDataListener();

public:

    /**
     * @brief 行情更新回调
     * @param pInstrument
     * @param pMarketData
     */
    virtual void MarketDataUpdated(Instrument const*pInstrument,MarketData const*pMarketData) const = 0 ;

};

#endif // _TRACKER_MARKETDATALISTENER_H_
