#include "sample.h"
#include "apiConstants.h"

#define FILL_PARAMS( NAME, PARAM)\
  if(customParams->getValue(NAME,PARAM) != API2::UserParamsError_OK)\
{\
  DEBUG_VARSHOW(reqQryDebugLog(), "Issue in ",NAME);\
  return false;\
}\

namespace TestStrategy
{
  TestContext::TestContext(API2::StrategyParameters *params):
    API2::SGContext(params,"Test_Strategy"),
    _riskStatus(API2::CONSTANTS::RSP_RiskStatus_MAX),
    _buyOrder(API2::CONSTANTS::CMD_OrderMode_BUY),
    _sellOrder(API2::CONSTANTS::CMD_OrderMode_SELL),
    _modify(false),
    _terminate(false),
    _isTbtEnabled(false),
    _buyTotalTradedLots(0),
    _sellTotalTradedLots(0)
  {
    /**
     * convert api paramaters into your own data structure
     */
    API2::UserParams* customParams = (API2::UserParams*) params->getInfo();
    if(!setInternalParameters(customParams))
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Front End Parameters Failed");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
      return;
    }
    /*
     *
     * register symbolids
     *          
     */
    try
    {
      registerSymbols();
    }
    catch(API2::MarketDataSubscriptionFailedException &e)
    {
      std::cout<<e.what()<<
        std::endl;
      DEBUG_MESSAGE(reqQryDebugLog(), "TBT Subscription Failed");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED);
      return;
    }
      catch(API2::InstrumentNotFoundException& e)
      {
        std::cout<<e.what()
          <<std::endl;
        std::cout << "TBT Subscription Failed, terminating strategy\n";
        DEBUG_MESSAGE(reqQryDebugLog(), "TBT Subscription Failed");
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED);
        return;
      }
      catch(std::exception &e)
      {
        std::cout<<e.what()
          <<std::endl;
        std::cout << "TBT Subscription Failed, terminating strategy\n";
        DEBUG_MESSAGE(reqQryDebugLog(), "TBT Subscription Failed");
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED);
        return;
      }
    if(_terminate)
      return;

    setOrderWrapper();
    dump();
    reqTimerEvent(10000);
    DEBUG_FLUSH(reqQryDebugLog());
  }
  bool TestContext::setInternalParameters(API2::UserParams* customParams){
    /*
     *  Storing all Front End Parameters into _userParams structure
     *       
     */
    FILL_PARAMS("SYMBOL LEG1",_userParams._symbolIdBidding);
    FILL_PARAMS("Order Lots(B)",_userParams._buyOrderLots);
    FILL_PARAMS("Total Lots(B)",_userParams._buyTotalLots);
    FILL_PARAMS("Order Lots(S)",_userParams._sellOrderLots);
    FILL_PARAMS("Total Lots(S)",_userParams._sellTotalLots);
    FILL_PARAMS("Price(B)",_userParams._buyPrice);
    FILL_PARAMS("Price(S)",_userParams._sellPrice);
    FILL_PARAMS("Max Diff",_userParams._maxDiff);
    return true;
  }
  bool TestContext::setModifiedInternalParameters(API2::UserParams* customParams){
    FILL_PARAMS("Order Lots(B)",_modUserParams._buyOrderLots);
    FILL_PARAMS("Total Lots(B)",_modUserParams._buyTotalLots);
    FILL_PARAMS("Order Lots(S)",_modUserParams._sellOrderLots);
    FILL_PARAMS("Total Lots(S)",_modUserParams._sellTotalLots);
    FILL_PARAMS("Price(B)",_modUserParams._buyPrice);
    FILL_PARAMS("Price(S)",_modUserParams._sellPrice);
    FILL_PARAMS("Max Diff",_modUserParams._maxDiff);
    return true;
  }

  void TestContext::registerSymbols()
  {
    /*
     * Creating Instrument for Leg
     */
    DEBUG_METHOD(reqQryDebugLog());

    if((GET_EXCHANGE_ID(_userParams._symbolIdBidding) != API2::CONSTANTS::CMD_ExchangeId_NSECM ) &&
        (GET_EXCHANGE_ID(_userParams._symbolIdBidding) != API2::CONSTANTS::CMD_ExchangeId_NSEFO ) &&
        ( GET_EXCHANGE_ID(_userParams._symbolIdBidding)!= API2::CONSTANTS::CMD_ExchangeId_NSECDS))

      _biddingInstrument = createNewInstrument(_userParams._symbolIdBidding,true,true,false); 

    else
    {
      /** 
       * If Snapshot feed required for this instrument , pass third argument as true
       * false in case of TBT
       */
      _biddingInstrument = createNewInstrument(_userParams._symbolIdBidding,true,!_isTbtEnabled);
    }
  }

  void TestContext::setOrderWrapper()
  {
    /*
     * Creating instances of OrderWrapper here , to place or cancel orders through this instance
     */
    DEBUG_METHOD(reqQryDebugLog());
    API2::AccountDetail account;

    _buyOrderWrapper = API2::COMMON::OrderWrapper(
        _biddingInstrument,
        _buyOrder,
        this,
        account
        );

    _sellOrderWrapper = API2::COMMON::OrderWrapper(
        _biddingInstrument,
        _sellOrder,
        this,
        account
        );
  }
  void TestContext::dump(){
    /**
     * Params Dump
     */
    DEBUG_VARSHOW(reqQryDebugLog(),"Symbol Id : ",_userParams._symbolIdBidding);
    DEBUG_VARSHOW(reqQryDebugLog(),"Buy Order Lots : ",_userParams._buyOrderLots);
    DEBUG_VARSHOW(reqQryDebugLog(),"Buy Total Lots : ",_userParams._buyTotalLots);
    DEBUG_VARSHOW(reqQryDebugLog(),"Sell Order Lots : ",_userParams._sellOrderLots);
    DEBUG_VARSHOW(reqQryDebugLog(),"Sell Total Lots : ",_userParams._sellTotalLots);
    DEBUG_VARSHOW(reqQryDebugLog(),"Buy Price : ",_userParams._buyPrice);
    DEBUG_VARSHOW(reqQryDebugLog(),"Sell Price : ",_userParams._sellPrice);
    DEBUG_VARSHOW(reqQryDebugLog(),"Max Diff : ",_userParams._maxDiff);
  }
  void TestContext::onTimerEvent()
  {
    /**
     * again requesting timer after 10000 micro seconds
     */
    reqTimerEvent(10000);
  }
  /**
   * Places Orders
   */
  void TestContext::placeOrder(const API2::DATA_TYPES::OrderMode &orderMode)
  {
    DEBUG_METHOD(reqQryDebugLog());

    /**
     * If strategy has been requested for termination or modification,
     * need to return from here
     */
    if(_terminate || _modify)
      return;
    /**
     * If any order is pending
     * we need to return from here
     */
    if(isAnyOrderPending())
      return;
    /**
     * Buy Case
     */
    if(orderMode == API2::CONSTANTS::CMD_OrderMode_BUY)
    {
      API2::DATA_TYPES::QTY qty = std::min(_userParams._buyOrderLots,_userParams._buyTotalLots - _buyTotalTradedLots);
      API2::DATA_TYPES::PRICE price = _userParams._buyPrice;

      // price in terms of tick size
      // e.g if price is 200.07
      // converting it to 200.05
      price = price - (price % _buyOrderWrapper._instrument->getStaticData()->tickSize);

      qty *= _biddingInstrument->getStaticData()->marketLot;

      if( qty != 0 )
      qty += _buyOrderWrapper.getLastFilledQuantity();

      if(qty <= 0 || price <= 0)
      {
        placeCancelOrder( _buyOrderWrapper );
        return;
      }
      /**
       * getLastQuantity() returns the last quantity of which order was placed
       *
       * getLastQuotedPrice() returns the last price on which order was placed
       */

      if(qty == _buyOrderWrapper.getLastQuantity() &&
          price == _buyOrderWrapper.getLastQuotedPrice())
        return;

      /**
       * If getLastQuantity() returns a non zero ,
       * that means an order is already standing 
       * we can replace it
       */
      if(_buyOrderWrapper.getLastQuantity())
      {
        /**
         *replaces the existing order
         */
        if(!_buyOrderWrapper.replaceOrder(_riskStatus,price,qty))
        {
          /**
           * If replaceOrder returns false
           * RMS checks have been failed
           * Terminating strategy here
           */
          _buyOrderWrapper._isPendingReplace = false;
          DEBUG_MESSAGE(reqQryDebugLog()," Buy Could not be Replaced");
          terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
          return;
        }
        DEBUG_MESSAGE(reqQryDebugLog()," Buy Replaced");
      }
      else
      {
        /**
         *If getLastQuantity() returns 0
         * we need to reset orderWrapper(generate an new order structure and new common orderId)
         *
         */
        _buyOrderWrapper.reset();
        /**
         * places a new order
         */
        if(!_buyOrderWrapper.newOrder(_riskStatus,price,qty))
        {
          /**
           * If placeOrder returns false
           * RMS checks have been failed
           * Terminating strategy here
           */
          _buyOrderWrapper._isPendingNew = false;
          DEBUG_MESSAGE(reqQryDebugLog()," Buy Could not be Placed")
            terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
          return;
        }
        DEBUG_MESSAGE(reqQryDebugLog()," Buy Placed");
      }
    }
    /**
     * Sell Case
     */
    else if(orderMode == API2::CONSTANTS::CMD_OrderMode_SELL)
    {
      API2::DATA_TYPES::QTY qty = std::min(_userParams._sellOrderLots,_userParams._sellTotalLots - _sellTotalTradedLots);
      API2::DATA_TYPES::PRICE price = _userParams._sellPrice;

      // price in terms of tick size
      // e.g. if price is 300.02 , then converting it to 300.05
      SIGNED_LONG rem = price % _sellOrderWrapper._instrument->getStaticData()->tickSize;
      if(rem)
      {
        price = price + (_sellOrderWrapper._instrument->getStaticData()->tickSize - rem);
      }
      qty *= _biddingInstrument->getStaticData()->marketLot;
      
      if( qty != 0 )
      qty += _sellOrderWrapper.getLastFilledQuantity();

      if(qty <= 0 || price <= 0)
      {
        placeCancelOrder( _sellOrderWrapper );
        return;
      }

      if(qty == _sellOrderWrapper.getLastQuantity() &&
          price == _sellOrderWrapper.getLastQuotedPrice())
        return;

      if(_sellOrderWrapper.getLastQuantity())
      {
        if(!_sellOrderWrapper.replaceOrder(_riskStatus,price,qty))
        {
          _sellOrderWrapper._isPendingReplace = false;
          DEBUG_MESSAGE(reqQryDebugLog()," Sell Could not be Replaced");
          terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
          return;
        }
        DEBUG_MESSAGE(reqQryDebugLog()," Sell Replaced");
      }
      else
      {
        _sellOrderWrapper.reset();
        if(!_sellOrderWrapper.newOrder(_riskStatus,price,qty))
        {
          _buyOrderWrapper._isPendingNew = false;
          DEBUG_MESSAGE(reqQryDebugLog()," Sell Could not be Placed")
            terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
          return;
        }
        DEBUG_MESSAGE(reqQryDebugLog()," Sell Placed");
      }
    }
  }
  void TestContext::onDefaultEvent()
  {
    /**
     * If termination requested , not proceeding furthur
     */
    if(_terminate)
      return;

    placeOrder(_buyOrder);
    placeOrder(_sellOrder);
  }
  void TestContext::onMarketDataEvent(UNSIGNED_LONG symbolId)
  {
    /** This function gets called if any market data event occurs 
     * on the registered instruments
     *
     * symbolId tells from which instrument tick has been generated
     */

    onDefaultEvent();
  }
  void TestContext::placeCancelOrder(API2::COMMON::OrderWrapper &wrapper)
  {
    // if order stands , then only we should go for its cancelation
    if( wrapper.getLastQuantity() )
    {
      // canceling order
      if( !wrapper.cancelOrder( _riskStatus ) )
      {
        // if risk failure comes
        DEBUG_MESSAGE( reqQryDebugLog(),"Order Cancel Failed" );
        wrapper._isPendingCancel = false;
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_RMS_FAILURE);
        return;
      }
      DEBUG_MESSAGE( reqQryDebugLog(),"Order Canceled" );
    }    
  }
  void TestContext::terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment)
  {
    _terminate = true;
    reqAddStrategyComment(comment);
    reqTerminateStrategy();
  }
  void TestContext::terminateStrategy()
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Terminated From Front End");
    reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
    reqTerminateStrategy();
    return;
  }
  bool TestContext::isAnyOrderPending()
  {
    if(_buyOrderWrapper.isOrderPending() || _sellOrderWrapper.isOrderPending())
      return true;
    return false;
  }
  void TestContext::mapFrontEndValues(){
    DEBUG_METHOD(reqQryDebugLog());
    /**
     * Copying the modifiedParams structure to original structure
     */
    _userParams._buyOrderLots = _modUserParams._buyOrderLots;
    _userParams._sellOrderLots = _modUserParams._sellOrderLots;
    _userParams._buyTotalLots = _modUserParams._buyTotalLots;
    _userParams._sellTotalLots = _modUserParams._sellTotalLots;
    _userParams._buyPrice = _modUserParams._buyPrice;
    _userParams._sellPrice = _modUserParams._sellPrice;
    _userParams._maxDiff = _modUserParams._maxDiff;

  }
  /**
   * Map the modified front end params to front end params
   */
  void TestContext::modifyStrategy(){
    DEBUG_METHOD(reqQryDebugLog());
    _modify = false;
    mapFrontEndValues();
    dump();
  }
  /**
   * Request from fornt end to modify params
   */
  void TestContext::onCMDModifyStrategy(API2::AbstractUserParams* newParams)
  {
    DEBUG_METHOD(reqQryDebugLog());
    _modify = true;
    API2::UserParams* modParams = (API2::UserParams*) newParams;

    /**
     * setting new params in a new data structure of params
     */
    if(!setModifiedInternalParameters(modParams))
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Front End Parameters Failed");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_VERSION_DIFFERS);
      return;
    }

    /**
     * If no order pending , we can modifyStartegy
     */
    if(_modify && !isAnyOrderPending())
      modifyStrategy();

    /** need to send this response to front end that strategy has successfully recieved modify command
    */
    reqSendStrategyResponse(API2::CONSTANTS::RSP_ResponseType_STRATEGY_RUNNING,
        API2::CONSTANTS::RSP_RiskStatus_SUCCESS,
        API2::CONSTANTS::RSP_StrategyComment_USER_INPUT);
  }

  /**
   * processStrategyState
   * we have to call this after event callback has been recieved from exchange
   * to confirm that if termination or modification has been requested 
   * and any order is not pending
   * we can now terminate or modify strategy
   */
  void TestContext::processStrategyState()
  {
    if(_terminate && !isAnyOrderPending())
      terminateStrategy();

    if(_modify && !isAnyOrderPending())
      modifyStrategy();
    return;
  }

  /** Event Callbacks */
  void TestContext::onConfirmed(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId){

    if(orderId == _buyOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Buy Order Confirmed-----");
      _buyOrderWrapper.processConfirmation(confirmation);
    }
    else if(orderId == _sellOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Sell Order Confirmed-----");
      _sellOrderWrapper.processConfirmation(confirmation);
    }
    processStrategyState();
  }
  void TestContext::onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId){
    if(orderId == _buyOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Buy Order Replaced-----");
      _buyOrderWrapper.processConfirmation(confirmation);
    }
    else if(orderId == _sellOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Sell Order Replaced-----");
      _sellOrderWrapper.processConfirmation(confirmation);
    }
    processStrategyState();
  }
  void TestContext::onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId){
    if(orderId == _buyOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Buy Order Canceled-----");
      _buyOrderWrapper.processConfirmation(confirmation);
    }
    else if(orderId == _sellOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Sell Order Canceled-----");
      _sellOrderWrapper.processConfirmation(confirmation);
    }
    processStrategyState();
  }
  void TestContext::onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId){
    if(orderId == _buyOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Buy Order Cancel Rejected-----");
      _buyOrderWrapper.processConfirmation(confirmation);
    }
    else if(orderId == _sellOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Sell Order Cancel Rejected-----");
      _sellOrderWrapper.processConfirmation(confirmation);
    }
    processStrategyState();
  }
  void TestContext::onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId){
    if(orderId == _buyOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Buy Order Replace Rejected-----");
      _buyOrderWrapper.processConfirmation(confirmation);
    }
    else if(orderId == _sellOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Sell Order Replace Rejected-----");
      _sellOrderWrapper.processConfirmation(confirmation);
    }
    processStrategyState();
  }
  void TestContext::onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId){
    if(orderId == _buyOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Buy Order Filled-----");
      _buyOrderWrapper.processConfirmation(confirmation);
      _buyTotalTradedLots += confirmation.getLastFillQuantity() / _biddingInstrument->getStaticData()->marketLot;
    }
    else if(orderId == _sellOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Sell Order Filled-----");
      _sellOrderWrapper.processConfirmation(confirmation);
      _sellTotalTradedLots += confirmation.getLastFillQuantity() / _biddingInstrument->getStaticData()->marketLot;
    }
  }
  void TestContext::onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId){
    if(orderId == _buyOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Buy Order Partial Filled-----");
      _buyOrderWrapper.processConfirmation(confirmation);
      _buyTotalTradedLots += confirmation.getLastFillQuantity() / _biddingInstrument->getStaticData()->marketLot;
    }
    else if(orderId == _sellOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Sell Order Partial Filled-----");
      _sellOrderWrapper.processConfirmation(confirmation);
      _sellTotalTradedLots += confirmation.getLastFillQuantity() / _biddingInstrument->getStaticData()->marketLot;
    }
  }
  void TestContext::onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId){
    if(orderId == _buyOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Buy Order New Rejected-----");
      _buyOrderWrapper.processConfirmation(confirmation);
    }
    else if(orderId == _sellOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Sell Order New Rejected-----");
      _sellOrderWrapper.processConfirmation(confirmation);
    }
  }
  void TestContext::onFrozen(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId){
    if(orderId == _buyOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Buy Order Frozen-----");
      _buyOrderWrapper.processConfirmation(confirmation);
    }
    else if(orderId == _sellOrderWrapper._orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"-----Sell Order Frozen-----");
      _sellOrderWrapper.processConfirmation(confirmation);
    }
  }
  /**
   * Request from front end to terminate strategy
   */
  void TestContext::onCMDTerminateStartegy()
  {
    DEBUG_METHOD(reqQryDebugLog());
    _terminate = true;
    if(_terminate && !isAnyOrderPending())
      terminateStrategy();
    return;
  }
  void TestContext::driver(void *params)
  {
    API2::StrategyParameters *sgParams = (API2::StrategyParameters *)params;
    /**
     * Constructor Call
     */
    boost::shared_ptr<API2::SGContext> context (new TestContext(sgParams));
    context->reqStartAlgo(true,false);
    API2::SGContext::registerStrategy(context);
  }
}
