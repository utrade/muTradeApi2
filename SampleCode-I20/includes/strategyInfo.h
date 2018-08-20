#ifndef STRATEGYINFO_H
#define STRATEGYINFO_H
#include<sharedResponse.h>
#include<sharedDefines.h>
#include<position.h>
#include<invokingApi.h>
#include <boost/unordered_map.hpp>
namespace INVOKING
{
  class StrategyInfo
  {

    public:
      
      /**
       * @brief getPosition gets the position of the child strategy with respect to symbolId and orderMode
       * @param symbolId
       * @param orderMode
       * @return returns Position
       */
      Position* getPosition( long symbolId, UNSIGNED_SHORT orderMode );

      /**
       * @brief getExSpread gets the execution spread of child strategy
       * @param symbolIds symbols ids of all legs
       * @param orderModes order mode of all legs
       * @return returns executionSpread as per max precision of both legs
       */
      double getExSpread(const std::vector<long> &symbolIds,const std::vector<UNSIGNED_SHORT> &orderModes );
 
      /**
       * @brief getResponseType gets the latest response sent by strategy
       * @return returns response
       */
      UNSIGNED_CHARACTER getResponseType() const;
      
      /**
       * @brief getRiskStatus gets the latest risk status sent by strategy
       * @return returns risk status
       */
      UNSIGNED_CHARACTER getRiskStatus() const;

      /**
       * @brief getStrategyComment gets the latest strategy comment sent by strategy
       * @return returns strategy comment
       */
      UNSIGNED_CHARACTER getStrategyComment() const;

      /*
       * @brief StrategyInfo constructor
       * @param debugObject for message prints in strategy
       */
      StrategyInfo( API2::DebugLog *debugObject );

     
      /*
       * @brief ~StrategyInfo a destructor
       */
      ~StrategyInfo();
  }; 
}
#endif
