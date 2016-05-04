#include "Account.h"
#include "Order.h"
#include "Position.h"
#include "Instrument.h"
#include "PositionCost.h"
#include "OrderOperator.h"
#include "AccountResourceManager.h"
#include "TradeResourceManager.h"

#include <math.h>


Account::Account(
    QString const& strId,
    QString const& strName,
    QString const& strPassword,
    Broker *pBroker
    )
    :m_strId(strId),
     m_strName(strName),
     m_strPassword(strPassword),
     m_pBroker(pBroker)
{

}

Account::~Account()
{

}

QString const& Account::GetId() const
{
    return m_strId;
}

QString const& Account::GetName() const
{
    return m_strName;
}

QString const& Account::GetPassword() const
{
    return m_strPassword;
}

Broker* Account::GetBroker() const
{
    return m_pBroker;
}

double Account::GetDynamicMargin() const
{
    double dMargin = m_dStaticMargin;
    for(auto InstrumentIter = m_mPositions.begin(); InstrumentIter != m_mPositions.end(); InstrumentIter++)
    {
        QList<Position*> const&lPositions = *InstrumentIter;
        for(auto PositionIter = lPositions.begin() ; PositionIter != lPositions.end() ; PositionIter++)
        {
            Position *pPosition = *PositionIter;
            dMargin = dMargin + pPosition->GetTradeDayProfit();
        }
    }
    return dMargin;
}

double Account::GetStaticMargin() const
{
    return m_dStaticMargin;
}

double Account::GetAvailableMargin() const
{
    return m_dStaticMargin - GetFrezonMargin();
}

double Account::GetFrezonMargin() const
{
    double dMargin = 0;
    QMap<Instrument*,QList<Position*>> mPositions = GetPositions();
    for(auto iInstrumentPosition = mPositions.begin() ; iInstrumentPosition != mPositions.end() ; iInstrumentPosition++)
    {
        QList<Position*> const&lPositions = iInstrumentPosition.value();
        for(auto iPosition = lPositions.begin(); iPosition != lPositions.end() ;iPosition++)
        {
            Position *pPosition = *iPosition;
            dMargin += pPosition->GetFrezonMargin();
        }
    }
    QMap<Instrument*,QList<Order*>> mPositions = GetRunningOrders();
    for(auto iInstrumentOrder = mPositions.begin() ; iInstrumentOrder != mPositions.end() ; iInstrumentOrder++)
    {
        QList<Order*> const&lOrders = iInstrumentOrder.value();
        for(auto iOrder = lOrders.begin(); iOrder != lOrders.end() ;iOrder++)
        {
            Order *pOrder = *iOrder;
            dMargin += pOrder->GetFrezonMargin();
        }
    }
    return dMargin;
}

double Account::GetPositionProfit() const
{
    double dProfit = 0;
    QMap<Instrument*,QList<Position*>> mPositions = GetPositions();
    for(auto iInstrumentPosition = mPositions.begin() ; iInstrumentPosition != mPositions.end() ; iInstrumentPosition++)
    {
        QList<Position*> const&lPositions = iInstrumentPosition.value();
        for(auto iPosition = lPositions.begin(); iPosition != lPositions.end() ;iPosition++)
        {
            Position *pPosition = *iPosition;
            dProfit += pPosition->GetTotalProfit();
        }
    }
    return dProfit;
}

size_t Account::GetAvailableQuantity(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag) const
{
    return GetAvailableQuantity(pInstrument,eDirection,eHedgeFlag,pInstrument->GetLastPrice());
}


size_t Account::GetAvailableQuantity(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag,double dQuote) const
{
    size_t nResult = 0;
    double dAvailableMargin = GetAvailableMargin();
    PositionCost *pPositionCost = m_mCosts[pInstrument];
    if(pPositionCost)
    {
        if(pPositionCost->GetMarginMode() == mmRatio)
        {
            if(eDirection == dLong)
            {
                nResult = floor(dAvailableMargin / (dQuote * pPositionCost->GetLongMargin()) );
            }
            else
            {
                nResult = floor(dAvailableMargin / (dQuote * pPositionCost->GetShortMargin()) );
            }
        }
        else
        {
            if(eDirection == dShort)
            {
                nResult = floor(dAvailableMargin / pPositionCost->GetLongMargin());
            }
            else
            {
                nResult = floor(dAvailableMargin / pPositionCost->GetShortMargin());
            }
        }
    }
    return nResult;
}


QList<Instrument*> Account::GetInstruments() const
{
    return m_lInstrument;
}

PositionCost* Account::GetPositionCost(Instrument *pInstrument)
{
    return m_mCosts[pInstrument];
}


QMap<Instrument*,PositionCost*> const& Account::GetAllPositionCost() const
{
    return m_mCosts;
}


Order* Account::CreateOrder(Instrument const* pInstrument,Direction eDirection,Operation eOperation,
            HedgeFlag eHedgeFlag,PriceMode ePriceMode,size_t nQuantity,double dQuote)
{
    InstrumentResourceManager *pInstrumentReourceManager = m_mInstrumentResources[pInstrument];
    if(pInstrumentReourceManager)
    {
        return pInstrumentReourceManager->CreateOrder(eDirection,eOperation,eHedgeFlag,ePriceMode,nQuantity,dQuote);
    }
    return nullptr;
}



Position* Account::OpenOrderHasTraded(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    InstrumentResourceManager *pInstrumentReourceManager = m_mInstrumentResources[pOrder->GetInstrument()];
    if(pInstrumentReourceManager)
    {
        return pInstrumentReourceManager->OpenOrderHasTraded(pOrder,oTimestamp,nQuantity,dPrice);
    }
    return nullptr;
}


