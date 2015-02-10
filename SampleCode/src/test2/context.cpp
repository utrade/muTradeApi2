#include "context.h"
#include <sharedCommands.h>
#include <fstream>
#include <sgMktData.h>
#include <ctime>
#include <sys/time.h>
#include <math.h>
#define TESTING
#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW CLOCK_MONOTONIC
#endif


API2::Test2::Context::Context(API2::StrategyParameters *params):
  API2::SGContext(params, "CustomTest2"),
  _Instrument(NULL),
  _userParams()
{
  API2::UserParams *customOMMParams = (API2::UserParams *)params->getInfo();
  DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__ );

  customOMMParams->dump();
  if(!setInternalParameters(customOMMParams))
  {
    reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
    reqTerminateStrategy();
  }



}
void API2::Test2::Context::onMarketDataEvent(UNSIGNED_LONG symbolId)
{
  API2::DATA_TYPES::RiskStatus risk;

  //    DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__ );
  //    DEBUG_FLUSH(reqQryDebugLog());

  //    reqQryMarketData(symbolId)->dump();
  //    return;





  if(_orderWrapper._isReset)
  {
    DEBUG_MESSAGE(reqQryDebugLog(), "Sending New Order");

    if(!_orderWrapper.newOrder(risk,getPrice(),_userParams._qty))
    {
      DEBUG_VARSHOW(reqQryDebugLog(), "Failed Sending New Order, Reason:", risk);
      DEBUG_FLUSH(reqQryDebugLog());

      reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_RMS_FAILURE);
      reqTerminateStrategy();
    }
  }
  else
  {
    switch(reqQryOrderStatus(_orderWrapper._orderId))
    {
      case API2::CONSTANTS::RSP_OrderStatus_PENDING:
        return;
      case API2::CONSTANTS::RSP_OrderStatus_FILLED:
      case API2::CONSTANTS::RSP_OrderStatus_CANCELED:
        _orderWrapper.reset();
        onMarketDataEvent(symbolId);
        return;
      case API2::CONSTANTS::RSP_OrderStatus_CONFIRMED:
      case API2::CONSTANTS::RSP_OrderStatus_PARTIALLY_FILLED:
      case API2::CONSTANTS::RSP_OrderStatus_REPLACED:
        if(_orderWrapper.replaceOrder(risk,getPrice(),_userParams._qty)){
          DEBUG_MESSAGE(reqQryDebugLog(), "Sent Replace Order");
        }
        else{
          DEBUG_VARSHOW(reqQryDebugLog(), "Failed Replace Order, reason",risk);
        }


    }

  }

  DEBUG_FLUSH(reqQryDebugLog());

}
void API2::Test2::Context::onCMDModifyStrategy(API2::AbstractUserParams* obj)
{
}


void API2::Test2::Context::onProcessOrderConfirmation(API2::OrderConfirmation &confirmation)
{
  DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__);
  DEBUG_MESSAGE(reqQryDebugLog(), getStrConfirmation(confirmation).c_str());
  _orderWrapper.processConfirmation(confirmation);

}

void API2::Test2::Context::onConfirmed(API2::OrderConfirmation &confirmation,
    API2::COMMON::OrderId *orderId)
{
  DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__ );

}

void API2::Test2::Context::onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__ );

  DEBUG_MESSAGE(reqQryDebugLog(), "Order Filled, Terminating");
  reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
  reqTerminateStrategy(false);
}


void API2::Test2::Context::onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__ );

}


bool API2::Test2::Context::setInternalParameters(API2::UserParams *params)
{
#ifndef TESTING
  if(params->getValue("SYMBOL LEG1",_userParams._symbolId) != API2::UserParamsError_OK)
  {
    DEBUG_MESSAGE(reqQryDebugLog(), "Issue in SYMBOL LEG1");

    return false;
  }
  if(params->getValue("Order Mode 1",_userParams._side) != API2::UserParamsError_OK)
  {
    DEBUG_MESSAGE(reqQryDebugLog(), "Order Mode 1");

    return false;
  }
  if(params->getValue("Price Type",_userParams._priceType) != API2::UserParamsError_OK)
  {
    DEBUG_MESSAGE(reqQryDebugLog(), "issue in Price Type");

    return false;
  }
  if(params->getValue("Order Qty",_userParams._qty) != API2::UserParamsError_OK)
  {
    DEBUG_MESSAGE(reqQryDebugLog(), "issue in Qty");

    return false;
  }
#else
  setTestParameters();
#endif
  std::stringstream ss;
  _userParams.dump(ss, "Frontend Params:");
  DEBUG_MESSAGE(reqQryDebugLog(),ss.str().c_str());
  try{
    _Instrument = createNewInstrument(_userParams._symbolId,true,true);
    _orderWrapper = API2::COMMON::OrderWrapper(_Instrument,API2::DATA_TYPES::OrderMode(_userParams._side),API2::CONSTANTS::CMD_OrderType_LIMIT, this);
    return true;
  }
  catch(API2::MarketDataSubscriptionFailedException e)
  {
    DEBUG_VARSHOW(reqQryDebugLog(), "Exception occured", e.what());
    return false;
  }
  DEBUG_FLUSH(reqQryDebugLog());

}

bool API2::Test2::Context::setTestParameters()
{
  _userParams._symbolId = reqQrySymbolID("ESMNSE ESMNSE RELIANCE");
  DEBUG_VARSHOW(reqQryDebugLog(), "====SymbolID: ", _userParams._symbolId);
  //_userParams._symbolId = GET_SYMBOL_ID_NEW(268084,API2::CONSTANTS::CMD_ExchangeId_SMART,API2::CONSTANTS::CMD_SourceId_IB);
  //    _userParams._symbolId = GET_SYMBOL_ID_NEW(2885,CMD::ExchangeId_ESMNSE,CMD::SourceId_ESMNSE);
  _userParams._priceType=1;
  _userParams._qty=1000;
  _userParams._side = API2::CONSTANTS::CMD_OrderMode_BUY;
  std::stringstream ss;
  _userParams.dump(ss, "Frontend Params:");
  DEBUG_MESSAGE(reqQryDebugLog(),ss.str().c_str());
  try{
    _Instrument = createNewInstrument(_userParams._symbolId,true,true);
    _orderWrapper = API2::COMMON::OrderWrapper(_Instrument,API2::DATA_TYPES::OrderMode(_userParams._side),API2::CONSTANTS::CMD_OrderType_LIMIT, this);
    return true;
  }
  catch(API2::MarketDataSubscriptionFailedException e)
  {
    DEBUG_VARSHOW(reqQryDebugLog(), "Exception occured", e.what());
    return false;
  }


}

API2::DATA_TYPES::PRICE API2::Test2::Context::getPrice()
{
  if(_userParams._priceType == FrontEndParameters::BestBid)
    return reqQryMarketData(_Instrument->getSymbolId())->getBidPrice(0);
  else if(_userParams._priceType == FrontEndParameters::BestAsk)
    return reqQryMarketData(_Instrument->getSymbolId())->getAskPrice(0);
  else
    return reqQryMarketData(_Instrument->getSymbolId())->getLastTradePrice();

}

void API2::Test2::TestDriver(void *params)
{
  API2::StrategyParameters *sgParams = (API2::StrategyParameters*)params;
  boost::shared_ptr<API2::Test2::Context> context(new API2::Test2::Context(sgParams));
  context->reqStartAlgo(true,false);
  API2::SGContext::registerStrategy(context);

}
