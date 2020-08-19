#include "sampleAlgo.h"
#include "apiConstants.h"

#define PERCENTAGE_MULTIPLIER 10000.0

//Flag used for sending custom data to API
#define SEND_CUSTOM_DATA 0

SBA::Bidding::Bidding( API2::StrategyParameters *params ):
  API2::SGContext( params, "DemoStrategy" ),
  _orderPrice(0),
  _triggerPrice(0),
  _lastPrice(0),
  _lastTriggerPrice(0),
  _traded(0),
  _modify(false),
  _terminateCheck(false)
{
  API2::UserParams* customParams = (API2::UserParams*) params->getInfo();
  if( !setInternalParameters(customParams,_params) )
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Parameters not set from front end");
    terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return;
  }
  try 
  {
    registerSymbols();
  }
  catch(API2::MarketDataSubscriptionFailedException& e)
  { 
    DEBUG_MESSAGE(reqQryDebugLog(),"TBT subscription Failed");
    terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return;
  }
  catch(API2::InstrumentNotFoundException &e)
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Instrument Not Found");
    terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return;
  }
  catch(std::exception &e)
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"standard exception raised");
    terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return;
  }

  _algoIdSet.insert(_bidInstrument->getStaticData()->marketId);

  //Read Algo ID from Conf File
  readConfForAlgoid("SAMPLE_BIDDING", "SampleBidding.txt", "_ALGO_ID", true);

  if(!createOrderIds())
    return;

  _mkData=reqQryUpdateMarketData(_params.symbol);

#if INVOKING_API
  runCashFut();
#endif
}

bool SBA::Bidding::setInternalParameters(API2::UserParams *customParams, SBA::FrontEndParameters &params)
{
  FILL_PARAMS("SYMBOL LEG1",params.symbol);
  FILL_PARAMS("TotalLots",params.totalLots);
  FILL_PARAMS("OrderLots",params.orderLots);
  FILL_PARAMS("AchievedPrice",params.achievedPrice);
  FILL_PARAMS("OppositePrice",params.oppositePrice);
  FILL_PARAMS("OrderPriceTicks",params.orderPriceTicks);
  FILL_PARAMS("Acc Detail 1",params.account);
  FILL_PARAMS("Order Mode 1",params.orderMode);
  params.strategyId = customParams->getStrategyId();
  FILL_PARAMS("TriggerPriceTicks", params.triggerPriceTicks);
  FILL_PARAMS("MarketPercentage", params.marketPercentage);
  FILL_PARAMS("OrderType", params.orderType);
  dump( params );

  return checkValidations();
}

void SBA::Bidding::dump(SBA::FrontEndParameters &params)
{
  DEBUG_VARSHOW(reqQryDebugLog(),"order Mode is",(int)params.orderMode);
  DEBUG_VARSHOW(reqQryDebugLog(),"SYMBOL id for buy",params.symbol);
  DEBUG_VARSHOW(reqQryDebugLog(),"Total lots are",params.totalLots);
  DEBUG_VARSHOW(reqQryDebugLog(),"order lots are",params.orderLots);
  DEBUG_VARSHOW(reqQryDebugLog(),"Achieved price is",params.achievedPrice);
  DEBUG_VARSHOW(reqQryDebugLog(),"Oppsite Price is",params.oppositePrice);
  DEBUG_VARSHOW(reqQryDebugLog(),"Order Price Ticks are ",params.orderPriceTicks);
  DEBUG_VARSHOW(reqQryDebugLog(),"Trigger Price Ticks are ",params.triggerPriceTicks);
  DEBUG_VARSHOW(reqQryDebugLog(),"Market percentage is ",params.marketPercentage);
  DEBUG_VARSHOW(reqQryDebugLog(),"Order Type is ",(short)params.orderType);
}

void SBA::Bidding::mapModifiedParameters()
{
  _params.symbol = _modParams.symbol;
  _params.totalLots = _modParams.totalLots;
  _params.orderLots = _modParams.orderLots;
  _params.orderPriceTicks = _modParams.orderPriceTicks;
  _params.orderMode = _modParams.orderMode;
  _params.account = _modParams.account;
  _params.triggerPriceTicks = _modParams.triggerPriceTicks;
  _params.marketPercentage = _modParams.marketPercentage;
  _params.orderType = _modParams.orderType;
}


