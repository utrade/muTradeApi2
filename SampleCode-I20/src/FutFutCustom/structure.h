#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "../api_includes/sgContext.h"
#include "../common/common.h"
#include "../api_includes/sgMktData.h"
#include "../api_includes/sgDebugLogDefines.h"

namespace SampleFutFutArbitrage{

  struct Utilities
  {
    Utilities():
      context(nullptr),
      instrument1(nullptr),
      instrument2(nullptr),
      mktData1(nullptr),
      mktData2(nullptr),
      debugLog(nullptr),
      ratio1(0),
      ratio2(0),
      checkBasicChecks(0)
    {
    }

    API2::SGContext *context;
    API2::COMMON::Instrument *instrument1;
    API2::COMMON::Instrument *instrument2;
    API2::COMMON::MktData *mktData1;
    API2::COMMON::MktData *mktData2;
    API2::DebugLog *debugLog;
    int32_t ratio1;
    int32_t ratio2;

    /**
     * @brief checkBasicChecks
     * set true or false in config file
     * user wants to check Basic checks before placing order like DPR check,TER check,freeze qty check or not
     */
    bool checkBasicChecks; 

    void init(API2::SGContext *sgContext,
        API2::DebugLog *debugLogContext)
    {
      context = sgContext;
      debugLog = debugLogContext;
    }
  };
}

#endif // STRUCTURE_H
