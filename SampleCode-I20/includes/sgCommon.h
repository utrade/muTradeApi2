#ifndef SG_COMMON_H
#define SG_COMMON_H

#include "time.h"
#include <sharedDefines.h>
#include <sharedResponse.h>
#include <sharedCommands.h>
#include <fstream>
#include <list>
#include <sgMktData.h>

#include <memory>
#include <string>

#include <cmdDefines.h>
#include <apiConstants.h>

#include <sgSymbolDataDefines.h>

typedef uint64_t SYMBOL_ID;

namespace API2{
  namespace COMMON {

    struct OrderId;
    struct Position;
    struct Instrument;

    /**
     * @brief The InstrumentPosition struct Provides the basic information like Open Qty, OpenSide, Traded Quantity in Buy/Sell Side,
     *  \n Average traded Price in Buy/Sell Side, Booked and Mark-To-Market Profit and loss
     */
    struct InstrumentPosition
    {

      /**
       * @brief getOpenQty, To get the Open Quantity i,e Buy Qty-Sell Qty
       * @return
       */
      SIGNED_LONG getOpenQty();

      /**
       * @brief getTradedQty To get Traded Quantity at requested OrderMode
       * @param mode DATA_TYPES::CMD_OrderMode
       * @return traded Qty as DATA_TYPES::QTY
       */
      SIGNED_LONG getTradedQty(const DATA_TYPES::OrderMode &mode);

      /**
       * @brief getOpenSide, To get Open Side Position, if BuyQty>SellQty, returns API2::CONSTANTS::CMD_OrderMode_BUY else API2::CONSTANTS::CMD_OrderMode_SELL
       * @return OpenSide as DATA_TYPES::OrderMode
       */
      DATA_TYPES::OrderMode getOpenSide();

      /**
       * @brief getBookedPnl, To get Booked Pnl
       * @return Booked PnL as DATA_TYPES::SIGNED_LONG in paisa ( to convert in Rupee, convert to float and divide by 100)
       */
      SIGNED_LONG getBookedPnl();

      /**
       * @brief getMtmPnl, To get Mark to Market Pnl
       * @param ltp, Last trade Price is to be provided
       * @return Mark to Market Pnl as DATA_TYPES::SIGNED_LONG in paisa ( to convert in Rupee, convert to float and divide by 100)
       */
      SIGNED_LONG getMtmPnl(UNSIGNED_LONG ltp);

      /**
       * @brief getAvgPrice, Get Average Trade Price at requested OrderMode
       * @param mode
       * @return Average Price as DATA_TYPES::SIGNED_LONG in paisa ( to convert in Rupee, convert to float and divide by 100)
       */
      DATA_TYPES::PRICE getAvgPrice(const DATA_TYPES::OrderMode &mode);

      /**
       * @brief getPendingQty, To get Quantity Pending (or not filled)
       * @param mode
       * @return
       */
      UNSIGNED_LONG getPendingQty(const DATA_TYPES::OrderMode &mode);

#if API_COMPILATION == 0
#include <sgInstrumentPosition.ph> 
#endif
    };

    /**
     * @brief The Instrument class Provides all the information about Market Instrument
     */
    class Instrument
    {

    public:

      /**
       * @brief getStaticData To get the static details of a tradable Instrument
       * @return Static Data about the instrument as API2::SymbolStaticData
       */
      SymbolStaticData *getStaticData();

      /**
       * @brief getLastQuoteUpdateTime To get Last time when the Quote for the Instrument was updated
       * @return Time when Quote was last Updated, in time_t
       */
      time_t getLastQuoteUpdateTime();

      /**
       * @brief getSymbolId To get The System unique ID of the Instrument
       * @return
       */
      SYMBOL_ID getSymbolId();

      /**
       * brief getPosition To get Pointer to the API2::COMMON::InstrumentPosition
       * @return
       */
      InstrumentPosition *getPosition();

      /**
       * @brief getLastQuotedPrice To get last quoted price from this Instrument
       * @param mode
       * @return Price as DATA_TYPES::SIGNED_LONG in Paisa ( to convert in Rupee, convert to float and divide by 100)
       */
      UNSIGNED_LONG getLastQuotedPrice(const DATA_TYPES::OrderMode &mode);


      /**
       * @brief updatePositionFromString
       * Format: Buy Qty <delimeter> Sell Qty <delimeter> Buy Avg Price <delimeter> Sell Avg Price
       * @param positionString
       * @param delimiter
       */
      void updatePositionFromString(const std::string &positionString,const char *delimiter="|");

      /**
       * @brief getPositionString
       * Format: Buy Qty <delimeter> Sell Qty <delimeter> Buy Avg Price <delimeter> Sell Avg Price
       * @param delimiter
       * @return
       */
      std::string getPositionString(const char *delimiter="|");

#if API_COMPILATION == 0
#include <sgInstrument.ph> 
#endif
    };


  }  //namspace COMMON
}//namspace SG
#endif // SGCOMMON_H
