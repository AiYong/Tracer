#ifndef _TRACKER_MARKETDATA_H_
#define _TRACKER_MARKETDATA_H_

#include <QObject>
#include <QDateTime>

/**
 * @brief 行情
 */
class MarketData
{
public:

    /**
     * @brief MarketData
     */
    MarketData();

    /**
     * @brief MarketData
     * @param timestamp
     * @param lastPrice
     * @param lastVolume
     * @param lastAmount
     * @param amount
     * @param volume
     * @param highestLimitPrice
     * @param lowestLimitPrice
     * @param openInterest
     * @param preOpenInterest
     * @param openPrice
     * @param highestPrice
     * @param lowestPrice
     * @param settlementPrice
     * @param preClosePrice
     * @param preSettlementPrice
     * @param bidPrice1
     * @param bidVolume1
     * @param askPrice1
     * @param askVolume1
     */
    MarketData(
            QDateTime const& timestamp,
            double lastPrice,
            size_t lastVolume,
            double lastAmount,
            double amount,
            size_t volume,
            double highestLimitPrice,
            double lowestLimitPrice,
            size_t openInterest,
            size_t preOpenInterest,
            double openPrice,
            double highestPrice,
            double lowestPrice,
            double settlementPrice,
            double preClosePrice,
            double preSettlementPrice,
            double bidPrice1,
            size_t   bidVolume1,
            double askPrice1,
            size_t  askVolume1
            );


    /**
     * @brief MarketData
     * @param timestamp
     * @param lastPrice
     * @param lastVolume
     * @param lastAmount
     * @param amount
     * @param volume
     * @param highestLimitPrice
     * @param lowestLimitPrice
     * @param openInterest
     * @param preOpenInterest
     * @param openPrice
     * @param highestPrice
     * @param lowestPrice
     * @param settlementPrice
     * @param preClosePrice
     * @param preSettlementPrice
     * @param bidPrice1
     * @param bidVolume1
     * @param askPrice1
     * @param askVolume1
     * @param bidPrice2
     * @param bidVolume2
     * @param askPrice2
     * @param askVolume2
     */
    MarketData(
            QDateTime const& timestamp,
            double lastPrice,
            size_t lastVolume,
            double lastAmount,
            double amount,
            size_t volume,
            double highestLimitPrice,
            double lowestLimitPrice,
            size_t openInterest,
            size_t preOpenInterest,
            double openPrice,
            double highestPrice,
            double lowestPrice,
            double settlementPrice,
            double preClosePrice,
            double preSettlementPrice,
            double bidPrice1,
            size_t   bidVolume1,
            double askPrice1,
            size_t  askVolume1,
            double bidPrice2,
            size_t   bidVolume2,
            double askPrice2,
            size_t  askVolume2
            );

    /**
     * @brief MarketData
     * @param timestamp
     * @param lastPrice
     * @param lastVolume
     * @param lastAmount
     * @param amount
     * @param volume
     * @param highestLimitPrice
     * @param lowestLimitPrice
     * @param openInterest
     * @param preOpenInterest
     * @param openPrice
     * @param highestPrice
     * @param lowestPrice
     * @param settlementPrice
     * @param preClosePrice
     * @param preSettlementPrice
     * @param bidPrice1
     * @param bidVolume1
     * @param askPrice1
     * @param askVolume1
     * @param bidPrice2
     * @param bidVolume2
     * @param askPrice2
     * @param askVolume2
     * @param bidPrice3
     * @param bidVolume3
     * @param askPrice3
     * @param askVolume3
     */
    MarketData(
            QDateTime const& timestamp,
            double lastPrice,
            size_t lastVolume,
            double lastAmount,
            double amount,
            size_t volume,
            double highestLimitPrice,
            double lowestLimitPrice,
            size_t openInterest,
            size_t preOpenInterest,
            double openPrice,
            double highestPrice,
            double lowestPrice,
            double settlementPrice,
            double preClosePrice,
            double preSettlementPrice,
            double bidPrice1,
            size_t   bidVolume1,
            double askPrice1,
            size_t  askVolume1,
            double bidPrice2,
            size_t   bidVolume2,
            double askPrice2,
            size_t  askVolume2,
            double bidPrice3,
            size_t   bidVolume3,
            double askPrice3,
            size_t  askVolume3
            );

