#ifndef _TRACKER_ACCOUNTTRACKERPOSITION_H_
#define _TRACKER_ACCOUNTTRACKERPOSITION_H_

#include <QDate>

#include "Order.h"
#include "Direction.h"
#include "HedgeFlag.h"
#include "Instrument.h"
#include "PositionCost.h"

class AccountTrackerPosition
{
public:

    AccountTrackerPosition(
            double dPrice,size_t nQuantity,QDate const& oTradeDay,
            Instrument *pInstrument,Direction eDirection,HedgeFlag eHedgeFlag
            );

    AccountTrackerPosition(Position const* pPosition);

    ~AccountTrackerPosition();

public:

    double GetPrice() const;

    size_t GetQuantity() const;

    void SetQuantity(size_t nQuantity);

    QDate const& GetTradeDay() const;

    Instrument const* GetInstrument() const;

    Direction GetDirection() const;

    HedgeFlag GetHedgeFlag() const;

    double GetProfit() const;

private:

    double m_dPrice;
    size_t m_nQuantity;
    QDate m_oTradeDay;
    Instrument *m_pInstrument;
    Direction m_eDirection;
    HedgeFlag m_eHedgeFlag;

};

#endif // _TRACKER_ACCOUNTTRACKERPOSITION_H_
