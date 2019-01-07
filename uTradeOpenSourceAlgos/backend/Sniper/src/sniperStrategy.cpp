#include "sniperStrategy.h"
#include "apiConstants.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <boost/program_options.hpp>

#define EXCHANGE_ID_BASE 10000000000
#define GET_EXCHANGE_ID_TEMP(symbolId) ((API2::DATA_TYPES::ExchangeId)(symbolId/EXCHANGE_ID_BASE))
#define DEBUG_DEV 1
#define DEPTH 5
//#define INTELLECT

namespace SniperStrategy
{
  Sniper::Sniper(API2::StrategyParameters *params):
    API2::SGContext(params,"SNIPER-Strategy"),
    _riskStatus(API2::CONSTANTS::RSP_RiskStatus_MAX),
    _buyOrder(API2::CONSTANTS::CMD_OrderMode_BUY),
    _sellOrder(API2::CONSTANTS::CMD_OrderMode_SELL),
    _modify(false),
    _terminate(false),
    _isTbtEnabled(false),
    _isStrategyPaused(false),
    _wrapperParametersModified(false),
    _modifyReject(false)
  {
    API2::UserParams* customParams = (API2::UserParams*) params->getInfo();
    if(!setInternalParameters(customParams))
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Front End Parameters Failed");
      DEBUG_FLUSH(reqQryDebugLog());
#ifdef INTELLECT
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_PARAMETERS_FAILED);
#else
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
#endif
      return;
    }
    else
    {
#ifdef INTELLECT
      setParentOrder(_userParams._parentOrderId);
#endif
    }


    if(!performValidations(_userParams))
    {
      _terminate = true;
#ifdef INTELLECT
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_TRIGGER_PRICE_CONDITION_FAILED);
#else
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
#endif
      return;
    }

    try
    {
      readParams("./config/intellectAlgos.conf");
    }
    catch(boost::program_options::error &e)
    {
      DEBUG_VARSHOW(reqQryDebugLog(),"Bad Options: ",e.what());
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
      return;
    }
    catch(std::exception& e)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Got Some Exception in reading config file");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
      return;
    }
    DEBUG_VARSHOW(reqQryDebugLog(),"TBT: ",_isTbtEnabled);
    DEBUG_VARSHOW(reqQryDebugLog(),"MAX_VALUE:  ",_maxValue);

    try
    {
      _firstLegInstrument = registerSymbols();
    }
    catch(API2::MarketDataSubscriptionFailedException e)
    {
      std::cout<<e.what()
        <<std::endl;
      DEBUG_MESSAGE(reqQryDebugLog(), "TBT Subscription Failed");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED);
      return;
    }
    catch(API2::InstrumentNotFoundException e)
    {
      std::cout<<e.what()
        <<std::endl;

      DEBUG_MESSAGE(reqQryDebugLog(), "Instrument not found");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED);
      return;
    }

    if(_firstLegInstrument == NULL)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "TBT Subscription Failed");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED);
      return;
    }

    if(_userParams._orderType == API2::CONSTANTS::CMD_OrderType_LIMIT)
    {
      SIGNED_LONG rem = _userParams._limitPrice % _firstLegInstrument->getStaticData()->tickSize;
      
      if(_userParams._orderMode == API2::CONSTANTS::CMD_OrderMode_BUY)
      {
        _userParams._limitPrice -= rem;
      }
      else if(rem != 0)
      {
        _userParams._limitPrice += (_firstLegInstrument->getStaticData()->tickSize - rem);
      }
    }
    setFirstLegOrderWrapper();
    dump();
    DEBUG_FLUSH(reqQryDebugLog());
  }


  void Sniper::readParams(const std::string &file)
  {
    namespace bpo = boost::program_options;
    std::string configFile = file;
    bpo::options_description config("Configuration");
    config.add_options()

      ("SNIPER.TBT",
       bpo::value<bool>(&_isTbtEnabled)->default_value(0),
       "Tbt Enabled")
      ("GLOBAL.MAX_VALUE",
       bpo::value<UNSIGNED_LONG>(&_maxValue)->default_value(0),
       "Max Order Value")
      ;
    bpo::options_description configFileOptions ;
    configFileOptions.add( config ) ;

    bpo::variables_map vm ;
    std::ifstream ifs( configFile.c_str() ) ;

    if ( ifs )
    {
      store( parse_config_file( ifs, configFileOptions, true ), vm ) ;
      bpo::notify ( vm ) ;
    }
    else
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"intellectAlgos.conf file not found");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
      return;
    }
  }

  bool Sniper::performValidations(FrontEndParameters &_userParams)
  {
    if(_modify && (_userParams._quantity * _firstLegInstrument->getStaticData()->marketLot < _firstLegOrderWrapper._totalTradedQty ))
    {
      return false;      
    }

    if(_userParams._orderType == API2::CONSTANTS::CMD_OrderType_LIMIT)
    {
      if(_userParams._orderMode == API2::CONSTANTS::CMD_OrderMode_BUY )
      {
        if(_userParams._triggerPrice < _userParams._limitPrice)
        {
          DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPrice < _userParams._limitPrice");
          return false;

        }
      }
      else
      {
        if(_userParams._triggerPrice > _userParams._limitPrice)
        {
          DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPrice > _userParams._limitPrice");
          return false;

        }
      }
    }
    return true;

  }

  API2::COMMON::Instrument* Sniper::registerSymbols()
  {

    if((GET_EXCHANGE_ID_TEMP(_userParams._symbolId) != API2::CONSTANTS::CMD_ExchangeId_NSEFO )&&
        ( GET_EXCHANGE_ID_TEMP(_userParams._symbolId)!= API2::CONSTANTS::CMD_ExchangeId_NSECDS))
      return createNewInstrument(_userParams._symbolId, true);
    else
      return createNewInstrument(_userParams._symbolId, true,!_isTbtEnabled);
  }

  void Sniper::setFirstLegOrderWrapper()
  {
    _firstLegOrderWrapper = SniperWrapper(_firstLegInstrument,_userParams._orderMode,this,_userParams._account,_userParams._orderType,_userParams._fillType,_userParams._quantity);
  }


  void Sniper:: modifyStrategy()
  {
    if(!performValidations(_modUserParams))
    {
      _modify = false;
      _modifyReject = true;
      return;
    }
    _modify = false;
    mapFrontEndValues();
    dump();
    if(_firstLegOrderWrapper._orderValidity != _userParams._fillType || _firstLegOrderWrapper._orderType != _userParams._orderType)
    {
      _firstLegOrderWrapper._orderValidity = _userParams._fillType;
      _firstLegOrderWrapper._orderType = _userParams._orderType;
      _wrapperParametersModified = true;
    }
  }


  void Sniper::processCallBack(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId* orderId,const std::string &str)
  {
    DEBUG_VARSHOW(reqQryDebugLog(),"Client Order Id is:",confirmation.getClOrderId());
    if(_firstLegOrderWrapper._orderId == orderId)
    {
      if(!_firstLegOrderWrapper.processConfirmation(confirmation))
      {
        _terminate = true;
#ifdef INTELLECT
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_CONFIRMATION_CALLBACK_FAILED);
#else
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
#endif
        DEBUG_VARSHOW(reqQryDebugLog(),"Process CallBack failed ",str.c_str());
        return;
      }
      DEBUG_VARSHOW(reqQryDebugLog(),"First Leg Order ",str.c_str());
    }
    return;
  }

  void Sniper::processStrategyState()
  {
    if(_terminate && !_firstLegOrderWrapper.isOrderPending())
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY); 
    if(_modify && !_firstLegOrderWrapper.isOrderPending())
      modifyStrategy();
    return;
  }

  void Sniper::dump()
  {
    DEBUG_VARSHOW(reqQryDebugLog(),"_symbolId",_userParams._symbolId);
    DEBUG_VARSHOW(reqQryDebugLog(),"_quantity",_userParams._quantity);
    DEBUG_VARSHOW(reqQryDebugLog(),"_fillType",short(_userParams._fillType));
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderType",short(_userParams._orderType));
    DEBUG_VARSHOW(reqQryDebugLog(),"_triggerPrice",_userParams._triggerPrice);
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderMode",int(_userParams._orderMode));
  }


  bool Sniper::setModifiedInternalParameters(API2::UserParams* customParams)
  {
    if(customParams->getValue("Quantity",_modUserParams._quantity)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Quantity");
      return false;
    }
    if(customParams->getValue("Order Mode 1",_modUserParams._orderMode)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Mode");
      return false;
    }
    /*if(customParams->getValue("Fill Type",_modUserParams._fillType) !=API2::UserParamsError_OK)
      {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Fill Type ");
      return false;
      }*/
    _modUserParams._fillType = API2::CONSTANTS::CMD_OrderValidity_IOC;

    if(customParams->getValue("Order Type",_modUserParams._orderType) !=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Type ");
      return false;
    }
    if(customParams->getValue("Trigger Price",_modUserParams._triggerPrice) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Trigger Price ");
      return false;
    }
    if(customParams->getValue("Limit Price",_modUserParams._limitPrice) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Limit Price ");
      return false;
    }
    else if(_modUserParams._orderType == API2::CONSTANTS::CMD_OrderType_LIMIT)
    {
      SIGNED_LONG rem = _modUserParams._limitPrice % _firstLegInstrument->getStaticData()->tickSize;
      if(_modUserParams._orderMode == API2::CONSTANTS::CMD_OrderMode_BUY)
      {
        _modUserParams._limitPrice -= rem;
      }
      else if(rem != 0)
      {
        _modUserParams._limitPrice += (_firstLegInstrument->getStaticData()->tickSize - rem);
      }
    }
    if(customParams->getValue("Acc Detail 1", _modUserParams._account) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Account ");
      return false;
    }
    return true;
  }

  void Sniper::mapFrontEndValues()
  {
#if DEBUG_DEV
    DEBUG_MESSAGE(reqQryDebugLog(),"In front end map values");
#endif
    _userParams._quantity = _modUserParams._quantity;
    _userParams._orderMode = _modUserParams._orderMode;
    _userParams._fillType = _modUserParams._fillType;
    _userParams._orderType = _modUserParams._orderType;
    _userParams._triggerPrice = _modUserParams._triggerPrice;
    _userParams._limitPrice = _modUserParams._limitPrice;
  }

  bool Sniper::setInternalParameters(API2::UserParams* customParams)
  {
    if(customParams->getValue("SYMBOL LEG1",_userParams._symbolId) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue In First Leg Symbol ID ");
      return false;
    }
    if(customParams->getValue("Quantity",_userParams._quantity)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Quantity");
      return false;
    }
    if(customParams->getValue("Order Mode 1",_userParams._orderMode)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Mode");
      return false;
    }
    /*if(customParams->getValue("Fill Type",_userParams._fillType) !=API2::UserParamsError_OK)
      {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Fill Type ");
      return false;
      }*/
    _userParams._fillType = API2::CONSTANTS::CMD_OrderValidity_IOC;

    if(customParams->getValue("Order Type",_userParams._orderType) !=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Type ");
      return false;
    }
    if(customParams->getValue("Trigger Price",_userParams._triggerPrice) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Trigger Price ");
      return false;
    }
    if(customParams->getValue("Limit Price",_userParams._limitPrice) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Limit Price ");
      return false;
    }
    if(customParams->getValue("Acc Detail 1", _userParams._account) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Account ");
      return false;
    }
#ifdef INTELLECT
    _userParams._parentOrderId=customParams->getParentOrderId();
#endif
    return true;
  }

  bool Sniper::_marketTickEnabled = true;

  void Sniper::driver(void *params)
  {
    API2::StrategyParameters *sgParams = (API2::StrategyParameters *)params;
    boost::shared_ptr<API2::SGContext> context (new Sniper(sgParams));
    context->reqStartAlgo(_marketTickEnabled,false);
    if(!_marketTickEnabled)
      context->reqTimerEvent(TIMER);
    API2::SGContext::registerStrategy(context);
  }
  
  void Sniper::onMarketDataEvent(UNSIGNED_LONG symbolId)
  {
    onDefaultTimerEvent();
  }

  void Sniper::onDefaultTimerEvent()
  {
    if(!_isStrategyPaused)
    {
#if DEBUG_DEV
      //DEBUG_MESSAGE(reqQryDebugLog(),"Inside Market Data Event");
      //DEBUG_FLUSH(reqQryDebugLog());
#endif

      SIGNED_LONG depthQty = 0;


      if(_firstLegOrderWrapper._totalTradedQty >= _userParams._quantity * _firstLegInstrument->getStaticData()->marketLot)
      {
        _terminate = true;
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
        return;
      }
      if(_terminate)
      {
        return;
      }
      if(_firstLegOrderWrapper.isOrderPending())
      {
        return;
      }
      API2::COMMON::MktData *mktData = reqQryUpdateMarketData(_userParams._symbolId);
      UNSIGNED_LONG lastTradePrice = mktData->getLastTradePrice();
      //if(symbolId == _userParams._symbolId)
      {
        if(_userParams._orderMode == API2::CONSTANTS::CMD_OrderMode_BUY)
        {          
          for(int i = 0; i < DEPTH && mktData->getAskQty(i) && mktData->getAskPrice(i) <= _userParams._triggerPrice; i++)
            depthQty += mktData->getAskQty(i);
          
          if(lastTradePrice && mktData->getAskPrice(0) && mktData->getAskPrice(0) <= _userParams._triggerPrice)
            placeFirstLegOrder(_userParams._limitPrice,depthQty,lastTradePrice);
        }
        else
        {

          for(int i = 0; i < DEPTH && mktData->getBidQty(i) && mktData->getBidPrice(i) >= _userParams._triggerPrice; i++)
            depthQty += mktData->getBidQty(i);

          if(lastTradePrice && mktData->getBidPrice(0) && mktData->getBidPrice(0) >= _userParams._triggerPrice)
            placeFirstLegOrder(_userParams._limitPrice,depthQty,lastTradePrice);
        }
      }
      return;
    }
  }

  void Sniper::placeFirstLegOrder(UNSIGNED_LONG price, SIGNED_LONG depthQty, UNSIGNED_LONG lastTradePrice) 
  {
#if DEBUG_DEV
    DEBUG_MESSAGE(reqQryDebugLog(),"Inside Place First Leg Order");
    DEBUG_FLUSH(reqQryDebugLog());
#endif
    SIGNED_LONG qty = _userParams._quantity * _firstLegInstrument->getStaticData()->marketLot;

    if(_terminate) 
    {
      return;
    }
    if(_firstLegOrderWrapper._totalTradedQty >= qty)
    {
      _terminate = true;
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
      return;
    }

    qty -= _firstLegOrderWrapper._totalTradedQty;
    if(_userParams._orderType == API2::CONSTANTS::CMD_OrderType_MARKET && qty > depthQty)
    {
      qty = depthQty;
    }
    SIGNED_LONG remainingLots = qty / _firstLegInstrument->getStaticData()->marketLot;
    if(_maxValue && (remainingLots * lastTradePrice >= _maxValue))
    {
      qty = (_maxValue/lastTradePrice) * _firstLegInstrument->getStaticData()->marketLot;
    }

    qty += _firstLegOrderWrapper.getLastFilledQuantity();

    if(!_wrapperParametersModified && (_firstLegOrderWrapper.getLastQuantity() == qty) && (price == _firstLegOrderWrapper.getLastQuotedPrice() || _firstLegOrderWrapper._orderType == API2::CONSTANTS::CMD_OrderType_MARKET))
      return;

    _wrapperParametersModified = false;


#if DEBUG_DEV
    DEBUG_VARSHOW(reqQryDebugLog(),"Qty is           : ",qty);
    DEBUG_FLUSH(reqQryDebugLog());
#endif

#if DEBUG_DEV
    DEBUG_MESSAGE(reqQryDebugLog(),"first leg day || ioc");
    DEBUG_FLUSH(reqQryDebugLog());
#endif

    if(qty <= 0 || (_userParams._orderType == API2::CONSTANTS::CMD_OrderType_LIMIT && price <=0))
      return;

    if(_firstLegOrderWrapper.getLastQuantity())
    {
      if(_userParams._fillType == API2::CONSTANTS::CMD_OrderValidity_IOC)
      {
        return;
      }
      if(!_firstLegOrderWrapper.replaceOrder(_riskStatus,price,qty))
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Order Could Not Be Placed ");
#ifdef INTELLECT
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_INTELLECT_ORDER_NOT_PLACED);
#else
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
#endif
        return;
      }
    }
    else 
    {

      _firstLegOrderWrapper.reset();

      if(!_firstLegOrderWrapper.newOrder(_riskStatus,price,qty))
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "DAY Order Could Not Be Placed ");
        DEBUG_VARSHOW(reqQryDebugLog(),"price",price);
        DEBUG_VARSHOW(reqQryDebugLog(),"Quantity",qty);
