#include "bracketOrderStrategy.h"
#include "apiConstants.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <boost/program_options.hpp>

#define EXCHANGE_ID_BASE 10000000000
#define GET_EXCHANGE_ID_TEMP(symbolId) ((API2::DATA_TYPES::ExchangeId)(symbolId/EXCHANGE_ID_BASE))
#define DEBUG_DEV 1
#define LTP
//#define INTELLECT

namespace BracketOrderStrategy
{
  BracketOrder::BracketOrder(API2::StrategyParameters *params):
    API2::SGContext(params,"BRACKET-ORDER-Strategy"),
    _riskStatus(API2::CONSTANTS::RSP_RiskStatus_MAX),
    _buyOrder(API2::CONSTANTS::CMD_OrderMode_BUY),
    _sellOrder(API2::CONSTANTS::CMD_OrderMode_SELL),
    _modify(false),
    _terminate(false),
    _isTbtEnabled(false),
    _isStrategyPaused(false),
    _secondLegCalculatedQty(0),
    _thirdLegCalculatedQty(0),
    _cancelSecondLegOrder(false),
    _cancelThirdLegOrder(false),
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
      _instrument = registerSymbols();
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

      DEBUG_MESSAGE(reqQryDebugLog(), "Instrument Not Found");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED);
      return;
    }
    if(_instrument == NULL)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "TBT Subscription Failed");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED);
      return;
    }

    if(_userParams._orderTypeLeg1 == API2::CONSTANTS::CMD_OrderType_LIMIT)
    {
      SIGNED_LONG rem = _userParams._limitPriceLeg1 % _instrument->getStaticData()->tickSize;
      if(_userParams._orderModeLeg1 == API2::CONSTANTS::CMD_OrderMode_BUY)
      {
        _userParams._limitPriceLeg1 -= rem;
      }
      else if(rem != 0)
      {
        _userParams._limitPriceLeg1 += (_instrument->getStaticData()->tickSize - rem);
      }
    }

    if(_userParams._orderTypeLeg2 == API2::CONSTANTS::CMD_OrderType_LIMIT)
    {
      SIGNED_LONG rem = _userParams._limitPriceLeg2 % _instrument->getStaticData()->tickSize;
      if(_userParams._orderModeLeg2 == API2::CONSTANTS::CMD_OrderMode_BUY)
      {
        _userParams._limitPriceLeg2 -= rem;
      }
      else if(rem != 0)
      {
        _userParams._limitPriceLeg2 += (_instrument->getStaticData()->tickSize - rem);
      }
    }

    if(_userParams._orderTypeLeg3 == API2::CONSTANTS::CMD_OrderType_LIMIT)
    {
      SIGNED_LONG rem = _userParams._limitPriceLeg3 % _instrument->getStaticData()->tickSize;
      if(_userParams._orderModeLeg3 == API2::CONSTANTS::CMD_OrderMode_BUY)
      {
        _userParams._limitPriceLeg3 -= rem;
      }
      else if(rem != 0)
      {
        _userParams._limitPriceLeg3 += (_instrument->getStaticData()->tickSize - rem);
      }
    }

    setOrderWrapper();
    calculateSecondThirdLegQty();
    dump();
    DEBUG_FLUSH(reqQryDebugLog());
  }

  void BracketOrder::readParams(const std::string &file)
  {
    namespace bpo = boost::program_options;
    std::string configFile = file;
    bpo::options_description config("Configuration");
    config.add_options()

      ("BRACKET_ORDER.TBT",
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

  bool BracketOrder::performValidations(FrontEndParameters &_userParams)
  {
    if(_modify && (_userParams._quantityLeg1 * _instrument->getStaticData()->marketLot < _firstLegOrderWrapper._totalTradedQty ))
    {
      return false;      
    }

    if(_userParams._orderModeLeg1 == API2::CONSTANTS::CMD_OrderMode_BUY )
    {
      if(_userParams._orderTypeLeg1 == API2::CONSTANTS::CMD_OrderType_LIMIT && _userParams._triggerPriceLeg1 < _userParams._limitPriceLeg1)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg1 < _userParams._limitPriceLeg1");
        return false;

      }
      if(_userParams._orderTypeLeg2 == API2::CONSTANTS::CMD_OrderType_LIMIT && _userParams._triggerPriceLeg2 < _userParams._limitPriceLeg2)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg2 < _userParams._limitPriceLeg2");
        return false;

      }
      if(_userParams._orderTypeLeg3 == API2::CONSTANTS::CMD_OrderType_LIMIT && _userParams._triggerPriceLeg3 > _userParams._limitPriceLeg3)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg3 > _userParams._limitPriceLeg3");
        return false;

      }
      if(_userParams._triggerPriceLeg3 < _userParams._triggerPriceLeg2)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg3 < _userParams._triggerPriceLeg2");
        return false;

      }
      if(_userParams._triggerPriceLeg2 > _userParams._triggerPriceLeg1)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg2 > _userParams._triggerPriceLeg1");
        return false;

      }
      if(_userParams._triggerPriceLeg3 < _userParams._triggerPriceLeg1)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg3 < _userParams._triggerPriceLeg1");
        return false;

      }

    }
    else
    {
      if(_userParams._orderTypeLeg1 == API2::CONSTANTS::CMD_OrderType_LIMIT && _userParams._triggerPriceLeg1 > _userParams._limitPriceLeg1)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg1 > _userParams._limitPriceLeg1");
        return false;

      }
      if(_userParams._orderTypeLeg2 == API2::CONSTANTS::CMD_OrderType_LIMIT && _userParams._triggerPriceLeg2 > _userParams._limitPriceLeg2)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg2 > _userParams._limitPriceLeg2");
        return false;

      }
      if(_userParams._orderTypeLeg3 == API2::CONSTANTS::CMD_OrderType_LIMIT && _userParams._triggerPriceLeg3 < _userParams._limitPriceLeg3)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg3 < _userParams._limitPriceLeg3");
        return false;

      }
      if(_userParams._triggerPriceLeg3 > _userParams._triggerPriceLeg2)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg3 > _userParams._triggerPriceLeg2");
        return false;

      }
      if(_userParams._triggerPriceLeg2 < _userParams._triggerPriceLeg1)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg2 < _userParams._triggerPriceLeg1");
        return false;

      }
      if(_userParams._triggerPriceLeg3 > _userParams._triggerPriceLeg1)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "_userParams._triggerPriceLeg3 > _userParams._triggerPriceLeg1");
        return false;

      }

    }
    return true;
  }

  API2::COMMON::Instrument* BracketOrder::registerSymbols()
  {
    if((GET_EXCHANGE_ID_TEMP(_userParams._symbolId) != API2::CONSTANTS::CMD_ExchangeId_NSEFO )&&
        ( GET_EXCHANGE_ID_TEMP(_userParams._symbolId)!= API2::CONSTANTS::CMD_ExchangeId_NSECDS))
      return createNewInstrument(_userParams._symbolId, true);
    else
      return createNewInstrument(_userParams._symbolId, true,!_isTbtEnabled);
  }

  void BracketOrder::setOrderWrapper()
  {

    _firstLegOrderWrapper = BracketOrderWrapper(_instrument,_userParams._orderModeLeg1,this,_userParams._account,_userParams._orderTypeLeg1,_userParams._fillTypeLeg1,_userParams._quantityLeg1);
    _secondLegOrderWrapper = BracketOrderWrapper(_instrument,_userParams._orderModeLeg2,this,_userParams._account,_userParams._orderTypeLeg2,_userParams._fillTypeLeg2,_userParams._quantityLeg2);
    _thirdLegOrderWrapper = BracketOrderWrapper(_instrument,_userParams._orderModeLeg3,this,_userParams._account,_userParams._orderTypeLeg3,_userParams._fillTypeLeg3,_userParams._quantityLeg3);

  }

  void BracketOrder::processCallBack(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId* orderId,const std::string &str)
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
        DEBUG_VARSHOW(reqQryDebugLog(),"Process CallBack failed",str.c_str());
        return;
      }
      DEBUG_VARSHOW(reqQryDebugLog(),"First Leg Order ",str.c_str());
    }
    else if(_secondLegOrderWrapper._orderId == orderId)
    {
      if(!_secondLegOrderWrapper.processConfirmation(confirmation))
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
      DEBUG_VARSHOW(reqQryDebugLog(),"Second Leg Order ",str.c_str());

    }
    else if(_thirdLegOrderWrapper._orderId == orderId)
    {
      if(!_thirdLegOrderWrapper.processConfirmation(confirmation))
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
      DEBUG_VARSHOW(reqQryDebugLog(),"Third Leg Order ",str.c_str());

    }
    return;
  }

  void BracketOrder::processStrategyState()
  {
    if(_terminate && !_firstLegOrderWrapper.isOrderPending() && !_secondLegOrderWrapper.isOrderPending() && !_thirdLegOrderWrapper.isOrderPending())
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY); 
    if(_modify && !_firstLegOrderWrapper.isOrderPending() && !_secondLegOrderWrapper.isOrderPending() && !_thirdLegOrderWrapper.isOrderPending())
      modifyStrategy();
    return;
  }

  void BracketOrder::dump()
  {
    DEBUG_VARSHOW(reqQryDebugLog(),"_symbolId",_userParams._symbolId);
    DEBUG_VARSHOW(reqQryDebugLog(),"_quantityLeg1",_userParams._quantityLeg1);
    DEBUG_VARSHOW(reqQryDebugLog(),"_quantityLeg2",int(_userParams._quantityLeg2));
    DEBUG_VARSHOW(reqQryDebugLog(),"_quantityLeg3",int(_userParams._quantityLeg3));
    DEBUG_VARSHOW(reqQryDebugLog(),"_triggerPriceLeg2",_userParams._triggerPriceLeg2);
    DEBUG_VARSHOW(reqQryDebugLog(),"_triggerPriceLeg3",_userParams._triggerPriceLeg3);
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderModeLeg1",int(_userParams._orderModeLeg1));
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderModeLeg2",int(_userParams._orderModeLeg2));
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderModeLeg3",int(_userParams._orderModeLeg3));
    DEBUG_VARSHOW(reqQryDebugLog(),"_limitPriceLeg1",int(_userParams._limitPriceLeg1));
    DEBUG_VARSHOW(reqQryDebugLog(),"_limitPriceLeg2",int(_userParams._limitPriceLeg2));
    DEBUG_VARSHOW(reqQryDebugLog(),"_limitPriceLeg3",int(_userParams._limitPriceLeg3));
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderTypeLeg1",int(_userParams._orderTypeLeg1));
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderTypeLeg2",int(_userParams._orderTypeLeg2));
    DEBUG_VARSHOW(reqQryDebugLog(),"_orderTypeLeg3",int(_userParams._orderTypeLeg3));

  }

  bool BracketOrder::setModifiedInternalParameters(API2::UserParams* customParams)
  {

    if(customParams->getValue("Quantity Leg1",_modUserParams._quantityLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in First Leg Quantity");
      return false;
    }
    if(customParams->getValue("Quantity Leg2",_modUserParams._quantityLeg2)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Second Leg Quantity");
      return false;
    }
    if(customParams->getValue("Quantity Leg3",_modUserParams._quantityLeg3)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Third Leg  Quantity");
      return false;
    }
    if(customParams->getValue("Order Mode 1",_modUserParams._orderModeLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Mode");
      return false;
    }    
    _modUserParams._orderModeLeg2 = _modUserParams._orderModeLeg1 == API2::CONSTANTS::CMD_OrderMode_BUY ? API2::CONSTANTS::CMD_OrderMode_SELL : API2::CONSTANTS::CMD_OrderMode_BUY;

    _modUserParams._orderModeLeg3 = _modUserParams._orderModeLeg2;

    if(customParams->getValue("Trigger Price Leg1",_modUserParams._triggerPriceLeg1) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in LEG 1 Trigger Price");
      return false;
    }
    if(customParams->getValue("Trigger Price Leg2",_modUserParams._triggerPriceLeg2) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in LEG 2 Trigger Price");
      return false;
    }
    if(customParams->getValue("Trigger Price Leg3",_modUserParams._triggerPriceLeg3) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in LEG 3 Trigger Price");
      return false;
    }
    if(customParams->getValue("Acc Detail 1", _modUserParams._account) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Account ");
      return false;
    }
    if(customParams->getValue("Order Type Leg1",_modUserParams._orderTypeLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in First Leg Order Type");
      return false;
    }
    if(customParams->getValue("Order Type Leg2",_modUserParams._orderTypeLeg2)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Second Leg Order Type");
      return false;
    }
    if(customParams->getValue("Order Type Leg3",_modUserParams._orderTypeLeg3)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Third Leg  Order Type");
      return false;
    }

    if(customParams->getValue("Fill Type Leg1",_modUserParams._fillTypeLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in First Leg Fill Type");
      return false;
    }
    if(customParams->getValue("Fill Type Leg2",_modUserParams._fillTypeLeg2)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Second Leg Fill Type");
      return false;
    }
    if(customParams->getValue("Fill Type Leg3",_modUserParams._fillTypeLeg3)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Third Leg Fill Type");
      return false;
    }

    if(customParams->getValue("Limit Price Leg1",_modUserParams._limitPriceLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in First Leg Limit Price");
      return false;
    }
    else if(_modUserParams._orderTypeLeg1 == API2::CONSTANTS::CMD_OrderType_LIMIT)
    {
      SIGNED_LONG rem = _modUserParams._limitPriceLeg1 % _instrument->getStaticData()->tickSize;
      if(_modUserParams._orderModeLeg1 == API2::CONSTANTS::CMD_OrderMode_BUY)
      {
        _modUserParams._limitPriceLeg1 -= rem;
      }
      else if(rem != 0)
      {
        _modUserParams._limitPriceLeg1 += (_instrument->getStaticData()->tickSize - rem);
      }
    }
    if(customParams->getValue("Limit Price Leg2",_modUserParams._limitPriceLeg2)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Second Leg Limit Price");
      return false;
    }
    else if(_modUserParams._orderTypeLeg2 == API2::CONSTANTS::CMD_OrderType_LIMIT)
    {
      SIGNED_LONG rem = _modUserParams._limitPriceLeg2 % _instrument->getStaticData()->tickSize;
      if(_modUserParams._orderModeLeg2 == API2::CONSTANTS::CMD_OrderMode_BUY)
      {
        _modUserParams._limitPriceLeg2 -= rem;
      }
      else if(rem != 0)
      {
        _modUserParams._limitPriceLeg2 += (_instrument->getStaticData()->tickSize - rem);
      }
    }
    if(customParams->getValue("Limit Price Leg3",_modUserParams._limitPriceLeg3)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Third Leg Limit Price");
      return false;
    }
    else if(_modUserParams._orderTypeLeg3 == API2::CONSTANTS::CMD_OrderType_LIMIT)
    {
      SIGNED_LONG rem = _modUserParams._limitPriceLeg3 % _instrument->getStaticData()->tickSize;
      if(_modUserParams._orderModeLeg3 == API2::CONSTANTS::CMD_OrderMode_BUY)
      {
        _modUserParams._limitPriceLeg3 -= rem;
      }
      else if(rem != 0)
      {
        _modUserParams._limitPriceLeg3 += (_instrument->getStaticData()->tickSize - rem);
      }
    }
    return true;
  }

  bool BracketOrder::setInternalParameters(API2::UserParams* customParams)
  {

    if(customParams->getValue("SYMBOL LEG1",_userParams._symbolId) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue In First Leg Symbol ID ");
      return false;
    }
    if(customParams->getValue("Quantity Leg1",_userParams._quantityLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in First Leg Quantity");
      return false;
    }
    if(customParams->getValue("Quantity Leg2",_userParams._quantityLeg2)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Second Leg Quantity");
      return false;
    }
    if(customParams->getValue("Quantity Leg3",_userParams._quantityLeg3)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Third Leg  Quantity");
      return false;
    }
    if(customParams->getValue("Order Mode 1",_userParams._orderModeLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Order Mode");
      return false;
    }    
    _userParams._orderModeLeg2 = _userParams._orderModeLeg1 == API2::CONSTANTS::CMD_OrderMode_BUY ? API2::CONSTANTS::CMD_OrderMode_SELL : API2::CONSTANTS::CMD_OrderMode_BUY;

    _userParams._orderModeLeg3 = _userParams._orderModeLeg2;

    if(customParams->getValue("Trigger Price Leg1",_userParams._triggerPriceLeg1) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in LEG 1 Trigger Price");
      return false;
    }
    if(customParams->getValue("Trigger Price Leg2",_userParams._triggerPriceLeg2) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in LEG 2 Trigger Price");
      return false;
    }
    if(customParams->getValue("Trigger Price Leg3",_userParams._triggerPriceLeg3) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in LEG 3 Trigger Price");
      return false;
    }
    if(customParams->getValue("Acc Detail 1", _userParams._account) != API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Account ");
      return false;
    }
    if(customParams->getValue("Order Type Leg1",_userParams._orderTypeLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in First Leg Order Type");
      return false;
    }
    if(customParams->getValue("Order Type Leg2",_userParams._orderTypeLeg2)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Second Leg Order Type");
      return false;
    }
    if(customParams->getValue("Order Type Leg3",_userParams._orderTypeLeg3)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Third Leg  Order Type");
      return false;
    }

    if(customParams->getValue("Fill Type Leg1",_userParams._fillTypeLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in First Leg Fill Type");
      return false;
    }
    if(customParams->getValue("Fill Type Leg2",_userParams._fillTypeLeg2)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Second Leg Fill Type");
      return false;
    }
    if(customParams->getValue("Fill Type Leg3",_userParams._fillTypeLeg3)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Third Leg Fill Type");
      return false;
    }


    if(customParams->getValue("Limit Price Leg1",_userParams._limitPriceLeg1)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in First Leg Limit Price");
      return false;
    }
    if(customParams->getValue("Limit Price Leg2",_userParams._limitPriceLeg2)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Second Leg Limit Price");
      return false;
    }
    if(customParams->getValue("Limit Price Leg3",_userParams._limitPriceLeg3)!=API2::UserParamsError_OK)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Issue in Third Leg Limit Price");
      return false;
    }
#ifdef INTELLECT
    _userParams._parentOrderId=customParams->getParentOrderId();
#endif

    return true;
  }

  bool BracketOrder::_marketTickEnabled = true;

  void BracketOrder::driver(void *params)
  {
    API2::StrategyParameters *sgParams = (API2::StrategyParameters *)params;
    boost::shared_ptr<API2::SGContext> context (new BracketOrder(sgParams));
    context->reqStartAlgo(_marketTickEnabled,false);
    if(!_marketTickEnabled)
      context->reqTimerEvent(TIMER);
    API2::SGContext::registerStrategy(context);
  }

  void BracketOrder::calculateSecondThirdLegQty()
  {
    _secondLegCalculatedQty = _userParams._quantityLeg1;
    _thirdLegCalculatedQty = _userParams._quantityLeg1;
    if(_userParams._quantityLeg2 == HALF)
    {
      _secondLegCalculatedQty = _secondLegCalculatedQty/2;
    }
    if(_userParams._quantityLeg3 == HALF)
    {
      _thirdLegCalculatedQty = _thirdLegCalculatedQty/2;
    }
    _secondLegCalculatedQty *= _instrument->getStaticData()->marketLot;
    _thirdLegCalculatedQty *= _instrument->getStaticData()->marketLot;
  }
  
  void BracketOrder::onMarketDataEvent(UNSIGNED_LONG symbolId)
  {
    onDefaultTimerEvent();
  }

  void BracketOrder::onDefaultTimerEvent()
  {
    if(!_isStrategyPaused)
    {
#if DEBUG_DEV
      DEBUG_MESSAGE(reqQryDebugLog(),"Inside Market Data Event");
      DEBUG_FLUSH(reqQryDebugLog());
#endif
      SIGNED_LONG qty = _userParams._quantityLeg1 * _instrument->getStaticData()->marketLot; 
      if((_firstLegOrderWrapper._totalTradedQty >= qty) && ((_secondLegOrderWrapper._totalTradedQty > 0 && _secondLegCalculatedQty == _secondLegOrderWrapper._totalTradedQty) ||  (_thirdLegOrderWrapper._totalTradedQty > 0 && _thirdLegCalculatedQty == _thirdLegOrderWrapper._totalTradedQty)))
      {
        _terminate = true;
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
        return;
      }
      if(_terminate)
      {
        return;
      }

#if DEBUG_DEV
      //DEBUG_MESSAGE(reqQryDebugLog(),"inside market data");
      //DEBUG_FLUSH(reqQryDebugLog());
#endif

      API2::COMMON::MktData *mktData = reqQryUpdateMarketData(_userParams._symbolId);
      UNSIGNED_LONG lastTradePrice = mktData->getLastTradePrice();
      //if(symbolId == _userParams._symbolId)
      {
        //DEBUG_VARSHOW(reqQryDebugLog(),"qty",qty);
        //DEBUG_VARSHOW(reqQryDebugLog(),"_totalTradedQty1",_firstLegOrderWrapper._totalTradedQty);
        //DEBUG_VARSHOW(reqQryDebugLog(),"getlastqty",_firstLegOrderWrapper.getLastQuantity());
        //DEBUG_FLUSH(reqQryDebugLog());

        if(!_firstLegOrderWrapper.isOrderPending()) 
        {

#ifdef LTP
          bool firstLegTriggered = _userParams._orderModeLeg1 == API2::CONSTANTS::CMD_OrderMode_BUY ? _userParams._triggerPriceLeg1 >= mktData->getLastTradePrice() : _userParams._triggerPriceLeg1 <= mktData->getLastTradePrice();
#else
          bool firstLegTriggered = _userParams._orderModeLeg1 == API2::CONSTANTS::CMD_OrderMode_BUY ? _userParams._triggerPriceLeg1 >= mktData->getPrice(0,API2::CONSTANTS::CMD_OrderMode_SELL) : _userParams._triggerPriceLeg1 <= mktData->getPrice(0,API2::CONSTANTS::CMD_OrderMode_BUY);
#endif

          if(firstLegTriggered)
          {

            placeFirstLegOrder(_userParams._limitPriceLeg1,lastTradePrice);

            /*if(_userParams._orderTypeLeg1 == API2::CONSTANTS::CMD_OrderType_MARKET || (_userParams._orderTypeLeg1 == API2::CONSTANTS::CMD_OrderType_LIMIT && ((_userParams._orderModeLeg1 == API2::CONSTANTS::CMD_OrderMode_BUY && _userParams._limitPriceLeg1 >= mktData->getAskPrice(0)) || (_userParams._orderModeLeg1 == API2::CONSTANTS::CMD_OrderMode_SELL && _userParams._limitPriceLeg1 <= mktData->getBidPrice(0)))))
              {
              placeFirstLegOrder(_userParams._limitPriceLeg1);
              }*/

          }
#if DEBUG_DEV
          DEBUG_MESSAGE(reqQryDebugLog(),"firstttt leg");
          DEBUG_FLUSH(reqQryDebugLog());
#endif
        }

        if(_userParams._orderModeLeg2 == API2::CONSTANTS::CMD_OrderMode_BUY)
        {
#ifdef LTP
          if(mktData->getLastTradePrice() >= _userParams._triggerPriceLeg2 && !_secondLegOrderWrapper.isOrderPending())
#else
            if(mktData->getAskPrice(0) && mktData->getAskPrice(0) >= _userParams._triggerPriceLeg2 && !_secondLegOrderWrapper.isOrderPending())
#endif
            {
              placeSecondLegOrder(_userParams._limitPriceLeg2,lastTradePrice);
            }
        }
        else if(_userParams._orderModeLeg2 == API2::CONSTANTS::CMD_OrderMode_SELL)
        {        
#ifdef LTP
          if(mktData->getLastTradePrice() <= _userParams._triggerPriceLeg2 && !_secondLegOrderWrapper.isOrderPending())
#else
            if(mktData->getBidPrice(0) && mktData->getBidPrice(0) <= _userParams._triggerPriceLeg2 && !_secondLegOrderWrapper.isOrderPending())
#endif
            {
              placeSecondLegOrder(_userParams._limitPriceLeg2,lastTradePrice);
            }
        }


        if(_userParams._orderModeLeg3 == API2::CONSTANTS::CMD_OrderMode_BUY)
        {
#ifdef LTP
          if(mktData->getLastTradePrice() <= _userParams._triggerPriceLeg3 && !_thirdLegOrderWrapper.isOrderPending())
#else
            if(mktData->getAskPrice(0) && mktData->getAskPrice(0) <= _userParams._triggerPriceLeg3 && !_thirdLegOrderWrapper.isOrderPending())
#endif
            {
              placeThirdLegOrder(_userParams._limitPriceLeg3,lastTradePrice);
            }
        }
        else if(_userParams._orderModeLeg3 == API2::CONSTANTS::CMD_OrderMode_SELL)
        {
#ifdef LTP
          if(mktData->getLastTradePrice() >= _userParams._triggerPriceLeg3 && !_thirdLegOrderWrapper.isOrderPending())
#else
            if(mktData->getBidPrice(0) && mktData->getBidPrice(0) >= _userParams._triggerPriceLeg3 && !_thirdLegOrderWrapper.isOrderPending())
#endif
            {
              placeThirdLegOrder(_userParams._limitPriceLeg3,lastTradePrice);
            }
        }
      }
      return;
    }
  }

  void BracketOrder::placeFirstLegOrder(UNSIGNED_LONG price, UNSIGNED_LONG lastTradePrice) 
  {
#ifdef DEBUG_DEV
    DEBUG_MESSAGE(reqQryDebugLog(),"Inside Place First Leg Order");
    DEBUG_FLUSH(reqQryDebugLog());
#endif
    if(_terminate)
    {
      return;
    }
    SIGNED_LONG qty = _userParams._quantityLeg1 * _instrument->getStaticData()->marketLot; 
    qty -= _firstLegOrderWrapper._totalTradedQty;
    SIGNED_LONG remainingLots = qty / _instrument->getStaticData()->marketLot;
    if(lastTradePrice && _maxValue && (remainingLots * lastTradePrice >= _maxValue))
    {
      qty = (_maxValue/lastTradePrice) * _instrument->getStaticData()->marketLot;
    }
    qty += _firstLegOrderWrapper.getLastFilledQuantity();

    if(qty <= 0 || (_userParams._orderTypeLeg1 == API2::CONSTANTS::CMD_OrderType_LIMIT && price <= 0))
      return;

    if(qty == _firstLegOrderWrapper.getLastQuantity() && (price == _firstLegOrderWrapper.getLastQuotedPrice() || _userParams._orderTypeLeg1 == API2::CONSTANTS::CMD_OrderType_MARKET))
    {
      return;
    }

    if(_firstLegOrderWrapper.getLastQuantity())
    {
      if(_userParams._fillTypeLeg1 == API2::CONSTANTS::CMD_OrderValidity_IOC)
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
        DEBUG_MESSAGE(reqQryDebugLog(), "Order Could Not Be Placed ");
#ifdef INTELLECT
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_INTELLECT_ORDER_NOT_PLACED);
#else
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
#endif
        return;
      }

    }
  }


  void BracketOrder::placeThirdLegOrder(SIGNED_LONG price, UNSIGNED_LONG lastTradePrice)
  {
#if DEBUG_DEV
    DEBUG_MESSAGE(reqQryDebugLog(),"Inside Place Third Leg Order");
    DEBUG_FLUSH(reqQryDebugLog());
#endif

    SIGNED_LONG qty;
    if(_terminate)
    {
      return;
    }

    DEBUG_MESSAGE(reqQryDebugLog(),"Checkpoint 1");
    DEBUG_FLUSH(reqQryDebugLog());

    if(_cancelThirdLegOrder)
    {
      return;
    }

    DEBUG_MESSAGE(reqQryDebugLog(),"Checkpoint 2");
    DEBUG_FLUSH(reqQryDebugLog());
    /*if(_firstLegOrderWrapper._totalTradedQty == _secondLegOrderWrapper._totalTradedQty || _firstLegOrderWrapper._totalTradedQty ==  _thirdLegOrderWrapper._totalTradedQty)
      {
      return;
      }*/
    SIGNED_LONG lots = _firstLegOrderWrapper._totalTradedQty/_instrument->getStaticData()->marketLot ;
    if(_userParams._quantityLeg3 == HALF)
    {
      lots = (lots + 1)/2;
    }
    qty = lots * _instrument->getStaticData()->marketLot;

    DEBUG_MESSAGE(reqQryDebugLog(),"Checkpoint 3");
    DEBUG_FLUSH(reqQryDebugLog());

    if(_thirdLegOrderWrapper._totalTradedQty == qty)
    {
      return;
    }

    DEBUG_MESSAGE(reqQryDebugLog(),"Checkpoint 4");
    DEBUG_FLUSH(reqQryDebugLog());

    qty -= _thirdLegOrderWrapper._totalTradedQty;
    SIGNED_LONG remainingLots = qty / _instrument->getStaticData()->marketLot;
    if(lastTradePrice && _maxValue && (remainingLots * lastTradePrice >= _maxValue))
    {
      qty = (_maxValue/lastTradePrice) * _instrument->getStaticData()->marketLot;
    }
    qty += _thirdLegOrderWrapper.getLastFilledQuantity();


    DEBUG_MESSAGE(reqQryDebugLog(),"Checkpoint 5");
    DEBUG_FLUSH(reqQryDebugLog());

    if(qty <=0 || (_userParams._orderTypeLeg3 == API2::CONSTANTS::CMD_OrderType_LIMIT && price <= 0))
      return;


    DEBUG_MESSAGE(reqQryDebugLog(),"Checkpoint 6");
    DEBUG_FLUSH(reqQryDebugLog());

    if(qty == _thirdLegOrderWrapper.getLastQuantity() && (price == _thirdLegOrderWrapper.getLastQuotedPrice() || _userParams._orderTypeLeg3 == API2::CONSTANTS::CMD_OrderType_MARKET))
    {
      return;
    }


    DEBUG_MESSAGE(reqQryDebugLog(),"Checkpoint 7");
    DEBUG_FLUSH(reqQryDebugLog());

    if(_thirdLegOrderWrapper.getLastQuantity())
    {

      DEBUG_MESSAGE(reqQryDebugLog(),"Checkpoint 8");
      DEBUG_FLUSH(reqQryDebugLog());
      if(_userParams._fillTypeLeg3 == API2::CONSTANTS::CMD_OrderValidity_IOC)
      {
        return;
      }
      if(!_thirdLegOrderWrapper.replaceOrder(_riskStatus,price,qty))
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


      DEBUG_MESSAGE(reqQryDebugLog(),"Checkpoint 9");
      DEBUG_FLUSH(reqQryDebugLog());
      _thirdLegOrderWrapper.reset();

      if(!_thirdLegOrderWrapper.newOrder(_riskStatus,price,qty))
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
  }

  void BracketOrder::placeSecondLegOrder(SIGNED_LONG price, UNSIGNED_LONG lastTradePrice)
  {
#if DEBUG_DEV
    DEBUG_MESSAGE(reqQryDebugLog(),"Inside Place Second Leg Order");
    DEBUG_FLUSH(reqQryDebugLog());
#endif
    SIGNED_LONG qty;

    if(_terminate)
    {
      return;
    }
    if(_cancelSecondLegOrder)
    {
      return;
    }
    /*if(_firstLegOrderWrapper._totalTradedQty == _secondLegOrderWrapper._totalTradedQty || _firstLegOrderWrapper._totalTradedQty ==  _thirdLegOrderWrapper._totalTradedQty)
      {
      return;
      }*/

    SIGNED_LONG lots = _firstLegOrderWrapper._totalTradedQty/_instrument->getStaticData()->marketLot ;
    if(_userParams._quantityLeg2 == HALF)
    {
      lots = (lots + 1)/2;
    }
    qty = lots * _instrument->getStaticData()->marketLot;

    if(_secondLegOrderWrapper._totalTradedQty == qty)
    {
      return;
    }
    qty -= _secondLegOrderWrapper._totalTradedQty;
    SIGNED_LONG remainingLots = qty / _instrument->getStaticData()->marketLot;
    if(lastTradePrice && _maxValue && (remainingLots * lastTradePrice >= _maxValue))
    {
      qty = (_maxValue/lastTradePrice) * _instrument->getStaticData()->marketLot;
    }
    qty += _secondLegOrderWrapper.getLastFilledQuantity();

    if(qty <= 0 || (_userParams._orderTypeLeg2 == API2::CONSTANTS::CMD_OrderType_LIMIT && price <= 0))
      return;

    if(qty == _secondLegOrderWrapper.getLastQuantity() && (price == _secondLegOrderWrapper.getLastQuotedPrice() || _userParams._orderTypeLeg2 == API2::CONSTANTS::CMD_OrderType_MARKET))
    {
      return;
    }

    if(_secondLegOrderWrapper.getLastQuantity())
    {
      if(_userParams._fillTypeLeg2 == API2::CONSTANTS::CMD_OrderValidity_IOC)
      {
        return;
      }
      if(!_secondLegOrderWrapper.replaceOrder(_riskStatus,price,qty))
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
      _secondLegOrderWrapper.reset();

      if(!_secondLegOrderWrapper.newOrder(_riskStatus,price,qty))
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
  }

  void BracketOrder:: terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment)
  {
    reqAddStrategyComment(comment);
    reqTerminateStrategy();

  }

  void BracketOrder::mapFrontEndValues()
  {
#if DEBUG_DEV
    DEBUG_MESSAGE(reqQryDebugLog(),"In front end map values");
#endif
    _userParams._quantityLeg1 = _modUserParams._quantityLeg1;
    _userParams._quantityLeg2 = _modUserParams._quantityLeg2;
    _userParams._quantityLeg3 = _modUserParams._quantityLeg3;
    _userParams._orderModeLeg1 = _modUserParams._orderModeLeg1;
    _userParams._orderModeLeg2 = _modUserParams._orderModeLeg2;
    _userParams._orderModeLeg3 = _modUserParams._orderModeLeg3;
    _userParams._triggerPriceLeg1 = _modUserParams._triggerPriceLeg1;
    _userParams._triggerPriceLeg2 = _modUserParams._triggerPriceLeg2;
    _userParams._triggerPriceLeg3 = _modUserParams._triggerPriceLeg3;
    _userParams._orderTypeLeg1 = _modUserParams._orderTypeLeg1;
    _userParams._orderTypeLeg2 = _modUserParams._orderTypeLeg2;
    _userParams._orderTypeLeg3 = _modUserParams._orderTypeLeg3;
    _userParams._fillTypeLeg1 = _modUserParams._fillTypeLeg1;
    _userParams._fillTypeLeg2 = _modUserParams._fillTypeLeg2;
    _userParams._fillTypeLeg3 = _modUserParams._fillTypeLeg3;
    _userParams._limitPriceLeg1 = _modUserParams._limitPriceLeg1;
    _userParams._limitPriceLeg2 = _modUserParams._limitPriceLeg2;
    _userParams._limitPriceLeg3 = _modUserParams._limitPriceLeg3;

  }

  void BracketOrder:: modifyStrategy()
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
    _firstLegOrderWrapper._orderType = _userParams._orderTypeLeg1;
    _firstLegOrderWrapper._orderValidity = _userParams._fillTypeLeg1;
    _secondLegOrderWrapper._orderType = _userParams._orderTypeLeg2;
    _secondLegOrderWrapper._orderValidity = _userParams._fillTypeLeg2;
    _thirdLegOrderWrapper._orderType = _userParams._orderTypeLeg3;
    _thirdLegOrderWrapper._orderValidity = _userParams._fillTypeLeg3;

  }

  void BracketOrder:: onCMDModifyStrategy(API2::AbstractUserParams* newParams)
  {
#if DEBUG_DEV
    DEBUG_MESSAGE(reqQryDebugLog(),"Inside Modify");
    DEBUG_FLUSH(reqQryDebugLog());
#endif
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
    calculateSecondThirdLegQty();
    reqSendStrategyResponse(API2::CONSTANTS::RSP_ResponseType_STRATEGY_RUNNING,
        API2::CONSTANTS::RSP_RiskStatus_SUCCESS,
        API2::CONSTANTS::RSP_StrategyComment_USER_INPUT);

    onDefaultTimerEvent();
  }

  void BracketOrder:: onConfirmed(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    if(orderId == _secondLegOrderWrapper._orderId)
      _cancelThirdLegOrder = true;
    else if(orderId == _thirdLegOrderWrapper._orderId)
      _cancelSecondLegOrder = true;

    processCallBack(confirmation,orderId,"on Confirmed");
    processStrategyState();
    //onDefaultTimerEvent();
    return;
  }

  void BracketOrder:: onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Replaced");
    processStrategyState();
    onDefaultTimerEvent();
    return;
  }

  void BracketOrder:: onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Canceled");
    processStrategyState();
    //onDefaultTimerEvent();
    return;
  }

  void BracketOrder:: onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Cancel Rejected");
    processStrategyState();
    //onDefaultTimerEvent();
    return;
  }

  void BracketOrder:: onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId* orderId)
  {
    processCallBack(confirmation,orderId,"on Replace Rejected");
    processStrategyState();
    //onDefaultTimerEvent();
    return;
  }

  void BracketOrder:: onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    if(_firstLegOrderWrapper._orderId == orderId)
    {
      _firstLegOrderWrapper._totalTradedQty += confirmation.getLastFillQuantity();
    }
    else if(_secondLegOrderWrapper._orderId == orderId)
    {
      _secondLegOrderWrapper._totalTradedQty += confirmation.getLastFillQuantity();
    }
    else if(_thirdLegOrderWrapper._orderId == orderId)
    {
      _thirdLegOrderWrapper._totalTradedQty += confirmation.getLastFillQuantity();
    }
    processCallBack(confirmation,orderId,"on Filled");
    onDefaultTimerEvent();
    return;
  }

  void BracketOrder:: onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    if(_firstLegOrderWrapper._orderId == orderId)
    {
      _firstLegOrderWrapper._totalTradedQty += confirmation.getLastFillQuantity();
    }
    else if(_secondLegOrderWrapper._orderId == orderId)
    {
      _secondLegOrderWrapper._totalTradedQty += confirmation.getLastFillQuantity();
    }
    else if(_thirdLegOrderWrapper._orderId == orderId)
    {
      _thirdLegOrderWrapper._totalTradedQty += confirmation.getLastFillQuantity();
    }

    processCallBack(confirmation,orderId,"on Partially Filled");
    onDefaultTimerEvent();
    return;
  }

  void BracketOrder:: onFrozen(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
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

  void BracketOrder:: onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
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

  void BracketOrder::onCMDTerminateStartegy()
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
