#include "Account.h"
#include "Order.h"
#include "Position.h"
#include "Instrument.h"
#include "PositionCost.h"
#include "OrderOperator.h"
#include "AccountResourceManager.h"
#include "AccountTradeInfo.h"

#include <cmath>
#include <algorithm>

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

QString const& Account::GetID() const
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
    double dDynamicMargin = m_dStaticMargin;
    for(auto iPos = m_hTradeInfos.begin() ; iPos != m_hTradeInfos.end() ; iPos++)
    {
        AccountTradeInfo *pTradeInfo = iPos.value();
        dDynamicMargin += pTradeInfo->GetTradeDayProfit();
        dDynamicMargin += pTradeInfo->GetTradeDayCommission();
    }
    return dDynamicMargin;
}

double Account::GetStaticMargin() const
{
    return m_dStaticMargin;
}

double Account::GetAvailableMargin() const
{
    return GetDynamicMargin() - GetFrezonMargin();
}

double Account::GetFrezonMargin() const
{
    double dFrezonMargin = 0;
    for(auto iPos = m_hTradeInfos.begin() ; iPos != m_hTradeInfos.end() ; iPos++)
    {
        AccountTradeInfo *pTradeInfo = iPos.value();
        dFrezonMargin += pTradeInfo->GetFrezonMargin();
    }
    return dFrezonMargin;
}

double Account::GetPositionProfit() const
{
    double dProfit = 0;
    for(auto iPos = m_hTradeInfos.begin() ; iPos != m_hTradeInfos.end() ; iPos++)
    {
        AccountTradeInfo *pTradeInfo = iPos.value();
        dProfit += pTradeInfo->GetPositionProfit();
    }
    return dProfit;
}

