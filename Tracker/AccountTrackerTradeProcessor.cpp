#include "AccountTrackerTradeProcessor.h"
#include "Account.h"
#include "Position.h"
#include "Transaction.h"
#include "AccountTrackerSetting.h"
#include "AccountTrackerPosition.h"

#include "ObjectPersistManager.h"


AccountTrackerTradeProcessor::AccountTrackerTradeProcessor(AccountTrackerSetting const*pAccountTrackerSetting)
    :m_pAccountTrackerSetting(pAccountTrackerSetting)
{

}


AccountTrackerTradeProcessor::~AccountTrackerTradeProcessor()
{

}

bool AccountTrackerTradeProcessor::IsTracking(Instrument const* pInstrument)
{
    return m_pAccountTrackerSetting->GetInstrument()->GetID() == pInstrument->GetID();
}

bool AccountTrackerTradeProcessor::IsTracking(Order const* pOrder)
{
    if(!IsTracking(pOrder->GetInstrument()))
    {
        return false;
    }
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTrackAccount()->GetID())
    {
        return true;
    }
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTradeAccount()->GetID())
    {
        return true;
    }
    return false;
}

QList<OrderOperation> AccountTrackerTradeProcessor::ProcessMarketData(Instrument const*pInstrumet,MarketData const* pMarketData)
{
    QList<OrderOperation> oResult;

    for(int nCount = 0 ; nCount < m_lPositions.size() ; nCount++)
    {
        AccountTrackerPosition *pPosition = m_lPositions[nCount];
        if(m_pAccountTrackerSetting->IsStopWin())
        {
            double dStopWinValue = 0;
            switch (m_pAccountTrackerSetting->GetStopWinPriceMode()) {
            case swpmDirect:
            {
                dStopWinValue = m_pAccountTrackerSetting->GetStopWinPrice();
            }
                break;
            case swpmRatio:
            {
                dStopWinValue = pPosition->GetPrice() * m_pAccountTrackerSetting->GetStopLossPrice();
            }
                break;
            default:
                break;
            }
            if( dStopWinValue < pPosition->GetProfit())
            {
                //止盈时，如果已经有止损单了，先撤销
                if(m_hStopLossInfo.contains(pPosition))
                {
                    OrderOperation oOrderOperation;
                    oOrderOperation.eOperation = ootCancel;
                    oOrderOperation.pOrder = m_hStopLossInfo[pPosition];
                    oResult.append(oOrderOperation);
                    continue;
                }
                //止盈时，如果已经有平仓单了，先撤销
                if(m_hCloseOrders.contains(pPosition))
                {
                    OrderOperation oOrderOperation;
                    oOrderOperation.eOperation = ootCancel;
                    oOrderOperation.pOrder = m_hCloseOrders[pPosition];
                    oResult.append(oOrderOperation);
                    continue;
                }
                if(!m_hStopWinInfo.contains(pPosition))
                {
                   Direction eDirection = pPosition->GetDirection();
                   HedgeFlag eHedgeFlag = pPosition->GetHedgeFlag();
                   Instrument const*pInstrument = pPosition->GetInstrument();
                   size_t nQuantity = pPosition->GetQuantity();
                   PriceMode ePriceMode = pmMarketPrice;
                   double dQuote = 0;
                   if(m_pAccountTrackerSetting->GetStopWinOrderType() == swotLimitPrice)
                   {
                       ePriceMode = pmLimitPrice;
                       if(m_pAccountTrackerSetting->GetStopWinOrderLimitPriceMode() == swolpmDelta)
                       {
                           dQuote = pInstrument->GetLastPrice() + m_pAccountTrackerSetting->GetStopWinOrderLimitPriceDelta();
                       }
                       else
                       {
                           dQuote = pInstrument->GetLastPrice();
                       }
                   }
                   Account *pTradeAccount = m_pAccountTrackerSetting->GetTradeAccount();
                   Order *pOrder = pTradeAccount->CreateOrder(pInstrument,eDirection,opClose,eHedgeFlag,ePriceMode,nQuantity,dQuote);
                   m_hStopWinInfo.insert(pPosition,pOrder);
                   m_lOrders.append(pOrder);
                   OrderOperation oOrderOperation;
                   oOrderOperation.eOperation = ootSubmit;
                   oOrderOperation.pOrder = pOrder;
                   oResult.append(oOrderOperation);
                   continue;
                }
            }
            else
            {
                //Todo 盈利小于止盈值是否撤单

            }
        }
        if(m_pAccountTrackerSetting->IsStopLoss())
        {
            double dStopLossValue = 0;

            switch (m_pAccountTrackerSetting->GetStopLossPriceMode()) {
            case slpmDirect:
            {
                dStopLossValue = -1 * m_pAccountTrackerSetting->GetStopLossPrice();
            }
                break;
            case slpmRatio:
            {
                dStopLossValue = -1 * pPosition->GetPrice() * m_pAccountTrackerSetting->GetStopLossPrice();
            }
                break;
            default:
                break;
            }

            if(dStopLossValue > pPosition->GetProfit() )
            {
                //止盈时，如果已经有止损单了，先撤销
                if(m_hStopWinInfo.contains(pPosition))
                {
                    OrderOperation oOrderOperation;
                    oOrderOperation.eOperation = ootCancel;
                    oOrderOperation.pOrder = m_hStopWinInfo[pPosition];
                    oResult.append(oOrderOperation);
                    continue;
                }
                //止盈时，如果已经有平仓单了，先撤销
                if(m_hCloseOrders.contains(pPosition))
                {
                    OrderOperation oOrderOperation;
                    oOrderOperation.eOperation = ootCancel;
                    oOrderOperation.pOrder = m_hCloseOrders[pPosition];
                    oResult.append(oOrderOperation);
                    continue;
                }
                if(m_hStopLossInfo.contains(pPosition))
                {
                    Direction eDirection = pPosition->GetDirection();
                    HedgeFlag eHedgeFlag = pPosition->GetHedgeFlag();
                    Instrument const*pInstrument = pPosition->GetInstrument();
                    size_t nQuantity = pPosition->GetQuantity();
                    PriceMode ePriceMode = pmMarketPrice;
                    double dQuote = 0;
                    if(m_pAccountTrackerSetting->GetStopLossOrderType() == slotLimitPrice)
                    {
                        ePriceMode = pmLimitPrice;
                        if(m_pAccountTrackerSetting->GetStopLossOrderLimitPriceMode() == slolpmDelta)
                        {
                            dQuote = pInstrument->GetLastPrice() + m_pAccountTrackerSetting->GetStopLossOrderLimitPriceDelta();
                        }
                        else
                        {
                            dQuote = pInstrument->GetLastPrice();
                        }
                    }
                    Account *pTradeAccount = m_pAccountTrackerSetting->GetTradeAccount();
                    Order *pOrder = pTradeAccount->CreateOrder(pInstrument,eDirection,opClose,eHedgeFlag,ePriceMode,nQuantity,dQuote);
                    m_hStopLossInfo.insert(pPosition,pOrder);
                    m_lOrders.append(pOrder);
                    OrderOperation oOrderOperation;
                    oOrderOperation.eOperation = ootSubmit;
                    oOrderOperation.pOrder = pOrder;
                    oResult.append(oOrderOperation);
                    continue;
                }
            }
            continue;
        }
    }
    return oResult;
}


