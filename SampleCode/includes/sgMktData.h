#ifndef SG_COMMON_MKDATAH
#define SG_COMMON_MKDATAH
#include <cmdDefines.h>
#include <apiStructs.h>
//#include <volumeProfile/defines.h>
#include <sharedCommands.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <queue>

namespace TBTDATA {
  struct SymbolData ;
}


namespace API2 { namespace COMMON {

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
    OhlcQuote(UNSIGNED_LONG symbolId);

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
     * @brief IsSnapShot, If Set true, will provide Snapshot Data, else Tick-By-Tick Data
     */
    CREATE_FIELD( bool, IsSnapShot);

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
    volatile unsigned long _LatestIndexCounter;

    /**
     * @brief _LatestTick
     */
    int _LatestTickIndex;

    private:
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

    UNSIGNED_LONG getSymbolId(){return _symbolId;}


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
     * @brief subscribe
     * @param symbol
     * @param isSnapshot
     * @return
     */
    bool subscribe(DATA_TYPES::SYMBOL_ID symbol,bool isSnapshot);

    /**
     * @brief unsubscribe
     */
    void unsubscribe();

    /**
     * @brief MktData
     * @param symbolId
     * @param isSnapshot
     */
    MktData(DATA_TYPES::SYMBOL_ID symbolId,bool isSnapshot = true);

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

  };
}
}
#endif
