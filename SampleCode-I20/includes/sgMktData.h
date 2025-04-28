#ifndef SG_COMMON_MKDATAH
#define SG_COMMON_MKDATAH
#include <cmdDefines.h>
#include <apiStructs.h>
//#include <volumeProfile/defines.h>
#include <sharedCommands.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <queue>
#include <sgDebugLogDefines.h>
#include <money.h>

namespace TBTDATA {
  struct SymbolData ;
}


namespace API2 
{ 
  class SGContext;
  class SymbolStaticData;

  namespace COMMON 
  {
    enum UpdateType
    {
      UpdateType_TBT,
      UpdateType_SNAPSHOT,
      UpdateType_MAX
    };

    class OhlcQuoteImpl;

    /**
     * @brief The OhlcQuote class
     */
    class OhlcQuote{

      /**
       * @brief _impl
       */
      OhlcQuoteImpl *_impl;

    public:

      /**
       * @brief OhlcQuote
       * @param symbolId
       */
      explicit OhlcQuote(UNSIGNED_LONG symbolId);

      /**
       * @brief getOpenPrice
       * @return
       */
      DATA_TYPES::PRICE getOpenPrice();

      /**
       * @brief getHighPrice
       * @return
       */
      DATA_TYPES::PRICE getHighPrice();

      /**
       * @brief getLowPrice
       * @return
       */
      DATA_TYPES::PRICE getLowPrice();

      /**
       * @brief getClosePrice
       * @return
       */
      DATA_TYPES::PRICE getClosePrice();

      /**
       * @brief getVolume
       * @return
       */
      DATA_TYPES::VOLUME getVolume();
      /**
       * @brief getAverageOhlcPrice
       * @return
       */
      DATA_TYPES::PRICE getAverageOhlcPrice();

      /**
       * @brief getLastProcessTimestamp
       * @return
       */
      time_t getLastProcessTimestamp();

      /**
       * @brief checkForModification
       * @param lastProcessTimeStamp
       * @return
       */
      bool checkForModification(time_t lastProcessTimeStamp);
     
    private:

      /**
       * @brief OhlcQuote : copy constructor
       * @param other
       */
      OhlcQuote(const OhlcQuote &other) = delete;

      /**
       *  @brief operator= : copy assignment operator
       *  @param other
       */
      OhlcQuote& operator=(const OhlcQuote &other) = delete;

      /**
       *  @brief OhlcQuote : move constructor
       *  @param other
       */
      OhlcQuote(OhlcQuote &&other) = delete;

      /**
       *  @brief operator= : move assignment operator
       *  @brief other
       */
      OhlcQuote& operator=(OhlcQuote &&other) = delete;
  };

    /**
     * @brief The TradeTick struct
     */
    struct TradeTick{

      CREATE_FIELD(DATA_TYPES::PRICE, Price);
      CREATE_FIELD(DATA_TYPES::QTY, Qty);
      CREATE_FIELD(UNSIGNED_LONG, Timestamp);

    public:

      /**
       * @brief TradeTick
       * @param price
       * @param qty
       * @param timestamp
       */
      TradeTick(
          const DATA_TYPES::PRICE &price,
          const DATA_TYPES::QTY &qty,
          const UNSIGNED_LONG &timestamp
          )
        :
          _Price(price),
          _Qty(qty),
          _Timestamp(timestamp)
      {}

    };


    /**
 * @brief The MktData class, The wrapper class for getting Market Feed for both Snapshot and Tick-By-Tick
 */
    class MktData
    {

      /**
       * @brief _symbolId
       */
      DATA_TYPES::SYMBOL_ID _symbolId;

      /**
       * @brief Quote
       */
      CREATE_FIELD( COMMON::MarketDataWrapper, Quote);

      /**
       * @brief Temp Quote for internal processing
       */
      CREATE_FIELD( COMMON::MarketDataWrapper, TempQuote);

      /**
       * @brief IsSnapShot, If Set true, will provide Snapshot Data, else Tick-By-Tick Data
       */
      bool _IsSnapShot;

      /**
       * @brief _isOISubscribe, If Set true, will provide OI Data
       */
      bool _isOISubscribe;

