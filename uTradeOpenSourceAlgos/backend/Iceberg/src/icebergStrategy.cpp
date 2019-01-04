#include "icebergStrategy.h"
#include "apiConstants.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <boost/program_options.hpp>

#define EXCHANGE_ID_BASE 10000000000
#define GET_EXCHANGE_ID_TEMP(symbolId) ((API2::DATA_TYPES::ExchangeId)(symbolId/EXCHANGE_ID_BASE))
#define DEBUG_DEV 1
#define MIN(A, B) A < B ?A:B
//#define INTELLECT

namespace IcebergStrategy
{
  Iceberg::Iceberg(API2::StrategyParameters *params):
    API2::SGContext(params,"ICEBERG-Strategy"),
    _riskStatus(API2::CONSTANTS::RSP_RiskStatus_MAX),
    _disclosedQty(0),
    _terminate(false),
    _modify(false),
    _modifyReject(false),
    _isTbtEnabled(false),
    _isStrategyPaused(false),
    _totalTradedQty(0)
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

    _disclosedQty = _userParams._disclosedQty == 0 ? (_userParams._disclosedQtyPercent * _userParams._quantity)/10000 : _userParams._disclosedQty; 
    dump();
    DEBUG_FLUSH(reqQryDebugLog());
  }

  void Iceberg::readParams(const std::string &file)
  {
    namespace bpo = boost::program_options;
    std::string configFile = file;
    bpo::options_description config("Configuration");
    config.add_options()

      ("ICEBERG.TBT",
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

  API2::COMMON::Instrument* Iceberg::registerSymbols()
  {

    if((GET_EXCHANGE_ID_TEMP(_userParams._symbolId) != API2::CONSTANTS::CMD_ExchangeId_NSEFO )&&
        ( GET_EXCHANGE_ID_TEMP(_userParams._symbolId)!= API2::CONSTANTS::CMD_ExchangeId_NSECDS))
      return createNewInstrument(_userParams._symbolId, true);
    else
      return createNewInstrument(_userParams._symbolId, true,!_isTbtEnabled);
  }

  void Iceberg::addOrderIntoList(SIGNED_LONG qty)
  {
    IcebergWrapper orderWrapper = 
      IcebergWrapper(_firstLegInstrument,_userParams._orderMode,this,_userParams._account,_userParams._orderType,_userParams._fillType,qty);
    _orderIdWrapperList.push_back(std::make_pair(orderWrapper._orderId,orderWrapper));
  }

  void Iceberg:: modifyStrategy()
  {
    for(auto it = _orderIdWrapperList.begin(); it != _orderIdWrapperList.end(); it++)
    {
      IcebergWrapper &orderWrapper = it->second;
      if(orderWrapper.isOrderPending())
      {
        DEBUG_MESSAGE(reqQryDebugLog(),"Modify !orderWrapper.isOrderPending()");
        return;
      }      
    }
    
    _modify = false;
    if(_modUserParams._quantity * _firstLegInstrument->getStaticData()->marketLot < _totalTradedQty)
    {

      DEBUG_MESSAGE(reqQryDebugLog(), "Modify Rejected");
      DEBUG_FLUSH(reqQryDebugLog());

      _modifyReject = true;

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

    if(_modUserParams._fillType != _userParams._fillType || _modUserParams._orderType != _userParams._orderType || isNewPriceBetter())
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Cancel All");
      API2::DATA_TYPES::RiskStatus risk;
      for(auto it = _orderIdWrapperList.begin(); it != _orderIdWrapperList.end(); it++)
      {
        IcebergWrapper &orderWrapper = it->second;
        if(!orderWrapper.cancelOrder(risk))
        {
          DEBUG_VARSHOW(reqQryDebugLog(), "Cancel Bid Failed: ", risk);
        }
      }
    }
    mapFrontEndValues();
    dump();
    _disclosedQty = _userParams._disclosedQty == 0 ? (_userParams._disclosedQtyPercent * _userParams._quantity)/10000 : _userParams._disclosedQty; 
  }

  bool Iceberg::isNewPriceBetter()
  {
    if(_userParams._orderMode == API2::CONSTANTS::CMD_OrderMode_BUY)
    {
      if(_modUserParams._limitPrice > _userParams._limitPrice)
        return true;
      else
        return false;
    }
    else
    {
      if(_modUserParams._limitPrice < _userParams._limitPrice)
        return true;
      else
        return false;
    }

  }

  void Iceberg::processCallBack(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId* orderId,const std::string &str)
  {
    DEBUG_VARSHOW(reqQryDebugLog(),"Client Order Id is:",confirmation.getClOrderId());
    int i = 0;
    for(auto iter = _orderIdWrapperList.begin(); iter != _orderIdWrapperList.end(); iter++)
    {
      if(iter->first == orderId)
      {
        DEBUG_VARSHOW(reqQryDebugLog(),"process Callback order id found i :",i++);
        if(!iter->second.processConfirmation(confirmation))
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
    }
    return;
  }
  
  void Iceberg::processStrategyState()
  {
    if(_modify)
      modifyStrategy();
    return;
  }

  void Iceberg::dump()
  {
    DEBUG_VARSHOW(reqQryDebugLog(),"_symbolId",_userParams._symbolId);
    DEBUG_VARSHOW(reqQryDebugLog(),"_quantity",_userParams._quantity);
    DEBUG_VARSHOW(reqQryDebugLog(),"_disclosedQtyPercent",_userParams._disclosedQtyPercent);
    DEBUG_VARSHOW(reqQryDebugLog(),"_disclosedQty",_userParams._disclosedQty);
    DEBUG_VARSHOW(reqQryDebugLog(),"_limitPrice",_userParams._limitPrice);
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderMode",short(_userParams._orderMode));
    DEBUG_VARSHOW(reqQryDebugLog(),"_fillType",short(_userParams._fillType));
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderType",short(_userParams._orderType));
  }


  bool Iceberg::setModifiedInternalParameters(API2::UserParams* customParams)
  {
    if(customParams->getValue("Quantity",_modUserParams._quantity)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Quantity");
      return false;
    }
    if(customParams->getValue("Disclosed Qty Percent",_modUserParams._disclosedQtyPercent)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Disclosed Quantity Percent");
      return false;
    }
    if(customParams->getValue("Disclosed Qty",_modUserParams._disclosedQty)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Disclosed Quantity");
      return false;
    }
    if(customParams->getValue("Order Mode 1",_modUserParams._orderMode)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Mode");
      return false;
    }
    if(customParams->getValue("Fill Type",_modUserParams._fillType) !=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Fill Type ");
      return false;
    }
    if(customParams->getValue("Order Type",_modUserParams._orderType) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Type ");
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
      else if(rem !=0)
      {
        _modUserParams._limitPrice += (_firstLegInstrument->getStaticData()->tickSize - rem);
      }
    }
    return true;
  }

  void Iceberg::mapFrontEndValues()
  {
#if DEBUG_DEV
    DEBUG_MESSAGE(reqQryDebugLog(),"In front end map values");
#endif
    _userParams._quantity = _modUserParams._quantity;
    _userParams._disclosedQtyPercent = _modUserParams._disclosedQtyPercent;
    _userParams._disclosedQty = _modUserParams._disclosedQty;
    _userParams._limitPrice = _modUserParams._limitPrice;
    _userParams._orderMode = _modUserParams._orderMode;
    _userParams._fillType = _modUserParams._fillType;
    _userParams._orderType = _modUserParams._orderType;
  }

  bool Iceberg::setInternalParameters(API2::UserParams* customParams)
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
    if(customParams->getValue("Disclosed Qty Percent",_userParams._disclosedQtyPercent)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Disclosed Quantity Percent");
      return false;
    }
    if(customParams->getValue("Disclosed Qty",_userParams._disclosedQty)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Disclosed Quantity");
      return false;
    }
    if(customParams->getValue("Order Mode 1",_userParams._orderMode)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Mode");
      return false;
    }
    if(customParams->getValue("Fill Type",_userParams._fillType) !=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Fill Type ");
      return false;
    }
    if(customParams->getValue("Order Type",_userParams._orderType) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Type ");
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

  void Iceberg::driver(void *params)
  {
    API2::StrategyParameters *sgParams = (API2::StrategyParameters *)params;
    boost::shared_ptr<API2::SGContext> context (new Iceberg(sgParams));
    context->reqStartAlgo(true,false);
    context->reqTimerEvent(TIMER);
    API2::SGContext::registerStrategy(context);
  }

  void Iceberg::onMarketDataEvent(UNSIGNED_LONG symbolId)
  {
    onDefaultTimerEvent();
    reqTimerEvent(TIMER);
  }

  void Iceberg::onDefaultTimerEvent()
  {
    if(!_isStrategyPaused)
    {
#if DEBUG_DEV
      DEBUG_MESSAGE(reqQryDebugLog(),"Inside Market Data Event");
      DEBUG_FLUSH(reqQryDebugLog());
#endif
      API2::DATA_TYPES::QTY givenQty = _userParams._quantity * _firstLegInstrument->getStaticData()->marketLot;
      
      if(_terminate)
        return;
      
      if(_totalTradedQty >= givenQty)
      {
        _terminate = true;
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
        return;
      }

      UNSIGNED_LONG orderedQty = 0;
      bool isAnyOrderPending = false;
      DEBUG_VARSHOW(reqQryDebugLog(),"size of list ",_orderIdWrapperList.size()); 
      int i = 0;
      _disclosedQty = MIN(_disclosedQty, givenQty - _totalTradedQty);
      for(auto it = _orderIdWrapperList.begin(); it != _orderIdWrapperList.end(); it++)
      {
        DEBUG_VARSHOW(reqQryDebugLog(),"i ",i++); 
        IcebergWrapper &orderWrapper = it->second;
        if(orderWrapper.isOrderPending())
        {
          DEBUG_MESSAGE(reqQryDebugLog(),"!orderWrapper.isOrderPending()");
          isAnyOrderPending = true;
          continue;
        }
        if(orderedQty + orderWrapper.getQty() - orderWrapper.getLastFilledQuantity() > _disclosedQty)
        {
          DEBUG_MESSAGE(reqQryDebugLog(),"orderedQty > disclosedQty");
          UNSIGNED_LONG modifyQty = _disclosedQty - orderedQty;
          orderedQty += modifyQty;
          if(modifyQty > 0)
          {
            orderWrapper.setQty(modifyQty + orderWrapper.getLastFilledQuantity());
            if(!placeFirstLegOrder(orderWrapper.getQty(),orderWrapper))
              return;
          }
          else if(modifyQty == 0)
          {
            API2::DATA_TYPES::RiskStatus risk;
            if(!orderWrapper.cancelOrder(risk))
            {
              DEBUG_VARSHOW(reqQryDebugLog(), "Cancel Bid Failed: ", risk);
            }
          }
        }
        else
        {
          DEBUG_VARSHOW(reqQryDebugLog(),"orderWrapper.getQty()",orderWrapper.getQty());
          DEBUG_VARSHOW(reqQryDebugLog(),"orderWrapper.getLastFilledQuantity()",orderWrapper.getLastFilledQuantity());
          orderedQty += orderWrapper.getQty() - orderWrapper.getLastFilledQuantity();
          if(!placeFirstLegOrder(orderWrapper.getQty(),orderWrapper))
            return;
        }
      }
      if(orderedQty < _disclosedQty && !isAnyOrderPending)
      {
        API2::DATA_TYPES::QTY qty = _disclosedQty - orderedQty;
        if(qty + _totalTradedQty + orderedQty > givenQty)
          qty = givenQty - (_totalTradedQty + orderedQty);
        addOrderIntoList(qty);
      }
    }
  }

  bool Iceberg::placeFirstLegOrder(SIGNED_LONG qty, IcebergWrapper &orderWrapper) 
  {
    DEBUG_MESSAGE(reqQryDebugLog(),"Inside Place First Leg Order");
    if(_userParams._limitPrice <= 0 || qty <= 0)
      return true;
    DEBUG_VARSHOW(reqQryDebugLog(),"orderWrapper.getLastQuotedPrice()",orderWrapper.getLastQuotedPrice());
    DEBUG_VARSHOW(reqQryDebugLog(),"orderWrapper.getLastQuantity()",orderWrapper.getLastQuantity());
  
    if((_userParams._limitPrice == orderWrapper.getLastQuotedPrice() || _userParams._orderType == API2::CONSTANTS::CMD_OrderType_MARKET) && qty == orderWrapper.getLastQuantity())
      return true;

    if(orderWrapper.getLastQuantity())
    {
      if(!orderWrapper.replaceOrder(_riskStatus,_userParams._limitPrice,qty))
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Order Could Not Be Placed ");
        _terminate = true;
#ifdef INTELLECT
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_INTELLECT_ORDER_NOT_PLACED);
#else
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
#endif
        return false; 
      }
    }
    else 
    {
      if(!orderWrapper._isReset)
      {
        orderWrapper.reset();
      }
      if(!orderWrapper.newOrder(_riskStatus,_userParams._limitPrice,qty))
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Order Could Not Be Placed ");
        _terminate = true;
#ifdef INTELLECT
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_INTELLECT_ORDER_NOT_PLACED);
#else
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
#endif
        return false;
      }
    }
    DEBUG_MESSAGE(reqQryDebugLog(), "Order Placed ");
    return true;
  }

  void Iceberg:: terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment)
  {
    reqAddStrategyComment(comment);
    reqTerminateStrategy();
  }

  void Iceberg:: onCMDModifyStrategy(API2::AbstractUserParams* newParams)
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
      return;
    }
    reqSendStrategyResponse(API2::CONSTANTS::RSP_ResponseType_STRATEGY_RUNNING,
        API2::CONSTANTS::RSP_RiskStatus_SUCCESS,
        API2::CONSTANTS::RSP_StrategyComment_USER_INPUT);
  }

  void Iceberg:: onConfirmed(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Confirmed");
    processStrategyState();
    return;
  }

  void Iceberg:: onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Replaced");
    processStrategyState();
    return;
  }

  void Iceberg:: onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Canceled");
    for(auto iter = _orderIdWrapperList.begin(); iter != _orderIdWrapperList.end(); iter++)
    {
      if(iter->first == orderId)
      {
        _orderIdWrapperList.erase(iter);
        return;
      }
    }
    processStrategyState();
    return;
  }

  void Iceberg:: onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Cancel Rejected");
    processStrategyState();
    return;
  }

  void Iceberg:: onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Replace Rejected");
    processStrategyState();
    return;
  }

  void Iceberg:: onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    _totalTradedQty += confirmation.getLastFillQuantity();
    //addOrderIntoList(confirmation.getLastFillQuantity());
    processCallBack(confirmation,orderId,"on Filled");
    for(auto iter = _orderIdWrapperList.begin(); iter != _orderIdWrapperList.end(); iter++)
    {
      if(iter->first == orderId)
      {
        _orderIdWrapperList.erase(iter);
        return;
      }
    }
    return;
  }

  void Iceberg:: onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    _totalTradedQty += confirmation.getLastFillQuantity();
   // addOrderIntoList(confirmation.getLastFillQuantity());
    processCallBack(confirmation,orderId,"on Partially Filled");
    return;
  }

  void Iceberg:: onFrozen(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
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

  void Iceberg:: onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
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

  void Iceberg::onCMDTerminateStartegy()
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
