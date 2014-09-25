#include "context.h"
API2::Context::Context(API2::StrategyParameters *params):
  API2::SGContext(params, "FutFut"),
  _firstLegOrder(NULL),
  _replaceOrder(NULL)
{
  /*
   * convert api paramaters into your own data structure
   */
  API2::UserParams *futfutParams = (API2::UserParams *)params->getInfo();
  futfutParams->dump();
  setInternalParameters(futfutParams,_params);
  /*
   *
   * register symbolids
   *
   */
  try
  {
    registerSymbols();
  }
  catch(std::exception &e)
  {
    std::cout
      <<"\n"
      <<e.what();
    reqTerminateStrategy();
    std::cout<<"Terminating strategy\n";
    return ;
  }
  createOrderIds();

  _state = placeFirstLegOrder;
}

void API2::Context::setInternalParameters(API2::UserParams *futfutParams,
    API2::FrontEndParameters &params)
{
  if(futfutParams->getValue("SYMBOL LEG1",params._symbolIdFirstLeg) != API2::UserParamsError_OK)
  {
    std::cout<<"SYMBOL LEG1"<<std::endl;
  }

  if(futfutParams->getValue("SYMBOL LEG2",params._symbolIdSecondLeg) != API2::UserParamsError_OK)
  {
    std::cout<<"SYMBOL LEG2"<<std::endl;
  }


  if(futfutParams->getValue("Total Qty",
        params._totalQty) != API2::UserParamsError_OK)
  {
    std::cout<<"Total Qty"<<std::endl;
  }
  std::cout<<std::endl
    <<params._symbolIdFirstLeg<<","
    <<params._symbolIdSecondLeg<<","
    <<params._totalQty
    <<std::endl;
}
void API2::Context::registerSymbols()
{
  _firstLegInstrument = createNewInstrument(_params._symbolIdFirstLeg,true);
  _secondLegInstrument = createNewInstrument(_params._symbolIdSecondLeg,true);
}
void API2::Context::createOrderIds()
{
}
void API2::Context::OnDefaultEvent()
{
  (*_state)(*this);
}
void API2::Context::OnMarketDataEvent(UNSIGNED_LONG symbolid)
{
  std::cout<<"Symbol id Market Data "
    <<symbolid
    <<std::endl;
  API2::COMMON::MktData *mkData = reqQryUpdateMarketData(symbolid);
  mkData->dump();

  (*_state)(*this);

}
void API2::Context::onCMDModifyStrategy(API2::AbstractUserParams* obj)
{
}


SIGNED_LONG API2::Context::getFirstLegPrice()
{
  SIGNED_LONG price = 0;
  API2::COMMON::MktData *mkDataFirstLeg = reqQryUpdateMarketData(_params._symbolIdFirstLeg);
  API2::COMMON::MktData *mkDataSecondLeg = reqQryUpdateMarketData(_params._symbolIdSecondLeg);
  
  std::cout<<"_______________\nSecond Leg \n______________"<<std::endl;
  mkDataSecondLeg->dump();
  
  if(_params._firstLegOrderMode == API2::CONSTANTS::CMD_OrderMode_BUY)
  {
    std::cout
      <<"Second leg top price "
      <<mkDataSecondLeg->getQuote().MarketDepth[0].BidPrice
      <<std::endl;;
    if(mkDataSecondLeg->getQuote().MarketDepth[0].BidQty > 0)
    {
      price = mkDataSecondLeg->getQuote().MarketDepth[0].BidPrice -
        _params._minProfit;
    }
  }
  else
  {
    if(mkDataSecondLeg->getQuote().MarketDepth[0].AskQty > 0)
    {
      price = _params._minProfit -
        mkDataSecondLeg->getQuote().MarketDepth[0].AskPrice;
    }
  }
  return price;

}

void API2::Context::waitState(Context &obj)
{
  //Could be a timer here
}


void API2::Context::onProcessOrderConfirmation(API2::OrderConfirmation &confirmation)
{
  confirmation.dump();
}

void API2::Context::onNewConfirmed(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId)
{ 
  if( _firstLegOrder != NULL 
      && confirmation.getClOrderId() == _firstLegOrder->getClOrdId() )
  {
    _state = replaceOrder;
    _currentOrderId = orderId;
  }
  onDefaultEvent();
}

