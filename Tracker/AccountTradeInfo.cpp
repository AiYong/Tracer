#include "AccountTradeInfo.h"

#include <cmath>

#include "Order.h"
#include "Account.h"
#include "Instrument.h"
#include "Position.h"
#include "PositionCost.h"
#include "Transaction.h"
#include "OrderOperator.h"
#include "OrderPersister.h"
#include "PositionPersister.h"
#include "PositionCostPersister.h"
#include "TransactionPersister.h"

#include "ObjectPersistManager.h"


AccountTradeInfo::AccountTradeInfo(Account *pAccount,Instrument *pInstrument,PositionCost *pPositionCost)
    :m_pAccount(pAccount),m_pInstrument(pInstrument),m_pPositionCost(pPositionCost),
     m_bOrderLoaded(false),m_bPositionLoaded(false),m_bTransactionLoaded(false)
{  
    LoadPositions();
    LoadTradeDayOrders();
    LoadTradeDayTransactions();
}

AccountTradeInfo::~AccountTradeInfo()
{

}


Account* AccountTradeInfo::GetAccount() const
{
    return m_pAccount;
}

Instrument* AccountTradeInfo::GetInstrument() const
{
    return m_pInstrument;
}

PositionCost* AccountTradeInfo::GetPositionCost() const
{
    return m_pPositionCost;
}

size_t AccountTradeInfo::GetAvailableQuantity(Direction eDirection,HedgeFlag eHedgeFlag,double dMargin,double dQuote) const
{
    size_t nAvailableQuantity = (size_t)floor(dMargin/(dQuote * m_pInstrument->GetPriceMultiple()));
    return nAvailableQuantity;
}

size_t AccountTradeInfo::GetPositionQuantity(Direction eDirection,HedgeFlag eHedgeFlag) const
{
    QMutexLocker oLocker(m_mLock);
    size_t nQuantity = 0;
    for(auto iPos = m_lPositions.begin() ; iPos != m_lPositions.end() ; iPos++)
    {
        Position *pPosition = *iPos;
        if(pPosition->GetDirection() == eDirection && pPosition->GetHedgeFlag() == eHedgeFlag)
        {
            nQuantity += pPosition->GetQuantity();
        }
    }
    return nQuantity;
}

Order* AccountTradeInfo::CreateOrder(Direction eDirection,Operation eOperation,
                   HedgeFlag eHedgeFlag,PriceMode ePriceMode,size_t nQuantity,double dQuote)
{
    QMutexLocker oLocker(m_mLock);
    Order *pOrder = nullptr;
    if(eOperation == opOpen)
    {
        pOrder = new Order(m_pAccount->GenUniqueId(),m_pAccount,m_pInstrument,m_pPositionCost,QDateTime::currentDateTime(),eOperation,
                           eDirection,eHedgeFlag,ePriceMode,nQuantity,dQuote,osNew);
    }
    else
    {
        pOrder = new Order(m_pAccount->GenUniqueId(),m_pAccount,m_pInstrument,m_pPositionCost,QDateTime::currentDateTime(),eOperation,
                                       eDirection,eHedgeFlag,ePriceMode,nQuantity,dQuote,osNew);
    }
    SaveOrder(pOrder);
    m_lRunningOrders.push_back(pOrder);
    m_lTradeDayOrders.push_back(pOrder);
}

Position* AccountTradeInfo::CreatePosition(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    QMutexLocker oLocker(m_mLock);
    OrderOperator oOperator;
    Position *pPosition = oOperator.Open(pOrder,oTimestamp,nQuantity,dPrice);
    UpdateOrder(pOrder);
    SavePosition(pPosition);
    m_lPositions.push_back(pPosition);
    return pPosition;
}

QList<Transaction*> AccountTradeInfo::CreateTransaction(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    QMutexLocker oLocker(m_mLock);
    OrderOperator oOperator;
    QList<Transaction*> lTransactions;
    QList<Position*> lPositions;
    auto iPos = m_lPositions; 
    while(iPos != m_lPositions.begin())
    {
        Position *pPosition = *iPos;
        Transaction* pTransaction = oOperator.Close(pPosition,pOrder,oTimestamp,nQuantity,dPrice);
        lTransactions.append(pTransaction);
        if(pPosition->GetQuantity() == 0)
        {
            iPos = m_lPositions.erase(iPos);
            lPositions.append(pPosition);
        }
        else
        {
            break;
        }
    }
    m_lTradeDayTransactions.append(lTransactions);
    UpdateOrder(pOrder);
    SaveTransaction(lTransactions);
    RemovePosition(lPositions);
}

