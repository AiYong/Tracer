#include "TradeResourceManager.h"

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
#include "ObjectPersistManager.h"

InstrumentResourceManager::InstrumentResourceManager(Account *pAccount,Instrument *pInstrument,PositionCost *pPositionCost)
    :m_pAccount(pAccount),m_pInstrument(pInstrument),m_pPositionCost(pPositionCost),
     m_bOrderLoaded(false),m_bPositionLoaded(false),m_bTransactionLoaded(false)
{  
}

InstrumentResourceManager::~InstrumentResourceManager()
{

}

void InstrumentResourceManager::Initialize()
{
    LoadPositions();   
}

void InstrumentResourceManager::Destroy()
{
    SaveOrders();
    SavePositions();
}

Account* InstrumentResourceManager::GetAccount() const
{
    return m_pAccount;
}

Instrument* InstrumentResourceManager::GetInstrument() const
{
    return m_pInstrument;
}

PositionCost* InstrumentResourceManager::GetPositionCost() const
{
    return m_pPositionCost;
}

Order* InstrumentResourceManager::CreateOrder(Direction eDirection,Operation eOperation,
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
    //保存数据
    if(pOrder != nullptr)
    {
        SaveOrder(pOrder);
        m_lRunningOrders.push_back(pOrder);
        m_lTradeDayOrders.push_back(pOrder);
    }
}

Position* InstrumentResourceManager::OpenOrderHasTraded(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
{
    QMutexLocker oLocker(m_mLock);
    OrderOperator oOperator;
    Position *pPosition = oOperator.Open(pOrder,oTimestamp,nQuantity,dPrice);
    UpdateOrder(pOrder);
    SavePosition(pPosition);
    m_lPositions.push_back(pPosition);
    return pPosition;
}

QList<Transaction*> InstrumentResourceManager::CloseOrderHasTraded(Order *pOrder,QDateTime const& oTimestamp,size_t nQuantity,double dPrice)
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

void InstrumentResourceManager::OrderHasCancelled(Order *pOrder)
{
    QMutexLocker oLocker(m_mLock);
    OrderOperator oOperator;
    oOperator.Cancelled(pOrder);
    UpdateOrder(pOrder);
    m_lRunningOrders.removeOne(pOrder);
}


QList<Order*> InstrumentResourceManager::GetOrders() const
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

QList<Order*> InstrumentResourceManager::GetOrders(QDate const& oTradeDay) const
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

QList<Order*> InstrumentResourceManager::GetTradeDayOrders() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Order*> lOrders;
    lOrders.append(m_lTradeDayOrders);
    return lOrders;
}

QList<Order*> InstrumentResourceManager::GetRunningOrders() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Order*> lOrders;
    lOrders.append(m_lRunningOrders);
    return lOrders;
}

QList<Position*> InstrumentResourceManager::GetPositions() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Position*> lPositions;
    lPositions.append(m_lPositions);
    return lPositions;
}

QList<Transaction*> InstrumentResourceManager::GetTransactions() const
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

QList<Transaction*> InstrumentResourceManager::GetTradeDayTransactions() const
{
    QMutexLocker oLocker(m_mLock);
    QList<Transaction*> lTransactions;
    lTransactions.append(m_lTradeDayTransactions);
    return lTransactions;
}

QList<Transaction*> InstrumentResourceManager::GetTransactions(QDate const& oTradeDay) const
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


void InstrumentResourceManager::LoadOrders()
{
    m_lOrders = ObjectPersistManager::GetInstance()->Load(m_pAccount);
}

void InstrumentResourceManager::LoadPositions()
{
     m_lPositions = ObjectPersistManager::GetInstance()->Load(m_pAccount);
}

void InstrumentResourceManager::LoadTransactions()
{
    m_lTransactions = ObjectPersistManager::GetInstance()->Load(m_pAccount);
}

void InstrumentResourceManager::SaveOrders()
{
    
}

void InstrumentResourceManager::SavePositions()
{
    
}

void InstrumentResourceManager::SaveOrder(Order *pOrder)
{
    ObjectPersistManager::GetInstance()->Save(pOrder);
}

void InstrumentResourceManager::UpdateOrder(Order *pOrder)
{
    ObjectPersistManager::GetInstance()->Update(pOrder);
}

void InstrumentResourceManager::SavePosition(Position *pPosition)
{
    ObjectPersistManager::GetInstance()->Save(pPosition);
}

void InstrumentResourceManager::UpdatePosition(Position *pPosition)
{
    ObjectPersistManager::GetInstance()->Update(pPosition);
}

void InstrumentResourceManager::SaveTransaction(QList<Transaction*> const& lTransactions)
{
    ObjectPersistManager::GetInstance()->Save(lTransactions);
}


void InstrumentResourceManager::RemovePosition(QList<Position*> const& lPositions)
{
    
}
