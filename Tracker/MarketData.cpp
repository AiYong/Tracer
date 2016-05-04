#include "MarketData.h"

MarketData::MarketData()
            :
             mTimestamp(QDateTime::currentDateTime()),
             mLastPrice(0),
             mLastVolume(0),
             mLastAmount(0),
             mAmount(0),
             mVolume(0),
             mHighestLimitPrice(0),
             mLowestLimitPrice(0),
             mOpenInterest(0),
             mPreOpenInterest(0),
             mOpenPrice(0),
             mHighestPrice(0),
             mLowestPrice(0),
             mSettlementPrice(0),
             mPreOpenPrice(0),
             mPreClosePrice(0),
             mPreSettlementPrice(0),
             mDepth(0),
             mMaxDepth(5)
    {
        memset(mBidPrice,0,40);
        memset(mBidVolume,0,20);
        memset(mAskPrice,0,40);
        memset(mAskVolume,0,20);
    }

   MarketData:: MarketData(
           QDateTime const& timestamp,
           double lastPrice,
           double lastVolume,
           size_t lastAmount,
           size_t amount,
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
            )
        :
         mTimestamp(timestamp),
         mLastPrice(lastPrice),
         mLastVolume(lastVolume),
         mLastAmount(lastAmount),
         mAmount(amount),
         mVolume(volume),
         mHighestLimitPrice(highestLimitPrice),
         mLowestLimitPrice(lowestLimitPrice),
         mOpenInterest(openInterest),
         mPreOpenInterest(preOpenInterest),
         mOpenPrice(openPrice),
         mHighestPrice(highestPrice),
         mLowestPrice(lowestPrice),
         mSettlementPrice(settlementPrice),
         mPreClosePrice(preClosePrice),
         mPreSettlementPrice(preSettlementPrice),
         mDepth(1),
         mMaxDepth(5)
   {
       mBidPrice[0] =  bidPrice1;
       mBidVolume[0] = bidVolume1;
       mAskPrice[0] = askPrice1;
       mAskVolume[0] = askVolume1;
   }


   MarketData:: MarketData(
           QDateTime const& timestamp,
           double lastPrice,
           double lastVolume,
           size_t lastAmount,
           size_t amount,
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
            )
       :
        mTimestamp(timestamp),
        mLastPrice(lastPrice),
        mLastVolume(lastVolume),
        mLastAmount(lastAmount),
        mAmount(amount),
        mVolume(volume),
        mHighestLimitPrice(highestLimitPrice),
        mLowestLimitPrice(lowestLimitPrice),
        mOpenInterest(openInterest),
        mPreOpenInterest(preOpenInterest),
        mOpenPrice(openPrice),
        mHighestPrice(highestPrice),
        mLowestPrice(lowestPrice),
        mSettlementPrice(settlementPrice),
        mPreClosePrice(preClosePrice),
        mPreSettlementPrice(preSettlementPrice),
        mDepth(2),
        mMaxDepth(5)
  {
      mBidPrice[0] =  bidPrice1;
      mBidVolume[0] = bidVolume1;
      mAskPrice[0] = askPrice1;
      mAskVolume[0] = askVolume1;
      mBidPrice[1] =  bidPrice2;
      mBidVolume[1] = bidVolume2;
      mAskPrice[1] = askPrice2;
      mAskVolume[1] = askVolume2;
  }


    MarketData::MarketData(
            QDateTime const& timestamp,
            double lastPrice,
            double lastVolume,
            size_t lastAmount,
            size_t amount,
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
            )
        :
         mTimestamp(timestamp),
         mLastPrice(lastPrice),
         mLastVolume(lastVolume),
         mLastAmount(lastAmount),
         mAmount(amount),
         mVolume(volume),
         mHighestLimitPrice(highestLimitPrice),
         mLowestLimitPrice(lowestLimitPrice),
         mOpenInterest(openInterest),
         mPreOpenInterest(preOpenInterest),
         mOpenPrice(openPrice),
         mHighestPrice(highestPrice),
         mLowestPrice(lowestPrice),
         mSettlementPrice(settlementPrice),
         mPreClosePrice(preClosePrice),
         mPreSettlementPrice(preSettlementPrice),
         mDepth(3),
         mMaxDepth(5)
   {
       mBidPrice[0] =  bidPrice1;
       mBidVolume[0] = bidVolume1;
       mAskPrice[0] = askPrice1;
       mAskVolume[0] = askVolume1;
       mBidPrice[1] =  bidPrice2;
       mBidVolume[1] = bidVolume2;
       mAskPrice[1] = askPrice2;
       mAskVolume[1] = askVolume2;
       mBidPrice[2] =  bidPrice3;
       mBidVolume[2] = bidVolume3;
       mAskPrice[2] = askPrice3;
       mAskVolume[2] = askVolume3;
   }

    MarketData::MarketData(
            QDateTime const& timestamp,
            double lastPrice,
            double lastVolume,
            size_t lastAmount,
            size_t amount,
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
            )
        :
         mTimestamp(timestamp),
         mLastPrice(lastPrice),
         mLastVolume(lastVolume),
         mLastAmount(lastAmount),
         mAmount(amount),
         mVolume(volume),
         mHighestLimitPrice(highestLimitPrice),
         mLowestLimitPrice(lowestLimitPrice),
         mOpenInterest(openInterest),
         mPreOpenInterest(preOpenInterest),
         mOpenPrice(openPrice),
         mHighestPrice(highestPrice),
         mLowestPrice(lowestPrice),
         mSettlementPrice(settlementPrice),
         mPreClosePrice(preClosePrice),
         mPreSettlementPrice(preSettlementPrice),
         mDepth(4),
         mMaxDepth(5)
   {
       mBidPrice[0] =  bidPrice1;
       mBidVolume[0] = bidVolume1;
       mAskPrice[0] = askPrice1;
       mAskVolume[0] = askVolume1;
       mBidPrice[1] =  bidPrice2;
       mBidVolume[1] = bidVolume2;
       mAskPrice[1] = askPrice2;
       mAskVolume[1] = askVolume2;
       mBidPrice[2] =  bidPrice3;
       mBidVolume[2] = bidVolume3;
       mAskPrice[2] = askPrice3;
       mAskVolume[2] = askVolume3;
       mBidPrice[3] =  bidPrice4;
       mBidVolume[3] = bidVolume4;
       mAskPrice[3] = askPrice4;
       mAskVolume[3] = askVolume4;
   }


    MarketData::MarketData(
            QDateTime const& timestamp,
            double lastPrice,
            double lastVolume,
            size_t lastAmount,
            size_t amount,
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
            )
        :
         mTimestamp(timestamp),
         mLastPrice(lastPrice),
         mLastVolume(lastVolume),
         mLastAmount(lastAmount),
         mAmount(amount),
         mVolume(volume),
         mHighestLimitPrice(highestLimitPrice),
         mLowestLimitPrice(lowestLimitPrice),
         mOpenInterest(openInterest),
         mPreOpenInterest(preOpenInterest),
         mOpenPrice(openPrice),
         mHighestPrice(highestPrice),
         mLowestPrice(lowestPrice),
         mSettlementPrice(settlementPrice),
         mPreClosePrice(preClosePrice),
         mPreSettlementPrice(preSettlementPrice),
         mDepth(5),
         mMaxDepth(5)
   {
       mBidPrice[0] =  bidPrice1;
       mBidVolume[0] = bidVolume1;
       mAskPrice[0] = askPrice1;
       mAskVolume[0] = askVolume1;
       mBidPrice[1] =  bidPrice2;
       mBidVolume[1] = bidVolume2;
       mAskPrice[1] = askPrice2;
       mAskVolume[1] = askVolume2;
       mBidPrice[2] =  bidPrice3;
       mBidVolume[2] = bidVolume3;
       mAskPrice[2] = askPrice3;
       mAskVolume[2] = askVolume3;
       mBidPrice[3] =  bidPrice4;
       mBidVolume[3] = bidVolume4;
       mAskPrice[3] = askPrice4;
       mAskVolume[3] = askVolume4;
       mBidPrice[4] =  bidPrice5;
       mBidVolume[4] = bidVolume5;
       mAskPrice[4] = askPrice5;
       mAskVolume[4] = askVolume5;
   }

     MarketData::MarketData(MarketData const& from)
     {
         this->mTimestamp = from.mTimestamp;
         this->mLastPrice =  from.mLastPrice;
         this->mLastVolume = from.mLastVolume;
         this->mLastAmount = from.mLastAmount;
         this->mAmount = from.mAmount;
         this->mVolume = from.mVolume;
         this->mHighestLimitPrice = from.mHighestLimitPrice;
         this->mLowestLimitPrice = from.mLowestLimitPrice;
         this->mOpenInterest = from.mOpenInterest;
         this->mPreOpenInterest = from.mPreOpenInterest;
         this->mOpenPrice = from.mOpenPrice;
         this->mHighestPrice = from.mHighestPrice;
         this->mLowestPrice = from.mLowestPrice;
         this->mSettlementPrice = from.mSettlementPrice;
         this->mPreOpenPrice  = from.mPreOpenPrice;
         this->mPreSettlementPrice = from.mPreSettlementPrice;
         this->mDepth = from.mDepth;
         this->mMaxDepth = from.mMaxDepth;
         memcpy(mBidPrice,from.mBidPrice,40);
         memcpy(mBidVolume,from.mBidVolume,20);
         memcpy(mAskPrice,from.mAskPrice,40);
         memcpy(mAskVolume,from.mAskVolume,20);
     }


     MarketData &MarketData::operator=(MarketData const& from)
     {
         MarketData::operator =(from);
         this->mLastPrice =  from.mLastPrice;
         this->mLastVolume = from.mLastVolume;
         this->mLastAmount = from.mLastAmount;
         this->mAmount = from.mAmount;
         this->mVolume = from.mVolume;
         this->mHighestLimitPrice = from.mHighestLimitPrice;
         this->mLowestLimitPrice = from.mLowestLimitPrice;
         this->mOpenInterest = from.mOpenInterest;
         this->mPreOpenInterest = from.mPreOpenInterest;
         this->mOpenPrice = from.mOpenPrice;
         this->mHighestPrice = from.mHighestPrice;
         this->mLowestPrice = from.mLowestPrice;
         this->mSettlementPrice = from.mSettlementPrice;
         this->mPreOpenPrice  = from.mPreOpenPrice;
         this->mPreSettlementPrice = from.mPreSettlementPrice;
         this->mDepth = from.mDepth;
         this->mMaxDepth = from.mMaxDepth;
         memcpy(mBidPrice,from.mBidPrice,40);
         memcpy(mBidVolume,from.mBidVolume,20);
         memcpy(mAskPrice,from.mAskPrice,40);
         memcpy(mAskVolume,from.mAskVolume,20);
         return *this;
     }


    MarketData::~MarketData()
     {
     }

    double MarketData::GetLastPrice()  const
    {
        return mLastPrice;
    }

    void MarketData::SetLastPrice(double lastPrice)
    {
        mLastPrice = lastPrice;
    }

    size_t MarketData::GetLastVolume() const
    {
        return mLastVolume;
    }


    void MarketData::SetLastVolume(size_t volume)
    {
        mLastVolume = volume;
    }


    size_t MarketData::GetLastAmount() const
    {
       return  mLastAmount;
    }

    void MarketData::SetLastAmount(size_t lastAmount)
    {
        mLastAmount = lastAmount;
    }

    double MarketData::GetAmount() const
    {
        return mAmount;
    }

    void MarketData::SetAmount(double amount)
    {
        mAmount = amount;
    }

    size_t MarketData::GetVolume() const
    {
        return mVolume;
    }

    void MarketData::SetVolume(size_t volume)
    {
        mVolume = volume;
    }

    double MarketData::GetHighestLimitPrice() const
    {
        return mHighestLimitPrice;
    }

    void MarketData::SetHighestLimitPrice(double highestLimitPrice)
    {
        mHighestLimitPrice = highestLimitPrice;
    }

    double MarketData::GetLowestLimitPrice() const
    {
        return mLowestLimitPrice;
    }

    void MarketData::SetLowestLimitPrice(double lowestLimitPrice)
    {
        mLowestLimitPrice = lowestLimitPrice;
    }

    size_t MarketData::GetOpenInterest() const
    {
        return mOpenInterest;
    }

    void MarketData::SetOpenInterest(size_t openInterest)
    {
        mOpenInterest = openInterest;
    }

    size_t MarketData::GetPreOpenInterest() const
    {
        return mOpenInterest;
    }

    void MarketData::SetPreOpenInterest(size_t openInterest)
    {
        mOpenInterest = openInterest;
    }

    double  MarketData::GetOpenPrice() const
    {
        return mOpenPrice;
    }

    void MarketData::SetOpenPrice(double openPrice)
    {
        mOpenPrice = openPrice;
    }

    double MarketData::GetHighestPrice() const
    {
        return mHighestPrice;
    }

    void MarketData::SetHighestPrice(double highestPrice)
    {
        mHighestPrice = highestPrice;
    }

    double MarketData::GetLowestPrice() const
    {
        return mLowestPrice;
    }

    void MarketData::SetLowestPrice(double lowestPrice)
    {
        mLowestPrice = lowestPrice;
    }

    double MarketData::GetSettlementPrice() const
    {
        return mSettlementPrice;
    }

    void MarketData::SetSettlementPrice(double settlementPrice)
    {
        mSettlementPrice = settlementPrice;
    }

    double MarketData::GetPreClosePrice()const
    {
        return mPreClosePrice;
    }

    void MarketData::SetPreClosePrice(double preClosePrice)
    {
        mPreClosePrice = preClosePrice;
    }

    double MarketData::GetPreSettlementPrice() const
    {
        return mPreSettlementPrice;
    }

    void MarketData::SetPreSettlementPrice(double preSettlementPrice)
    {
        mPreSettlementPrice = preSettlementPrice;
    }

    size_t MarketData::GetDepth()const
    {
        return mDepth;
    }

    void MarketData::SetDepth(size_t depth)
    {
        mDepth = depth;
    }


    size_t MarketData::GetMaxDepth()const
    {
        return mMaxDepth;
    }

    double MarketData::GetBidPrice(size_t depth)const
    {
        return mBidPrice[depth - 1];
    }


    size_t MarketData::GetBidVolume(Size depth)const
    {
        return mBidVolume[depth - 1];
    }

    double MarketData::GetAskPrice(size_t depth)const
    {
        return mAskPrice[depth - 1];
    }

    size_t MarketData::GetAskVolume(size_t depth)const
    {
        return mAskVolume[depth - 1];
    }

    void MarketData::SetBidPrice(size_t depth,double bidPrice)
    {
        mBidPrice[depth - 1] = bidPrice;
    }


    void  MarketData::SetBidVolume(size_t depth,size_t bidVolume)
    {
        mBidVolume[depth - 1]  = bidVolume;
    }


    void MarketData::SetAskPrice(size_t depth,double askPrice)
    {
        mAskPrice[depth - 1] = askPrice;
    }


    void MarketData::SetAskVolume(size_t depth,size_t askVolume)
    {
        mAskVolume[depth - 1] = askVolume;
    }
