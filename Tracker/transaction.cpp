#include "Transaction.h"

Transaction::Transaction(
        Account const*pAccount,
        Instrument const*pInstrument,
        Direction eDirection,
        HedgeFlag eHedgeFlag,
        size_t nQuantity,
        double dOpenPrice,
        double dClosePrice,
        double dCommission,
        double dOpenCommission,
        double dCloseCommission,
        double dProfit,
        QDateTime const& oOpenTime,
        QDateTime const& oCloseTime
        )
    :m_pAccount(pAccount),
     m_pInstrument(pInstrument),
     m_eDirection(eDirection),
     m_eHedgeFlag(eHedgeFlag),
     m_nQuantity(nQuantity),
     m_dOpenPrice(dOpenPrice),
     m_dClosePrice(dClosePrice),
     m_dCommission(dCommission),
     m_dOpenCommission(dOpenCommission),
     m_dCloseCommission(dCloseCommission),
     m_dProfit(dProfit),
     m_oOpenTime(oOpenTime),
     m_oCloseTime(oCloseTime)
{
}


Transaction::~Transaction()
{
}

Account const* Transaction::GetAccount() const
{
    return m_pAccount;
}

Instrument const* Transaction::GetInstrument() const
{
    return m_pInstrument;
}

Direction Transaction::GetDirection() const
{
    return m_eDirection;
}

HedgeFlag Transaction::GetHedgeFlag() const
{
    return m_eHedgeFlag;
}

size_t Transaction::GetQuantity() const
{
    return m_nQuantity;
}

double Transaction::GetOpenPrice() const
{
    return m_dOpenPrice;
}

double Transaction::GetClosePrice() const
{
    return m_dClosePrice;
}

double Transaction::GetOpenCommission() const
{
    return m_dOpenCommission;
}

double Transaction::GetCloseCommission() const
{
    return m_dCloseCommission;
}

double Transaction::GetCommission() const
{
    return m_dCommission;
}

double Transaction::GetProfit() const
{
    return m_dProfit;
}

QDateTime const& Transaction::GetOpenTime() const
{
    return m_oOpenTime;
}

QDateTime const& Transaction::GetCloseTime() const
{
    return m_oCloseTime;
}
