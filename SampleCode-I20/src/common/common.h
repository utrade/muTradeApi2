#ifndef API2_COMMON_H
#define API2_COMMON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <sgContext.h>
#include <commands.h>
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
    API2::COMMON::Instrument* registerSymbol(SIGNED_LONG symbolId,const bool &isTbtEnabled,SGContext *context);
    bool isPriceInTradeExecutionRange(API2::COMMON::Instrument* instrument,const SIGNED_LONG &orderPrice,DebugLog *debugLog);
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
