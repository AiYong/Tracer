#ifndef _TRACKER_ACCOUNTTRACKOPTIONS_H_
#define _TRACKER_ACCOUNTTRACKOPTIONS_H_

#include <QMap>
#include <QString>

#include <Direction.h>
#include <HedgeFlag.h>


class Order;
class Account;
class Position;
class Instrument;
class MarketData;

enum OpenPriceMode
{
    opmLimitPrice,
    opmMarketPrice
};

enum OpenLimitPriceMode
{
    olpmDelta,
    olpmLastPrice
};

enum ClosePriceMode
{
    cpmLimitPrice,
    cpmMarketPrice
};

enum CloseLimitPriceMode
{
    clpmDelta,
    clpmLastPrice
};

/**
 * @brief 止损模式
 */
enum StopLossPriceMode
{
    slpmDirect,//按点数
    slpmRatio//按比例
};

enum StopLossOrderType
{
    slotLimitPrice,
    slotMarketPrice
};

enum StopLossOrderLimitPriceMode
{
    slolpmDelta,
    slopmLastPrice
};

/**
 * @brief 止盈模式
 */
enum StopWinPriceMode
{
    swpmDirect,//按点数
    swpmRatio//按比例
};

enum StopWinOrderType
{
    swotLimitPrice,
    swotMarketPrice
};


enum StopWinOrderLimitPriceMode
{
    swolpmDelta,
    swopmLastPrice
};


/**
 * @brief 持仓限制模式
 */
enum PositionLimitMode
{
    plmMargin,//按保证金
    plmQuantity//按数量
};


/**
 * @brief 持仓超出限额处理模式
 */
enum BeyondPositionLimitProcessMode
{
    bplpmClose,//平仓
    bplpmPrompt//提示
};

/**
 * @brief 报单模式
 */
enum OrderSubmitMode
{
    osmSubmit,//Order被提交时
    osmQueued,//Order排队时
    osmTraded//Order成交时
};


/**
 * @brief The AccountTrackerSetting class
 */
class AccountTrackerSetting
{
public:

    /**
     * @brief AccountTrackSettings
     * @param pAccount
     */
    AccountTrackerSetting(Account *pTradeAccount);

    /**
     *
     */
    ~AccountTrackerSetting();

public://账号

    /**
     * @brief GetID
     * @return
     */
    int GetID() const;

    /**
     * @brief 返回交易账号
     * @return
     */
    Account* GetTradeAccount() const;


    /**
     * @brief 跟踪账号
     * @return
     */
    Account* GetTrackAccount() const;

    /**
     * @brief 设置跟踪账号
     * @param pAccount
     */
    void SetTrackAccount(Account *pAccount);


public://持仓限制

    /**
     * @brief 返回持仓限制模式
     * @return
     */
    PositionLimitMode GetPositionLimitMode() const;

    /**
     * @brief 设置持仓限制模式
     * @param ePositionLimitMode
     */
    void SetPositionLimitMode(PositionLimitMode ePositionLimitMode);

    /**
     * @brief GetBeyondPositionLimitProcessMode
     * @return 
     */
    BeyondPositionLimitProcessMode GetBeyondPositionLimitProcessMode() const;
    
    /**
     * @brief SetBeyondPositionLimitProcessMode
     * @param eBeyondPositionLimitProcessMode
     */
    void SetBeyondPositionLimitProcessMode(BeyondPositionLimitProcessMode eBeyondPositionLimitProcessMode);
    
    /**
     * @brief 返回持仓限制
     * @return
     */
    double GetPositionLimit() const;

    /**
     * @brief 设置持仓限制
     * @param dPositionLimit
     */
    void SetPositionLimit(double dPositionLimit);

public://开仓设置


    OpenPriceMode GetOpenPriceMode() const;


    void SetOpenPriceMode(OpenPriceMode eOpenPriceMode);


    OpenLimitPriceMode GetOpenLimitPriceMode() const;


    void SetOpenLimitPriceMode(OpenLimitPriceMode eOpenLimitPriceMode);


    double GetOpenLimitPriceDelta() const;


    void SetOpenLimitPriceDelta(double eDelta);

public://平仓设置


    ClosePriceMode GetClosePriceMode() const;


    void SetClosePriceMode(ClosePriceMode eClosePriceMode);


    CloseLimitPriceMode GetCloseLimitPriceMode() const;


    void SetCloseLimitPriceMode(CloseLimitPriceMode eCloseLimitPriceMode);


    double GetCloseLimitPriceDelta() const;


    void SetCloseLimitPriceDelta(double eDelta);


public: //止盈设置

    /**
     * @brief 返回知否止盈
     * @return
     */
    bool IsStopWin() const;

    /**
     * @brief 设置是否止盈
     * @param bStopWin
     */
    void SetStopWin(bool bStopWin) const;

