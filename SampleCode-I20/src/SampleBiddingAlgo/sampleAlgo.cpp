#include "sampleAlgo.h"
#include "apiConstants.h"
SBA::Bidding::Bidding( API2::StrategyParameters *params ):
  API2::SGContext( params, "DemoStrategy" ),
  _marketPrice(0),
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
  
  _algoIdSet.insert( _bidInstrument->getStaticData()->marketId);

  readConfForAlgoid("SampleAlgo","sample.txt");

  if( !validateAlgoDetail() )
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Invalid Algo Id " );
    terminateStrategyComment( API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return ;
  }
  
  createOrderIds();
  _mkData=reqQryUpdateMarketData(_params.symbol);
 

  reqTimerEvent(1000000);
}

bool SBA::Bidding::setInternalParameters(API2::UserParams *customParams, SBA::FrontEndParameters &params)
{
  FILL_PARAMS("SYMBOL LEG1",params.symbol);
  FILL_PARAMS("TotalLots",params.totalLots);
  FILL_PARAMS("OrderLots",params.orderLots);
  FILL_PARAMS("AchievedPrice",params.achievedPrice);
  FILL_PARAMS("OppositePrice",params.oppositePrice);
  FILL_PARAMS("BestPriceTicks",params.bestPriceTicks);
  FILL_PARAMS("Acc Detail 1",params.account);
  FILL_PARAMS("Order Mode 1",params.orderMode);
  params.strategyId = customParams->getStrategyId();
  dump( params );

  return true;
}

void SBA::Bidding::dump(SBA::FrontEndParameters &params)
{
  DEBUG_VARSHOW(reqQryDebugLog(),"order Mode is",(int)params.orderMode);
  DEBUG_VARSHOW(reqQryDebugLog(),"SYMBOL id for buy",params.symbol);
  DEBUG_VARSHOW(reqQryDebugLog(),"Total lots are",params.totalLots);
  DEBUG_VARSHOW(reqQryDebugLog(),"order lots are",params.orderLots);
  DEBUG_VARSHOW(reqQryDebugLog(),"Achieved price is",params.achievedPrice);
  DEBUG_VARSHOW(reqQryDebugLog(),"Oppsite Price is",params.oppositePrice);
  DEBUG_VARSHOW(reqQryDebugLog(),"Best Price Ticks are ",params.bestPriceTicks);
}

void SBA::Bidding::mapModifiedParameters()
{
  _params.symbol = _modParams.symbol;
  _params.totalLots = _modParams.totalLots;
  _params.orderLots = _modParams.orderLots;
  _params.bestPriceTicks = _modParams.bestPriceTicks;
  _params.orderMode = _modParams.orderMode;
  _params.account = _modParams.account;
}


void SBA::Bidding::createOrderIds()
{
  _bidOrderWrapper = API2::COMMON::OrderWrapper(_bidInstrument ,(int)_params.orderMode , this , _params.account );
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
    _marketPrice = getMarketPrice();

    DEBUG_VARSHOW(reqQryDebugLog(),"Market Price ",_marketPrice);
    if(_marketPrice == 0) 
    {
      return;
    }
    placeOrder();
  }
}

void SBA::Bidding::terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment)
{
  if(_terminateCheck) return;

  _terminateCheck = true;
 

  reqAddStrategyComment(comment);
  reqTerminateStrategy();
}

SIGNED_LONG SBA::Bidding::getMarketPrice()
{
  _mkData=reqQryUpdateMarketData(_params.symbol);

  SIGNED_LONG price = 0;

  switch(_params.orderMode)
  {
    case API2::CONSTANTS::CMD_OrderMode_BUY: 
      {
        price = _mkData->getPrice( 0 , _params.orderMode );
        if( price == 0 )
        {
          price = _mkData->getLastTradePrice();
          if( price == 0 )
          {
            price = _mkData->getClosePrice();
          }
        }
        break;
      }

    case API2::CONSTANTS::CMD_OrderMode_SELL:
      {
        SIGNED_LONG priceTick = ( _bidInstrument->getStaticData()->tickSize )* _params.bestPriceTicks;
        price = _mkData->getPrice( 0 , _params.orderMode );
        if( price == 0  || price <= priceTick )
        {
          price = _mkData->getLastTradePrice();
          if( price == 0 || price <= priceTick )
          {
            price = _mkData->getClosePrice();
          }
        }
        if ( price <= priceTick ) 
          price = 0;
        break;
      }
    default:
      DEBUG_VARSHOW( reqQryDebugLog(), "Order Mode not handled", _params.orderMode);
  }
  return price;
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
  if(_bidOrderWrapper.getLastQuantity())
  {
    return;
  }

  _qty = ( _params.orderLots < _params.totalLots-_traded ) ? _params.orderLots : _params.totalLots-_traded;
  _qty *= _bidInstrument->getStaticData()->marketLot;

  if( _qty == 0 ) return;

  if( _params.orderMode == API2::CONSTANTS::CMD_OrderMode_BUY)
  {
    _marketPrice+=((_bidInstrument->getStaticData()->tickSize)*(_params.bestPriceTicks));
  }
  else //SELL
  {
    _marketPrice -= ( _bidInstrument->getStaticData()->tickSize )* _params.bestPriceTicks ;
  }

  _params.achievedPrice = _marketPrice;
  _bidOrderWrapper.reset();  
  if( !_bidOrderWrapper.newOrder( _riskStatus, _marketPrice, _qty ) )
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"New order request failed");
    DEBUG_VARSHOW( reqQryDebugLog(), "Price: ", _marketPrice );
    DEBUG_VARSHOW( reqQryDebugLog(), "Quantity: ", _qty );
    terminateStrategyComment(API2::CONSTANTS::
        RSP_StrategyComment_STRATEGY_ERROR_STATE );
    return;
  }
}

void SBA::Bidding::popup(std::string message)
{
 std::ostringstream str1;
 std::list<std::string> list1;
 std::ostringstream dd;
 str1.str("");
 str1.clear();
 dd <<message;
 str1 << "POPUP:" << dd.str();
  list1.push_back(str1.str());
  std::string z;
  int _rowId = 0;
  if(!reqQrySendCustomResponse(z,list1,_rowId))
  {
  DEBUG_MESSAGE(reqQryDebugLog(),"CustomResponseFailed");
  reqTerminateStrategy(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
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
  std::list< std::string > list;

  std::string str = std::string("POPUP:") + std::string("Processing confirmation 1");
  list.push_back( str );
  str = std::string("POPUP:") + std::string("Processing confirmation 2");
  list.push_back( str );

  std::string customData;

  if( !reqQrySendCustomResponse( customData, list, 0 ) )
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Unable to send custom response to frontend");  
  }
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

  std::list< std::string > list;
  std::string str = std::string("POPUP:") + std::string("Filled order received 1")  ;
  list.push_back( str );
  str = std::string("POPUP:") + std::string("Filled order received 2")  ;
  list.push_back( str );

  std::string customData;

  /*
  if( !reqQrySendCustomResponse( customData, list, 0 ) )
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Unable to send custom response to frontend");  
  }
  */
  if( processOrder(confirmation, orderId) )
  {
    _traded+=(confirmation.getLastFillQuantity())/(_bidInstrument->getStaticData()->marketLot);
    _params.oppositePrice = confirmation.getLastFillPrice();
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