void API2::Context::onCanceled(API2::OrderConfirmation &confirmation, 
    API2::COMMON::OrderId *orderId)
{
  if(confirmation.getOriginalClOrderId() == _firstLegOrder->getClOrdId())
  {
    _firstLegOrder = NULL;
    _currentOrderId = NULL;
    _replaceOrder = NULL;
    _state = placeFirstLegOrder;
  }
}
void API2::Context::onReplaced(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId)
{ 
  if( _replaceOrder != NULL 
      && confirmation.getClOrderId() == _replaceOrder->getClOrdId() )
  {
    _firstLegOrder = _replaceOrder;
    _firstLegOrder = NULL;
    _state = replaceOrder;
    _currentOrderId = orderId;
  }
  onDefaultEvent();
}

void API2::Context::placeFirstLegOrder(Context &obj)
{
  if(obj._savedQty._firstLegTradedQty >= obj._params._totalQty)
  {
    obj.reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
    obj.reqTerminateStrategy();
    return;
  }

  SIGNED_LONG price = obj.getFirstLegPrice();
  std::cout<<"Price is "<<price<<std::endl;

  if(price > 0 )
  {

    API2::DATA_TYPES::RiskStatus riskStatus = API2::CONSTANTS::RSP_RiskStatus_MAX;

    obj._firstLegOrderId = obj.createNewOrderId(obj._firstLegInstrument,
                                                API2::AccountDetail(),
                                                obj._params._firstLegOrderMode
                                                );

    obj._firstLegOrder = obj.createNewOrder(
        obj._firstLegInstrument,
        obj._params._orderQty,
        obj._params._orderQty,
        obj._params._firstLegOrderMode,
        API2::CONSTANTS::CMD_OrderType_LIMIT,
        API2::CONSTANTS::CMD_OrderValidity_DAY,
        API2::CONSTANTS::CMD_ProductType_DELIVERY,
        price);


    if(!obj.reqNewSingleOrder(
          riskStatus,
          obj._firstLegInstrument,
          obj._firstLegOrder,
          obj._firstLegOrderId)
      )
    {
      std::cout<<"=========Error Placing Order============="<<std::endl;
      std::cout<<"==========Risk Status========="<<riskStatus<<std::endl;
      obj.reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_RMS_FAILURE);
      obj.reqTerminateStrategy();
    }
    else
    {
      std::cout <<" Sent New Order---------------->" <<std::endl;
      obj._firstLegOrder->dump();
      obj._state = waitState;

      //setCurrentState(BidCheckState::getInstance());
    }
  }
}

void API2::Context::replaceOrder(Context &obj)
{
  if(obj._savedQty._firstLegTradedQty >= obj._params._totalQty)
  {
    obj.reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
    obj.reqTerminateStrategy();
    return;
  }

  SIGNED_LONG price = obj.getFirstLegPrice();
  std::cout<<"Price is "<<price<<std::endl;

  if(price > 0 && price != obj._firstLegOrder->getPrice() )
  {

    API2::DATA_TYPES::RiskStatus riskStatus = API2::CONSTANTS::RSP_RiskStatus_MAX;
    
    obj._replaceOrder = obj.createNewOrder(
        obj._firstLegInstrument,
        obj._params._orderQty,
        obj._params._orderQty,
        obj._params._firstLegOrderMode,
        API2::CONSTANTS::CMD_OrderType_LIMIT,
        API2::CONSTANTS::CMD_OrderValidity_DAY,
        API2::CONSTANTS::CMD_ProductType_DELIVERY,
        price);
    
    obj._replaceOrder->setOrigClientOrderId(obj._firstLegOrder->getClOrdId());
    
    obj._replaceOrder->setTransactionType(API2::CONSTANTS::CMD_TransactionType_MODIFY);
    
    if(!obj.reqReplaceOrder(
          riskStatus,
          obj._firstLegInstrument,
          obj._replaceOrder,
          obj._firstLegOrderId)
      )
    {
      std::cout<<"=========Error Placing Order============="<<std::endl;
      std::cout<<"==========Risk Status========="<<riskStatus<<std::endl;
      obj.reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_RMS_FAILURE);
      obj.reqTerminateStrategy();
    }
    else
    {
      std::cout <<" Sent New Order---------------->" <<std::endl;
      obj._replaceOrder->dump();
      obj._state = &waitState;
      
      //setCurrentState(BidCheckState::getInstance());
    }
  }
  else
  {
    obj.cancelOrder();
  }
}

void API2::Context::cancelOrder()
{
  //cancelOrder(_currentOrderId);
  _state = waitState;
}

void *API2::FutFutDriver(void *params)
{
  API2::StrategyParameters *sgParams = (API2::StrategyParameters*)params;
  API2::Context context(sgParams);
  std::cout<<"Hey "<<std::endl;
  return context.reqStartAlgo(true,false);
}
