#include "Instrument.h"
#include "MarketData.h"

Instrument::Instrument(QString const& strID,QString const& Name,QString const& strVariety,
           QString const& strExchange,double dPriceMultiple,QDate const& oLastTradeDay,
           QDateTime const& oCloseTime,QDateTime const& oLastTradeDayCloseTime
           )
{

}

QString const& Instrument::GetID() const
{
    return m_strID;
}

QString const& Instrument::GetName() const
{
    return m_strName;
}

QString const& Instrument::GetVariety() const
{
    return m_strVariety;
}

QString const& Instrument::GetExchange() const
{
    return m_strExchange;
}

double Instrument::GetPriceMultiple() const
{
    return m_dPriceMultiple;
}

QDate const& Instrument::GetTradeDay() const
{
    return m_oTradeDay;
}

QDate const& Instrument::GetLastTradeDay() const
{
    return m_oLastTradeDay;
}

QDateTime const& Instrument::GetCloseTime() const
{
    return m_oCloseTime;
}

double Instrument::GetLastPrice() const
{
    return m_dLastPrice;
}

size_t Instrument::GetLastVolume() const
{
    return m_nLastVolume;
}

double Instrument::GetHighestPrice() const
{
    return m_dHighestPrice;
}

double Instrument::GetLowestPrice() const
{
    return m_dLowestPrice;
}

double Instrument::GetClosePrice() const
{
    return m_dClosePrice;
}

double Instrument::GetOpenPrice() const
{
    return m_dOpenPrice;
}

double Instrument::GetPreSuttlementPrice() const
{
    return m_dPreSuttlementPrice;
}

double Instrument::GetSuttlementPrice() const
{
    return m_dSuttlementPrice;
}

double Instrument::GetAmount() const
{
    return m_dAmount;
}

size_t Instrument::GetVolume() const
{
    return m_nVolume;
}

QDateTime const& Instrument::GetLastUpdateTime() const
{
    return m_oLastUpdateTime;
}

bool Instrument::IsTrading() const
{
    return QDate::currentDate() <= m_oLastTradeDay;
}

void Instrument::Updated(MarketData const*pMarketData)
{
    m_lMarketDatas.append(pMarketData);
    if(m_bFirst)
    {
        m_dOpenPrice = pMarketData->GetOpenPrice();
        m_dPreSuttlementPrice = pMarketData->GetPreSettlementPrice();
        m_bFirst = false;
    }
    m_oLastUpdateTime = pMarketData->GetTimestamp();
    m_dLastPrice = pMarketData->GetLastPrice();
    m_nLastVolume = pMarketData->GetLastVolume();
    m_dAmount = pMarketData->GetAmount();
    m_dHighestPrice = pMarketData->GetHighestPrice();
    m_dLowestPrice = pMarketData->GetLowestPrice();
    m_dSuttlementPrice = pMarketData->GetLastPrice();
}

QList<MarketData*> const& Instrument::GetMarketDataList() const
{
    return m_lMarketDatas;
}
