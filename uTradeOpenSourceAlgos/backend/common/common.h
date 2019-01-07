#ifndef API2_COMMON_H
#define API2_COMMON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <sgContext.h>
#include "orderWrapper.h"

/**
 * This file is provided to perform some common functions that are generally useful in algos.
 * User can change code as per their requirement and apply neccessary checks to minimize risk
 * and maximize performance of application.
 * These functions may not fullfill all the requirements. So, user should check the implementation and 
 * documentation before use.
 * 
 * Disclaimer: uTrade will not be responsible for any issue due to this code as implementation is also provided
 *
 */

#define FILL_PARAMS( NAME, PARAM)\
  if(customParams->getValue(NAME,PARAM) != API2::UserParamsError_OK)\
{\
  DEBUG_VARSHOW(reqQryDebugLog(), "Issue in ",NAME);\
  return false;\
}\

#define PUSH_TO_LIST( list, ostringStream, arg1, arg2 )  \
  ostringStream.str( "" );  \
  ostringStream.clear();  \
  ostringStream << arg1 << arg2;  \
  list.push_back( ostringStream.str() );  \

namespace API2
{
  namespace COMMON
  {
    bool readFile(std::ifstream &file,std::string fileName,bool &isTbtEnabled,API2::DebugLog *debugLog);

    /**
     * @brief registerSymbol, To register a symbol. Market data event comes only after this registeration
     * @param symbolId, identifier of a symbol
     * @param isTbtEnabled, is market data will come from TBT or snapshot
     * @param context, reference of an object which want to register this symbol
     * @return created Instrument object
     */
    API2::COMMON::Instrument* registerSymbol(SIGNED_LONG symbolId,const bool &isTbtEnabled,SGContext *context);

    /**
     * @brief isPriceInTradeExecutionRange, To check if price passed is in Trade execustion range as per exchane feed
     * @param instrument, instrument or symbol for which we are checking TER
     * @param orderPrice, price which need to be checked
     * @param debugLog, logging object
     * @return true if price in range otherwise false
     */
    bool isPriceInTradeExecutionRange(API2::COMMON::Instrument* instrument,const SIGNED_LONG &orderPrice,DebugLog *debugLog);

    /**
     * @brief getBestPrice, To get best price as per market depth for buy/sell mode passed
     * @param symbolId, identifier of a symbol
     * @param side,(buy/sell) side of an order for which best price required
     * @param price, calculated price
     * @param orderWrapper, reference of an orderWrapper object
     * @param context, reference of an object which have been registered as an algo
     * @param tickFactor, Best Price by how much ticks
     * @param pickOpportunityEnabled, If set to True -> Ignore best Price if tradable
     * @param pickedOpportunity, return value as reference if Tradable
     * @param opportunityPrice, Price against which value needs to be compare for picking opportunity 
     * @param useBasePrice, If wanted price to be always aggressive against base price
     * @param basePrice, Base Price Value for which it will be aggressive
     * @param bidInTop5, If price is not in top 5, Base Price will be set  
     * @param notBestBid, If set as True, It will return base Price if best price is not set   
     * @return true if best price calculated otherwise false
     */
    bool getBestPrice(SIGNED_LONG symbolId,
        DATA_TYPES::OrderMode side,
        SIGNED_LONG &price,
        OrderWrapper &orderWrapper,
        SGContext *context,
        int tickFactor,
        bool pickOpportunityEnabled,
        bool &pickedOpportunity,
        const SIGNED_LONG &opportunityPrice,
        bool useBasePrice=false,
        const SIGNED_LONG &basePrice = 0,
        bool bidInTop5 = false,
        bool notBestBid = false
        );


    /**
     * @brief isCurrencyExchange, To get if passed id is for currency exchane or normal. Not true for every exchange
     * @return
     */
    bool isCurrencyExchange(API2::DATA_TYPES::ExchangeId exchangeId);

    /*
     * to check if profitInTicks need to be hopped due to hopTradedLots exceeding hopLots,
     * if the hopTradedLots are more than hopLots, we check for number of hops, and increase the profitInTicks by that much
     * number of hopSpreadInTicks, also we reduce the hopTradedLots
     *
     * @brief roundToTickSize
     * @param price - price which is to be rounded off
     * @param tickSize - tick size for that instrument
     * @param orderMode - in case of buy reduce the price, in case of sell, increase it ( be defensive )
     */
    bool checkForHop(
        SIGNED_LONG &hopTradedLots,
        const SIGNED_LONG &hopLots,
        SIGNED_LONG &profitInTicks,
        const SIGNED_LONG &hopSpreadInTicks,
        DebugLog *debugLog );
  }
}

#endif