void AccountTradeInfo::UpdateOrderStatus(Order *pOrder,OrderStatus eStatus)
{
    QMutexLocker oLocker(m_mLock);
    OrderOperator oOperator;
    oOperator.UpdateOrderStatus(pOrder,eStatus);
    UpdateOrder(pOrder);
    switch (eStatus) {
    case osCancelled:
    case osCancelledAndPartedTraded:
    case osError:
    {
        m_lRunningOrders.removeOne(pOrder);
    }
        break;
    default:
        break;
    }
}


double AccountTradeInfo::GetPositionProfit() const
{
    QMutexLocker oLocker(m_mLock);
    double dProfit = 0;
    for(auto iPos = m_lPositions.begin() ; iPos != m_lPositions.end() ; iPos++)
    {
        Position *pPosition = *iPos;
        dProfit = pPosition->GetTotalProfit();
    }
    return dProfit;
}

double AccountTradeInfo::GetTradeDayProfit() const
{
    QMutexLocker oLocker(m_mLock);
    double dProfit = 0;
    for(auto iPos = m_lPositions.begin() ; iPos != m_lPositions.end() ; iPos++)
    {
        Position *pPosition = *iPos;
        dProfit = pPosition->GetTradeDayProfit();
    }
    return dProfit;
}


double AccountTradeInfo::GetTradeDayCommission() const
{
    QMutexLocker oLocker(m_mLock);
    double dCommission = 0;
    for(auto iPos = m_lPositions.begin() ; iPos != m_lPositions.end() ; iPos++)
    {
        Position *pPosition = *iPos;
        if(pPosition->GetTimestamp().date() == m_pInstrument->GetTradeDay())
        {
            dCommission += pPosition->GetCommission();
        }
    }
    for(auto iPos = m_lTradeDayTransactions.begin() ; iPos !=  m_lTradeDayTransactions.end() ; iPos++)
    {
        Transaction *pTransaction = *iPos;
        dCommission +=pTransaction->GetOpenCommission();
        dCommission += pTransaction->GetCloseCommission();
    }
    return dCommission;
}


double AccountTradeInfo::GetFrezonMargin() const
{
    double dFrezonMargin = 0;
    QMutexLocker oLocker(m_mLock);
    for(auto iPos = m_lRunningOrders.begin() ; iPos != m_lRunningOrders.end() ; iPos++)
    {
        Order *pOrder = *iPos;
        dFrezonMargin += pOrder->GetFrezonMargin();
    }
    for(auto iPos = m_lPositions.begin() ; iPos != m_lPositions.end() ; iPos++)
    {
        Position *pPosition = *iPos;
        dFrezonMargin += pPosition->GetFrezonMargin();
    }
    return dFrezonMargin;
}


QList<Order*> AccountTradeInfo::GetOrders() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Order*> lOrders ;
    lOrders.append(m_lTradeDayOrders);
    if(!m_bOrderLoaded)
    {
        LoadOrders();
        m_bOrderLoaded = true;
    }
    lOrders.append(m_lOrders);
    return lOrders;
}


QList<Order*> AccountTradeInfo::GetOrders(QDate const& oTradeDay) const
{

    QMutexLocker oLocker(m_mLock);
    if(oTradeDay == m_pInstrument->GetTradeDay())
    {
        return m_lTradeDayOrders;
    }
    QList<Order*> lOrders;
    if(!m_bOrderLoaded)
    {
        m_bOrderLoaded = true;
        LoadOrders();  
    }
    for(int nCount = 0 ; nCount < m_lOrders.size() ; nCount)
    {
        Order *pOrder = m_lOrders[nCount];
        if(pOrder->GetTimestamp().date() == oTradeDay)
        {
            lOrders.append(pOrder);
        }
    }
    return lOrders;
}


QList<Order*> AccountTradeInfo::GetTradeDayOrders() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Order*> lOrders;
    lOrders.append(m_lTradeDayOrders);
    return lOrders;
}