bool SBA::Bidding::createOrderIds()
{
  if(_params.orderType == Type_LIMIT)
  {
    _bidOrderWrapper = API2::COMMON::OrderWrapper(
        _bidInstrument ,
        (int)_params.orderMode , 
        this , 
        _params.account , 
        API2::CONSTANTS::CMD_OrderType_LIMIT);
    return true;
  }
  else if(_params.orderType == Type_STOP_LIMIT ||
      _params.orderType == Type_STOP)
  {
    //Treating Stop Loss market as stop loss limit here, as it is not 
    //allowed to fire algo order with zero price, so we will be explicitly 
    //calculating Stop loss market order price using market percentage.

    _bidOrderWrapper = API2::COMMON::OrderWrapper(
        _bidInstrument ,
        (int)_params.orderMode , 
        this , 
        _params.account , 
        API2::CONSTANTS::CMD_OrderType_STOP_LIMIT);
    return true;
  }
  else
  {
    DEBUG_VARSHOW( reqQryDebugLog(), "1: Order Type not handled", _params.orderType);
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
    return false;
  }
}

void SBA::Bidding::registerSymbols()
{
  _bidInstrument=createNewInstrument(_params.symbol,true,true);
}

void SBA::Bidding::onTimerEvent()
{
  if(_terminateCheck) return; 
  reqTimerEvent(1000000);
  onDefaultEvent();
}

void SBA::Bidding::bidDriver(void *params)
{
  API2::StrategyParameters *sgParams = (API2::StrategyParameters *) params;
  boost::shared_ptr<API2::SGContext> obj (new SBA::Bidding(sgParams));
  obj->reqStartAlgo(true, false);
  API2::SGContext::registerStrategy(obj);
  obj->reqTimerEvent(1000000);
}

void SBA::Bidding::onCMDModifyStrategy(API2::AbstractUserParams* newParams)
{
  _modify = true;

  API2::UserParams* customParams = (API2::UserParams*) newParams;
  DEBUG_MESSAGE(reqQryDebugLog(),"Modifying strategy");
  if(!setInternalParameters(customParams, _modParams))
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Parameters not set from front end");
    dump( _modParams );
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return;
  }

  if(_terminateCheck) return;

  modifyStrategy();

  reqSendStrategyResponse(API2::CONSTANTS::RSP_ResponseType_STRATEGY_RUNNING,
      API2::CONSTANTS::RSP_RiskStatus_SUCCESS,
      API2::CONSTANTS::RSP_StrategyComment_USER_INPUT);
}

void SBA::Bidding::modifyStrategy()
{
  _modify = false;

  if( _modParams.totalLots < _traded)
  {
    terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY );
    return;
  }
  mapModifiedParameters();
  
  
  // If the order was in pending state and meanwhile modification is received 
  // from frontend, then modification will be missed on that iteration, as it is 
  // a rare scenario so not handled currently.
  if( !_bidOrderWrapper.isOrderPending() &&
      !_terminateCheck &&
      _bidOrderWrapper.getLastQuantity() )
  { 
    //Modify order if new price calculated, using new parameters
    //passed from frontend
    if(!calculatePrice())
      return;

    //Price should be different from previous
    if( !isPriceValid() )
      return;

    replaceOrder();
  }
}

void SBA::Bidding::onCMDTerminateStartegy()
{
  DEBUG_MESSAGE( reqQryDebugLog(), "Terminated from frontend" );
  terminateStrategyComment(API2::CONSTANTS::
      RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY );
}

void SBA::Bidding::onDefaultEvent()
{
   
  if( _terminateCheck )
  {
    DEBUG_MESSAGE( reqQryDebugLog(), "stratergy terminating");
    return;
  }
  if( !_bidOrderWrapper.isOrderPending() && !_terminateCheck )
  { 
    if(!calculatePrice())
      return;

    placeOrder();
  }
}