    /**
     * @brief 返回止盈价格
     * @return
     */
    double GetStopWinPrice() const;

    /**
     * @brief 设置止盈价格
     * @param dStopWinPrice
     */
    void SetStopWinPrice(double dStopWinPrice);

    /**
     * @brief 返回止盈价格模式
     * @return
     */
    StopWinPriceMode GetStopWinPriceMode() const;

    /**
     * @brief 设置止盈价格模式
     * @param eStopWinPriceMode
     */
    void SetStopWinPriceMode(StopWinPriceMode eStopWinPriceMode);

    /**
     * @brief GetStopWinOrderType
     * @return
     */
    StopWinOrderType GetStopWinOrderType() const;

    /**
     * @brief SetStopWinOrderType
     * @param eStopWinOrderType
     */
    void SetStopWinOrderType(StopWinOrderType eStopWinOrderType);

    /**
     * @brief GetStopWinOrderLimitPriceMode
     * @return
     */
    StopWinOrderLimitPriceMode GetStopWinOrderLimitPriceMode() const;

    /**
     * @brief SetStopWinOrderLimitPriceMode
     * @param eStopWinOrderLimitPriceMode
     */
    void SetStopWinOrderLimitPriceMode(StopWinOrderLimitPriceMode eStopWinOrderLimitPriceMode);

    /**
     * @brief GetStopLossOrderLimitPriceDelta
     * @return
     */
    double GetStopWinOrderLimitPriceDelta() const;

    /**
     * @brief SetStopLossOrderLimitPriceDelta
     * @param dStopLossOrderLimitPriceDelta
     */
    void SetStopWinOrderLimitPriceDelta(double dStopWinOrderLimitPriceDelta);


public://止损设置

    /**
     * @brief 返回是否止损
     * @return
     */
    bool IsStopLoss() const;

    /**
     * @brief 设置是否止损
     * @param bStopLoss
     */
    void SetStopLoss(bool bStopLoss);

    /**
     * @brief 返回止损价格
     * @return
     */
    double GetStopLossPrice() const;

    /**
     * @brief 设置止损价格
     * @param StopLossPrice
     */
    void SetStopLossPrice(double StopLossPrice);

    /**
     * @brief 返回止损价格模式
     * @return
     */
    StopLossPriceMode GetStopLossPriceMode() const;

    /**
     * @brief 设置止损价格模式
     * @param eStopLossPriceMode
     */
    void SetStopLossPriceMode(StopLossPriceMode eStopLossPriceMode);

    /**
     * @brief GetStopLossOrderType
     * @return
     */
    StopLossOrderType GetStopLossOrderType() const;

    /**
     * @brief SetStopLossOrderType
     * @param eStopLossOrderType
     */
    void SetStopLossOrderType(StopLossOrderType eStopLossOrderType);

    /**
     * @brief GetStopWinOrderLimitPriceMode
     * @return
     */
    StopLossOrderLimitPriceMode GetStopLossOrderLimitPriceMode() const;

    /**
     * @brief SetStopWinOrderLimitPriceMode
     * @param eStopWinOrderLimitPriceMode
     */
    void SetStopLossOrderLimitPriceMode(StopLossOrderLimitPriceMode eStopLossOrderLimitPriceMode);

    /**
     * @brief GetStopLossOrderLimitPriceDelta
     * @return
     */
    double GetStopLossOrderLimitPriceDelta() const;

    /**
     * @brief SetStopLossOrderLimitPriceDelta
     * @param dStopLossOrderLimitPriceDelta
     */
    void SetStopLossOrderLimitPriceDelta(double dStopLossOrderLimitPriceDelta);


public:

    /**
     * @brief 设置合约
     * @param pInstrument
     */
    void SetInstrument(Instrument *pInstrument);

    /**
     * @brief 返回跟踪合约
     * @return
     */
    Instrument* GetInstrument() const;

    /**
     * @brief IsTracking
     * @param pInstrument
     * @return
     */
    bool IsTracking(Instrument *pInstrument) const;


public:

    /**
     * @brief GetOrderSubmitMode
     * @return
     */
    OrderSubmitMode GetOrderSubmitMode() const;

    /**
     * @brief GetOrderSubmitMode
     * @param eOrderSubmitMode
     */
    void SetOrderSubmitMode(OrderSubmitMode eOrderSubmitMode) const;


private:

    Account *m_pTradeAccount;
    Account *m_pTrackAccount;
    PositionLimitMode m_ePositionLimitMode;
    double m_dPositionLimit;
    bool m_bIsStopWin;
    double m_dStopWinPrice;
    StopWinPriceMode m_eStopWinPriceMode;
    bool m_bIsStopLoss;
    double m_dStopLossPrice;
    StopLossPriceMode m_eStopLossPriceMode;
    OrderSubmitMode m_eOrderSubmitMode;

};

#endif // _TRACKER_ACCOUNTTRACKOPTIONS_H_