      /**
       * @brief _IsTbt, If Set true, will provide TBT feed
       */
      bool _IsTbt;

      /**
       * @brief ClientType
       * Client Type for the TBT market data (CUR,FO,CM,IFSC,COM)
       */
      CREATE_FIELD(short, ClientType );

      /**
       * @brief StreamId, Stream Id for the TBT market data
       */
      CREATE_FIELD(short, StreamId );
      
      /**
       * @brief multiplier
       */
      CREATE_FIELD( int, multiplier);

      /**
       * @brief _tbtData
       */
      TBTDATA::SymbolData *_tbtData;

      CREATE_FIELD(std::queue<TradeTick>, TradeTicks);

      /**
       * @brief _LatestIndexCounter
       */
      volatile UNSIGNED_LONG _LatestIndexCounter;

      /**
       * @brief _LatestTick
       */
      int _LatestTickIndex;

      UpdateType _LastUpdateType;

      /**
       * @brief _marketDataNotFound
       */
      bool _marketDataNotFound;

      /**
       * @brief PreTradeDepthCount
       * For Customized Tbt
       * */
      CREATE_FIELD( int, PreTradeDepthCount );

      /**
       * @brief PreTradeOrderQty
       * For Customized Tbt
       * */
      CREATE_FIELD( int, PreTradeOrderQty );

      /**
       * @brief PreTradeOrderMode
       * For Customized Tbt
       * */
      CREATE_FIELD( char, PreTradeOrderMode );

      /**
       * @brief PreTradeAveragePrice
       * For Customized Tbt
       * */
      CREATE_FIELD( long, PreTradeAveragePrice );

      /**
       * @brief IsPreTrade
       * For Customized Tbt
       * */
      CREATE_FIELD( bool, IsPreTrade );

      /**
       * @brief DepthSize
       * Max depth to process
       * */
      const size_t _depthSize;

      private:

      Currency::CurrencyType _currencyType;
      int _precision;

      /**
       * @brief _sgContext  - strategy which constructed this market data
       */
      SGContext *_sgContext;

      /**
       * @brief getPrice
       * @param wrapper
       * @param mode
       * @return
       */
      DATA_TYPES::PRICE  getPrice(const COMMON::MarketDepthWrapper &wrapper,
                                  const DATA_TYPES::OrderMode & mode);

      /**
       * @brief getQty
       * @param wrapper
       * @param mode
       * @return
       */
      DATA_TYPES::QTY  getQty(const COMMON::MarketDepthWrapper &wrapper,
                              const DATA_TYPES::OrderMode & mode);

      /**
       * @brief getNoOfOrdersInDepth To get the number of orders in depth
       * @param wrapper
       * @param mode
       * @return
       */
      DATA_TYPES::DEPTH_POSITION  getNoOfOrdersInDepth(const COMMON::MarketDepthWrapper &wrapper,
                              const DATA_TYPES::OrderMode & mode);

      /**
       * @brief updateTbt To update the TBT data
       * @param updateType
       * @param isFeedStuck (Not used, to be used in case of feed stuck check based on timestamp)
       * @param retString (Not used, to be used in case of feed stuck check based on timestamp)
       * @param status returns STRUCTURE_UNCHANGED if feed is unchanged, otherwise does not change the status
       * @param orderMode OrderMode_BUY or OrderMode_SELL, for which side the status is required
       * @return
       */
      bool updateTbt( UpdateType & updateType,
                      bool *isFeedStuck = nullptr,
                      std::string * retString = nullptr,
                      int *status = nullptr,
                      DATA_TYPES::OrderMode orderMode = API2::CONSTANTS::CMD_OrderMode_MAX);

      /**
       * @brief isFeedStuckThresholdBreached
       * @param lastTimeStamp
       * checks if the difference of lastTimeStamp and current time is greater than 
       * FeedStuckThreshold( FEED_STUCK_CHECK_DURATION provided HFT Block of params.conf, default value 500 milliseconds)
       * @param retString returns the string with the details of timestamps of the feed stuck
       * @param isSnapshotCase if true, then it is snapshot case else TBT case
       * @return True if Feed is stuck for more than FeedStuckThreshold value
       */
      bool isFeedStuckThresholdBreached(int64_t lastTimeStamp, std::string * retString = nullptr, bool isSnapshotCase = false);

