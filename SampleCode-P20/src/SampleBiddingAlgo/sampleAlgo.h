#ifndef ALGO_H
#define ALGO_H
#include <../common/common.h>
#include <sgContext.h>
#include<../common/orderWrapper.h>
#include<sys/time.h>
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <iostream>
#include <boost/unordered_map.hpp>
//#include <sharedUtilities.h>
namespace SBA
{ 
  struct FrontEndParameters
  {
    SIGNED_LONG symbol;
    SIGNED_LONG totalLots;
    SIGNED_LONG orderLots;
    SIGNED_LONG achievedPrice;
    SIGNED_LONG oppositePrice;
    SIGNED_LONG bestPriceTicks;
    char orderMode;
    API2::AccountDetail account;
    SIGNED_INTEGER strategyId;
    FrontEndParameters():
      symbol(0),
      totalLots(0),
      orderLots(0),
      achievedPrice(0),
      oppositePrice(0),
      bestPriceTicks(0),
      orderMode(0),
      strategyId(0)
    {
    }
  };
  class Bidding: public API2::SGContext
  {
    API2::COMMON::Instrument *_bidInstrument;
    FrontEndParameters _params, _modParams;
    SIGNED_LONG _marketPrice;
    SIGNED_LONG _traded;
    SIGNED_LONG _qty;
   // int  _child1 = 0;
    bool _modify;
    bool _terminateCheck;
    bool _isTimerOver;
    API2::CUSTOM_COMMON::OrderWrapper _bidOrderWrapper; 
    API2::DATA_TYPES::RiskStatus _riskStatus;
    API2::COMMON::MktData *_mkData;
    public:
    
   void popup(std::string);
    /*
     * @brief: Constructor
     */
    Bidding( API2::StrategyParameters *params );

    /*
     * @brief: algo driver
     * @params: obj
     */
    static void bidDriver(void *);

    /**
     * @brief: onTimerEvent
     */
    void onTimerEvent();

    /**
     * @brief: onDefaultEvent
     */
    void onDefaultEvent();

    /**
     * @brief: onCMDModifyStrategy
     * @params: AbstractUserParams
     */
    void onCMDModifyStrategy(API2::AbstractUserParams* newParams);

    /**
     * @brief: onCMDTerminateStartegy
     */
    void onCMDTerminateStartegy();

    /**
     * @brief: setInternalParameters 
     * @params: UserParams
     */
    bool setInternalParameters(API2::UserParams *customParams, SBA::FrontEndParameters &params);
    
    /**
     * @brief: mapModifiedParameters
     */
    void mapModifiedParameters();

    /*
     * @brief: dump
     */
    void dump(SBA::FrontEndParameters &params);

    /*
     * @brief: terminateStrategyComment
     * @params: StrategyComment
     */
    void terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment);
    /**
     * @brief: getMarketPrice
     * gets current market price or last trade price 
     * or close price
     */
    SIGNED_LONG getMarketPrice();

    /**
     * @brief: modifyStrategy
     */
    void modifyStrategy();

    /**
     * @brief: registerSymbols
     */
    void registerSymbols();

    /**
     * @brief: createOrderId
     */
    void createOrderIds();

    /**
     * @brief: sendUpdateResponse
     */
    void sendUpdateResponse();
SIGNED_LONG _algoId;
    /**
     * @brief: onMarketDataEvent
     */
    void onMarketDataEvent(UNSIGNED_LONG symbolId);

    /**
     * @brief: placeOrder
     */
    void placeOrder();

    /*
     * @brief: onConfirmed
     * @param: OrderConfirmation
     * @params: OrderId
     */
    void onConfirmed(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId);

    /*
     * @brief: onReplaced
     * @param: OrderConfirmation
     * @params: OrderId
     */
    void onReplaced(API2::OrderConfirmation&, API2::COMMON::OrderId*);

    /*
     * @brief: onFilled
     * @param: OrderConfirmation
     * @params: OrderId
     */
    void onFilled(API2::OrderConfirmation&, API2::COMMON::OrderId*);

    /*
     * @brief: onPartialFill
     * @param: OrderConfirmation
     * @params: OrderId
     */
    void onPartialFill(API2::OrderConfirmation&, API2::COMMON::OrderId*);

    /*
     * @brief: onRelaceRejected
     * @param: OrderConfirmation
     * @params: OrderId
     */
    void onReplaceRejected(API2::OrderConfirmation&, API2::COMMON::OrderId*);

    /*
     * @brief: onCancelRejected
     * @param: OrderConfirmation
     * @params: OrderId
     */
    void onCancelRejected(API2::OrderConfirmation&, API2::COMMON::OrderId*);

    /*
     * @brief: onNewRejected
     * @param: OrderConfirmation
     * @params: OrderId
     */
    void onNewReject(API2::OrderConfirmation&, API2::COMMON::OrderId*); 

    /*
     * @brief: onCanceled
     * @param: OrderConfirmation
     * @params: OrderId
     */
    void onCanceled(API2::OrderConfirmation&,API2::COMMON::OrderId*);
    /*
     * @brief: processOrder
     * @param: OrderConfirmation
     * @param: OrderId
     */
    bool processOrder(API2::OrderConfirmation&,API2::COMMON::OrderId*);
    
    void onRmsReject(API2::OrderConfirmation&,API2::COMMON::OrderId*);
    bool readParamsFromFile();
  };
}

/* This strategy place an order after adding or subtracting some value from market price, so that
 * order should be at the top of order depth.
 * On buy, it places an order at price = marketPrice(or ltp or close price) + (tickSize * bestPriceTicks)
 * On sell, it places an order at price =  marketPrice(or ltp or close price) - (tickSize * bestPriceTicks)
 * bestPriceTicks is set at frontend by user
 */
#endif