OrderOperation AccountTrackerTradeProcessor::ProcessSubmit(Order const* pOrder)
{
    OrderOperation oResult;
    //监听账号报单插入事件
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTrackAccount()->GetID() &&
       m_pAccountTrackerSetting->GetOrderSubmitMode() == osmSubmit )
    {
        if(pOrder->GetOperation() == opOpen)
        {
            size_t nAvailableOpenQuantity = GetAvailableOpenQuantity(pOrder);
            if(nAvailableOpenQuantity > 0)
            {
                size_t nQuantity = pOrder->GetQuantity() > nAvailableOpenQuantity ? nAvailableOpenQuantity : pOrder->GetQuantity();
                Direction eDirection = pOrder->GetDirection();
                HedgeFlag eHedgeFlag = pOrder->GetHedgeFlag();
                Operation eOperation = opOpen;
                PriceMode ePriceMode = pmMarketPrice;
                double dQuote = pOrder->GetInstrument()->GetLastPrice();
                if(m_pAccountTrackerSetting->GetOpenPriceMode() == opmLimitPrice)
                {
                    ePriceMode = pmLimitPrice;
                    if(m_pAccountTrackerSetting->GetOpenLimitPriceMode() == olpmDelta)
                    {
                        dQuote = m_pAccountTrackerSetting->GetOpenLimitPriceDelta() + pOrder->GetInstrument()->GetLastPrice();
                    }
                    else
                    {
                        dQuote = pOrder->GetInstrument()->GetLastPrice();
                    }
                }
                Order *pNewOrder = m_pAccountTrackerSetting->GetTradeAccount()->CreateOrder(pOrder->GetInstrument(),eDirection,eOperation,eHedgeFlag,ePriceMode,nQuantity,dQuote);
                m_lOrders.append(pNewOrder);
                oResult.eOperation = ootSubmit;
                oResult.pOrder = pNewOrder;
            }
        }
        else
        {
            size_t nAvailableCloseQuantity = GetAvailableCloseQuantity();
            if(nAvailableCloseQuantity > 0)
            {
                size_t nQuantity = pOrder->GetQuantity() > nAvailableCloseQuantity ? nAvailableCloseQuantity : pOrder->GetQuantity();
                Direction eDirection = pOrder->GetDirection();
                HedgeFlag eHedgeFlag = pOrder->GetHedgeFlag();
                Operation eOperation = opClose;
                PriceMode ePriceMode = pmMarketPrice;
                double dQuote = pOrder->GetInstrument()->GetLastPrice();
                if(m_pAccountTrackerSetting->GetClosePriceMode() == cpmLimitPrice)
                {
                    ePriceMode = pmLimitPrice;
                    if(m_pAccountTrackerSetting->GetCloseLimitPriceMode() == clpmDelta)
                    {
                        dQuote = m_pAccountTrackerSetting->GetCloseLimitPriceDelta() + pOrder->GetInstrument()->GetLastPrice();
                    }
                    else
                    {
                        dQuote = pOrder->GetInstrument()->GetLastPrice();
                    }
                }
                Order *pNewOrder = m_pAccountTrackerSetting->GetTradeAccount()->CreateOrder(pOrder->GetInstrument(),eDirection,eOperation,eHedgeFlag,ePriceMode,nQuantity,dQuote);
                m_lOrders.append(pNewOrder);
                oResult.eOperation = ootSubmit;
                oResult.pOrder = pNewOrder;
            }
        }
        return oResult;
    }

    return oResult;
}

