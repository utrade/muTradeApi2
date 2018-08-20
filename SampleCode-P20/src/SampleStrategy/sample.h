#ifndef TEST_STRATEGY_H
#define TEST_STRATEGY_H

#include <orderWrapper.h>
#include <sgContext.h>
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <string>

namespace TestStrategy
{
  class TestContext;

  /**
   * @brief The FrontEndParameters struct
   */
  struct FrontEndParameters
  {
    SIGNED_LONG _symbolIdBidding;
    SIGNED_LONG _buyOrderLots;
    SIGNED_LONG _buyTotalLots;
    SIGNED_LONG _sellOrderLots;
    SIGNED_LONG _sellTotalLots;
    SIGNED_LONG _buyPrice;
    SIGNED_LONG _sellPrice;
    SIGNED_LONG _maxDiff;

    FrontEndParameters():
      _symbolIdBidding(0),
      _buyOrderLots(0),
      _buyTotalLots(0),
      _sellOrderLots(0),
      _sellTotalLots(0),
      _buyPrice(0),
      _sellPrice(0),
      _maxDiff(0)
    {}
  };

  /**
   *  @brief The Context class
   */
  class TestContext:public API2::SGContext
  {
    public:
      FrontEndParameters _userParams;
      FrontEndParameters _modUserParams;
      API2::COMMON::Instrument* _biddingInstrument;
      API2::CUSTOM_COMMON::OrderWrapper _buyOrderWrapper;
      API2::CUSTOM_COMMON::OrderWrapper _sellOrderWrapper;
      API2::DATA_TYPES::RiskStatus _riskStatus;
      TestContext(API2::StrategyParameters * params);
      const API2::DATA_TYPES::OrderMode _buyOrder;
      const API2::DATA_TYPES::OrderMode _sellOrder;
      bool _modify;
      bool _terminate;
      bool _isTbtEnabled;
      SIGNED_LONG _buyTotalTradedLots;
      SIGNED_LONG _sellTotalTradedLots;

      bool setInternalParameters(API2::UserParams *customParams);
      bool setModifiedInternalParameters(API2::UserParams *customParams);
      void registerSymbols();
      void setOrderWrapper();
      void placeOrder(const API2::DATA_TYPES::OrderMode &orderMode);
      void placeCancelOrder( API2::CUSTOM_COMMON::OrderWrapper &wrapper );
      void dump();
      void processStrategyState();
      void terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment);
      void terminateStrategy();
      void modifyStrategy();
      void mapFrontEndValues();
      void onDefaultEvent();
      void onMarketDataEvent(UNSIGNED_LONG symbolId);
      bool isAnyOrderPending();

      void onTimerEvent();
      /**
       * Exchange CallBacks
       */
      void onConfirmed(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId);
      void onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId);
      void onFrozen(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId);
      void onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId);
      /**
       * when front end requests for termination ,
       * this function gets called
       */
      void onCMDTerminateStartegy();
      /**
       * when front end requests for modification of params,
       * this function gets called
       */
      void onCMDModifyStrategy(API2::AbstractUserParams* newParams);
      /**
       * this function gets called from externalInterface.cpp 
       */
      static void driver(void *params);
  };
}
#endif



