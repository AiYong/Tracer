#include "PositionCost.h"

PositionCost::PositionCost(
          Instrument *pInstrument,
          CommissionMode eCommissionMode,
          double dLongOpenCommission,
          double dShortOpenCommission,
          double dLongCloseCommission,
          double dShortCloseCommission,
          MarginMode eMarginMode,
          double dLongMargin,
          double dShortMargin
        )
    :m_pInstrument(pInstrument),
     m_eCommissionMode(eCommissionMode),
     m_dLongOpenCommission(dLongOpenCommission),
     m_dShortOpenCommission(dShortOpenCommission),
     m_dLongCloseCommission(dLongCloseCommission),
     m_dShortCloseCommission(dShortCloseCommission),
     m_eMarginMode(eMarginMode),
     m_dLongMargin(dLongMargin),
     m_dShortMargin(dShortMargin)
{
}

Instrument* PositionCost::GetInstrument() const
{
    return m_pInstrument;
}

CommissionMode PositionCost::GetCommissionMode() const
{
    return m_eCommissionMode;
}


double PositionCost::GetLongOpenCommission() const
{
    return m_dLongOpenCommission;
}


double PositionCost::GetShortOpenCommission() const
{
    return m_dShortOpenCommission;
}


double PositionCost::GetLongCloseCommission() const
{
    return m_dLongCloseCommission;
}


double PositionCost::GetShortCloseCommission() const
{
    return m_dShortCloseCommission;
}


MarginMode PositionCost::GetMarginMode() const
{
    return m_eMarginMode;
}


double PositionCost::GetLongMargin() const
{
    return m_dLongMargin;
}


double PositionCost::GetShortMargin() const
{
    return m_dShortMargin;
}