void SBA::Bidding::terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment)
{
  if(_terminateCheck) return;

  _terminateCheck = true;


#if INVOKING_API
  printChildPosition(_child1);
  invokingApi->terminateInvokedStrategy( _child1,
      API2::CONSTANTS::CMD_CommandCategory_TERMINATE_STRATEGY );
#endif

  reqAddStrategyComment(comment);
  reqTerminateStrategy();
}

bool SBA::Bidding::calculatePrice()
{
  _mkData=reqQryUpdateMarketData(_params.symbol);

   switch( _params.orderType)
    {
      case Type_LIMIT:
        {
          return calculateLimitPrice();
        }

      case Type_STOP_LIMIT:
        {
          return calculateStopLossLimitPrice();
        }

      case Type_STOP:
        {
          return calculateStopLossMarketPrice();
        }

      default:
        DEBUG_VARSHOW( reqQryDebugLog(), "2 : Order Type not handled", (short)_params.orderType);
    }
   return false;
}

bool SBA::Bidding::calculateLimitPrice()
{
  SIGNED_LONG priceTick = ( _bidInstrument->getStaticData()->tickSize )*_params.orderPriceTicks;
  _orderPrice = _mkData->getPrice( 0 , _params.orderMode );
  if( _orderPrice == 0 )
  {
    _orderPrice = _mkData->getLastTradePrice();
    if( _orderPrice == 0 )
    {
      _orderPrice = _mkData->getClosePrice();
    }
  }

  if(!_orderPrice)
  {
    DEBUG_MESSAGE( reqQryDebugLog(), "ERROR: Limit Order Price calculated zero");
    return false;
  }

  switch(_params.orderMode)
  {   
    case API2::CONSTANTS::CMD_OrderMode_BUY: 
      {
        _orderPrice += priceTick;
        return true;
      }

    case API2::CONSTANTS::CMD_OrderMode_SELL:
      {
        if( _orderPrice <= priceTick )
        {
          DEBUG_MESSAGE( reqQryDebugLog(),
              "ERROR: Limit Order Price calculated is less than tickPrice passed from frontend");
          return false;
        }

        _orderPrice -= priceTick;
        return true;
      }
    default:
      DEBUG_VARSHOW( reqQryDebugLog(), "ERROR: OrderMode not handled, orderMode: ",
          (short)_params.orderMode);
  }
  
  DEBUG_MESSAGE( reqQryDebugLog(), "ERROR: Unable to calculate Limit Order Price");
  return false;
}

bool SBA::Bidding::calculateStopLossLimitPrice()
{
  SIGNED_LONG priceTick = ( _bidInstrument->getStaticData()->tickSize )*_params.orderPriceTicks;
  SIGNED_LONG triggerTick = ( _bidInstrument->getStaticData()->tickSize )*_params.triggerPriceTicks;

  _orderPrice = _mkData->getLastTradePrice();
  _triggerPrice = _mkData->getLastTradePrice();
  if(!_orderPrice || !_triggerPrice)
  {
    DEBUG_MESSAGE( reqQryDebugLog(),
        "ERROR: Unable to calculate Stop Loss Limit Price, as LTP is zero");
    return false;
  }

  switch(_params.orderMode)
  {
    case API2::CONSTANTS::CMD_OrderMode_BUY: 
      {
        _triggerPrice += triggerTick;
        _orderPrice += priceTick;
        return true;
      }

    case API2::CONSTANTS::CMD_OrderMode_SELL:
      {
        if( _orderPrice <= priceTick ||
            _triggerPrice <= triggerTick )
        {
          DEBUG_MESSAGE( reqQryDebugLog(),
              "ERROR: Price calculated is less than ticks passed from frontend");
          DEBUG_VARSHOW( reqQryDebugLog(), "OrderPrice: ",   _orderPrice);
          DEBUG_VARSHOW( reqQryDebugLog(), "TriggerPrice: ", _triggerPrice);

          _orderPrice = 0;
          _triggerPrice = 0;
          return false;
        }

        _triggerPrice -= triggerTick;
        _orderPrice -= priceTick;
        return true;
      }
    default:
      DEBUG_VARSHOW( reqQryDebugLog(), "ERROR: OrderMode not handled, orderMode: ",
          (short)_params.orderMode);

  }
  
  DEBUG_MESSAGE( reqQryDebugLog(), "ERROR: Unable to calculate Stop Loss Limit Prices");
  return false;
}