QList<Order*> AccountTradeInfo::GetRunningOrders() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Order*> lOrders;
    lOrders.append(m_lRunningOrders);
    return lOrders;
}


QList<Position*> AccountTradeInfo::GetPositions() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Position*> lPositions;
    lPositions.append(m_lPositions);
    return lPositions;
}

QList<Transaction*> AccountTradeInfo::GetTransactions() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Transaction*> lTransactions;
    lTransactions.append(m_lTradeDayTransactions);
    if(!m_bTransactionLoaded)
    {
        LoadTransactions();
        m_bTransactionLoaded = true;
    }
    lTransactions.append(m_lTransactions);
    return lTransactions;
}

QList<Transaction*> AccountTradeInfo::GetTradeDayTransactions() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Transaction*> lTransactions;
    lTransactions.append(m_lTradeDayTransactions);
    return lTransactions;
}

QList<Transaction*> AccountTradeInfo::GetTransactions(QDate const& oTradeDay) const
{
   QMutexLocker oLocker(m_mLock);
   QList<Transaction*> lTransactions;
   if(m_pInstrument->GetTradeDay() == oTradeDay)
   {
       lTransactions.append(m_lTradeDayTransactions);
       return lTransactions;
   }
   if(!m_bTransactionLoaded)
   {
       LoadTransactions();
       m_bTransactionLoaded = true;
   }
   for(auto iPos = m_lTransactions.begin() ; iPos != m_lTransactions.end() ; iPos++)
   {
       Transaction *pTransaction = *iPos;
       if(pTransaction->GetOpenTime().date() != oTradeDay)
       {
           lTransactions.append(pTransaction);
       }
   }
   return lTransactions;
}


void AccountTradeInfo::LoadOrders()
{
    OrderLoadCondition oOrderCondition;
    oOrderCondition.bIsTradeDay = false;
    oOrderCondition.pAccount = m_pAccount;
    oOrderCondition.pInstrument = m_pInstrument;
    ObjectPersistManager::GetInstance()->Load(&oOrderCondition,m_lOrders);
}

void AccountTradeInfo::LoadPositions()
{
     ObjectPersistManager::GetInstance()->Load(m_pAccount,m_lPositions);
}

void AccountTradeInfo::LoadTransactions()
{
    TransactionLoadCondition oCondition;
    oCondition.bIsTradeDay = false;
    oCondition.pAccount = m_pAccount;
    oCondition.pInstrument = m_pInstrument;
    ObjectPersistManager::GetInstance()->Load(&oCondition,m_lTransactions);

}

void AccountTradeInfo::LoadTradeDayOrders()
{
    OrderLoadCondition oOrderCondition;
    oOrderCondition.bIsTradeDay = true;
    oOrderCondition.pAccount = m_pAccount;
    oOrderCondition.pInstrument = m_pInstrument;
    ObjectPersistManager::GetInstance()->Load(&oOrderCondition,m_lTradeDayOrders);
}


void AccountTradeInfo::LoadTradeDayTransactions()
{
    TransactionLoadCondition oCondition;
    oCondition.bIsTradeDay = true;
    oCondition.pAccount = m_pAccount;
    oCondition.pInstrument = m_pInstrument;
    ObjectPersistManager::GetInstance()->Load(&oCondition,m_lTradeDayTransactions);
}

void AccountTradeInfo::SaveOrder(Order *pOrder)
{
    ObjectPersistManager::GetInstance()->Save(pOrder);
}

void AccountTradeInfo::UpdateOrder(Order *pOrder)
{
    ObjectPersistManager::GetInstance()->Update(pOrder);
}

void AccountTradeInfo::SavePosition(Position *pPosition)
{
    ObjectPersistManager::GetInstance()->Save(pPosition);
}

void AccountTradeInfo::UpdatePosition(Position *pPosition)
{
    ObjectPersistManager::GetInstance()->Update(pPosition);
}

void AccountTradeInfo::RemovePosition(Position *pPosition)
{
    ObjectPersistManager::GetInstance()->Remove(pPosition);
}

void AccountTradeInfo::SaveTransaction(QList<Transaction*> const& lTransactions)
{
    ObjectPersistManager::GetInstance()->Save(lTransactions);
}

