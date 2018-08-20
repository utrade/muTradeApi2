#ifndef INVOKINGAPI_H
#define INVOKINGAPI_H
#include<invokingApiStructs.h>
#include<sgDebugLogDefines.h> 
namespace INVOKING
{

  //type of strategy to be invoked
  enum StrategyType
  {
    StrategyType_Cash_Fut,
    StrategyTye_MAX
  };

  class InvokingApi  
  {
    private:

      API2::DebugLog * _debugObject;

    public:

      /* @brief InvokingApi constructor
       * @param debugObject for message prints in strategy
       */
      InvokingApi(API2::DebugLog *debugObject);

      /* @brief runStrategy Runs a strategy from another strategy
       * @param sType The type of strategy to run
       * @param sParams The parameter structure required to run strategy
       * @param childId Holds the strategyId of strategy Invoked
       * @return returns false if not able to run the strategy
       */
      bool runStrategy( INVOKING::StrategyType sType,void *sParams, int *childId );

      /* @brief terminateInvokedStrategy
       * @param childId strategyId to be terminated
       * @param adminCommand command recieved for termi
       */
      void terminateInvokedStrategy( int childId, char adminCommand );

      /* @brief validateApi validation checks are performed here
       * @param params parameters inputed by the user
       * return returns false if any of the validation check fails
       */
      virtual bool validateApi( void *sParams ){ return true; }

  };
}
#endif