bool SBA::Bidding::calculateStopLossMarketPrice()
{
  SIGNED_LONG triggerTick = ( _bidInstrument->getStaticData()->tickSize )*_params.triggerPriceTicks;
  _triggerPrice = _mkData->getLastTradePrice();
  if(!_triggerPrice)
  {
    DEBUG_MESSAGE( reqQryDebugLog(), "ERROR: Trigger Price calculated zero");
    return false;
  }

  double marketPercentPrice = _params.marketPercentage / PERCENTAGE_MULTIPLIER;

  switch(_params.orderMode)
  {
    case API2::CONSTANTS::CMD_OrderMode_BUY:
      {
        _triggerPrice += triggerTick;
        _orderPrice = ( 1.0 +  marketPercentPrice ) * (double)(_triggerPrice);
        break;
      }

    case API2::CONSTANTS::CMD_OrderMode_SELL:
      {
        if(_triggerPrice <= triggerTick)
        {
          DEBUG_MESSAGE( reqQryDebugLog(),
              "ERROR: Calculated trigger price is less than tick passed from FE");

          _triggerPrice = 0;
          _orderPrice = 0;
          return false;
        }
        _triggerPrice -= triggerTick;
        _orderPrice = ( 1.0 -  marketPercentPrice ) * (double)(_triggerPrice);
        break;
      }
    default:
      {
        DEBUG_VARSHOW( reqQryDebugLog(), "ERROR: OrderMode not handled, orderMode: ",
            (short)_params.orderMode);
        return false;
      }
  }

  API2::SharedUtilities::roundPriceToTick(
      _orderPrice,
      _params.orderMode,
      *(_bidInstrument->getStaticData()));

  if(!_orderPrice)
  {
    DEBUG_MESSAGE( reqQryDebugLog(), "ERROR: Order Price calculated zero");
    return false;
  }

  return true;
}

void SBA::Bidding::placeOrder()
{
  if(_traded >= _params.totalLots)
  {
    DEBUG_VARSHOW( reqQryDebugLog(), "Strategy successfully terminated after trades: ",_traded);
    terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY );
    return;
  }
  
  // Modification is only done, when params are modified from frontend
  if(_bidOrderWrapper.getLastQuantity())
  {
    return;
  }
  
  _qty = ( _params.orderLots < _params.totalLots-_traded ) ? _params.orderLots : _params.totalLots-_traded;
  _qty *= _bidInstrument->getStaticData()->marketLot;

  if( _qty == 0 ) return; 
  
  DEBUG_VARSHOW( reqQryDebugLog(), "NewOrder OrderPrice: ", _orderPrice );
  DEBUG_VARSHOW( reqQryDebugLog(), "NewOrder TriggerPrice: ", _triggerPrice );
  DEBUG_VARSHOW( reqQryDebugLog(), "NewOrder Quantity: ", _qty );

  _bidOrderWrapper.reset();
  if( !_bidOrderWrapper.newOrder( _riskStatus, 
        _orderPrice,
        _qty, 
        _triggerPrice ) )
  {
    DEBUG_MESSAGE( reqQryDebugLog(),  "New order request failed");
    terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return;
  }
  else
  {
    _lastPrice = _orderPrice ;
    _lastTriggerPrice = _triggerPrice;
    _params.achievedPrice = _orderPrice;
    return;
  }
}

void SBA::Bidding::onMarketDataEvent(UNSIGNED_LONG symbolId)
{
  onDefaultEvent();
}

void SBA::Bidding::sendUpdateResponse()
{
  DEBUG_VARSHOW(reqQryDebugLog(),"Achieved Price ",_params.achievedPrice);
  DEBUG_VARSHOW(reqQryDebugLog(),"Opposite Price",_params.oppositePrice);

  std::list< std::string > list;

  std::string str = "AchievedPrice:" + std::to_string( (long long) _params.achievedPrice ) ;
  list.push_back( str );
  str = "OppositePrice:" + std::to_string( (long long) _params.oppositePrice );
  list.push_back( str );

  std::string customData;

  if( !reqQrySendCustomResponse( customData, list, 0 ) )
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Unable to send custom response to frontend");  
  }
}

