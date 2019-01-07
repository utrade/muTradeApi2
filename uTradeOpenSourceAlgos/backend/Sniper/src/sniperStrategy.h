#ifndef SNIPER_STRATEGY_H
#define SNIPER_STRATEGY_H

#include "../common/orderWrapper.h"
#include <sgContext.h>
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <chrono>
#include <string>
#define TIMER 250000

namespace SniperStrategy
{
  class Sniper;

  struct FrontEndParameters
  {
    API2::DATA_TYPES::SYMBOL_ID _symbolId;
    API2::DATA_TYPES::QTY _quantity;
    API2::DATA_TYPES::PRICE _triggerPrice;
    API2::DATA_TYPES::PRICE _limitPrice;
    char _orderMode;
    char _fillType;
    char _orderType;
    API2::AccountDetail _account;
    std::string _parentOrderId;
    FrontEndParameters():
      _symbolId(0),
      _quantity(0),
      _triggerPrice(0),
      _limitPrice(0),
      _orderMode(API2::CONSTANTS::CMD_OrderMode_MAX),
      _fillType(API2::CONSTANTS::CMD_OrderValidity_IOC),
      _orderType(API2::CONSTANTS::CMD_OrderType_LIMIT)
    {}
  };
class SniperWrapper:public API2::COMMON::OrderWrapper
  {
    public :

      SniperWrapper(API2::COMMON::Instrument * instrument,
          const API2::DATA_TYPES::OrderMode &mode,
          API2::SGContext *context,
          const API2::AccountDetail &account,
          const API2::DATA_TYPES::OrderType &type = API2::CONSTANTS::CMD_OrderType_LIMIT,
          const API2::DATA_TYPES::OrderValidity &validity = API2::CONSTANTS::CMD_OrderValidity_DAY,
          SIGNED_LONG qty = 0,
          SIGNED_LONG price = 0
          ): API2::COMMON::OrderWrapper(instrument,
            mode,
            context,
            account,
            type,
            validity
            )
      {
        _qty = qty;
        _wrapperPrice =  price;
        _totalTradedQty = 0;
      }

      SniperWrapper(){
        _qty = 0;
        _wrapperPrice =  0;
        _totalTradedQty = 0;
      }
      SIGNED_LONG getQty(){ return _qty;} 
      SIGNED_LONG getPrice(){ return _price;} 
      SIGNED_LONG _totalTradedQty;
    private :
      SIGNED_LONG _qty;
      SIGNED_LONG _wrapperPrice;
  };

  class Sniper:public API2::SGContext
  {
    public:
      FrontEndParameters _userParams;
      FrontEndParameters _modUserParams;
      API2::DATA_TYPES::RiskStatus _riskStatus;
      Sniper(API2::StrategyParameters * params);
      const API2::DATA_TYPES::OrderMode _buyOrder;
      const API2::DATA_TYPES::OrderMode _sellOrder;
      API2::COMMON::Instrument* _firstLegInstrument;
      SniperWrapper _firstLegOrderWrapper;
      bool _modify;
      bool _terminate;
      bool _isTbtEnabled;
      bool _isStrategyPaused;
      static bool _marketTickEnabled;      
      bool _wrapperParametersModified;
      bool _modifyReject;
      UNSIGNED_LONG _maxValue;
      void readParams(const std::string &file);
      API2::COMMON::Instrument* registerSymbols();
      void setFirstLegOrderWrapper();
      bool setInternalParameters(API2::UserParams *customParams);
      bool setModifiedInternalParameters(API2::UserParams *customParams);
      void modifyStrategy();    
      void processCallBack(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId* orderId,const std::string &str);
      void processStrategyState();

      void mapFrontEndValues();
      void onMarketDataEvent(UNSIGNED_LONG symbolId);
      void onDefaultTimerEvent();
      void onTimerEvent(){ onDefaultTimerEvent();reqTimerEvent(TIMER); }
      void terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment);
      void onCMDModifyStrategy(API2::AbstractUserParams* newParams);
      void onCMDPauseStrategy()
      { 
        DEBUG_METHOD_DETAILED(reqQryDebugLog()); 
        _isStrategyPaused = true;
      }
      void onCMDResumeStrategy()
      {
        DEBUG_METHOD_DETAILED(reqQryDebugLog());
        _isStrategyPaused = false;
      }
      void onConfirmed(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId);
      void onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId);
      void onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId);
      void onFrozen(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId);
      void onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId);
      void placeFirstLegOrder(UNSIGNED_LONG price, SIGNED_LONG depthQty, UNSIGNED_LONG lastTradePrice);
      void dump();
      static void driver(void *params);
      bool performValidations(FrontEndParameters &_userParams);
      void onCMDTerminateStartegy();
  };
}
#endif
