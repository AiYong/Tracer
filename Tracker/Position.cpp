#include "Position.h"
#include "Account.h"
#include "Instrument.h"
#include "PositionCost.h"
#include "Transaction.h"

Position::Position(
    QString const& strID,
    Account const*pAccount,
    Instrument const*pInstrument,
    PositionCost const*pPositionCost,
    QDateTime const& oTimestamp,
    Direction eDirection,
    HedgeFlag eHedgeFlag,
    size_t nQuantity,
    double dPrice
    )
    :m_strID(strID),
     m_pAccount(pAccount),
     m_pInstrument(pInstrument),
     m_pPositionCost(pPositionCost),
     m_oTimestamp(oTimestamp),
     m_eDirection(eDirection),
     m_eHedgeFlag(eHedgeFlag),
     m_nQuantity(nQuantity),
     m_dPrice(dPrice)
{
}

Position::~Position()
{

}

QString const& Position::GetID() const
{
    return m_strID;
}

Account const* Position::GetAccount() const
{
    return m_pAccount;
}

Instrument const* Position::GetInstrument() const
{
    return m_pInstrument;
}

QDateTime Position::GetTimestamp() const
{
    return m_oTimestamp;
}

Direction Position::GetDirection() const
{
    return m_eDirection;
}

HedgeFlag Position::GetHedgeFlag() const
{
    return m_eHedgeFlag;
}

size_t Position::GetQuantity() const
{
    return m_nQuantity;
}

double Position::GetPrice() const
{
    return m_dPrice;
}

double Position::GetCommission() const
{
    return GetCommission(m_dPrice);
}



double Position::GetFrezonMargin() const
{
    double dMargin = GetCommission();
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


double Position::GetTradeDayProfit() const
{
    double dProfit = 0;
    if(m_pInstrument->GetTradeDay() == m_oTimestamp.date())
    {
        if(m_eDirection == dLong)
        {
            dProfit = (m_pInstrument->GetLastPrice() - m_dPrice) * m_pInstrument->GetPriceMultiple();
        }
        else
        {
            dProfit = (m_dPrice - m_pInstrument->GetLastPrice()) * m_pInstrument->GetPriceMultiple();
        }
    }
    else
    {
        if(m_eDirection == dLong)
        {
            dProfit = (m_pInstrument->GetLastPrice() - m_pInstrument->GetPreSuttlementPrice()) * m_pInstrument->GetPriceMultiple();
        }
        else
        {
            dProfit = (m_pInstrument->GetPreSuttlementPrice() - m_pInstrument->GetLastPrice()) * m_pInstrument->GetPriceMultiple();
        }
    }
    return dProfit;
}

double Position::GetTotalProfit() const
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

Transaction* Position::Close(QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    double dCloseCommission = GetCommission(dPrice);
    double dProfit = 0;
    if(m_eDirection == dLong)
    {
        dProfit = (m_dPrice - dPrice) * m_pInstrument->GetPriceMultiple();
    }
    else
    {
        dProfit = (dPrice - m_dPrice) * m_pInstrument->GetPriceMultiple();
    }
    Transaction *pTransaction = new Transaction(m_pAccount,m_pInstrument,m_eDirection,m_eHedgeFlag,
                                                nQuantity,m_dPrice,dPrice,m_dCommission + dCloseCommission,
                                                m_dCommission,dCloseCommission,dProfit,m_oTimestamp,oTimestamp);
    return pTransaction;
}


double Position::GetCommission(double dPrice) const
{
    double dCommission = 0;
    if(m_pPositionCost->GetCommissionMode() == cmRatio)
    {
        if(m_eDirection == dLong)
        {
            dCommission = dPrice * m_pPositionCost->GetLongOpenCommission() * m_pInstrument->GetPriceMultiple();
        }
        else
        {
            dCommission = dPrice * m_pPositionCost->GetShortOpenCommission() * m_pInstrument->GetPriceMultiple();
        }
    }
    else
    {
        if(m_eDirection == dLong)
        {
            dCommission = m_pPositionCost->GetLongOpenCommission() * m_pInstrument->GetPriceMultiple();
        }
        else
        {
            dCommission = m_pPositionCost->GetShortOpenCommission() * m_pInstrument->GetPriceMultiple();
        }
    }
    return dCommission;
}
