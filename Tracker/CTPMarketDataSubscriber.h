#ifndef _TRACKER_CTPMARKETDATASUBSCRIBER_H_
#define _TRACKER_CTPMARKETDATASUBSCRIBER_H_

#include <QMap>
#include <QList>
#include <QString>
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>

#include "Broker.h"
#include "Account.h"
#include "MarketData.h"

#include "MarketDataSubscriber.h"
#include "ThostFtdcMdApi.h"

class CTPMarketDataSubscriber : public MarketDataSubscriber,public CThostFtdcMdSpi
{
public:

    CTPMarketDataSubscriber(Account const* pAccount);

    ~CTPMarketDataSubscriber();

public:

    bool Initialize() ;

    void Destroy();

public:


    void Subscribe(MarketDataListener *pListener, QList<Instrument*> const& lstInstrument);


    void UnSubscribe(MarketDataListener *pListener,QList<Instrument*> const& lstInstrument);

public:

    void OnFrontConnected();

    void OnFrontDisconnected(int nReason);

    void OnHeartBeatWarning(int nTimeLapse);

    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

private:

    Account *m_pAccount;
    QMap<QString,QList<MarketDataListener*>> m_mMarketDataListener;
    QMap<QString,Instrument*> m_lInstruments;
    CThostFtdcReqUserLoginField m_oLoginInfo;
    CThostFtdcRspInfoField m_oLoginResult;
    bool mDisconnect;
    QList<MarketData*> m_lMarketData;
    QString mName;
    QDateTime mTimestamp;
    int m_nRequestNumber;
    CThostFtdcMdApi *m_pMdApi;
    QMutex m_mLock;

};

#endif // _TRACKER_CTPMARKETDATASUBSCRIBER_H_
