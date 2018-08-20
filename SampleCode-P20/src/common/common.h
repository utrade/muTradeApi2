#ifndef API2_COMMON_H
#define API2_COMMON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
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

namespace API2
{
  namespace COMMON
  {
    static SIGNED_LONG defaultTerValue = -1;
    bool readFile(std::ifstream &file,std::string fileName,bool &isTbtEnabled,API2::DebugLog *debugLog);
    API2::COMMON::Instrument* registerSymbol(SIGNED_LONG symbolId,const bool &isTbtEnabled,SGContext *context);
    bool isPriceInTradeExecutionRange(API2::COMMON::Instrument* instrument,
        const SIGNED_LONG &orderPrice,
        DebugLog *debugLog,
        const bool &bidEnabledIfTerZero = true, 
        SIGNED_LONG &lowTer = defaultTerValue, 
        SIGNED_LONG &highTer = defaultTerValue);

    bool getBestPrice(SIGNED_LONG symbolId,
        DATA_TYPES::OrderMode side,
        SIGNED_LONG &price,
        CUSTOM_COMMON::OrderWrapper &orderWrapper,
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
    double getTimeToExpireInYears(API2::SymbolStaticData *data);
  }
}

#endif
