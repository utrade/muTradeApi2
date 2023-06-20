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
      UpdateType_SNAPSHOT
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
       * @brief _IsTbt, If Set true, will provide TBT feed
       */
      bool _IsTbt;

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
       * @brief getNoOfOrdersInDepth
       * @param wrapper
       * @param mode
       * @return
       */
      DATA_TYPES::DEPTH_POSITION  getNoOfOrdersInDepth(const COMMON::MarketDepthWrapper &wrapper,
                              const DATA_TYPES::OrderMode & mode);

      /**
       * @brief updateTbt
       * @return
       */
      bool updateTbt();



      /**
       * @brief updateMcl
       * @return
       */
      bool updateMcl();
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
       * @brief subscribe - subscribe to market data
       * @param symbolId  - symbol id for subscription
       * @param isSnapshot  - is snaphot enabled
       * @param isTbt - is tbt enabled
       * @return
       */
      bool subscribe(
          DATA_TYPES::SYMBOL_ID symbolId, bool isSnapshot, bool isTbt);

      /**
       * @brief unsubscribe
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
          size_t depthSize = CONSTANTS::MarketDepthArraySize);

      //MktData();
      ~MktData();

      /**
       * @brief update
       * @return
       */
      bool update();

      /**
       * @brief updateTbtTradeTicks
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
       * @return
       */
      double getMarketPercentPrice(const API2::DATA_TYPES::OrderMode orderMode,
          const double IOCFactor,
          const API2::SymbolStaticData * data,
          const bool dprCheckEnabled,
          const bool isRoundOffTypeAggressive = false);


    };
}
}
#endif
