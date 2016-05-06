#include "AccountTrackerSetting.h"
#include "Instrument.h"

AccountTrackerSetting::AccountTrackerSetting(Account *pTradeAccount)
    :m_pTradeAccount(pTradeAccount)
{
}

AccountTrackerSetting::~AccountTrackerSetting()
{

}


int AccountTrackerSetting::GetID() const
{
    return m_nID;
}


void AccountTrackerSetting::SetID(int nID)
{
    m_nID = nID;
}


Account* AccountTrackerSetting::GetTradeAccount() const
{
    return m_pTradeAccount;
}

void AccountTrackerSetting::SetTradeAccount(Account *pAccount)
{
    m_pTradeAccount = pAccount;
}

Account* AccountTrackerSetting::GetTrackAccount() const
{
    return m_pTrackAccountl
}

void AccountTrackerSetting::SetTrackAccount(Account *pAccount)
{
    m_pTrackAccount = pAccount;
}

PositionLimitMode AccountTrackerSetting::GetPositionLimitMode() const
{
    return m_ePositionLimitMode;
}

void AccountTrackerSetting::SetPositionLimitMode(PositionLimitMode ePositionLimitMode)
{
    m_ePositionLimitMode = ePositionLimitMode;
}


BeyondPositionLimitProcessMode AccountTrackerSetting::GetBeyondPositionLimitProcessMode() const
{
    return m_eBeyondPositionLimitProcessMode;
}

void AccountTrackerSetting::SetBeyondPositionLimitProcessMode(BeyondPositionLimitProcessMode eBeyondPositionLimitProcessMode)
{
    m_eBeyondPositionLimitProcessMode = eBeyondPositionLimitProcessMode;
}

double AccountTrackerSetting::GetPositionLimit() const
{
    return m_dPositionLimit;
}


void AccountTrackerSetting::SetPositionLimit(double dPositionLimit)
{
    m_dPositionLimit = dPositionLimit;
}

OpenPriceMode AccountTrackerSetting::GetOpenPriceMode() const
{
    return m_eOpenPriceMode;
}

void AccountTrackerSetting::SetOpenPriceMode(OpenPriceMode eOpenPriceMode)
{
    m_eOpenPriceMode = eOpenPriceMode;
}

OpenLimitPriceMode AccountTrackerSetting::GetOpenLimitPriceMode() const
{
    return m_eOpenLimitPriceMode;
}

void AccountTrackerSetting::SetOpenLimitPriceMode(OpenLimitPriceMode eOpenLimitPriceMode)
{
    m_eOpenLimitPriceMode = eOpenLimitPriceMode;
}

double AccountTrackerSetting::GetOpenLimitPriceDelta() const
{
    return m_dOpenLimitPriceDelta;
}

void AccountTrackerSetting::SetOpenLimitPriceDelta(double dDelta)
{
    m_dOpenLimitPriceDelta = dDelta;
}

ClosePriceMode AccountTrackerSetting::GetClosePriceMode() const
{
    return m_eClosePriceMode
}

void AccountTrackerSetting::SetClosePriceMode(ClosePriceMode eClosePriceMode)
{
    m_eClosePriceMode;
}

CloseLimitPriceMode AccountTrackerSetting::GetCloseLimitPriceMode() const
{
    return m_eCloseLimitPriceMode;
}

void AccountTrackerSetting::SetCloseLimitPriceMode(CloseLimitPriceMode eCloseLimitPriceMode)
{
    m_eCloseLimitPriceMode  = eCloseLimitPriceMode;
}

double AccountTrackerSetting::GetCloseLimitPriceDelta() const
{
    return m_dCloseLimitPriceDelta;
}

void AccountTrackerSetting::SetCloseLimitPriceDelta(double eDelta)
{
    m_dCloseLimitPriceDelta = eDelta;
}

bool AccountTrackerSetting::IsStopWin() const
{
    return m_bStopWin;
}

void AccountTrackerSetting::SetStopWin(bool bStopWin)
{
    m_bStopWin = bStopWin;
}

double AccountTrackerSetting::GetStopWinPrice() const
{
    return m_dStopWinPrice;
}

void AccountTrackerSetting::SetStopWinPrice(double dStopWinPrice)
{
    m_dStopWinPrice = dStopWinPrice;
}