      /**
       * @brief updateMcl To update the MCL data
       * @param isFeedStuck, if feed is stuck returns true
       * @param retString, returns the string with the details of timestamps of the feed stuck
       * @return
       */
      bool updateMcl(bool *isFeedStuck = nullptr, std::string * retString = nullptr);
    public:

    UpdateType getLastUpdateType(){return _LastUpdateType;}

    UNSIGNED_LONG getSymbolId(){return _symbolId;}

    bool getIsSnapShot(){return _IsSnapShot;}
    bool getIsTbt(){return _IsTbt;}
      
    /**
     * @brief getLatestIndexCounter
     * @return
     */
    UNSIGNED_LONG getLatestIndexCounter();

      /**
       * @brief getOpenPrice
       * @return
       */
      DATA_TYPES::PRICE getOpenPrice();

      /**
       * @brief getHighPrice
       * @return
       */
      DATA_TYPES::PRICE getHighPrice();

      /**
       * @brief getLowPrice
       * @return
       */
      DATA_TYPES::PRICE getLowPrice();

      /**
       * @brief getClosePrice
       * @return
       */
      DATA_TYPES::PRICE getClosePrice();

      /**
       * @brief getVolume
       * @return
       */
      DATA_TYPES::VOLUME getVolume();

      /**
       * @brief getLastTradeQty
       * @return
       */
      DATA_TYPES::QTY getLastTradeQty();
      
      /**
       * @brief getLastTradePrice
       * @return
       */
      DATA_TYPES::PRICE getLastTradePrice();

      /**
       * @brief getLastTradeTime
       * @return
       * In TBT Trade time in millisecond from 01 Jan 1980  00:00:00
       * To convert in Normal time : (lastTradeTime / NANO_MULTIPLIER) + SECS_1980_1970
       */
      DATA_TYPES::LAST_TRADE_TIME getLastTradeTime();

      /**
       * @brief getValue
       * @return
       */
      DATA_TYPES::PRICE getValue();

      /**
       * @brief getAvgTradePrice
       * @return
       */
      DATA_TYPES::VOLUME getAvgTradePrice();

      /**
       * @brief getTimeStamp : This method will return last update timestamp of Symbol.
       *                                       It Will return valid value in case of TBT (Symbol is subscibed on TBT)
       *                                       Else It Will return 0
       *
       * @return Timestamp in NanoSecond
       */
      DATA_TYPES::NanoSecondTimeStamp getTimeStamp();

      /**
       * @brief getPrice
       * @param position
       * @param mode
       * @return
       */
      DATA_TYPES::PRICE getPrice(size_t position, const DATA_TYPES::OrderMode & mode);

      /**
       * @brief getQty
       * @param position
       * @param mode
       * @return
       */
      DATA_TYPES::QTY getQty(size_t position, const DATA_TYPES::OrderMode & mode);

      /**
       * @brief getNoOfOrdersInDepth
       * @param position
       * @param mode
       * @return
       */
      DATA_TYPES::DEPTH_POSITION getNoOfOrdersInDepth(size_t position, const DATA_TYPES::OrderMode & mode);

      /**
       * @brief getBidPrice
       * @param pos
       * @return
       */
      DATA_TYPES::PRICE getBidPrice(size_t pos);

      /**
       * @brief getBidQty
       * @param pos
       * @return
       */
      DATA_TYPES::QTY getBidQty(size_t pos);

      /**
       * @brief getNoOfBids
       * @param pos
       * @return
       */
      DATA_TYPES::DEPTH_POSITION getNoOfBids(size_t pos);

      /**
       * @brief getAskPrice
       * @param pos
       * @return
       */
      DATA_TYPES::PRICE getAskPrice(size_t pos);

      /**
       * @brief getAskQty
       * @param pos
       * @return
       */
      DATA_TYPES::QTY getAskQty(size_t pos);

