#ifndef INVOKINGAPI_H
#define INVOKINGAPI_H
#include<invokingApiStructs.h>
#include<sgDebugLogDefines.h> 

//DTA Work
//namespace UT
//{
//  namespace PROTO
//  {
//    class TWAP;
//    class POV;
//    class DTA;
//    class SampleAlgo;
//    class Account;
//    class ExecutionAlgoParams;
//  }
//}
//
//namespace API2
//{
// class UserParams;
//}

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

      InvokingApi() = default;

      /* @brief InvokingApi constructor
       * @param debugObject for message prints in strategy
       */
      explicit InvokingApi(API2::DebugLog *debugObject);

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
      static void terminateInvokedStrategy( int childId, char adminCommand );

      /* @brief validateApi validation checks are performed here
       * @param params parameters inputed by the user
       * return returns false if any of the validation check fails
       */
      virtual bool validateApi( void *sParams ){ return true; }


      //      DTA Work
      //      /**
      //       * @brief loadApiStrategy: loads dynamic library passed
      //       * @param path: path of dynamic library
      //       */
      //      int loadApiStrategy( const std::string& path );
      //
      //      /**
      //       * @brief handleApiStrategy: handles(run/modify) api strategy
      //       * @param apiId
      //       * @param buff
      //       * @param apiFrontEndDesign
      //       */
      //      bool handleApiStrategy(const int apiId, const char* buff, const std::string& apiFrontEndDesign );
      //      
      //      /**
      //       * @brief fillTwapParams: fills param for Execution Algo(twap)
      //       * @param userParams
      //       * @param twap
      //       */
      //      bool fillTwapParams( API2::UserParams& userParams, const UT::PROTO::TWAP& twap, API2::AccountDetail& acc );
      //
      //      /**
      //       * @brief fillPovParams: fills param for Execution Algo(pov)
      //       * @param userParams
      //       * @param pov
      //       */
      //      bool fillPovParams( API2::UserParams& userParams, const UT::PROTO::POV& pov, API2::AccountDetail& acc );
      //  
      //      /**
      //       * @brief fillApiParams: fills param of API strategies
      //       * @param userParams
      //       * @param dta
      //       */
      //      bool fillApiParams( API2::UserParams& userParams, const UT::PROTO::DTA& dta );
      //
      //      /**
      //       * @brief fillSampleParams: fills param for Sample algo
      //       * @param userParams
      //       * @param sample
      //       */
      //      bool fillSampleParams( API2::UserParams& userParams, const UT::PROTO::SampleAlgo& sample, API2::AccountDetail& acc );
      //  
      //      /**
      //       * @brief setAccountDetailFromProto: sets account details from proto structure
      //       * @param pAcc
      //       * @param acc
      //       */
      //      void setAccountDetailFromProto(const UT::PROTO::Account& pAcc, API2::AccountDetail& acc);
      //  
      //      /**
      //       * @brief fillExecParams: fills execution slago params
      //       * @param userParams
      //       * @param eParams
      //       */
      //      bool fillExecParams( API2::UserParams& userParams, const UT::PROTO::ExecutionAlgoParams& eParams );


  };
}
#endif
