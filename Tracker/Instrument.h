#ifndef _TRACKER_INSTRUMENT_H_
#define _TRACKER_INSTRUMENT_H_

#include <QObject>
#include <QDateTime>
#include <QString>

class MarketData;

class Instrument
{
public:

    Instrument(QString const& strID,QString const& Name,QString const& strVariety,
               QString const& strExchange,double dPriceMultiple,double dPriceTick,
               QDate const& oLastTradeDay,
               QTime const& oCloseTime,QTime const& oLastTradeDayCloseTime
               );

public:

    /**
     * @brief 返回合约ID
     * @return
     */
    QString const& GetID() const;
    
    /**
     * @brief 返回合约名称
     * @return 
     */
    QString const& GetName() const;

    /**
     * @brief GetVeriety
     * @return
     */
    QString const& GetVariety() const;

    /**
     * @brief GetExchange
     * @return
     */
    QString const& GetExchange() const;

    /**
     * @brief 返回合约价格乘数
     * @return
     */
    double GetPriceMultiple() const;

    /**
     * @brief 返回价格跳动最小单位
     * @return
     */
    double GetPriceTick() const;

    /**
     * @brief 返回交易日期
     * @return
     */
    QDate const& GetTradeDay() const;

    /**
     * @brief 返回最后交易日
     * @return
     */
    QDate const& GetLastTradeDay() const;

    /**
     * @brief 收盘时间
     * @return
     */
    QTime const& GetCloseTime() const;

    /**
     * @brief GetLastTradeDayCloseTime
     * @return
     */
    QTime const& GetLastTradeDayCloseTime() const;

public:

    /**
     * @brief 返回交易日最近成交价格
     * @return
     */
    double GetLastPrice() const;

    /**
     * @brief 返回交易日最近成交额
     * @return
     */
    size_t GetLastVolume() const;

    /**
     * @brief 返回交易日最高成交价格
     * @return
     */
    double GetHighestPrice() const;

    /**
     * @brief 返回交易日最低成交价格
     * @return
     */
    double GetLowestPrice() const;

    /**
     * @brief 返回交易日收盘价格
     * @return
     */
    double GetClosePrice() const;

    /**
     * @brief 返回交易日开盘价格
     * @return
     */
    double GetOpenPrice() const;

    /**
     * @brief GetPreSuttlementPrice
     * @return
     */
    double GetPreSuttlementPrice() const;

    /**
     * @brief 返回交易日结算价格
     * @return
     */
    double GetSuttlementPrice() const;

    /**
     * @brief 返回交易日成交额
     * @return
     */
    double GetAmount() const;

    /**
     * @brief 返回交易日成交量
     * @return
     */
    size_t GetVolume() const;

    /**
     * @brief 最后更新时间
     * @return
     */
    QDateTime const& GetLastUpdateTime() const;


public:

    /**
     * @brief 当前交易日，是否可交易
     * @return
     */
    bool IsTrading() const;


    /**
     * @brief Updated
     * @param pMarketData
     */
    void Updated(MarketData const*pMarketData);

    /**
     * @brief GetMarketDataList
     * @return
     */
    QList<MarketData const*> const& GetMarketDataList() const;

private:

    QString m_strID;
    QString m_strName;
    QString m_strVariety;
    QString m_strExchange;
    double m_dPriceMultiple;
    double m_dPriceTick;
    QDate m_oTradeDay;
    QDate m_oLastTradeDay;
    QTime m_oCloseTime;
    QTime m_oLastTradeDayCloseTime;

    bool m_bFirst;
    QList<MarketData const*> m_lMarketDatas;
    double m_dLastPrice;
    size_t m_nLastVolume;
    double m_dAmount;
    size_t m_nVolume;
    double m_dOpenPrice;
    double m_dClosePrice;
    double m_dHighestPrice;
    double m_dLowestPrice;
    double m_dSuttlementPrice;
    double m_dPreSuttlementPrice;
    QDateTime m_oLastUpdateTime;

};

#endif // _TRACKER_INSTRUMENT_H_