QList<Transaction*> Account::CloseOrderHasTraded(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    InstrumentResourceManager *pInstrumentReourceManager = m_mInstrumentResources[pOrder->GetInstrument()];
    if(pInstrumentReourceManager)
    {
        return pInstrumentReourceManager->CloseOrderHasTraded(pOrder,oTimestamp,nQuantity,dPrice);
    }
    return nullptr;
}

void Account::OrderHasCancelled(Order *pOrder)
{
    InstrumentResourceManager *pInstrumentReourceManager = m_mInstrumentResources[pOrder->GetInstrument()];
    if(pInstrumentReourceManager)
    {
        pInstrumentReourceManager->OrderHasCancelled(pOrder);
    }
}


QMap<Instrument*,QList<Order*>> Account::GetRunningOrders()
{
    QMap<Instrument*,QList<Order*>> mOrders;
    for(auto iPos = m_mInstrumentResources.begin(); iPos != m_mInstrumentResources.end() ; iPos++)
    {
        Instrument *pInstrument = iPos.key();
        InstrumentResourceManager *pManager = iPos.value();
        mOrders.insert(pInstrument,pManager->GetRunningOrders());
    }
    return mOrders;
}

QList<Order*> Account::GetRunningOrders(Instrument* pInstrument)
{
    QList<Order*> lOrders;
    auto iPos = m_mInstrumentResources.find(pInstrument);
    if(iPos != m_mInstrumentResources.end())
    {
        InstrumentResourceManager *pManager = iPos.value();
        lOrders.append(pManager->GetRunningOrders());
    }
    return lOrders;
}

QMap<Instrument*,QList<Order*>> Account::GetOrders()
{
    QMap<Instrument*,QList<Order*>> mOrders;
    for(auto iPos = m_mInstrumentResources.begin(); iPos != m_mInstrumentResources.end() ; iPos++)
    {
        Instrument *pInstrument = iPos.key();
        InstrumentResourceManager *pManager = iPos.value();
        mOrders.insert(pInstrument,pManager->GetOrders());
    }
    return mOrders;
}

QList<Order*> const& Account::GetOrders(Instrument *pInstrument)
{
    QList<Order*> lOrders;
    auto iPos = m_mInstrumentResources.find(pInstrument);
    if(iPos != m_mInstrumentResources.end())
    {
        InstrumentResourceManager *pManager = iPos.value();
        lOrders.append(pManager->GetOrders());
    }
    return lOrders;
}

QMap<Instrument*,QList<Order*>> const& Account::GetTradeDayOrders() const
{
    QMap<Instrument*,QList<Order*>> mOrders;
    for(auto iPos = m_mInstrumentResources.begin(); iPos != m_mInstrumentResources.end() ; iPos++)
    {
        Instrument *pInstrument = iPos.key();
        InstrumentResourceManager *pManager = iPos.value();
        mOrders.insert(pInstrument,pManager->GetTradeDayOrders());
    }
    return mOrders;
}

QList<Order*> const& Account::GetTradeDayOrders(Instrument *pInstrument)
{
    QList<Order*> lOrders;
    auto iPos = m_mInstrumentResources.find(pInstrument);
    if(iPos != m_mInstrumentResources.end())
    {
        InstrumentResourceManager *pManager = iPos.value();
        lOrders.append(pManager->GetTradeDayOrders());
    }
    return lOrders;
}


QMap<Instrument*,QList<Position*>> Account::GetPositions() const
{
    QMap<Instrument*>,QList<Position*>> mPositoins;
    for(auto iPos = m_lInstrument.begin() ; iPos != m_lInstrument.end(); iPos++)
    {
        InstrumentResourceManager *pManager = m_mInstrumentResources[*iPos];
        if(pManager)
        {
            mPositions.insert(*iPos,pManager->GetPositions());
        }
    }
    return mPositions;
}

QList<Position*> Account::GetPositions(Instrument *pInstrument) const
{
    QList<Position*> lPositions;
    InstrumentResourceManager *pManager = m_mInstrumentResources[*iPos];
    if(pManager)
    {
        lPositions.append(pManager->GetPositions());
    }
    return lPositions;
}


QList<Transaction*> const& Account::GetTransactions(Instrument *pInstrument) const
{
    QList<Transaction*> lTransactions;
    InstrumentResourceManager *pManager = m_mInstrumentResources[*iPos];
    if(pManager)
    {
        lTransactions.append(pManager->GetTransactions());
    }
    return lTransactions;
}

QMap<Instrument*,QList<Transaction*>> const& Account::GetTransactions() const
{
    QMap<Instrument*>,QList<Position*>> mTransactions;
    for(auto iPos = m_lInstrument.begin() ; iPos != m_lInstrument.end(); iPos++)
    {
        InstrumentResourceManager *pManager = m_mInstrumentResources[*iPos];
        if(pManager)
        {
            mTransactions.insert(*iPos,pManager->GetTransactions());
        }
    }
    return mTransactions;
}

QList<Transaction*> const& Account::GetTradeDayTransactions(Instrument *pInstrument)const
{
    QList<Transaction*> lTransactions;
    InstrumentResourceManager *pManager = m_mInstrumentResources[*iPos];
    if(pManager)
    {
        lTransactions.append(pManager->GetTradeDayTransactions());
    }
    return lTransactions;
}

QMap<Instrument*,QList<Transaction*>> const& Account::GetTradeDayTransactions() const
{
    QMap<Instrument*>,QList<Position*>> mTransactions;
    for(auto iPos = m_lInstrument.begin() ; iPos != m_lInstrument.end(); iPos++)
    {
        InstrumentResourceManager *pManager = m_mInstrumentResources[*iPos];
        if(pManager)
        {
            mTransactions.insert(*iPos,pManager->GetTradeDayTransactions());
        }
    }
    return mTransactions;
}
