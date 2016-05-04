#include "AccountTrackerPosition.h"

AccountTrackerPosition::AccountTrackerPosition(
        double dPrice,size_t nQuantity,QDate const& oTradeDay,
        Instrument *pInstrument,Direction eDirection,HedgeFlag eHedgeFlag
        )
    :m_dPrice(dPrice),m_nQuantity(nQuantity),m_oTradeDay(oTradeDay),m_pInstrument(pInstrument),
     m_eDirection(eDirection),m_eHedgeFlag(eHedgeFlag)
{

}


AccountTrackerPosition::~AccountTrackerPosition()
{

}

double AccountTrackerPosition::GetPrice() const
{
    return m_dPrice;
}

size_t AccountTrackerPosition::GetQuantity() const
{
    return m_nQuantity;
}

QDate const& AccountTrackerPosition::GetTradeDay() const
{
    return m_oTradeDay;
}

Instrument const* AccountTrackerPosition::GetInstrument() const
{
    return m_pInstrument;
}

Direction AccountTrackerPosition::GetDirection() const
{
    return m_eDirection;
}

HedgeFlag AccountTrackerPosition::GetHedgeFlag() const
{
    return m_eHedgeFlag;
}

double AccountTrackerPosition::GetProfit() const
{
    double dProfit = 0;
    if(m_eDirection == dLong)
    {
        dProfit = (m_pInstrument->GetLastPrice() - m_dPrice) * m_pInstrument->GetPriceMultiple();
    }
    else
    {
        dProfit = (m_dPrice - m_pInstrument->GetLastPrice()) * m_pInstrument->GetPriceMultiple();
    }
    return dProfit;
}

