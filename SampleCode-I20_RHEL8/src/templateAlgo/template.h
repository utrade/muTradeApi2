#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "../common/common.h"
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <orderWrapperAPI.h>
#include <sgContext.h>
#include <cmdDefines.h>

namespace SampleTemplate{

struct FrontEndParameters
{
  API2::DATA_TYPES::SYMBOL_ID symbol;
  API2::DATA_TYPES::QTY totalQuantity;
  API2::DATA_TYPES::QTY perOrderQuantity;
  API2::DATA_TYPES::OrderMode orderMode;
  API2::AccountDetail account;
  SIGNED_INTEGER strategyID;
  FrontEndParameters():
    symbol(0),
    totalQuantity(0),
    perOrderQuantity(0),
    orderMode(API2::CONSTANTS::CMD_OrderMode_MAX),
    strategyID(0)
  {
  }
};


/**
 * @brief Derived from SGContext, this class Drives our strategy through callbacks
 * @brief Handle the Bidding leg
 * @brief FrontEndParameters Structure
 * @brief Typically we keep instruments(for different legs), order wrappers(for different usages in different legs), and strategy state variables here
 */
class Template : public API2::SGContext
{

    /**
     * @brief Save Parameters Received from FrontEnd
     * @returnType FrontEndParameters Structure
     */
    FrontEndParameters _userParams;

    /**
     * @brief Save Modified Parameters Received from FrontEnd
     * @returnType FrontEndParameters Structure
     */
    FrontEndParameters _modUserParams;

    /**
     * @brief Bidding Order Wrapper
     * @returnType OrderWrapper
     */
    API2::COMMON::OrderWrapper _orderWrapper;

    /**
     * @brief Flag to Maintain Terminate State
     * @returnType Boolean
     */
    bool _terminateCheck;


    /**
     * @brief OrderValidity
     * @returnType OrderValidity
     */
    void dump(FrontEndParameters &params);
public:

    /**
     * @brief Constructor
     * @param pointer to StrategyParameters
     */
    Template(API2::StrategyParameters* params);

    /* ---------------------------------------------Implementation Functions --------------------------------------------------*/

    /**
     * @type Implementation Function
     * @brief Register Our Strategy with shared Object of this class
     * @param Void Pointer
     * @return void
     */
    static void bidDriver(void *);

    /**
     * @type Implementation Function
     * @brief Maps Values from Frontend to our Structure Object of FrontEndParameters
     * @param customParams
     * @param userParams
     * @return Boolean
     */
    bool setInternalParameters(API2::UserParams *customParams,FrontEndParameters &_userParams);

    /**
     * @type Implementation Function
     * @brief Maps Modified Values from Frontend to our Structure Object of FrontEndParameters
     * @param customParams
     * @param userParams
     * @return Boolean
     */
    bool setModifiedInternalParameters(API2::UserParams *customParams,FrontEndParameters &_userParams);

    /**
     * @brief Map Modified Params to our current FrontEndParams Structure Object
     * @return bool 
     */
    bool mapModParameters();

    /**
     * @type Implementation Function
     * @brief Terminate Strategy and turn _terminateCheck to True
     * @param comment
     * @return void
     */
    void terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment);

    /**
     * @type Implementation Function
     * @brief process OrderConfirmation of a given order Wrapper
     * @param orderWrapper
     * @param Confirmation
     * @param orderId
     * @return void
     */
    bool processConfirmation(API2::COMMON::OrderWrapper &orderWrapper,API2::OrderConfirmation &confirmation,const API2::COMMON::OrderId *orderId);

    /* ---------------------------------------------Workflow Functions --------------------------------------------------*/

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever a MarketEvent is Generated, on Subscribed Symbols via TBT or SnapShot
     * @param symbolId
     * @return void
     */
    void onMarketDataEvent(UNSIGNED_LONG symbolId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever Timer has expired of reqTimerEvent
     * @return void
     */
    void onTimerEvent() override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback from Most of the events
     * @return void
     */
    void onDefaultEvent() override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Order is Confirmed
     * @param OrderConfirmation
     * @param OrderId
     * @return void
     */
    void onConfirmed(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId) override;
    
    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an IOC order gets canceled by exchange
     * @param OrderConfirmation
     * @param OrderId
     * @return void
     */
    void onIOCCanceled(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever a new order gets rejected by the exchange
     * @param OrderConfirmation
     * @param OrderId
     * @return void
     */
    void onNewReject(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId) override;
    
    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Order is Completely Filled
     * @param OrderConfirmation
     * @param OrderId
     * @return void
     */
    void onFilled(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Order is Partially  Filled
     * @param OrderConfirmation
     * @param OrderId
     * @return void
     */
    void onPartialFill(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Order is Canceled
     * @param OrderConfirmation
     * @param OrderId
     * @return void
     */
    void onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Replace Order is Confirmed
     * @param OrderConfirmation
     * @param OrderId
     * @return void
     */
    void onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Replace Order is Confirmed
     * @param OrderConfirmation
     * @param OrderId
     * @return void
     */
    void onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Cancel Order is Rejected
     * @param OrderConfirmation
     * @param OrderId
     * @return void
     */
    void onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever a Strategy is terminated from FrontEnd
     * @return void
     */
    void onCMDTerminateStartegy() override;

    /**
     * @type Implementation Function
     * @brief Initialize Modifying Strategy, when signaled from FrontEnd
     * @param newParams
     * @return void
     */
    void onCMDModifyStrategy(API2::AbstractUserParams* newParams) override;

};
}
#endif // TEMPLATE_H
