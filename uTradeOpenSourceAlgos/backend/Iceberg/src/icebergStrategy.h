#ifndef ICEBERG_STRATEGY_H
#define ICEBERG_STRATEGY_H

#include "../common/orderWrapper.h"
#include <sgContext.h>
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <chrono>
#include <string>
#include <list>
#define TIMER 1000

namespace IcebergStrategy
{
  class Iceberg;

  struct FrontEndParameters
  {
    API2::DATA_TYPES::SYMBOL_ID _symbolId;
    API2::DATA_TYPES::QTY _quantity;
    SIGNED_LONG _disclosedQtyPercent;
    API2::DATA_TYPES::QTY _disclosedQty;
    API2::DATA_TYPES::PRICE _limitPrice;
    char _orderMode;
    char _fillType;
    char _orderType;
    API2::AccountDetail _account;
    std::string _parentOrderId;
    FrontEndParameters():
      _symbolId(0),
      _quantity(0),
      _disclosedQtyPercent(0),
      _disclosedQty(0),
      _limitPrice(0),
      _orderMode(API2::CONSTANTS::CMD_OrderMode_MAX),
      _fillType(API2::CONSTANTS::CMD_OrderValidity_DAY),
      _orderType(API2::CONSTANTS::CMD_OrderType_LIMIT)
    {}
  };
class IcebergWrapper:public API2::COMMON::OrderWrapper
  {
    public :

      IcebergWrapper(API2::COMMON::Instrument * instrument,
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

      IcebergWrapper(){
        _qty = 0;
        _wrapperPrice =  0;
        _totalTradedQty = 0;
      }
      SIGNED_LONG getQty(){ return _qty;} 
      void setQty(SIGNED_LONG qty){
        _qty = qty;
      }
      SIGNED_LONG getPrice(){ return _price;} 
      SIGNED_LONG _totalTradedQty;
    private :
      SIGNED_LONG _qty;
      SIGNED_LONG _wrapperPrice;
  };

  class Iceberg:public API2::SGContext
  {
    public:
      FrontEndParameters _userParams;
      FrontEndParameters _modUserParams;
      API2::DATA_TYPES::RiskStatus _riskStatus;
      Iceberg(API2::StrategyParameters * params);
      API2::COMMON::Instrument* _firstLegInstrument;
      API2::DATA_TYPES::QTY _disclosedQty;
      bool _terminate;
      bool _modify;
      bool _modifyReject;
      bool _isTbtEnabled;
      bool _isStrategyPaused;
      static bool _marketTickEnabled;      
      SIGNED_LONG _totalTradedQty;
      UNSIGNED_LONG _maxValue;
      std::list <std::pair<API2::COMMON::OrderId* , IcebergWrapper>> _orderIdWrapperList;
      void readParams(const std::string &file);
      API2::COMMON::Instrument* registerSymbols();
      void addOrderIntoList(SIGNED_LONG qty);
      bool setInternalParameters(API2::UserParams *customParams);
      bool setModifiedInternalParameters(API2::UserParams *customParams);
      void modifyStrategy();    
      void processCallBack(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId* orderId,const std::string &str);

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
      bool placeFirstLegOrder(SIGNED_LONG qty, IcebergWrapper &orderWrapper);
      void dump();
      static void driver(void *params);
      void onCMDTerminateStartegy();
      bool isNewPriceBetter();
      void processStrategyState();
  };
}
#endif
