#ifndef _TRACKER_CTPTRADEPROCESSOR_H_
#define _TRACKER_CTPTRADEPROCESSOR_H_

#include <mutex>
#include <condition_variable>

#include <QMap>
#include <QQueue>

#include "OrderListener.h"
#include "OrderProcessor.h"
#include "ThostFtdcTraderApi.h"


class CTPOrder
{
public:

    CTPOrder(Order *pOrder,OrderListener *pOrderListener);

    ~CTPOrder();

public:

    Order* GetOrder() const;

    OrderListener* GetOrderListener() const;

    CThostFtdcInputOrderField const& GetInputOrder() const;

    CThostFtdcInputOrderActionField const& GetInputOrderAction() const;

    void SetOrderResponse(CThostFtdcOrderField const& oOrderResponse);

private:

    void Init();

    Order *m_pOrder;
    OrderListener *m_pOrderListener;
    CThostFtdcInputOrderField m_oInputOrder;
    CThostFtdcInputOrderActionField m_oInputOrderAction;
    CThostFtdcOrderField m_oOrderResponse;

};

enum CTPOrderOperationType
{
    ootSubmit,
    ootCancel
};

struct CTPOrderOperation
{
    Order const*pOrder;
    OrderListener const*pOrderListener;
    CTPOrderOperationType eType;
};

class CTPOrderProcessor : public CThostFtdcTraderSpi ,public OrderProcessor
{
public:

    CTPOrderProcessor(Account *pAccount);


    ~CTPOrderProcessor();

public:

    bool Initialize();

    void Destroy();
public:

    void operator()();

public:

    void Submit(Order const* pOrder,OrderListener *pOrderListener);


    void Cancel(Order const* pOrder);

public:

    void OnFrontConnected();

    void OnFrontDisconnected(int nReason);

    void OnHeartBeatWarning(int nTimeLapse);

    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast) ;

    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast) ;

    void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast) ;

    void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast) ;

    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast) ;

    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    void OnRtnOrder(CThostFtdcOrderField *pOrder) ;

    void OnRtnTrade(CThostFtdcTradeField *pTrade) ;

    void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) ;

    void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) ;

    void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) ;

    void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) ;

private:

    CThostFtdcTraderApi *m_pTradeApi;
    CThostFtdcInputOrderField m_oOrder;
    CThostFtdcInputOrderActionField m_oOrderAction;
    CThostFtdcRspInfoField m_oRequstResult;
    int32_t m_nRequestNumber;
    int32_t m_nOrderActionRef;
    int64_t m_nOrderRef;
    int64_t m_nDateNumber;
    CThostFtdcQryOrderField m_oQryOrder;
    CThostFtdcReqUserLoginField m_oLoginInfo;
    CThostFtdcRspUserLoginField m_oLoginResult;
    CThostFtdcSettlementInfoConfirmField m_oSettlementInfoConfirm;
    bool m_bStop;
    bool m_bConnected;
    std::mutex m_lLock;
    std::condition_variable m_cWaitCondition;
    QMap<QString,CTPOrder*> m_hOrders;
    QQueue<CTPOrderOperation> m_qOrders;
};

#endif // _TRACKER_CTPTRADEPROCESSOR_H_