OrderOperation AccountTrackerTradeProcessor::ProcessQueued(Order const* pOrder)
{
    OrderOperation oResult;
    //监听账号报单插入事件
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTrackAccount()->GetID() &&
       m_pAccountTrackerSetting->GetOrderSubmitMode() == osmQueued)
    {
        if(pOrder->GetOperation() == opOpen)
        {
            size_t nAvailableOpenQuantity = GetAvailableOpenQuantity(pOrder);
            if(nAvailableOpenQuantity > 0)
            {
                size_t nQuantity = pOrder->GetQuantity() > nAvailableOpenQuantity ? nAvailableOpenQuantity : pOrder->GetQuantity();
                Direction eDirection = pOrder->GetDirection();
                HedgeFlag eHedgeFlag = pOrder->GetHedgeFlag();
                Operation eOperation = opOpen;
                PriceMode ePriceMode = pmMarketPrice;
                double dQuote = pOrder->GetInstrument()->GetLastPrice();
                if(m_pAccountTrackerSetting->GetOpenPriceMode() == opmLimitPrice)
                {
                    ePriceMode = pmLimitPrice;
                    if(m_pAccountTrackerSetting->GetOpenLimitPriceMode() == olpmDelta)
                    {
                        dQuote = m_pAccountTrackerSetting->GetOpenLimitPriceDelta() + pOrder->GetInstrument()->GetLastPrice();
                    }
                    else
                    {
                        dQuote = pOrder->GetInstrument()->GetLastPrice();
                    }
                }
                Order *pNewOrder = m_pAccountTrackerSetting->GetTradeAccount()->CreateOrder(pOrder->GetInstrument(),eDirection,eOperation,eHedgeFlag,ePriceMode,nQuantity,dQuote);
                m_lOrders.append(pNewOrder);
                oResult.eOperation = ootSubmit;
                oResult.pOrder = pNewOrder;
            }
        }
        else
        {
            size_t nAvailableCloseQuantity = GetAvailableCloseQuantity();
            if(nAvailableCloseQuantity > 0)
            {
                size_t nQuantity = pOrder->GetQuantity() > nAvailableCloseQuantity ? nAvailableCloseQuantity : pOrder->GetQuantity();
                Direction eDirection = pOrder->GetDirection();
                HedgeFlag eHedgeFlag = pOrder->GetHedgeFlag();
                Operation eOperation = opClose;
                PriceMode ePriceMode = pmMarketPrice;
                double dQuote = pOrder->GetInstrument()->GetLastPrice();
                if(m_pAccountTrackerSetting->GetClosePriceMode() == cpmLimitPrice)
                {
                    ePriceMode = pmLimitPrice;
                    if(m_pAccountTrackerSetting->GetCloseLimitPriceMode() == clpmDelta)
                    {
                        dQuote = m_pAccountTrackerSetting->GetCloseLimitPriceDelta() + pOrder->GetInstrument()->GetLastPrice();
                    }
                    else
                    {
                        dQuote = pOrder->GetInstrument()->GetLastPrice();
                    }
                }
                Order *pNewOrder = m_pAccountTrackerSetting->GetTradeAccount()->CreateOrder(pOrder->GetInstrument(),eDirection,eOperation,eHedgeFlag,ePriceMode,nQuantity,dQuote);
                m_lOrders.append(pNewOrder);
                oResult.eOperation = ootSubmit;
                oResult.pOrder = pNewOrder;
            }
        }
        return oResult;
    }

    return oResult;
}