      /**
       * @brief getNoOfAsks
       * @param pos
       * @return
       */
      DATA_TYPES::DEPTH_POSITION getNoOfAsks(size_t pos);

      /**
       * @brief Get the exchange identifier for Open Interest data
       * @return ExchangeId The exchange identifier where the Open Interest is from
       */
      DATA_TYPES::ExchangeId getOpenInterestExchangeId();

      /**
       * @brief Get the security identifier for Open Interest data
       * @return SECURITY_ID The unique identifier of the security for which Open Interest is reported
       */
      DATA_TYPES::SECURITY_ID getOpenInterestSecurityId();

      /**
       * @brief Get the current Open Interest quantity
       * @return QTY The total number of outstanding contracts/positions
       */
      DATA_TYPES::QTY getOpenInterestOIQty();

      /**
       * @brief Get the current Open Interest value
       * @return PRICE The monetary value of the Open Interest
       */
      DATA_TYPES::PRICE getOpenInterestOIValue();

      /**
       * @brief Get the change in Open Interest from previous period
       * @return PRICE The change in Open Interest value (positive for increase, negative for decrease)
       */
      DATA_TYPES::PRICE getOpenInterestOIChange();

      /**
       * @brief subscribe - subscribe to market data
       * @param symbolId  - symbol id for subscription
       * @param isSnapshot  - is snaphot enabled
       * @param isTbt - is tbt enabled
       * @return
       */
      bool subscribe(
          DATA_TYPES::SYMBOL_ID symbolId, bool isSnapshot, bool isTbt);

      /**
       * @brief unsubscribe To unsubscribe from market data
       */
      void unsubscribe();

      /**
       * @brief MktData
       * @param symbolId  - symbol id for which market data needs to be constructed
       * @param sgContext - strategy from which subscription requested
       * @param isSnapshot  - is snapshot enabled
       * @param isTbt - is tbt enabled
       * @param depthSize - depth size required
       */
      explicit MktData(
          DATA_TYPES::SYMBOL_ID symbolId,
          SGContext *sgContext,
          bool isSnapshot = true, bool isTbt = false,
          size_t depthSize = CONSTANTS::MarketDepthArraySize,
          bool isOISubscribe = false);

      //MktData();
      ~MktData();

      /**
       * @brief update
       * @param isFeedStuck (Not used, to be used in case of feed stuck check based on timestamp)
       * @param retString (Not used, to be used in case of feed stuck check based on timestamp)
       * @param status returns STRUCTURE_UNCHANGED if feed is unchanged, otherwise does not change the status
       * @param orderMode OrderMode_BUY or OrderMode_SELL, for which side the status is required
       * @return
       */
      bool update( bool *isFeedStuck = nullptr,
                   std::string * retString = nullptr,
                   int *status = nullptr,
                   DATA_TYPES::OrderMode orderMode = API2::CONSTANTS::CMD_OrderMode_MAX);

      /**
       * @brief updateTbtTradeTicks To update the TBT trade ticks
       * @return
       */
      bool updateTbtTradeTicks();

      /**
       *Check if the counter has been updated for Trade Tick Or Not.
       * Return true if the latest counter in shared memory is larger than
       * the one in local else return false;
       *@brief Returns true if trade has occured.
       */
      bool hasTradeBeenProcessed();

      /**
       * @brief checkIfPriceLieBetweenMarketDataRange
       * @param priceToBeValidatedForInsideRange
       * @return true if price lie between market data
       */
      bool checkIfPriceLieBetweenMarketDataRange(DATA_TYPES::PRICE priceToBeValidatedForInsideRange );

#if 0
      /**
       * @brief checkUpdateStatus
       * @param lastProcessTime
       * @return
       */
      bool checkUpdateStatus(time_t lastProcessTime);

      /**
       * @brief checkUpdateStatus
       * @param lastProcessTime
       * @return
       */
      bool checkUpdateStatus(boost::posix_time::ptime lastProcessTime);
#endif
      /**
       * @brief operator ()
       */
      void operator ()();

      /**
       * @brief dump
       */
      void dump();
      
