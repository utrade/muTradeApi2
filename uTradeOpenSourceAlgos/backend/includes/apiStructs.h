#ifndef API_STRUCTS
#define API_STRUCTS
#include <apiConstants.h>
#include <apiDataTypes.h>
#include <string>
namespace API2
{
  namespace COMMON
  {
    /**
     * @brief The MarketDepthWrapper class will store Bid Ask Price at particular level
     */
    class MarketDepthWrapper
    {
      public:

        /**
         * @brief BidPrice
         */
        DATA_TYPES::PRICE BidPrice;

        /**
         * @brief BidQty
         */
        DATA_TYPES::QTY BidQty;

        /**
         * @brief AskPrice
         */
        DATA_TYPES::PRICE AskPrice;

        /**
         * @brief AskQty
         */
        DATA_TYPES::QTY AskQty;

        /**
         * @brief NoOfBids
         */
        DATA_TYPES::DEPTH_POSITION NoOfBids;

        /**
         * @brief NoOfAsks
         */
        DATA_TYPES::DEPTH_POSITION NoOfAsks;

        /**
         * @brief toString will return formated Bid Ask Price Qty for debug purpose
         * @return
         */
        std::string toString();
    };

    /**
     * @brief The MarketDataWrapper class will contain the Snapshot/TBT Market Data
     */
    class MarketDataWrapper
    {
      public:

        /**
         * @brief OpenPrice
         */
        DATA_TYPES::PRICE OpenPrice;

        /**
         * @brief HighPrice
         */
        DATA_TYPES::PRICE HighPrice;

        /**
         * @brief LowPrice
         */
        DATA_TYPES::PRICE LowPrice;

        /**
         * @brief ClosePrice
         */
        DATA_TYPES::PRICE ClosePrice;

        /**
         * @brief Volume
         */
        DATA_TYPES::VOLUME Volume;

        /**
         * @brief LastTradeQty
         */
        DATA_TYPES::QTY LastTradeQty;

        /**
         * @brief LastTradePrice
         */
        DATA_TYPES::PRICE LastTradePrice;

        /**
         * @brief LastTradeTime
         */
        DATA_TYPES::LAST_TRADE_TIME LastTradeTime;

        /**
         * @brief Value
         */
        DATA_TYPES::PRICE Value;

        /**
         * @brief AvgTradePrice
         */
        DATA_TYPES::PRICE AvgTradePrice;

        /**
         * @brief MarketDepth
         */
        MarketDepthWrapper MarketDepth[CONSTANTS::MarketDepthArraySize];

        /**
         * @brief MarketDataWrapper
         */
        MarketDataWrapper();

        /**
         * @brief toString will return formatted Market Picture for debug purpose
         * @return
         */
        std::string toString();

        /**
         * @brief Reset will set value of its member variables to zero
         */
        void reset(const size_t &size); 

        /**
         * @brief operator ==
         * @param a
         * @return
         */
        bool operator == (const MarketDataWrapper & a);
    };
  }
}
#endif
