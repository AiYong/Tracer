#ifndef _TRACKER_TRACKSERVICE_H_
#define _TRACKER_TRACKSERVICE_H_

#include <QList>
#include <QString>

#include "Instrument.h"
#include "MarketDataListener.h"
#include "AccountResourceManager.h"


class TrackService
{
public:

    explicit TrackService();

    /**
     * @brief ~TrackService
     */
    ~TrackService();

public:

    /**
     * @brief SubscribeMarketData
     * @param lInstruments
     * @param pMarketDataListener
     */
    void SubscribeMarketData(QList<Instrument*> const& lInstruments,MarketDataListener *pMarketDataListener);

    /**
     * @brief UnsubscribeMarketDat
     * @param lInstruments
     * @param pMarketDataListener
     */
    void UnsubscribeMarketDat(QList<Instrument*> const& lInstruments,MarketDataListener *pMarketDataListener);

};

#endif // _TRACKER_TRACKSERVICE_H_