void SBA::Bidding::onConfirmed(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId)
{ 
#if SEND_CUSTOM_DATA
  std::shared_ptr<StrategyCustomData> strategyCustomDataPtr  = std::make_shared<StrategyCustomData>();
  sendCustomDataToStrategiesDealerWise(reqQryClientID(), strategyCustomDataPtr);
#endif

#if SEND_POPUP
  std::list< std::string > list;
  std::string str = std::string("POPUP:") + std::string("Order confirmed");
  list.push_back( str );

  std::string customData;

  if( !reqQrySendCustomResponse( customData, list, 0 ) )
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Unable to send custom response to frontend");  
  }
#endif

  processOrder(confirmation, orderId);
}

void SBA::Bidding::onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{ 
  processOrder(confirmation, orderId);
}

void SBA::Bidding::onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  processOrder(confirmation, orderId);
}

void SBA::Bidding::onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
#if SEND_POPUP
  std::list< std::string > list;
  std::string str = std::string("POPUP:") + std::string("Order Filled")  ;
  list.push_back( str );

  std::string customData;

  if( !reqQrySendCustomResponse( customData, list, 0 ) )
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Unable to send custom response to frontend");  
  }
#endif

  if( processOrder(confirmation, orderId) )
  {
    _traded+=(confirmation.getLastFillQuantity())/(_bidInstrument->getStaticData()->marketLot);
    _params.oppositePrice = confirmation.getLastFillPrice();
    _lastPrice = 0;
    _lastTriggerPrice = 0;
    sendUpdateResponse();
    onDefaultEvent();
  }
}

void SBA::Bidding::onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{ 
  if(processOrder(confirmation, orderId))
  {
    _traded+=(confirmation.getLastFillQuantity())/(_bidInstrument->getStaticData()->marketLot);
  }
}
void SBA::Bidding::onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  processOrder(confirmation, orderId);
}
void SBA::Bidding::onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  processOrder(confirmation, orderId);
}
void SBA::Bidding::onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  processOrder(confirmation, orderId);
}


void SBA::Bidding::onRmsReject( API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  reqQryDebugLog()->saveConfirmation(confirmation);

  DEBUG_MESSAGE(reqQryDebugLog(),"ON rms reject");
  if(_bidOrderWrapper._orderId==orderId)
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"processing confirmation ");
    _bidOrderWrapper.processConfirmation(confirmation);
  }
  terminateStrategyComment(API2::CONSTANTS::
      RSP_StrategyComment_STRATEGY_ERROR_STATE );


}
bool SBA::Bidding::processOrder( API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
{
  reqQryDebugLog()->saveConfirmation(confirmation);
  if(_bidOrderWrapper._orderId==orderId)
  {
    return _bidOrderWrapper.processConfirmation(confirmation);
  }
  return false;
}

bool SBA::Bidding::isPriceValid()
{
  switch( _params.orderType)
  {
    case Type_LIMIT:
      {
        if(_orderPrice == _lastPrice)
          return false;

        break;
      }
    case Type_STOP_LIMIT:
      {
        if(_orderPrice == _lastPrice &&
            _triggerPrice == _lastTriggerPrice )
          return false;

        break;
      }
    case Type_STOP:
      {
        if( _triggerPrice == _lastTriggerPrice )
          return false;

        break;
      }
  }
  return true;
}

bool SBA::Bidding::checkValidations()
{
  if( _params.orderType == Type_LIMIT &&
      _params.orderPriceTicks == 0 )
  {
    DEBUG_MESSAGE( reqQryDebugLog(), "ERROR: OrderPriceTicks can not be zero");
    return false;
  }

  if( _params.orderType == Type_STOP_LIMIT && 
        ( _params.triggerPriceTicks > _params.orderPriceTicks ||
          _params.triggerPriceTicks == 0 ) )
  {
    DEBUG_MESSAGE( reqQryDebugLog(),
        "ERROR: TriggerPriceTicks should be non zero & less than or equal to OrderPriceTicks");
    return false;
  }

  if( _params.orderType == Type_STOP &&
      ( _params.marketPercentage == 0 ||
        _params.triggerPriceTicks == 0 ) )
  {
    DEBUG_MESSAGE( reqQryDebugLog(),
        "ERROR: TriggerPriceTicks & market percentage should be non zero");
    DEBUG_VARSHOW( reqQryDebugLog(),"TriggerPriceTicks: ", _params.triggerPriceTicks );
    DEBUG_VARSHOW( reqQryDebugLog(),"MarketPercentage: ",_params.marketPercentage );

    return false;
  }

  return true;
}

void SBA::Bidding::replaceOrder()
{
  if(_traded >= _params.totalLots)
  {
    DEBUG_VARSHOW( reqQryDebugLog(), "Strategy successfully terminated after trades: ",_traded);
    terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY );
    return;
  }

  _qty = _bidOrderWrapper.getLastQuantity();
  
  if( _qty == 0 ) return; 

  DEBUG_VARSHOW( reqQryDebugLog(), "ReplaceOrder OrderPrice: ", _orderPrice );
  DEBUG_VARSHOW( reqQryDebugLog(), "ReplaceOrder TriggerPrice: ", _triggerPrice );
  DEBUG_VARSHOW( reqQryDebugLog(), "ReplaceOrder Quantity: ", _qty );

  if( !_bidOrderWrapper.replaceOrder( _riskStatus, 
        _orderPrice, 
        _qty, 
        _triggerPrice ) )
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Replace order request failed");
      terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return;
  }
  else
  {
    _lastPrice = _orderPrice ;
    _lastTriggerPrice = _triggerPrice;
    _params.achievedPrice = _orderPrice;
  }
}