OrderOperation AccountTrackerTradeProcessor::ProcessOpen(Order const* pOrder, Position const*pPosition)
{
    OrderOperation oResult;
    //监听账号报单插入事件
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTrackAccount()->GetID() &&
       m_pAccountTrackerSetting->GetOrderSubmitMode() == osmTraded )
    {
        size_t nAvailableOpenQuantity = GetAvailableOpenQuantity(pOrder);
        if(nAvailableOpenQuantity > 0)
        {
            size_t nQuantity = pOrder->GetQuantity() > nAvailableOpenQuantity ? nAvailableOpenQuantity : pOrder->GetQuantity();
            Direction eDirection = pOrder->GetDirection();
            HedgeFlag eHedgeFlag = pOrder->GetHedgeFlag();
            Operation eOperation = opOpen;
            PriceMode ePriceMode = pmMarketPrice;
            double dQuote = pOrder->GetInstrument()->GetLastPrice();
            if(m_pAccountTrackerSetting->GetOpenPriceMode() == opmLimitPrice)
            {
                ePriceMode = pmLimitPrice;
                if(m_pAccountTrackerSetting->GetOpenLimitPriceMode() == olpmDelta)
                {
                    dQuote = m_pAccountTrackerSetting->GetOpenLimitPriceDelta() + pOrder->GetInstrument()->GetLastPrice();
                }
                else
                {
                    dQuote = pOrder->GetInstrument()->GetLastPrice();
                }
            }
            Order *pNewOrder = m_pAccountTrackerSetting->GetTradeAccount()->CreateOrder(pOrder->GetInstrument(),eDirection,eOperation,eHedgeFlag,ePriceMode,nQuantity,dQuote);
            m_lOrders.append(pNewOrder);
            oResult.eOperation = ootSubmit;
            oResult.pOrder = pNewOrder;
        }
        return oResult;
    }

    //交易账号报单成交事件
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTradeAccount()->GetID())
    {
        AccountTrackerPosition *pTrackerPosition = new AccountTrackerPosition(pPosition);
        m_lPositions.append(pTrackerPosition);
        ObjectPersistManager::GetInstance()->Save(pTrackerPosition);
    }
    return oResult;
}