StopWinPriceMode AccountTrackerSetting::GetStopWinPriceMode() const
{
    return m_eStopWinPriceMode;
}


void AccountTrackerSetting::SetStopWinPriceMode(StopWinPriceMode eStopWinPriceMode)
{
    m_eStopWinPriceMode = eStopWinPriceMode;
}

StopWinOrderType AccountTrackerSetting::GetStopWinOrderType() const
{
    return m_eStopWinOrderType;
}


void AccountTrackerSetting::SetStopWinOrderType(StopWinOrderType eStopWinOrderType)
{
    m_eStopWinOrderType = eStopWinOrderType;
}


StopWinOrderLimitPriceMode AccountTrackerSetting::GetStopWinOrderLimitPriceMode() const
{
    return m_eStopWinOrderLimitPriceMode;
}

void AccountTrackerSetting::SetStopWinOrderLimitPriceMode(StopWinOrderLimitPriceMode eStopWinOrderLimitPriceMode)
{
    return m_eStopWinOrderLimitPriceMode = eStopWinOrderLimitPriceMode;
}

double AccountTrackerSetting::GetStopWinOrderLimitPriceDelta() const
{
    return m_dStopWinOrderLimitPriceDelta;
}

void AccountTrackerSetting::SetStopWinOrderLimitPriceDelta(double dStopWinOrderLimitPriceDelta)
{
    m_dStopWinOrderLimitPriceDelta = dStopWinOrderLimitPriceDelta;
}


bool AccountTrackerSetting::IsStopLoss() const
{
    return m_bStopLoss;
}

void AccountTrackerSetting::SetStopLoss(bool bStopLoss)
{
    m_bStopLoss = bStopLoss;
}

double AccountTrackerSetting::GetStopLossPrice() const
{
    return m_dStopLossPrice;
}

void AccountTrackerSetting::SetStopLossPrice(double dStopLossPrice)
{
    m_dStopLossPrice = dStopLossPrice;
}

StopLossPriceMode AccountTrackerSetting::GetStopLossPriceMode() const
{
    return m_eStopLossPriceMode;
}

void AccountTrackerSetting::SetStopLossPriceMode(StopLossPriceMode eStopLossPriceMode)
{
    m_eStopLossPriceMode = eStopLossPriceMode;
}

StopLossOrderType AccountTrackerSetting::GetStopLossOrderType() const
{
    return m_eStopLossOrderType;
}

void AccountTrackerSetting::SetStopLossOrderType(StopLossOrderType eStopLossOrderType)
{
    m_eStopLossOrderType = eStopLossOrderType;
}

StopLossOrderLimitPriceMode AccountTrackerSetting::GetStopLossOrderLimitPriceMode() const
{
    return m_eStopLossOrderLimitPriceMode;
}


void AccountTrackerSetting::SetStopLossOrderLimitPriceMode(StopLossOrderLimitPriceMode eStopLossOrderLimitPriceMode)
{
    m_eStopLossOrderLimitPriceMode = eStopLossOrderLimitPriceMode;
}

double AccountTrackerSetting::GetStopLossOrderLimitPriceDelta() const
{
    return m_dStopLossOrderLimitPriceDelta;
}

void AccountTrackerSetting::SetStopLossOrderLimitPriceDelta(double dStopLossOrderLimitPriceDelta)
{
    m_dStopLossOrderLimitPriceDelta = dStopLossOrderLimitPriceDelta;
}

void AccountTrackerSetting::SetInstrument(Instrument *pInstrument)
{
    m_pInstrument = pInstrument;
}

Instrument* AccountTrackerSetting::GetInstrument() const
{
    return m_pInstrument;
}

bool AccountTrackerSetting::IsTracking(Instrument *pInstrument) const
{
    return m_pInstrument != nullptr &&  m_pInstrument->GetID() == pInstrument->GetID();
}

OrderSubmitMode AccountTrackerSetting::GetOrderSubmitMode() const
{
    return m_eOrderSubmitMode;
}

void AccountTrackerSetting::SetOrderSubmitMode(OrderSubmitMode eOrderSubmitMode) const
{
    m_eOrderSubmitMode = eOrderSubmitMode;
}
