#include "Order.h"
#include "Instrument.h"
#include "PositionCost.h"

Order::Order(
      int nId,
      Account *pAccount,
      Instrument *pInstrument,
      PositionCost *pPositionCost,
      QDateTime const& oTimestamp,
      Operation eOperation,
      Direction eDirection,
      HedgeFlag eHedgeFlag,
      PriceMode ePriceMode,
      size_t nQuantity,
      double dQuote,
      OrderStatus eStatus,
      size_t nTradeVolume
      )
    :m_nId(nId),
     m_pAccount(pAccount),
     m_pInstrument(pInstrument),
     m_pPositionCost(pPositionCost),
     m_oTimestamp(oTimestamp),
     m_eOperation(eOperation),
     m_eDirection(eDirection),
     m_eHedgeFlag(eHedgeFlag),
     m_ePriceMode(ePriceMode),
     m_nQuantity(nQuantity),
     m_dQuote(dQuote),
     m_eStatus(eStatus),
     m_nTradeVolume(nTradeVolume)
{
}

int Order::GetId() const
{
    return m_nId;
}

Account* Order::GetAccount() const
{
    return m_pAccount;
}

Instrument* Order::GetInstrument() const
{
    return m_pInstrument;
}

 PositionCost* Order::GetPositionCost() const
 {
     return m_pPositionCost;
 }
 
QDateTime Order::GetTimestamp() const
{
    return m_oTimestamp;
}

Operation Order::GetOperation()const
{
    return m_eOperation;
}

Direction Order::GetDirection() const
{
    return m_eDirection;
}

HedgeFlag Order::GetHedgeFlag() const
{
    return m_eHedgeFlag;
}

PriceMode Order::GetPriceMode() const
{
    return m_ePriceMode;
}

size_t Order::GetQuantity() const
{
    return m_nQuantity;
}

double Order::GetQuote() const
{
    return m_dQuote;
}

OrderStatus Order::GetStatus() const
{
    return m_eStatus;
}


double Order::GetFrezonMargin() const
{
    double dMargin = 0;
    if(m_pPositionCost->GetMarginMode() == mmRatio)
    {
        if(m_eDirection == dLong)
        {
            dMargin += m_pInstrument->GetLastPrice() * m_pPositionCost->GetLongMargin() * m_pInstrument->GetPriceMultiple();
        }
        else
        {
            dMargin += m_pInstrument->GetLastPrice() * m_pPositionCost->GetShortMargin() * m_pInstrument->GetPriceMultiple();
        }
    }
    else
    {
        if(m_eDirection == dLong)
        {
            dMargin += m_pPositionCost->GetLongMargin() * m_pInstrument->GetPriceMultiple();
        }
        else
        {
            dMargin += m_pPositionCost->GetShortMargin() * m_pInstrument->GetPriceMultiple();
        }
    }
    return dMargin;
}


size_t Order::GetTradeVolume() const
{
    return m_nTradeVolume;
}
