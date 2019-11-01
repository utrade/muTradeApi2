#include "template.h"
#include "apiConstants.h"

namespace SampleTemplate{

// Template class constructor
// It Recieves the Parameter Structure from the Bid Driver Function
// Where it Type Casts them to user Params type for FILL_PARAMS Macro to work
// In this, typically strategy creates instruments for different symbols (legs), subscribes to market data (tbt / snapshot), and create order wrappers for bidding / hedging legs
Template::Template(API2::StrategyParameters* params):
    API2::SGContext(params, "Template"),
    _terminateCheck(false)
{
    //Set Parameters
    API2::UserParams* customParams = (API2::UserParams*) params->getInfo();
    if( !setInternalParameters(customParams,_userParams) )
    {
        DEBUG_MESSAGE(reqQryDebugLog(),"Parameters not set from front end");
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
        return;
    }
}


/* ---------------------------------------------Workflow Functions --------------------------------------------------*/

//Recieve Callbacks on Every Market Data Event
//In this function,we can perform the calculations if any change in market corresponding to symbolId
void Template::onMarketDataEvent(UNSIGNED_LONG symbolId)
{
    DEBUG_MESSAGE(reqQryDebugLog(), "In onMarketDataEvent");
    onDefaultEvent();
}

//Recieve Callbacks from reqTimerEvent
//In this function,Call back when an timer set by reqTimerEvent expires
//Here,after 1000000 microsecond i.e. 1 second this function gets the callback
void Template::onTimerEvent()
{

    reqTimerEvent(1000000);
    onDefaultEvent();

}

//Strategy Driver event
//onDefaultEvent Called as an event if Not configured to received marketData Event while Running strategy
void Template::onDefaultEvent()
{

}
 
//Method to do common work for all type of confirmations, confirmation status dependent work is done in specific methods
bool Template::processConfirmation(API2::COMMON::OrderWrapper &orderWrapper,API2::OrderConfirmation &confirmation,const API2::COMMON::OrderId *orderId)
{
    reqQryDebugLog()->saveConfirmation(confirmation);
    if(orderWrapper._orderId==orderId)
    {
      return orderWrapper.processConfirmation(confirmation);
    }
    return false;
}

//CallBack When a new Order gets confirmed by exchange
//Here we typically update the corresponding order wrapper's state, update any strategy state variables
void Template::onConfirmed(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId)
{
    if(!processConfirmation(_orderWrapper,confirmation,orderId))
    {
        DEBUG_MESSAGE(reqQryDebugLog(),"Process Confirmation Failed");
    }
}

//CallBack When a new order gets rejected by the exchange
void Template::onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  if(!processConfirmation(_orderWrapper,confirmation,orderId))
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Process Confirmation Failed");
  }
}

//CallBack When an IOC order gets canceled by the exchange
void Template::onIOCCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  if(!processConfirmation(_orderWrapper,confirmation,orderId))
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Process Confirmation Failed");
  }
}
//CallBack When an Order gets Filled at the exchange
//Here we typically update the corresponding order wrapper's state, update any strategy member variables like self maintained custom positions etc
void Template::onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{

    if(!processConfirmation(_orderWrapper,confirmation,orderId))
    {
        DEBUG_MESSAGE(reqQryDebugLog(),"Process Confirmation Failed");
    }

}

//CallBack When an Order gets Partially Filled at the exchange
void Template::onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
    if(!processConfirmation(_orderWrapper,confirmation,orderId))
    {
        DEBUG_MESSAGE(reqQryDebugLog(),"Process Confirmation Failed");
    }


}

//CallBack When a order is cancelled from exchange
void Template::onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
    if(!processConfirmation(_orderWrapper,confirmation,orderId))
    {
        DEBUG_MESSAGE(reqQryDebugLog(),"Process Confirmation Failed");
    }
}

//CallBack When an Order gets Replaced successfully at the exchange
void Template::onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
    if(!processConfirmation(_orderWrapper,confirmation,orderId))
    {
        DEBUG_MESSAGE(reqQryDebugLog(),"Process Confirmation Failed");
    }

}

//CallBack When an Order's Replace Request gets rejected by the exchange
void Template::onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
    if(!processConfirmation(_orderWrapper,confirmation,orderId))
    {
        DEBUG_MESSAGE(reqQryDebugLog(),"Process Confirmation Failed");
    }
}
//CallBack for When an Order's Cancel Request gets rejected by the exchange
void Template::onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
    if(!processConfirmation(_orderWrapper,confirmation,orderId))
    {
        DEBUG_MESSAGE(reqQryDebugLog(),"Process Confirmation Failed");
    }

}
//Strategy receives Terminate command from Front End
void Template::onCMDTerminateStartegy()
{
    DEBUG_MESSAGE(reqQryDebugLog(),"Strategy Ended From FrontEnd");
    terminateStrategyComment(API2::CONSTANTS::CMD_CommandCategory_TERMINATE_STRATEGY);
}


