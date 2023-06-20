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
#include <sharedUtilities.h>
#include <invokingApi.h>

//Flag used to demonstrate functionality of invoking
//API(running built in strategy from API strategy)
#define INVOKING_API 0

//Flag used to demonstrate sending popup to frontend
#define SEND_POPUP 0

namespace SBA
{
  struct FrontEndParameters
  {
    SIGNED_LONG symbol;
    SIGNED_LONG totalLots;
    SIGNED_LONG orderLots;
    SIGNED_LONG achievedPrice;
    SIGNED_LONG oppositePrice;
    
    /*
     * @brief: orderPriceTicks 
     */
    SIGNED_LONG orderPriceTicks;

    /*
     * @brief: triggerPriceTicks
     */
    SIGNED_LONG triggerPriceTicks;

    /*
     * @brief: marketPercentage
     */
    SIGNED_LONG marketPercentage;

    /*
     * @brief: orderType
     * There can be 3 types of order - limit, stop loss market and stop loss limit
     */
    char orderType;

    char orderMode;
    API2::AccountDetail account;
    SIGNED_INTEGER strategyId;
    FrontEndParameters():
      symbol(0),
      totalLots(0),
      orderLots(0),
      achievedPrice(0),
      oppositePrice(0),
      orderPriceTicks(0),
      triggerPriceTicks(0),
      marketPercentage(0),
      orderType(0),
      orderMode(0),
      strategyId(0)
    {
    }
  };
  class Bidding: public API2::SGContext
  {
    API2::COMMON::Instrument *_bidInstrument;
    FrontEndParameters _params, _modParams;

    /*
     * @brief: _orderPrice (at which order is placed) 
     */
    SIGNED_LONG _orderPrice;

    /*
     * @brief: _triggerPrice (price at which stop loss order will be triggered) 
     */
    SIGNED_LONG _triggerPrice;

    /*
     * @brief: _lastPrice (last price at which bid order was placed)
     */
    SIGNED_LONG _lastPrice;

    /*
     * @brief _lastTriggerPrice(last triggerPrice at which stop loss order was placed)
     */
    SIGNED_LONG _lastTriggerPrice;

    SIGNED_LONG _traded;
    SIGNED_LONG _qty;
    int  _child1 = 0;
    bool _modify;
    bool _terminateCheck;
    bool _isTimerOver;
    API2::COMMON::OrderWrapper _bidOrderWrapper; 
    API2::DATA_TYPES::RiskStatus _riskStatus;
    API2::COMMON::MktData *_mkData;
#ifdef INVOKING_API
    INVOKING::InvokingApi *invokingApi;
    INVOKING::TwoLegArbitrage *cashFutParams;
#endif

    enum Type
    {
      Type_LIMIT = 0,
      Type_STOP_LIMIT = 1,
      Type_STOP = 2,
    };

    public:
    
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
     * @brief: calculatePrice
     * gets current market price or last trade price 
     * or close price or trigger price
     */
    bool calculatePrice();

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
    bool createOrderIds();

    /**
     * @brief: sendUpdateResponse
     */
    void sendUpdateResponse();

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
    
    /*
     * @brief: onRmsReject
     * @param: OrderConfirmation
     * @param: OrderId
     */
    void onRmsReject(API2::OrderConfirmation&,API2::COMMON::OrderId*);

    /*
     * @brief: calculateLimitPrice - Calculates order price for limit orders.
     */
    bool calculateLimitPrice();

    /*
     * @brief: calculateStopLossLimitPrice - Calculates orderPrice/triggerPrice for
     *                                       StopLossLimit orders.
     */
    bool calculateStopLossLimitPrice();

    /*
     * @brief: calculateStopLossMarketPrice - Calculates orderPrice/triggerPrice for
     *                                        StopLossMarket orders.
     *                                        Note: order price is calculated here as
     *                                        exchange dont allow algo order at orderPrice
     *                                        zero.
     */
    bool calculateStopLossMarketPrice();
  
    /*
     * @brief: isPriceValid - In case of modification checks if price is valid, i.e not
     *                        the same as previous.
     */
    bool isPriceValid();

    /*
     * @brief: checkValidations - Applies some basic validations on parameters passed
     *                            from frontend.
     */
    bool checkValidations();

    /*
     * @brief: replaceOrder - Replaces bid order, if parameters are changed at frontend,
     *                        and calculated price is different from price at which
     *                        order is placed.
     */
    void replaceOrder();

    /*
     * @brief: printChildPosition - This function is used to demonstrate how 
     *                              position of child strategy can be accessed,
     *                              if we are useing invoking api functionality.
     * @param childId
     */
    void printChildPosition( const API2::DATA_TYPES::STRATEGY_ID childId );

    /*
     * @brief: runCashFut - This function is used to demonstrate how a built in
     *                      strategy(cash future) can be run from an api strategy
     *                      if we are using invoking api functionality. Some random
     *                      values are passed in the params for now.
     */
    void runCashFut();
  };
}

/* This strategy places only bidding orders with three type of order modes( limit,
 * stop loss market and stop loss limit ).
 *
 * 1. limit
 *    - orderPriceTicks is set at frontend by user
 *    - BUY:  OrderPrice = bestBidPrice(or ltp or close price) + (tickSize * orderPriceTicks)
 *    - SELL: OrderPrice =  bestBiedPrice(or ltp or close price) - (tickSize * orderPriceTicks)
 *
 * 2. Stop Loss Market
 *    - TriggerPriceTicks and Market percentage is passed from frontend.
 *    - TriggerPrice is calculated by applying triggerPriceTicks on LTP.
 *      BUY:  TriggerPrice = LTP + TriggerTick
 *      SELL: TriggerPrice = LTP - TriggerTick
 *    - OrderPrice is calculated by applying market percentage on triggerPrice.
 *    
 *
 * 3. Stop Loss Limit
 *    - OrderPriceTicks and triggerPriceTicks is passed from frontend
 *    - TriggerPrice & OrderPrice both are calulated by applying OrderPriceTicks
 *      and triggerPriceTicks respectively.
 *    - TriggerTick = tickSize * triggerPriceTicks
 *    - PriceTick = tickSize * orderPriceTicks
 *    - BUY: OrderPrice = LTP + PriceTick
 *           TriggerPrice = LTP + TriggerTick
 *    - SELL: OrderPrice = LTP - PriceTick
 *           TriggerPrice = LTP - TriggerTick
 * 
 *
 * Note: Order are replaced only if parameters values are changed from frontend.
 */
#endif