      /**
       * @brief dump
       * @param debugObject
       */
      void dump(API2::DebugLog *debugObject);

      void dump(DebugLog *debugObject, size_t depth);

      /**
       * @brief isFeedUnchanged
       * Compares the local feed counter with the TBT Depth Feed Counter and
       * Returns true if the feed is changed, else returns false for feed unchanged
       * @param orderMode - The Side for which the feed is to be checked (Buy or Sell)
       * @param counter - The Last Counter Value of the feed previously received
       * @return bool - True if the feed is changed, else returns false for feed unchanged
       * Also updates the counter with the latest value received from the TBT Depth Feed
       */
      bool isFeedUnchanged(DATA_TYPES::OrderMode orderMode, volatile unsigned long& counter);

      /**
       * @brief getMaxDepthSupported : This method is used to get Max Depth supported by HFT infra.
       * @return Max Depth unsigned integer
       */
      static const size_t getMaxDepthSupported();
    
      /*
       * @brief getTradeBuyOrderId : returns exchange order id of last traded buy order.
       */
      DATA_TYPES::TBT_ORDER_ID getTradeBuyOrderId();
      
      /*
       * @brief getTradeSellOrderId : returns exchange order id of last traded sell order.
       */
      DATA_TYPES::TBT_ORDER_ID getTradeSellOrderId();

      /*
       * @brief getTradeSellOrderId : returns exchange order id of latest security update(new/modify/cancel).
       */
      DATA_TYPES::TBT_ORDER_ID getExchangeOrderId();

      /**
       * @brief getSymbolSpotPrice
       * @param retSpotPrice - SpotPrice of underlying symbol in scrip precision
       *                  - If scrip precision is 2 and actual price is 123.45 then
       *                  - price in scrip precision 12345( i.e. 123.45 * 100 )
       * @param symbolId - Symbol for which spot price need to br fetch.
       * @param referenceSpotPriceType - Default Value API2::CONSTANTS::ReferenceSpotPrice_LTP.
       * @note - Underlying price is getting fetch through API::COMMON::getSymbolSpotPrice which will add latency
       *       - If snapshot is disable then this method won't work as spot price can't be fetch.
       * @return bool - return true if successful otherwise returns false.
       */
      static bool getSymbolSpotPrice(
          API2::DATA_TYPES::PRICE &retSpotPrice,
          const API2::DATA_TYPES::SYMBOL_ID symbolId,
          const API2::DATA_TYPES::REFERENCE_SPOT_PRICE_TYPE referenceSpotPriceType = API2::CONSTANTS::ReferenceSpotPrice_LTP );


      /**
       * @brief getMarketPercentPrice - gets the price for market order. The price returned is IOCFactor'ed over the ltp
       * @param orderMode
       * @param IOCFactor - (market percentage over ltp)/ 100. Ex: 2% should be passed as 0.02
       * @param data
       * @param dprCheckEnabled - If true, DPR check gets applied and price returned will be adjusted as per dpr
       * @param isRoundOffTypeAggressive - If true, agressive rounding will happen. RoundUp in case of buy and rounddown in case of sell
       * @param isAggressive - If true, price will be adjusted in aggressive way. 
       *                       For Buy: Will place the order at price added with adjustment factor. 
       *                       For Sell: Will place the order at price subtracted with adjustment factor
       * @param useOppositeDepth - If true, opposite depth will be used to get the price. Else LTP will be used
       * @param useUpdatedDPRPriceHandling - If true, updated DPR price handling will be used
       * @param isDprFailed - If dpr check failed, this will be set to true
       * @param debugObject - DebugLog object
       * @return
       */
      double getMarketPercentPrice(const API2::DATA_TYPES::OrderMode orderMode,
          const double IOCFactor,
          const API2::SymbolStaticData * data,
          const bool dprCheckEnabled,
          const bool isRoundOffTypeAggressive = false,
          const bool isAggressive = false,
          const bool useOppositeDepth = false,
          const bool useUpdatedDPRPriceHandling = false,
          bool * isDprFailed = nullptr,
          DebugLog * debugObject = nullptr);
    };
}
}
#endif