OrderOperation AccountTrackerTradeProcessor::ProcessClose(Order const* pOrder, Transaction const*pTransaction)
{
    OrderOperation oResult;
    //监听账号报单插入事件
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTrackAccount()->GetID() &&
       m_pAccountTrackerSetting->GetOrderSubmitMode() == osmTraded )
    {
        size_t nAvailableCloseQuantity = GetAvailableCloseQuantity();
        if(nAvailableCloseQuantity > 0)
        {
            size_t nQuantity = pOrder->GetQuantity() > nAvailableCloseQuantity ? nAvailableCloseQuantity : pOrder->GetQuantity();
            Direction eDirection = pOrder->GetDirection();
            HedgeFlag eHedgeFlag = pOrder->GetHedgeFlag();
            Operation eOperation = opClose;
            PriceMode ePriceMode = pmMarketPrice;
            double dQuote = pOrder->GetInstrument()->GetLastPrice();
            if(m_pAccountTrackerSetting->GetClosePriceMode() == cpmLimitPrice)
            {
                ePriceMode = pmLimitPrice;
                if(m_pAccountTrackerSetting->GetCloseLimitPriceMode() == clpmDelta)
                {
                    dQuote = m_pAccountTrackerSetting->GetCloseLimitPriceDelta() + pOrder->GetInstrument()->GetLastPrice();
                }
                else
                {
                    dQuote = pOrder->GetInstrument()->GetLastPrice();
                }
            }
            Order *pNewOrder = m_pAccountTrackerSetting->GetTradeAccount()->CreateOrder(pOrder->GetInstrument(),eDirection,eOperation,eHedgeFlag,ePriceMode,nQuantity,dQuote);
            m_lOrders.append(pNewOrder);
            oResult.eOperation = ootSubmit;
            oResult.pOrder = pNewOrder;
        }
        return oResult;
    }

    //交易账号报单成交事件
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTradeAccount()->GetID())
    {
        auto iPos = m_lPositions.begin();
        size_t nQuantity = pTransaction->GetQuantity();
        while(iPos != m_lPositions.end() && nQuantity > 0)
        {
            AccountTrackerPosition *pTrackerPosition = *iPos;
            if(pTrackerPosition->GetDirection() == pTransaction->GetDirection())
            {
                size_t nPositionQuantity = pTrackerPosition->GetQuantity();
                if(nQuantity >= nPositionQuantity)
                {
                    iPos = m_lPositions.erase(iPos);
                    ObjectPersistManager::GetInstance()->Remove(pTrackerPosition);
                    delete pTrackerPosition;
                }
                else
                {
                    pTrackerPosition->SetQuantity(nPositionQuantity - nQuantity);
                    ObjectPersistManager::GetInstance()->Update(pTrackerPosition);
                    break;
                }
            }
        }
    }
    return oResult;
}

OrderOperation AccountTrackerTradeProcessor::ProcessCancelling(Order const* pOrder)
{
    OrderOperation oResult;
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTrackAccount()->GetID())
    {
        Order const*pTradeAccountOrder = m_hTrackToTrade[pOrder];
        if(pTradeAccountOrder && (pTradeAccountOrder->GetStatus() != osCancelling || pTradeAccountOrder->GetStatus() != osCancelled ))
        {
            oResult.eOperation= ootCancel;
            oResult.pOrder = pTradeAccountOrder;
        }
    }
    return oResult;
}

OrderOperation AccountTrackerTradeProcessor::ProcessCancelled(Order const* pOrder)
{
    OrderOperation oResult;
    if(pOrder->GetAccount()->GetID() == m_pAccountTrackerSetting->GetTradeAccount()->GetID())
    {
        Order const*pTrackAccountOrder =  m_hTrackToTrade.key(pOrder);
        if(pTrackAccountOrder)
        {
            m_hTrackToTrade.remove(pTrackAccountOrder);
        }
        m_lOrders.removeOne(pOrder);
    }
    return oResult;
}


OrderOperation AccountTrackerTradeProcessor::ProcessError(Order const* pOrder,OrderError eError)
{
    return OrderOperation();
}

void AccountTrackerTradeProcessor::Init()
{
    ObjectPersistManager::GetInstance()->Load(m_pAccountTrackerSetting,m_lPositions);
}