/* ---------------------------------------------Implementation Functions --------------------------------------------------*/



//This is called from external interface, it registers the strategy and starts it
//Here Strategy is Registered
void Template::bidDriver(void *params)
{

    API2::StrategyParameters *sgParams = (API2::StrategyParameters *) params;
    boost::shared_ptr<API2::SGContext> obj (new Template(sgParams));
    /**
      * @brief reqStartAlgo function call to Start the Strategy
      * @param marketDataEventRequired Set True to register for call-backs on Market-Data Event on registered Instruments [Required]
      * @param tradeTicksEventRequired Set True to register for call-backs on Trade Tick Events on registered Instruments [Required]
      * @param preTradeEventRequired Set True to register for call-backs for pre trade confirmations [Default is false]
      * @param isConvertToManualOrder Set True if you want your open order's to persist after termination of algo. Order will start behaving like manual order. [Default is false]
      * @param childConfirmationEvent Set True to register for call-backs for confirmations coming from child strategy [Default is false]
      * * @return
      */

    obj->reqStartAlgo(true, false);
    API2::SGContext::registerStrategy(obj);
    obj->reqTimerEvent(10000);
    DEBUG_MESSAGE(obj->reqQryDebugLog(),"Strategy Registered!");

}
 
//Set our Parameter Structure
bool Template::setInternalParameters(API2::UserParams *customParams, FrontEndParameters &userParams)
{
    char tempValue;
    FILL_PARAMS("SYMBOL LEG1",userParams.symbol);
    FILL_PARAMS("TotalQuantity",userParams.totalQuantity);
    FILL_PARAMS("OrderQuantity",userParams.perOrderQuantity);
    FILL_PARAMS("Acc Detail 1",userParams.account);
    FILL_PARAMS("Order Mode 1",tempValue);
    userParams.orderMode = (API2::DATA_TYPES::OrderMode)tempValue;
    userParams.strategyID = customParams->getStrategyId();
    dump(userParams);
    return true;
}
//Strategy modify command received from FrontEnd
//Here usually new parameters are saved and used from next strategy iteration (eg. bid / hedge cycle)
void Template::onCMDModifyStrategy(API2::AbstractUserParams* newParams)
{
  if(_terminateCheck) return;

  API2::UserParams* customParams = (API2::UserParams*) newParams;
 
  if(!setModifiedInternalParameters(customParams, _modUserParams))
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Parameters not set from front end");
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
    return;
  }
  if(!mapModParameters())
  {
    dump(_userParams);
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return;
  }
  reqSendStrategyResponse(
      API2::CONSTANTS::RSP_ResponseType_STRATEGY_RUNNING,
      API2::CONSTANTS::RSP_RiskStatus_SUCCESS,
      API2::CONSTANTS::RSP_StrategyComment_USER_INPUT);
}
//set modified parameters to current frontend parameters
bool Template::mapModParameters()
{
  _userParams.totalQuantity = _modUserParams.totalQuantity;
  _userParams.perOrderQuantity = _modUserParams.perOrderQuantity;
  return true;
}

//Set modified Internal parameters
bool Template::setModifiedInternalParameters(API2::UserParams *customParams, FrontEndParameters &userParams)
{
  FILL_PARAMS("TotalQuantity",userParams.totalQuantity);
  FILL_PARAMS("OrderQuantity",userParams.perOrderQuantity);
  return true;
}

//Terminate strategy and cancel strategy's open orders
void Template::terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment)
{
    if(_terminateCheck) return;

    _terminateCheck = true;

    reqAddStrategyComment(comment);
    reqTerminateStrategy();
}
//dump function to flush our FrontEnd Values
void Template::dump(FrontEndParameters &params)
{
    DEBUG_VARSHOW(reqQryDebugLog(),"SYMBOL LEG",(int)params.symbol);
    DEBUG_VARSHOW(reqQryDebugLog(),"TotalLots",params.totalQuantity);
    DEBUG_VARSHOW(reqQryDebugLog(),"OrderLots",params.perOrderQuantity);
    DEBUG_VARSHOW(reqQryDebugLog(),"Order Mode ",(API2::DATA_TYPES::OrderMode)params.orderMode);
}

}
