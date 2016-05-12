#ifndef _TRACKER_CTPORDERSUBSCRIBER_H_
#define _TRACKER_CTPORDERSUBSCRIBER_H_

#include <QMutex>
#include <QMutexLocker>

#include "Order.h"
#include "Broker.h"
#include "Account.h"
#include "Position.h"
#include "Instrument.h"
#include "OrderSubscriber.h"
#include "ThostFtdcTraderApi.h"

class CTPOrderSubscriber: public OrderSubscriber,public CThostFtdcTraderSpi
{
public:

    CTPOrderSubscriber(Account const* pAccount);

    ~CTPOrderSubscriber();

public:

    bool Initialize();

    void Destroy();

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

private:

    Order* EnsureOrder(CThostFtdcInputOrderField *pInputOrder);

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
    QMap<QString,Order*> m_hOrders;
    QMap<QString,Position*> m_hPositions;

};

#endif // _TRACKER_CTPORDERSUBSCRIBER_H_
