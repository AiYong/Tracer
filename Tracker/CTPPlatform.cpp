#include "CTPPlatform.h"
#include "ThostFtdcTraderApi.h"
#include "CTPOrderProcessor.h"
#include "CTPOrderSubscriber.h"
#include "CTPMarketDataSubscriber.h"


class CTPAccountInfoQuerier : public CThostFtdcTraderSpi
{
public:

    CTPAccountInfoQuerier(Account *pAccount)
    {

    }

    ~CTPAccountInfoQuerier()
    {

    }

public:

    void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {

    }

    void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {

    }

    void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {

    }

public:

    shared_ptr<AccountInfo> Query()
    {

    }


};



CTPPlatform::CTPPlatform()
{

}

CTPPlatform::~CTPPlatform()
{

}

shared_ptr<AccountInfo> CTPPlatform::QueryAccountInfo(const Account *pAccount)
{
    CTPAccountInfoQuerier oQuerier(pAccount);
    return oQuerier.Query();
}

shared_ptr<OrderProcessor> CTPPlatform::CreateOrderProcessor(const Account *pAccount)
{
    shared_ptr<OrderProcessor> oResult;
    CTPOrderProcessor *pOrderProcessor = new CTPOrderProcessor(pAccount);
    if(pOrderProcessor->Initialize())
    {
        oResult.reset(pOrderProcessor);
    }
    else
    {
        delete pOrderProcessor;
    }
    return oResult;
}

shared_ptr<OrderSubscriber> CTPPlatform::CreateOrderSubsriber(const Account *pAccount)
{
    shared_ptr<OrderSubscriber> oResult;
    CTPOrderSubscriber *pOrderSubscriber = new CTPOrderSubscriber(pAccount);
    if(pOrderSubscriber->Initialize())
    {
        oResult.reset(pOrderSubscriber);
    }
    else
    {
        delete pOrderSubscriber;
    }
    return oResult;
}

shared_ptr<MarketDataSubscriber> CTPPlatform::CreateMarketDataSubscriber(const Account *pAccount)
{
    if(m_pMarketDataSubscriber == nullptr)
    {
        CTPMarketDataSubscriber *pMarketDataSubscriber = new CTPMarketDataSubscriber(pAccount);
        if(pMarketDataSubscriber->Initialize())
        {
            m_pMarketDataSubscriber.reset(pMarketDataSubscriber);
        }
        else
        {
            delete pMarketDataSubscriber;
        }
    }
    return m_pMarketDataSubscriber;
}
