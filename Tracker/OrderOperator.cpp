#include "OrderOperator.h"

#include "Order.h"
#include "Account.h"
#include "Position.h"
#include "Transaction.h"
#include "PositionCost.h"

Position* OrderOperator::Open(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    Position* pPosition = new Position(pOrder->GetAccount(),pOrder->GetInstrument(),pOrder->GetPositionCost(),oTimestamp,
                                       pOrder->GetDirection(),pOrder->GetHedgeFlag(),nQuantity,dPrice);
    pOrder->m_nTradeVolume += nQuantity;
    if(pOrder->m_nQuantity == pOrder->m_nTradeVolume)
    {
        pOrder->m_eStatus = osCompletedTraded;
    }
    else
    {
        pOrder->m_eStatus = osPartedTraded;
    }
    return pPosition;
}

Transaction* OrderOperator::Close(Position *pPosition,Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    double dOpenCommission = 0;
    double dCloseCommission = 0;
    if(pOrder->GetPositionCost()->GetCommissionMode() == cmDirect)
    {
        if(pPosition->GetDirection() == dLong)
        {
            dOpenCommission = pOrder->GetInstrument()->GetPriceMultiple() * pOrder->GetPositionCost()->GetLongOpenCommission();
            dCloseCommission = pOrder->GetInstrument()->GetPriceMultiple() * pOrder->GetPositionCost()->GetLongCloseCommission();
        }
        else
        {
            dOpenCommission = pOrder->GetInstrument()->GetPriceMultiple() * pOrder->GetPositionCost()->GetShortOpenCommission();
            dCloseCommission = pOrder->GetInstrument()->GetPriceMultiple() * pOrder->GetPositionCost()->GetShortCloseCommission();
        }
    }
    else
    {
        if(pPosition->GetDirection() == dLong)
        {
            dOpenCommission = pOrder->GetInstrument()->GetPriceMultiple() * pOrder->GetPositionCost()->GetLongOpenCommission() *
                    pPosition->GetPrice();
            dCloseCommission = pOrder->GetInstrument()->GetPriceMultiple() * pOrder->GetPositionCost()->GetLongCloseCommission() *
                    dPrice;
        }
        else
        {
            dOpenCommission = pOrder->GetInstrument()->GetPriceMultiple() * pOrder->GetPositionCost()->GetShortOpenCommission() *
                    pPosition->GetPrice();
            dCloseCommission = pOrder->GetInstrument()->GetPriceMultiple() * pOrder->GetPositionCost()->GetShortCloseCommission() *
                    dPrice;
        }
    }
    double dProfit = 0;
    if(pPosition->GetDirection() == dLong)
    {
        dProfit = (dPrice - pPosition->GetPrice()) * pOrder->GetInstrument()->GetPriceMultiple();
    }
    else
    {
       dProfit = (pPosition->GetPrice() - dPrice) * pOrder->GetInstrument()->GetPriceMultiple();
    }
    Transaction *pTransaction = new Transaction(pOrder->GetAccount(),pOrder->GetInstrument(),pPosition->GetDirection(),
                                                pOrder->GetHedgeFlag(),nQuantity,pPosition->GetPrice(),dPrice,
                                                dOpenCommission + dCloseCommission,dOpenCommission,dCloseCommission,
                                                dProfit
                                                );
    pOrder->m_nTradeVolume += nQuantity;
    if(pOrder->m_nQuantity == pOrder->m_nTradeVolume)
    {
        pOrder->m_eStatus = osCompletedTraded;
    }
    else
    {
        pOrder->m_eStatus = osPartedTraded;
    }
    return pTransaction;
}

void OrderOperator::Cancelled(Order *pOrder)
{
    if(pOrder->m_nTradeVolume > 0)
    {
        pOrder->m_eStatus = osCancelledAndPartedTraded;
    }
    else
    {
        pOrder->m_eStatus = osCancelled;
    }
}