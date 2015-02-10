#include "context.h"
API2::Context::Context(API2::StrategyParameters *params):
    API2::SGContext(params, "FutFut")
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
  /*
   * Storing all Front End Parameters into _params structure
   *
   */

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
    if(futfutParams->getValue("Order Qty",
                              params._orderQty) != API2::UserParamsError_OK)
    {
        std::cout<<"Order Qty"<<std::endl;
    }
    if(futfutParams->getValue("Min Profit",params._minProfit) != API2::UserParamsError_OK)
    {
        std::cout<<"Min Profit"<<std::endl;
    }

    std::cout<<std::endl
            <<params._symbolIdFirstLeg<<","
           <<params._symbolIdSecondLeg<<","
          <<params._totalQty
         <<std::endl;
}
void API2::Context::registerSymbols()
{
  /*
   * Creating Instrument for First Leg symbol Id and Second Leg Symbol Id
   *
   */
    _firstLegInstrument = createNewInstrument(_params._symbolIdFirstLeg,true,true);
    _secondLegInstrument = createNewInstrument(_params._symbolIdSecondLeg,true,true);
}
void API2::Context::createOrderIds()
{
  /*
   * Creating Order Wrapper Structure for First Leg
   */
  _firstLegOrderWrapper = API2::COMMON::OrderWrapper(_firstLegInstrument,
      _params._firstLegOrderMode,
      API2::CONSTANTS::CMD_OrderType_LIMIT,
      this);
}

void API2::Context::onMarketDataEvent(UNSIGNED_LONG symbolId)
{
    //    std::cout<<"Symbol id Market Data "
    //      <<symbolId
    //      <<std::endl;
    //    API2::COMMON::MktData *mkData = reqQryUpdateMarketData(symbolId);
    //    mkData->dump();

    (*_state)(*this);

}
void API2::Context::onDefaultEvent()
{
    (*_state)(*this);
}
void API2::Context::onCMDModifyStrategy(API2::AbstractUserParams* obj)
{
}


SIGNED_LONG API2::Context::getFirstLegPrice()
{
    /*
     * Calculating Price Based on Second Leg SymbolId 
     */
    SIGNED_LONG price = 0;
    //  API2::COMMON::MktData *mkDataFirstLeg = reqQryUpdateMarketData(_params._symbolIdFirstLeg);
    API2::COMMON::MktData *mkDataSecondLeg = reqQryUpdateMarketData(_params._symbolIdSecondLeg);

    //  std::cout<<"_______________\nSecond Leg \n______________"<<std::endl;
    //  mkDataSecondLeg->dump();

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
    std::cout<<"On Wait State"<<std::endl;
    //Could be a timer here
}


void API2::Context::onProcessOrderConfirmation(API2::OrderConfirmation &confirmation)
{
    confirmation.dump();
}

void API2::Context::onConfirmed(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId)
{ 
    DEBUG_METHOD(reqQryDebugLog());
    if( _firstLegOrderWrapper._orderId == orderId )
    {
        _state = replaceOrder;
    }
}

void API2::Context::onCanceled(API2::OrderConfirmation &confirmation, 
                               API2::COMMON::OrderId *orderId)
{
    DEBUG_METHOD(reqQryDebugLog());

    if(_firstLegOrderWrapper._orderId == orderId)
    {
        _state = placeFirstLegOrder;
    }
}
void API2::Context::onReplaced(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId)
{ 
    DEBUG_METHOD(reqQryDebugLog());

    if( _firstLegOrderWrapper._orderId == orderId )
    {
        _state = replaceOrder;

    }
}

void API2::Context::placeFirstLegOrder(Context &obj)
{
    DEBUG_METHOD(obj.reqQryDebugLog());

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

        if(!obj._firstLegOrderWrapper._isReset)
        {
          obj._firstLegOrderWrapper.reset(); 
        }
        if(!obj._firstLegOrderWrapper.newOrder(riskStatus, 
              price,
              obj._params._orderQty))
        {
            std::cout<<"=========Error Placing Order============="<<std::endl;
            std::cout<<"==========Risk Status========="<<riskStatus<<std::endl;
            obj.reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_RMS_FAILURE);
            obj.reqTerminateStrategy();
        }
        else
        {
            std::cout <<" Sent New Order---------------->" <<std::endl;
            obj._firstLegOrderWrapper._order->dump();
            obj._state = waitState;
        }
    }
}

void API2::Context::replaceOrder(Context &obj)
{
    DEBUG_METHOD(obj.reqQryDebugLog());

    if(obj._savedQty._firstLegTradedQty >= obj._params._totalQty)
    {
        obj.reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
        obj.reqTerminateStrategy();
        return;
    }

    SIGNED_LONG price = obj.getFirstLegPrice();
    std::cout<<"Price is "<<price<<std::endl;

    if(price > 0 && price != obj._firstLegOrderWrapper._order->getPrice() )
    {
        API2::DATA_TYPES::RiskStatus riskStatus = API2::CONSTANTS::RSP_RiskStatus_MAX;

        if(!obj._firstLegOrderWrapper.replaceOrder(
            riskStatus,
            price,
            obj._params._orderQty))
        {
            std::cout<<"=========Error Placing Order============="<<std::endl;
            std::cout<<"==========Risk Status========="<<riskStatus<<std::endl;
            obj.reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_RMS_FAILURE);
            obj.reqTerminateStrategy();
        }
        else
        {
            std::cout <<" Sent New Order---------------->" <<std::endl;
            obj._state = &waitState;

        }
    }
}


void API2::Context::FutFutDriver(void *params)
{
  API2::StrategyParameters *sgParams = (API2::StrategyParameters* ) params;
  boost::shared_ptr <API2::SGContext> context (new Context(sgParams));
  context->reqStartAlgo(true, false);
  API2::SGContext::registerStrategy(context);

}