#ifdef INTELLECT
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_INTELLECT_ORDER_NOT_PLACED);
#else
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
#endif
        return;
      }
    }    

  }

  void Sniper:: terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment)
  {
    reqAddStrategyComment(comment);
    reqTerminateStrategy();
  }

  void Sniper:: onCMDModifyStrategy(API2::AbstractUserParams* newParams)
  {
    DEBUG_METHOD(reqQryDebugLog());
    _modify = true;
    API2::UserParams* modParams = (API2::UserParams*) newParams;
    if(!setModifiedInternalParameters(modParams))
    {      
      DEBUG_MESSAGE(reqQryDebugLog(), "Front End Parameters Failed");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_VERSION_DIFFERS);
      return;
    }

    processStrategyState();
    if(_modifyReject)
    {
      _modifyReject = false;
      DEBUG_MESSAGE(reqQryDebugLog(), "Modify Rejected");
      DEBUG_FLUSH(reqQryDebugLog());
#ifdef INTELLECT
      reqSendStrategyResponse(API2::CONSTANTS::RSP_ResponseType_MODIFICATION_REJECT,
          API2::CONSTANTS::RSP_RiskStatus_SUCCESS,
          API2::CONSTANTS::RSP_StrategyComment_USER_INPUT);
#else
      _terminate = true;
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
#endif
      return;
    }

    reqSendStrategyResponse(API2::CONSTANTS::RSP_ResponseType_STRATEGY_RUNNING,
        API2::CONSTANTS::RSP_RiskStatus_SUCCESS,
        API2::CONSTANTS::RSP_StrategyComment_USER_INPUT);

    onDefaultTimerEvent();
  }

  void Sniper:: onConfirmed(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Confirmed");
    processStrategyState();
    //onDefaultTimerEvent();
    return;
  }

  void Sniper:: onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Replaced");
    processStrategyState();
    onDefaultTimerEvent();
    return;
  }

  void Sniper:: onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Canceled");
    processStrategyState();
    //onDefaultTimerEvent();
    return;
  }

  void Sniper:: onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Cancel Rejected");
    processStrategyState();
    //onDefaultTimerEvent();
    return;
  }

  void Sniper:: onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Replace Rejected");
    processStrategyState();
    //onDefaultTimerEvent();
    return;
  }

  void Sniper:: onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    _firstLegOrderWrapper._totalTradedQty += confirmation.getLastFillQuantity();
    processCallBack(confirmation,orderId,"on Filled");
    onDefaultTimerEvent();
    return;
  }

  void Sniper:: onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    _firstLegOrderWrapper._totalTradedQty += confirmation.getLastFillQuantity();
    processCallBack(confirmation,orderId,"on Partially Filled");
    onDefaultTimerEvent();
    return;
  }

  void Sniper:: onFrozen(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    processCallBack(confirmation,orderId,"on Frozen");
    _terminate = true;
#ifdef INTELLECT
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_INTELLECT_ORDER_FROZEN);
#else
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_ORDER_FROZEN);
#endif
    return;
  }

  void Sniper:: onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    processCallBack(confirmation,orderId,"on NewRejected");
    _terminate = true;
#ifdef INTELLECT
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_INTELLECT_ORDER_FROZEN);
#else
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_ORDER_FROZEN);
#endif
    return;
  }

  void Sniper::onCMDTerminateStartegy()
  {
    DEBUG_METHOD_DETAILED(reqQryDebugLog());
    _terminate = true;
#ifdef INTELLECT 
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_INTELLECT_FRONTEND_TERMINATE);
#else
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
#endif
    return;
  }
}