    /**
     * @brief MarketData
     * @param timestamp
     * @param lastPrice
     * @param lastVolume
     * @param lastAmount
     * @param amount
     * @param volume
     * @param highestLimitPrice
     * @param lowestLimitPrice
     * @param openInterest
     * @param preOpenInterest
     * @param openPrice
     * @param highestPrice
     * @param lowestPrice
     * @param settlementPrice
     * @param preClosePrice
     * @param preSettlementPrice
     * @param bidPrice1
     * @param bidVolume1
     * @param askPrice1
     * @param askVolume1
     * @param bidPrice2
     * @param bidVolume2
     * @param askPrice2
     * @param askVolume2
     * @param bidPrice3
     * @param bidVolume3
     * @param askPrice3
     * @param askVolume3
     * @param bidPrice4
     * @param bidVolume4
     * @param askPrice4
     * @param askVolume4
     */
    MarketData(
            QDateTime const& timestamp,
            double lastPrice,
            size_t lastVolume,
            double lastAmount,
            double amount,
            size_t volume,
            double highestLimitPrice,
            double lowestLimitPrice,
            size_t openInterest,
            size_t preOpenInterest,
            double openPrice,
            double highestPrice,
            double lowestPrice,
            double settlementPrice,
            double preClosePrice,
            double preSettlementPrice,
            double bidPrice1,
            size_t   bidVolume1,
            double askPrice1,
            size_t  askVolume1,
            double bidPrice2,
            size_t   bidVolume2,
            double askPrice2,
            size_t  askVolume2,
            double bidPrice3,
            size_t   bidVolume3,
            double askPrice3,
            size_t  askVolume3,
            double bidPrice4,
            size_t   bidVolume4,
            double askPrice4,
            size_t  askVolume4
            );

    /**
     * @brief MarketData
     * @param timestamp
     * @param lastPrice
     * @param lastVolume
     * @param lastAmount
     * @param amount
     * @param volume
     * @param highestLimitPrice
     * @param lowestLimitPrice
     * @param openInterest
     * @param preOpenInterest
     * @param openPrice
     * @param highestPrice
     * @param lowestPrice
     * @param settlementPrice
     * @param preClosePrice
     * @param preSettlementPrice
     * @param bidPrice1
     * @param bidVolume1
     * @param askPrice1
     * @param askVolume1
     * @param bidPrice2
     * @param bidVolume2
     * @param askPrice2
     * @param askVolume2
     * @param bidPrice3
     * @param bidVolume3
     * @param askPrice3
     * @param askVolume3
     * @param bidPrice4
     * @param bidVolume4
     * @param askPrice4
     * @param askVolume4
     * @param bidPrice5
     * @param bidVolume5
     * @param askPrice5
     * @param askVolume5
     */
    MarketData(
            QDateTime const& timestamp,
            double lastPrice,
            size_t lastVolume,
            double lastAmount,
            double amount,
            size_t volume,
            double highestLimitPrice,
            double lowestLimitPrice,
            size_t openInterest,
            size_t preOpenInterest,
            double openPrice,
            double highestPrice,
            double lowestPrice,
            double settlementPrice,
            double preClosePrice,
            double preSettlementPrice,
            double bidPrice1,
            size_t   bidVolume1,
            double askPrice1,
            size_t  askVolume1,
            double bidPrice2,
            size_t   bidVolume2,
            double askPrice2,
            size_t  askVolume2,
            double bidPrice3,
            size_t   bidVolume3,
            double askPrice3,
            size_t  askVolume3,
            double bidPrice4,
            size_t   bidVolume4,
            double askPrice4,
            size_t  askVolume4,
            double bidPrice5,
            size_t   bidVolume5,
            double askPrice5,
            size_t  askVolume5
            );

    /**
      * @brief MarketData
      */
     MarketData(MarketData const&);

     /**
      * @brief operator =
      * @param from
      * @return
      */
     MarketData &operator=(MarketData const& from);

     /**
     *
     */
    ~MarketData();

public:

     QDateTime const& GetTimestamp() const;

     /**
     * @brief getLastPrice
     * @return
     */
    double GetLastPrice()  const;

    /**
     * @brief setLastPrice
     * @param lastPrice
     */
    void SetLastPrice(double lastPrice);

    /**
     * @brief getLastVolume
     * @return
     */
    size_t GetLastVolume() const;

    /**
     * @brief setLastVolume
     * @param volume
     */
    void SetLastVolume(size_t volume);

    /**
     * @brief getLastAmount
     * @return
     */
    double GetLastAmount() const;

    /**
     * @brief setLastAmount
     * @param lastAmount
     */
    void SetLastAmount(double lastAmount);

    /**
     * @brief getAmount
     * @return
     */
    double GetAmount() const;

    /**
     * @brief setAmount
     * @param amount
     */
    void SetAmount(double amount);

    /**
     * @brief getVolume
     * @return
     */
    size_t GetVolume() const;

    /**
     * @brief setVolume
     * @param volume
     */
    void SetVolume(size_t volume);