size_t AccountTrackerTradeProcessor::GetAvailableOpenQuantity(Order const* pOrder) const
{
    size_t nAvailableQuantity = 0;
    size_t nCurrentQuantity = 0;
    for( int nCount = 0 ; nCount < m_lPositions.size() ; nCount++ )
    {
        AccountTrackerPosition *pPosition = m_lPositions[nCount];
        nCurrentQuantity += pPosition->GetQuantity();
    }

    for( int nCount = 0 ; nCount < m_lOrders.size() ; nCount++ )
    {
        Order const*pCurOrder = m_lOrders[nCount];
        if(pCurOrder->GetOperation() == opOpen)
        {
            nCurrentQuantity += pCurOrder->GetQuantity();
        }
    }

    switch (m_pAccountTrackerSetting->GetPositionLimitMode())
    {
    case plmMargin:
    {
        double dAvailableMargin = m_pAccountTrackerSetting->GetPositionLimit();
        if(m_pAccountTrackerSetting->GetOpenPriceMode() == opmMarketPrice)
        {
            nAvailableQuantity = m_pAccountTrackerSetting->GetTradeAccount()->GetAvailableQuantityWithMargin(m_pAccountTrackerSetting->GetInstrument(),
                                                                              pOrder->GetDirection(),pOrder->GetHedgeFlag(),
                                                                              dAvailableMargin);
        }
        else
        {
            double dQuote = m_pAccountTrackerSetting->GetInstrument()->GetLastPrice();
            if(m_pAccountTrackerSetting->GetOpenLimitPriceMode() == olpmDelta)
            {
                dQuote += m_pAccountTrackerSetting->GetCloseLimitPriceDelta();
            }
            nAvailableQuantity = m_pAccountTrackerSetting->GetTradeAccount()->GetAvailableQuantityWithMargin(m_pAccountTrackerSetting->GetInstrument(),
                                                                              pOrder->GetDirection(),pOrder->GetHedgeFlag(),
                                                                              dAvailableMargin,dQuote);
        }
        if(nAvailableQuantity > nCurrentQuantity)
        {
            return nAvailableQuantity - nCurrentQuantity;
        }
    }
        break;
    case plmQuantity:
    {
        if(m_pAccountTrackerSetting->GetOpenPriceMode() == opmMarketPrice)
        {
            nAvailableQuantity = m_pAccountTrackerSetting->GetTradeAccount()->GetAvailableQuantity(m_pAccountTrackerSetting->GetInstrument(),
                                                                              pOrder->GetDirection(),pOrder->GetHedgeFlag());
        }
        else
        {
            double dQuote = m_pAccountTrackerSetting->GetInstrument()->GetLastPrice();
            if(m_pAccountTrackerSetting->GetOpenLimitPriceMode() == olpmDelta)
            {
                dQuote += m_pAccountTrackerSetting->GetCloseLimitPriceDelta();
            }
            nAvailableQuantity = m_pAccountTrackerSetting->GetTradeAccount()->GetAvailableQuantity(m_pAccountTrackerSetting->GetInstrument(),
                                                                              pOrder->GetDirection(),pOrder->GetHedgeFlag(),
                                                                              dQuote);
        }
        if(nAvailableQuantity > nCurrentQuantity)
        {
            return nAvailableQuantity - nCurrentQuantity;
        }
    }
        break;
    default:
        break;
    }
    return 0;
}



size_t AccountTrackerTradeProcessor::GetAvailableCloseQuantity() const
{
    size_t nCurrentQuantity = 0;
    for( int nCount = 0 ; nCount < m_lPositions.size() ; nCount++ )
    {
        AccountTrackerPosition *pPosition = m_lPositions[nCount];
        nCurrentQuantity += pPosition->GetQuantity();
    }

    for( int nCount = 0 ; nCount < m_lOrders.size() ; nCount++ )
    {
        Order const*pOrder = m_lOrders[nCount];
        if(pOrder->GetOperation() == opClose)
        {
            nCurrentQuantity -= pOrder->GetQuantity();
        }
    }
    return nCurrentQuantity;
}
