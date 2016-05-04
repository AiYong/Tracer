#include "AccountResourceManager.h"

AccountResourceManager* AccountResourceManager::GetInstance()
{

}

QList<Instrument*> AccountResourceManager::GetInstrument(Account *pAccount)
{

}

QMap<Instrument*,PositionCost*> AccountResourceManager::GetPositionCost(Account *pAccount)
{

}

OrderProcessor* AccountResourceManager::GetOrderProcessor(Account *pAccount)
{

}

MarketDataSubscriber* AccountResourceManager::GetMarketDataSubscriber(Account *pAccount)
{

}