void SBA::Bidding::printChildPosition( const API2::DATA_TYPES::STRATEGY_ID childId )
{
  DEBUG_VARSHOW( reqQryDebugLog(), "Dump of Child positions, childId: ",childId );

  if(reqQryStrategyInfo(childId) != NULL )
  {
    DEBUG_VARSHOW( reqQryDebugLog(), "Total traded qty: ",
        reqQryStrategyInfo(childId)->getPosition(15047177,0)->getTradedQty());

    DEBUG_VARSHOW( reqQryDebugLog(), "Average traded price: ",
        reqQryStrategyInfo(childId)->getPosition(15047177,0)->getAvgTradedPrice() );
  }
  else 
  {
    DEBUG_VARSHOW( reqQryDebugLog(), "Child strategy not found, childId: ",childId);
  }
}

void SBA::Bidding::runCashFut()
{
  invokingApi = new INVOKING::InvokingApi( reqQryDebugLog() );
  cashFutParams = new INVOKING::TwoLegArbitrage();

  API2::AccountDetail acc1;
  API2::AccountDetail acc2;
  acc1.setPrimaryClientCode( "AAA" );
  acc2.setPrimaryClientCode( "AW2" );

  cashFutParams->setSymbolIdFirstLeg(15047177);
  cashFutParams->setSymbolIdSecondLeg(1503499);
  cashFutParams->setFirstLegAccountDetails( acc1 );
  cashFutParams->setSecondLegAccountDetails( acc2 );
  cashFutParams->setTransactionType( API2::CONSTANTS::CMD_TransactionType_NEW );
  cashFutParams->setQuantityFirstLeg( 4 );
  cashFutParams->setClientId( 17 ); 
  cashFutParams->setFirstLegMode( API2::CONSTANTS::CMD_OrderMode_BUY );
  cashFutParams->setParentStrategyId( _params.strategyId );
  cashFutParams->setThresholdQuantity_2(100);
  cashFutParams->setBidDifference(100);
  cashFutParams->setOpTicks(2);
  cashFutParams->setSqOff(3);
  cashFutParams->setMarketOrderPercent(200);
  cashFutParams->setPriceDifference(-305);

  if( !invokingApi->runStrategy( INVOKING::StrategyType_Cash_Fut, cashFutParams, &_child1 ) )
  {
    DEBUG_MESSAGE( reqQryDebugLog(), "Unable to run cash fut");
  }
  else
  {
    DEBUG_VARSHOW( reqQryDebugLog(), "Cash Fut ran, with child id: ", _child1 );
  }
}
