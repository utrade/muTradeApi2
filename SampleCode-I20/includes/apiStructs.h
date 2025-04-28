#ifndef API_STRUCTS
#define API_STRUCTS
#include <apiConstants.h>
#include <apiDataTypes.h>
#include <string>
#include <cmdDefines.h>
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

    class OpenInterestApiStruct
    {
      CREATE_FIELD(DATA_TYPES::ExchangeId, ExchangeId);
      CREATE_FIELD(DATA_TYPES::SECURITY_ID, SecurityId);
      CREATE_FIELD(DATA_TYPES::QTY, OIQty);
      CREATE_FIELD(DATA_TYPES::PRICE, OIValue);
      CREATE_FIELD(DATA_TYPES::PRICE, OIChange);

    public:
      OpenInterestApiStruct();
      ~OpenInterestApiStruct() = default;

      // Copy operations
      OpenInterestApiStruct(const OpenInterestApiStruct&) = default;
      OpenInterestApiStruct &operator=(const OpenInterestApiStruct &other)
      {
        // No need for self-assignment check as modern compilers optimize this
        setExchangeId(other.getExchangeId());
        setSecurityId(other.getSecurityId());
        setOIQty(other.getOIQty());
        setOIValue(other.getOIValue());
        setOIChange(other.getOIChange());
        return *this;
      }

      #ifndef FRONTEND_COMPILATION
      // Move operations
      OpenInterestApiStruct(OpenInterestApiStruct&&) noexcept = default;
      OpenInterestApiStruct& operator=(OpenInterestApiStruct&&) noexcept = default;
      #endif
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
         * @brief LastUpdatedTime
         */
        DATA_TYPES::LAST_TRADE_TIME LastUpdatedTime;


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
         * @brief OpenInterest
         */
        OpenInterestApiStruct OpenInterest;

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
         * @brief toString will return formatted Market Picture upto depth
         */
        const std::string toString(size_t depth);

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

    /**
     * @brief The OrderLimitsApiStruct class will store order limits for client or dealer.
     *  Note: For New RMS  if % is selected for client code by admin.
     *      It will return all values in % with precision 2.
     *  For Example:
     *  If % is select :
     *  MaximumTotalBuyValue = 4550(45.50)
     *  MaximumTotalSellValue =8890 (88.90)
     *  otherwise return original value :
     *  MaximumTotalSellValue = 100000000(100000.000) assuming RMS PRECISION is 3
     */
    class OrderLimitsApiStruct
    {
        /**
       * @brief isBuyValueInPercentage: true if MaximumTotalBuyValue is in %age
       */
      CREATE_FIELD( bool, IsBuyValueInPercentage);
      CREATE_FIELD( DATA_TYPES::UINTEGER64, MaximumTotalBuyQuantity);
      CREATE_FIELD( DATA_TYPES::UINTEGER64, MaximumTotalBuyValue);

      /**
       * @brief isSellValueInPercentage : true if MaximumTotalSellValue is in the %age
       */
      CREATE_FIELD( bool, IsSellValueInPercentage);
      CREATE_FIELD( DATA_TYPES::UINTEGER64, MaximumTotalSellQuantity);
      CREATE_FIELD( DATA_TYPES::UINTEGER64, MaximumTotalSellValue);

      /**
       * @brief IsNetValuesInPercentage: if Net Values in the %age
       * @brief MaximumNetQuantity and MaximumNetValue :
       *  For Old RMS: will store net qty and value
       *  For New RMS: Will store Net max qty and value respectively
       *  Ex:
       *
       *  RMS_PRECISION = 1000
       *  For Old RMS:
       *
       *  MaximumNetQuantity and MinimumNetQuantity will be same
       *  if MaximumNetQuantity = 100 then
       *  MinimumNetQuantity 100.
       *  MaximumNetValue and MinimumNetValue will be same,
       *  if MaximumNetValue = 1000,000
       *  then MinimumNetValue = 1000,000
       *
       *  For NEW RMS:
       *  MaximumNetQuantity/MaximumNetValue(Max Short position) and
       *  MinimumNetQuantity/MinimumNetValue(Max long position)
       *  both will be set from FE
       *  Both value could be different.
       *  MaximumNetQuantity= 100
       *  MaximumNetQuantity = 200
       *  MaximumNetValue = 100,000
       *  MinimumNetValue = 200,000
       *
       */
      CREATE_FIELD( bool, IsNetValuesInPercentage );
      CREATE_FIELD( DATA_TYPES::UINTEGER64, MaximumNetQuantity);
      CREATE_FIELD( DATA_TYPES::UINTEGER64, MaximumNetValue);

      /**
       * @brief MaximumNetQuantity and MaximumNetValue :
       * For Old RMS: will store net qty and value same as above parameter.
       * For New RMS: Will store Net max qty and value respectively
       */
      CREATE_FIELD( DATA_TYPES::UINTEGER64, MinimumNetQuantity);
      CREATE_FIELD( DATA_TYPES::UINTEGER64, MinimumNetValue);

      /**
       * AggregateDeposit:
       * For Old RMS : will return valid value for both client and dealer according to Old RMS Formula
       * For  New RMS: will return valid value only for client, for dealer , deposit is not handled.
       */
      CREATE_FIELD( DATA_TYPES::UINTEGER64, AggregateDeposit );

      /**
       * @brief MaximumMTM
       * For Old RMS : will store mtm value for both client and dealer according to Old RMS Formula
       * For  New RMS: will store mtm value only for client and for dealer.
       */
      CREATE_FIELD( DATA_TYPES::INTEGER64, MaximumMTM);

      public:

      /**
       * @brief OrderLimitsApiStruct - Default constructor
       */
      OrderLimitsApiStruct();

      /**
       * @brief OrderLimitsApiStruct - Parameterized constructor
       * @param maximumTotalBuyQuantity
       * @param maximumTotalBuyValue
       * @param maximumTotalSellQuantity
       * @param maximumTotalSellValue
       * @param maximumNetQuantity
       * @param maximumNetValue
       * @param AggregateDeposit
       * @param MaximumMTM
       */
      OrderLimitsApiStruct(
          DATA_TYPES::UINTEGER64 maximumTotalBuyQuantity,
          DATA_TYPES::UINTEGER64 maximumTotalBuyValue,
          DATA_TYPES::UINTEGER64 maximumTotalSellQuantity,
          DATA_TYPES::UINTEGER64 maximumTotalSellValue,
          DATA_TYPES::UINTEGER64 maximumNetQuantity,
          DATA_TYPES::UINTEGER64 maximumNetValue,
          DATA_TYPES::UINTEGER64 AggregateDeposit,
          DATA_TYPES::INTEGER64 MaximumMTM
          );

      /**
       * @brief getString
       * @description - return a dump string of OrderLimitsApiStruct
       * @return string
       */
      std::string getString();
    };
  }
}
#endif
