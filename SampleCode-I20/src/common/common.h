#ifndef API2_COMMON_H
#define API2_COMMON_H

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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <sgContext.h>
#include "orderWrapper.h"

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

    /**
     *  @brief lexicalCast
     *  @param template , template
     *  @return It returns the type casted value in the data type we want to convert to.
     * 
     *  This function typeCast the value using boost::lexical_cast.
     *  First argument is the value that is to be converted.
     *  Will throw exception if occured, it is the responsibility of strategy to catch it 
     *  as per required.
     *
     *  lexicalCast < string,long long > ( string ) return long long;
     */
    template <typename from, typename to>
      to convert( const from& input )
      {
        to outPut;
        outPut = boost::lexical_cast <to> ( input );
        return outPut;
      }

    inline std::string convertToHumanReadableFormat(const long epochTime)
    {
      char buffer[80];
      struct tm *timeinfo;
      timeinfo = localtime(&epochTime);
      strftime(buffer,80,"%a %d-%b-%Y %X",timeinfo);
      return buffer;
    }

    /**
     *@brief This function returns the weighted average price for given market data w.r.t. quantity and order mode.
     */
    SIGNED_LONG getWeightedAveragePrice(
        API2::COMMON::MktData* mktData,
        SIGNED_LONG quantity,
        bool askOrBid = true,//true for ask leg average, false for bid leg
        API2::DebugLog *debugLog = NULL);


    /**
     * Used to get time diffrence from end time to current time in millsecond.
     * @Params End time in millisecond
     * @Return Epoch time in millisecond
     **/
    int64_t getTimeDifferenceFromNowTo(int64_t endTime); 

    /**
     *@brief  places new order with Standard Checks like
     *@brief  if confirmation is pending, if order is partially filled,
     *@Params OrderWrapper
     *@Params riskStatus
     *@Params Price
     *@Params Quantity
     *@Params checkBasicChecks - check TER, DPR,Freeze qty
     *@Return bool
     **/
    bool placeOrReplaceOrder(API2::COMMON::OrderWrapper &orderWrapper,
                       API2::DATA_TYPES::RiskStatus &riskStatus,
                       const API2::DATA_TYPES::PRICE price,
                       const API2::DATA_TYPES::QTY qty,
                       const bool checkBasicChecks = false,
                       const API2::DATA_TYPES::QTY freezeQty = 0);

    /**
     *@brief  checks of
     *@brief  if DRP/TER is breached, if Quantity is bigger than freeze Quantity
     *@Params Price
     *@Params Quantity
     *@Params orderWrapper
     *@Params checkBasicChecks - check TER, DPR,Freeze qty 
     *@Return bool
     **/
    bool isOrderPlaceable(const API2::DATA_TYPES::PRICE price,
                          const API2::DATA_TYPES::QTY qty,
                          API2::COMMON::OrderWrapper &orderWrapper,
                          const bool checkBasicChecks = false,
                          const API2::DATA_TYPES::QTY freezeQty = 0);

    /**
     *@brief  check for Market Depth
     *@Params mktData
     *@Return bool
     **/

    bool isMarketDepthAvailable(API2::COMMON::MktData *mktData);
    
    /**
     *@brief  check if Symbol is of NSE
     *@Params exchangeId
     *@Return bool
     **/
    bool isNseMarket(const API2::DATA_TYPES::ExchangeId exchangeId);

  }
}

#endif
