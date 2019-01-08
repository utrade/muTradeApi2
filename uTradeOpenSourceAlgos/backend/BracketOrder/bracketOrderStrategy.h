#ifndef BRACKET_ORDER_STRATEGY_H
#define BRACKET_ORDER_STRATEGY_H

#include "../common/orderWrapper.h"
#include <sgContext.h>
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <chrono>
#include <string>
#define TIMER 250000

namespace BracketOrderStrategy
{
  enum Quantity 
  {
    HALF,
    FULL
  };

  class BracketOrder;

  struct FrontEndParameters
  {
    API2::DATA_TYPES::SYMBOL_ID _symbolId;
    API2::DATA_TYPES::QTY _quantityLeg1;
    char _quantityLeg2;    
    char _quantityLeg3;
    API2::DATA_TYPES::PRICE _triggerPriceLeg1;
    API2::DATA_TYPES::PRICE _triggerPriceLeg2;
    API2::DATA_TYPES::PRICE _triggerPriceLeg3;
    API2::DATA_TYPES::PRICE _limitPriceLeg1;
    API2::DATA_TYPES::PRICE _limitPriceLeg2;
    API2::DATA_TYPES::PRICE _limitPriceLeg3;
    char _orderModeLeg1;
    char _orderModeLeg2;
    char _orderModeLeg3;
    char _orderTypeLeg1;
    char _orderTypeLeg2;
    char _orderTypeLeg3;
    char _fillTypeLeg1;
    char _fillTypeLeg2;
    char _fillTypeLeg3;
    API2::AccountDetail _account;
    std::string _parentOrderId;
    FrontEndParameters():
      _symbolId(0),
      _quantityLeg1(0),
      _quantityLeg2(0),
      _quantityLeg3(0),
      _triggerPriceLeg1(0),
      _triggerPriceLeg2(0),
      _triggerPriceLeg3(0),
      _limitPriceLeg1(0),
      _limitPriceLeg2(0),
      _limitPriceLeg3(0),
      _orderModeLeg1(API2::CONSTANTS::CMD_OrderMode_MAX),
      _orderModeLeg2(API2::CONSTANTS::CMD_OrderMode_MAX),
      _orderModeLeg3(API2::CONSTANTS::CMD_OrderMode_MAX),
      _orderTypeLeg1(API2::CONSTANTS::CMD_OrderType_LIMIT),
      _orderTypeLeg2(API2::CONSTANTS::CMD_OrderType_LIMIT),
      _orderTypeLeg3(API2::CONSTANTS::CMD_OrderType_LIMIT),
      _fillTypeLeg1(API2::CONSTANTS::CMD_OrderValidity_DAY),
      _fillTypeLeg2(API2::CONSTANTS::CMD_OrderValidity_DAY),
      _fillTypeLeg3(API2::CONSTANTS::CMD_OrderValidity_DAY)
    {}
  };

class BracketOrderWrapper:public API2::COMMON::OrderWrapper
  {
    public :

      BracketOrderWrapper(API2::COMMON::Instrument * instrument,
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

      BracketOrderWrapper(){
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

  class BracketOrder:public API2::SGContext
  {
    public: 
      FrontEndParameters _userParams;
      FrontEndParameters _modUserParams;
      API2::DATA_TYPES::RiskStatus _riskStatus;
      BracketOrder(API2::StrategyParameters * params);
      const API2::DATA_TYPES::OrderMode _buyOrder;
      const API2::DATA_TYPES::OrderMode _sellOrder;
      API2::COMMON::Instrument* _instrument;
      BracketOrderWrapper _firstLegOrderWrapper; 
      BracketOrderWrapper _secondLegOrderWrapper;
      BracketOrderWrapper _thirdLegOrderWrapper;
      bool _modify;
      bool _terminate;
      bool _isTbtEnabled;
      bool _isStrategyPaused;
      static bool _marketTickEnabled;      
      bool _modifyReject;
      API2::DATA_TYPES::QTY _secondLegCalculatedQty;
      API2::DATA_TYPES::QTY _thirdLegCalculatedQty;
      UNSIGNED_LONG _maxValue;
      void readParams(const std::string &file);
      API2::COMMON::Instrument* registerSymbols();
      void setOrderWrapper();
      bool _cancelSecondLegOrder;
      bool _cancelThirdLegOrder;
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
      void placeFirstLegOrder(UNSIGNED_LONG price, UNSIGNED_LONG lastTradePrice);
      void placeSecondLegOrder(SIGNED_LONG price, UNSIGNED_LONG lastTradePrice);
      void placeThirdLegOrder(SIGNED_LONG price, UNSIGNED_LONG lastTradePrice);
      void calculateSecondThirdLegQty();
      void dump();
      static void driver(void *params);
      bool performValidations(FrontEndParameters &_userParams);
      void onCMDTerminateStartegy();
  };
}
#endif
