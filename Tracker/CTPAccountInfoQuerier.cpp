#include "CTPAccountInfoQuerier.h"
#include "Broker.h"
#include <thread>

CTPAccountInfoQuerier::CTPAccountInfoQuerier(Account *pAccount)
{

}

CTPAccountInfoQuerier::~CTPAccountInfoQuerier()
{

}

void CTPAccountInfoQuerier::OnFrontConnected()
{
    m_pTradeApi->ReqUserLogin(&m_oLoginInfo,m_nRequestNumber++);
}

void CTPAccountInfoQuerier::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
    if(pRspInfo == nullptr || pRspInfo != nullptr && pRspInfo->ErrorID == 0)
    {
        m_bCompleted = true;
        m_cWaitCondition.notify_one();
    }
}

void CTPAccountInfoQuerier::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if((pRspInfo == nullptr || pRspInfo != nullptr && pRspInfo->ErrorID == 0) && pInvestor == nullptr)
    {
        memcpy(&m_oInvestor,pInvestor,sizeof(CThostFtdcInvestorField));
        m_bCompleted = true;
        m_cWaitCondition.notify_one();
    }
}

void CTPAccountInfoQuerier::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if((pRspInfo == nullptr || pRspInfo != nullptr && pRspInfo->ErrorID == 0) && pInstrument == nullptr)
    {
        CThostFtdcInstrumentField *pNewInstrument = new CThostFtdcInstrumentField;
        memcpy(&pNewInstrument,pInstrument,sizeof(CThostFtdcInstrumentField));
        m_lInstruments.append(pNewInstrument);
        if(bIsLast)
        {
            m_bCompleted = true;
            m_cWaitCondition.notify_one();
        }
    }
}

void CTPAccountInfoQuerier::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if((pRspInfo == nullptr || pRspInfo != nullptr && pRspInfo->ErrorID == 0) && pTradingAccount == nullptr)
    {
        memcpy(&m_oTradingAccount,pTradingAccount,sizeof(CThostFtdcTradingAccountField));
        m_bCompleted = true;
        m_cWaitCondition.notify_one();
    }
}

void CTPAccountInfoQuerier::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if( pInstrumentMarginRate != nullptr && (pRspInfo == nullptr || (pRspInfo!= nullptr && pRspInfo->ErrorID == 0 )) )
    {
        CThostFtdcInstrumentMarginRateField *pNewInstrumentMarginRate = new CThostFtdcInstrumentMarginRateField;
        memcpy(pNewInstrumentMarginRate,pInstrumentMarginRate,sizeof(CThostFtdcInstrumentMarginRateField));
        m_lInstrumentMarginRates.insert(pNewInstrumentMarginRate->InstrumentID,pNewInstrumentMarginRate);
        if(bIsLast)
        {
            m_bCompleted = true;
            m_cWaitCondition.notify_one();
        }
    }
}

void CTPAccountInfoQuerier::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if( pInstrumentMarginRate != nullptr && (pRspInfo == nullptr || (pRspInfo!= nullptr && pRspInfo->ErrorID == 0 )) )
    {
        CThostFtdcInstrumentCommissionRateField *pNewInstrumentCommissionRate = new CThostFtdcInstrumentCommissionRateField;
        memcpy(pNewInstrumentCommissionRate,pInstrumentCommissionRate,sizeof(CThostFtdcInstrumentCommissionRateField));
        m_lInstrumentMarginRates.insert(pNewInstrumentCommissionRate->InstrumentID,pNewInstrumentCommissionRate);
        if(bIsLast)
        {
            m_bCompleted = true;
            m_cWaitCondition.notify_one();
        }
    }
}


std::shared_ptr<AccountInfo> CTPAccountInfoQuerier::Query()
{
    std::shared_ptr<AccountInfo> oResult;
    m_nRequestNumber = 1;
    strcpy(m_oLoginInfo.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oLoginInfo.UserID,m_pAccount->GetId().toStdString().c_str());
    strcpy(m_oLoginInfo.Password,m_pAccount->GetPassword().toStdString().c_str());
    m_pTradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
    m_pTradeApi->SubscribePrivateTopic(THOST_TERT_QUICK);
    m_pTradeApi->SubscribePublicTopic(THOST_TERT_QUICK);
    m_pTradeApi->RegisterSpi(this);
    QStringList lTradeUrls = m_pAccount->GetBroker()->GetTradeUrl();
    for(auto iPos = lTradeUrls.begin(); iPos != lTradeUrls.end();iPos++)
    {
        QString strUrl = *iPos;
        m_pTradeApi->RegisterFront(const_cast<char*>(strUrl.toStdString().c_str()));
    }
    m_bConnected = false;
    //初始化登录
    m_pTradeApi->Init();
    std::unique_lock<std::mutex> oLocker(m_lLock);
    auto oWaitCondition = [&]()->bool {
        return m_bCompleted == true;
    };
    if(!m_cWaitCondition.wait_for(std::chrono::seconds(10),oWaitCondition))
    {
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //查询投资人信息
    memset(&m_oQryInvestor,0,sizeof(CThostFtdcQryInvestorField));
    strcpy(m_oQryInvestor.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oQryInvestor.InvestorID,m_pAccount->GetID());
    m_bCompleted = false;
    m_pTradeApi->ReqQryInvestor(&m_oQryInvestor,m_nRequestNumber++);
    if(!m_cWaitCondition.wait_for(std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //查询账户信息
    memset(&m_oQryTradingAccount,0,sizeof(CThostFtdcQryInvestorField));
    strcpy(m_oQryTradingAccount.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oQryTradingAccount.InvestorID,m_pAccount->GetID());
    m_bCompleted = false;
    m_pTradeApi->ReqQryTradingAccount(&m_oTradingAccount,m_nRequestNumber++);
    if(!m_cWaitCondition.wait_for(std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //查询合约
    m_bCompleted = false;
    memset(&m_oQryInstrument,0,sizeof(CThostFtdcQryInstrumentField));
    m_pTradeApi->ReqQryInstrument(&m_oQryInstrument,m_nRequestNumber++);
    if(!m_cWaitCondition.wait_for(std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //查询费率
    memset(&m_oQryInstrumentCommissionRate,0,sizeof(CThostFtdcQryInstrumentCommissionRateField));
    strcpy(m_oQryInstrumentCommissionRate.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oQryInstrumentCommissionRate.InvestorID,m_pAccount->GetID());
    m_pTradeApi->ReqQryInstrumentCommissionRate(&m_oQryInstrumentCommissionRate,m_nRequestNumber++);
    if(!m_cWaitCondition.wait_for(std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //查询保证金率
    memset(&m_oQryInstrumentMarginRate,0,sizeof(CThostFtdcQryInstrumentMarginRateField));
    strcpy(m_oQryInstrumentMarginRate.BrokerID,m_pAccount->GetBroker()->GetId().toStdString().c_str());
    strcpy(m_oQryInstrumentMarginRate.InvestorID,m_pAccount->GetID());
    if(!m_cWaitCondition.wait_for(std::chrono::seconds(10),oWaitCondition))
    {
        Clear();
        return oResult;
    }
    m_pTradeApi->RegisterSpi(nullptr);
    m_pTradeApi->Release();
    m_pTradeApi = nullptr;

    return oResult;
}