    /**
     * @brief getHighestLimitPrice
     * @return
     */
    double GetHighestLimitPrice() const;

    /**
     * @brief setHighestLimitPrice
     * @param highestLimitPrice
     */
    void SetHighestLimitPrice(double highestLimitPrice);

    /**
     * @brief getLowestLimitPrice
     * @return
     */
    double GetLowestLimitPrice() const;

    /**
     * @brief setLowestLimitPrice
     * @param lowestLimitPrice
     */
    void SetLowestLimitPrice(double lowestLimitPrice);

    /**
     * @brief getOpenInterest
     * @return
     */
    size_t GetOpenInterest() const;

    /**
     * @brief setOpenInterest
     * @param openInterest
     */
    void SetOpenInterest(size_t openInterest);

    /**
     * @brief getPreOpenInterest
     * @return
     */
    size_t GetPreOpenInterest() const;

    /**
     * @brief setPreOpenInterest
     * @param openInterest
     */
    void SetPreOpenInterest(size_t openInterest);

    /**
     * @brief getOpenPrice
     * @return
     */
    double  GetOpenPrice() const;

    /**
     * @brief setOpenPrice
     * @param openPrice
     */
    void SetOpenPrice(double openPrice);

    /**
     * @brief getHighestPrice
     * @return
     */
    double GetHighestPrice() const;

    /**
     * @brief setHighestPrice
     * @param highestPrice
     */
    void SetHighestPrice(double highestPrice);

    /**
     * @brief getLowestPrice
     * @return
     */
    double GetLowestPrice() const;

    /**
     * @brief setLowestPrice
     * @param lowestPrice
     */
    void SetLowestPrice(double lowestPrice);

    /**
     * @brief getSettlementPrice
     * @return
     */
    double GetSettlementPrice() const;

    /**
     * @brief setSettlementPrice
     * @param settlementPrice
     */
    void SetSettlementPrice(double settlementPrice);

    /**
     * @brief getPreClosePrice
     * @return
     */
    double GetPreClosePrice()const;

    /**
     * @brief setPreClosePrice
     * @param preClosePrice
     */
    void SetPreClosePrice(double preClosePrice);

    /**
     * @brief getPreSettlementPrice
     */
    double GetPreSettlementPrice() const;

    /**
     * @brief setPreSettlementPrice
     * @param preSettlementPrice
     */
    void SetPreSettlementPrice(double preSettlementPrice);

    /**
     * @brief getDepth
     * @return
     */
    size_t GetDepth()const;

    /**
     * @brief setDepth
     * @param depth
     */
    void SetDepth(size_t depth);

    /**
     * @brief getMaxDepth
     * @return
     */
    size_t GetMaxDepth()const;

    /**
     * @brief getBidPrice
     * @param depth
     * @return
     */
    double GetBidPrice(size_t depth)const;

    /**
     * @brief setBidPrice
     * @param depth
     * @param bidPrice
     */
    void SetBidPrice(size_t depth,double bidPrice);

    /**
     * @brief getBidVolume
     * @param depth
     * @return
     */
    size_t GetBidVolume(size_t depth) const;

    /**
     * @brief setBidVolume
     * @param depth
     * @param bidVolume
     */
    void SetBidVolume(size_t depth,size_t bidVolume);

    /**
     * @brief getAskPrice
     * @param depth
     * @return
     */
    double GetAskPrice(size_t depth)const;

    /**
     * @brief setAskPrice
     * @param depth
     * @param askPrice
     */
    void SetAskPrice(size_t depth,double askPrice);

    /**
     * @brief getAskVolume
     * @param depth
     * @return
     */
    size_t GetAskVolume(size_t depth) const;

    /**
     * @brief setAskVolume
     * @param depth
     * @param askVolume
     */
    void SetAskVolume(size_t depth,size_t askVolume);

private:

    QDateTime mTimestamp;
    double mLastPrice;
    size_t mLastVolume;
    size_t mLastAmount;
    size_t mAmount;
    size_t mVolume;
    double mHighestLimitPrice;
    double mLowestLimitPrice;
    size_t mOpenInterest;
    size_t mPreOpenInterest;
    double mOpenPrice;
    double mHighestPrice;
    double mLowestPrice;
    double mSettlementPrice;
    double mPreOpenPrice;
    double mPreClosePrice;
    double mPreSettlementPrice;
    size_t  mDepth;
    size_t  mMaxDepth;
    double mBidPrice[5];
    size_t  mBidVolume[5];
    double mAskPrice[5];
    size_t mAskVolume[5];
};

#endif // _TRACKER_MARKETDATA_H_