double Account::GetTradeDayProfit() const
{
    double dProfit = 0;
    for(auto iPos = m_hTradeInfos.begin() ; iPos != m_hTradeInfos.end() ; iPos++)
    {
        AccountTradeInfo *pTradeInfo = iPos.value();
        dProfit += pTradeInfo->GetTradeDayProfit();
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
    auto iPos = m_hTradeInfos.find(pInstrument->GetID());
    if(iPos != m_hTradeInfos.end())
    {
        AccountTradeInfo *pTradeInfo = *iPos;
        nResult = pTradeInfo->GetAvailableQuantity(eDirection,eHedgeFlag,dAvailableMargin,dQuote);
    }
    return nResult;
}


size_t Account::GetAvailableQuantityWithMargin(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag,double dMargin) const
{
    return GetAvailableQuantityWithMargin(pInstrument,eDirection,eHedgeFlag,dMargin,pInstrument->GetLastPrice());
}


size_t Account::GetAvailableQuantityWithMargin(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag,double dMargin,double dQuote) const
{
    size_t nResult = 0;
    auto iPos = m_hTradeInfos.find(pInstrument->GetID());
    if(iPos != m_hTradeInfos.end())
    {
        AccountTradeInfo *pTradeInfo = *iPos;
        nResult = pTradeInfo->GetAvailableQuantity(eDirection,eHedgeFlag,dMargin,dQuote);
    }
    return nResult;
}

size_t Account::GetPositionQuantity(Instrument const* pInstrument,Direction eDirection,HedgeFlag eHedgeFlag) const
{
    size_t nResult = 0;
    auto iPos = m_hTradeInfos.find(pInstrument->GetID());
    if(iPos != m_hTradeInfos.end())
    {
        AccountTradeInfo *pTradeInfo = *iPos;
        nResult = pTradeInfo->GetPositionQuantity(eDirection,eHedgeFlag);
    }
    return nResult;
}

QList<Instrument*> const& Account::GetInstruments() const
{
    return m_lInstrument;
}


Instrument* Account::GetInstrument(const QString &strID) const
{
    auto iPos = m_hInstrument.find(strID);
    if(iPos != m_hInstrument.end())
    {
        return *iPos;
    }
    return nullptr;
}

PositionCost* Account::GetPositionCost(Instrument *pInstrument) const
{
    auto iPos = m_mCosts.find(pInstrument->GetID());
    if(iPos != m_mCosts.end())
    {
        return *iPos;
    }
    return nullptr;
}

QMap<QString,PositionCost*> const& Account::GetPositionCosts() const
{
    return m_mCosts;
}

Order* Account::CreateOrder(Instrument const* pInstrument,Direction eDirection,Operation eOperation,
            HedgeFlag eHedgeFlag,PriceMode ePriceMode,size_t nQuantity,double dQuote)
{
    size_t nAvaiableQuantity = 0;
    double dPrice = dQuote;
    if(ePriceMode == pmMarketPrice)
    {
        dPrice = pInstrument->GetLastPrice();
    }
    if(eOperation == opOpen)
    {
        nAvaiableQuantity = GetAvailableQuantity(pInstrument,eDirection,eHedgeFlag,dPrice);
    }
    else
    {
        nAvaiableQuantity = GetPositionQuantity(pInstrument,eDirection,eHedgeFlag);
    }
    if(nAvaiableQuantity < nQuantity)
    {
        return nullptr;
    }
    AccountTradeInfo *pTradeInfo = m_hTradeInfos[pInstrument->GetID()];
    if(pTradeInfo)
    {
        return pTradeInfo->CreateOrder(eDirection,eOperation,eHedgeFlag,ePriceMode,nQuantity,dQuote);
    }
    return nullptr;
}


Position* Account::CreatePosition(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    AccountTradeInfo *pTradeInfo = m_hTradeInfos[pOrder->GetInstrument()->GetID()];
    if(pTradeInfo)
    {
        return pTradeInfo->CreatePosition(pOrder,oTimestamp,nQuantity,dPrice);
    }
    return nullptr;
}


QList<Transaction*> Account::CreateTransaction(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    AccountTradeInfo *pTradeInfo = m_hTradeInfos[pOrder->GetInstrument()->GetID()];
    if(pTradeInfo)
    {
        return pTradeInfo->CreateTransaction(pOrder,oTimestamp,nQuantity,dPrice);
    }
    return nullptr;
}


void Account::UpdateOrderStatus(Order *pOrder,OrderStatus eStatus)
{
    AccountTradeInfo *pTradeInfo = m_hTradeInfos[pOrder->GetInstrument()->GetID()];
    if(pTradeInfo)
    {
        pTradeInfo->UpdateOrderStatus(pOrder,eStatus);
    }
}


QMap<Instrument*,QList<Order*>> Account::GetRunningOrders() const
{
    QMap<Instrument*,QList<Order*>> hOrders;
    for(auto iPos = m_hInstrument.begin(); iPos != m_hInstrument.end() ; iPos++)
    {
        Instrument *pInstrument = *iPos;
        auto iInstrumentPos = m_hTradeInfos.find(pInstrument->GetID());
        if(iInstrumentPos != m_hTradeInfos.end())
        {
            AccountTradeInfo *pTradeInfo = iPos.value();
            hOrders.insert(pInstrument,pTradeInfo->GetRunningOrders());
        }
    }
    return hOrders;
}

QList<Order*> Account::GetRunningOrders(Instrument* pInstrument) const
{
    QList<Order*> lOrders;
    auto iPos = m_hTradeInfos.find(pInstrument->GetID());
    if(iPos != m_hTradeInfos.end())
    {
        AccountTradeInfo *pTradeInfo = iPos.value();
        lOrders.append(pTradeInfo->GetRunningOrders());
    }
    return lOrders;
}

QMap<Instrument*,QList<Order*>> Account::GetOrders() const
{
    QMap<Instrument*,QList<Order*>> hOrders;
    for(auto iPos = m_hInstrument.begin(); iPos != m_hInstrument.end() ; iPos++)
    {
        Instrument *pInstrument = *iPos;
        auto iInstrumentPos = m_hTradeInfos.find(pInstrument->GetID());
        if(iInstrumentPos != m_hTradeInfos.end())
        {
            AccountTradeInfo *pTradeInfo = iPos.value();
            hOrders.insert(pInstrument,pTradeInfo->GetRunningOrders());
        }
    }
    return hOrders;
}

QList<Order*> Account::GetOrders(Instrument *pInstrument) const
{
    QList<Order*> lOrders;
    auto iPos = m_hTradeInfos.find(pInstrument->GetID());
    if(iPos != m_hTradeInfos.end())
    {
        AccountTradeInfo *pTradeInfo = iPos.value();
        lOrders.append(pTradeInfo->GetOrders());
    }
    return lOrders;
}

QMap<Instrument*,QList<Order*>> Account::GetTradeDayOrders() const
{
    QMap<Instrument*,QList<Order*>> hOrders;
    for(auto iPos = m_hInstrument.begin(); iPos != m_hInstrument.end() ; iPos++)
    {
        Instrument *pInstrument = *iPos;
        auto iInstrumentPos = m_hTradeInfos.find(pInstrument->GetID());
        if(iInstrumentPos != m_hTradeInfos.end())
        {
            AccountTradeInfo *pTradeInfo = iPos.value();
            hOrders.insert(pInstrument,pTradeInfo->GetRunningOrders());
        }
    }
    return hOrders;
}

QList<Order*> const& Account::GetTradeDayOrders(Instrument *pInstrument) const
{
    QList<Order*> lOrders;
    auto iPos = m_hTradeInfos.find(pInstrument->GetID());
    if(iPos != m_hTradeInfos.end())
    {
        AccountTradeInfo *pTradeInfo = iPos.value();
        lOrders.append(pTradeInfo->GetTradeDayOrders());
    }
    return lOrders;
}


QMap<Instrument*,QList<Position*>> Account::GetPositions() const
{
    QMap<Instrument*,QList<Position*>> hPositions;
    for(auto iPos = m_lInstrument.begin() ; iPos != m_lInstrument.end(); iPos++)
    {
        Instrument *pInstrument = *iPos;
        AccountTradeInfo *pTradeInfo  = m_hTradeInfos[pInstrument->GetID()];
        if(pTradeInfo)
        {
            hPositions.insert(pInstrument,pTradeInfo->GetPositions());
        }
    }
    return hPositions;
}

QList<Position*> Account::GetPositions(Instrument *pInstrument) const
{
    QList<Position*> lPositions;
    AccountTradeInfo *pTradeInfo  = m_hTradeInfos[pInstrument->GetID()];
    if(pTradeInfo)
    {
        lPositions.append(pTradeInfo->GetPositions());
    }
    return lPositions;
}


QList<Transaction*> const& Account::GetTransactions(Instrument *pInstrument) const
{
    QList<Transaction*> lTransactions;
    AccountTradeInfo *pTradeInfo  = m_hTradeInfos[pInstrument->GetID()];
    if(pTradeInfo)
    {
        lTransactions.append(pTradeInfo->GetTransactions());
    }
    return lTransactions;
}

QMap<Instrument*,QList<Transaction*>> const& Account::GetTransactions() const
{
    QMap<Instrument*,QList<Position*>> hTransactions;
    for(auto iPos = m_lInstrument.begin() ; iPos != m_lInstrument.end(); iPos++)
    {
        AccountTradeInfo *pTradeInfo  = m_hTradeInfos[*iPos];
        if(pTradeInfo)
        {
            hTransactions.insert(*iPos,pTradeInfo->GetTransactions());
        }
    }
    return hTransactions;
}

QList<Transaction*> const& Account::GetTradeDayTransactions(Instrument *pInstrument)const
{
    QList<Transaction*> lTransactions;
    AccountTradeInfo *pTradeInfo  = m_hTradeInfos[pInstrument->GetID()];
    if(pTradeInfo)
    {
        lTransactions.append(pTradeInfo->GetTradeDayTransactions());
    }
    return lTransactions;
}

QMap<Instrument*,QList<Transaction*>> const& Account::GetTradeDayTransactions() const
{
    QMap<Instrument*>,QList<Position*>> hTransactions;
    for(auto iPos = m_lInstrument.begin() ; iPos != m_lInstrument.end(); iPos++)
    {
        Instrument *pInstrument = *iPos;
        AccountTradeInfo *pTradeInfo  = m_hTradeInfos[pInstrument->GetID()];
        if(pTradeInfo)
        {
            hTransactions.insert(pInstrument,pManager->GetTradeDayTransactions());
        }
    }
    return hTransactions;
}
