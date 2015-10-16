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
         * @brief operator ==
         * @param a
         * @return
         */
        bool operator == (const MarketDataWrapper & a);
    };
  }
}
#endif
