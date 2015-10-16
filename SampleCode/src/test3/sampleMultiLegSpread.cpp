#include "sampleMultiLegSpread.h"
#include <sharedCommands.h>
#include <fstream>
#include <sgMktData.h>
#include <ctime>
#include <sys/time.h>
#include <math.h>
//#define TESTING
#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW CLOCK_MONOTONIC
#endif

namespace API2{
  namespace MultiTest{
    Context::Context(API2::StrategyParameters *params):
      API2::SGContext(params, "CustomTest2"),
      _Instrument1(NULL),
      _Instrument2(NULL),
      _Instrument3(NULL),
      _userParams()
    {
      API2::UserParams *customOMMParams = (API2::UserParams *)params->getInfo();
      DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__ );

      customOMMParams->dump();
      if(!setInternalParameters(customOMMParams))
      {
        reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
        reqTerminateStrategy(false);
      }

    }
    void Context::onMarketDataEvent(UNSIGNED_LONG symbolId)
    {

      DEBUG_METHOD(reqQryDebugLog());
      DEBUG_VARSHOW(reqQryDebugLog(),"SymbolID: ", symbolId);
      DEBUG_FLUSH(reqQryDebugLog());


    }

    void Context::registerMoreSymbol()
    {

    }

    void Context::onCMDModifyStrategy(API2::AbstractUserParams* obj)
    {
    }


    void Context::onProcessOrderConfirmation(API2::OrderConfirmation &confirmation)
    {
      _orderWrapper.processConfirmation(confirmation);

    }

    void Context::onConfirmed(API2::OrderConfirmation &confirmation,
        API2::COMMON::OrderId *orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__);
      //  DEBUG_MESSAGE(reqQryDebugLog(), getStrConfirmation(confirmation).c_str());
      //  DEBUG_MESSAGE(reqQryDebugLog(), getStrOrderId(orderId).c_str());
      DEBUG_FLUSH(reqQryDebugLog());
      onTimerEvent();

    }

    void Context::onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
    {
      DEBUG_METHOD(reqQryDebugLog());
      DEBUG_FLUSH(reqQryDebugLog());
      reqAddStrategyComment(CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
      reqTerminateStrategy();
    }

    void Context::onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Order Partial Filled");
      DEBUG_VARSHOW(reqQryDebugLog(), "Partial Filled Qty: ", confirmation.getLastFillQuantity());
      DEBUG_FLUSH(reqQryDebugLog());
      //    reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
      //    reqTerminateStrategy(false);
    }



    void Context::onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
    {
      DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__ );

    }


    /**
     * Logic:
     * if numLegs = 1 from Frontend, treat it as Spread Order REquest
     * Leg 1SymbolId, OrderMode, Order Price and Qty are used to sen a spread order.
     * On confirm , strategy will simple try to send a cancel Order.
     * on Filled or onCanceled, Strategy will be terminated with Success status
     *
     * For numLegs >1 or Less than eq to 3, treat it as Multileg IOC Order
     * on Cancelled, on Filled, terminate the stategy.
     */
    bool Context::setInternalParameters(API2::UserParams *params)
    {
      if(params->getValue("Legs",_userParams._numLegs) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Issue in num Legs");

        return false;
      }
      if(params->getValue("SYMBOL LEG1",_userParams._symbolIdLeg1) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Issue in SYMBOL LEG1");

        return false;
      }

      if(params->getValue("Order Mode 1",_userParams._side1) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Order Mode 1");

        return false;
      }


      if(params->getValue("SYMBOL LEG2",_userParams._symbolIdLeg2) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Issue in SYMBOL LEG2");

        return false;
      }

      if(params->getValue("Order Mode 2",_userParams._side2) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Order Mode 2");

        return false;
      }

      if(params->getValue("SYMBOL LEG3",_userParams._symbolIdLeg3) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Issue in SYMBOL LEG3");

        return false;
      }

      if(params->getValue("Order Mode 3",_userParams._side3) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Order Mode 3");

        return false;
      }

      if(params->getValue("Qty1",_userParams._qty1) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "issue in Qty1");

        return false;
      }

      if(params->getValue("Qty2",_userParams._qty2) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "issue in Qty2");

        return false;
      }

      if(params->getValue("Qty3",_userParams._qty3) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "issue in Qty3");

        return false;
      }

      if(params->getValue("Price1",_userParams._price1) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "issue in Price1");

        return false;
      }
      if(params->getValue("price2",_userParams._price2) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "issue in Price2");

        return false;
      }
      if(params->getValue("price3",_userParams._price3) != API2::UserParamsError_OK)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "issue in Price3");

        return false;
      }

      return setParams();
    }


    bool Context::setParams()
    {
      std::stringstream ss;
      _userParams.dump(ss, "Frontend Params:");
      DEBUG_MESSAGE(reqQryDebugLog(),ss.str().c_str());
      DEBUG_FLUSH(reqQryDebugLog());
      try{
        _Instrument1 =0, _Instrument2=0, _Instrument3 =0;
        if(_userParams._numLegs>=1)
          _Instrument1 = createNewInstrument(_userParams._symbolIdLeg1,false,true);
        if(_userParams._numLegs>=2)
          _Instrument2 = createNewInstrument(_userParams._symbolIdLeg2,false,true);
        if(_userParams._numLegs>=3)
          _Instrument3 = createNewInstrument(_userParams._symbolIdLeg3,false,true);
        if(_userParams._numLegs>1)
          _orderWrapper = API2::COMMON::OrderWrapper(
              CONSTANTS::CMD_OrderType_LIMIT,
              this,
              _Instrument1,
              API2::DATA_TYPES::OrderMode(_userParams._side1),
              _Instrument2,
              API2::DATA_TYPES::OrderMode(_userParams._side2),
              _Instrument3,
              API2::DATA_TYPES::OrderMode(_userParams._side3)
              );
        else
          _orderWrapper = API2::COMMON::OrderWrapper(
              _Instrument1,
              API2::DATA_TYPES::OrderMode(_userParams._side1),
              this,
              CONSTANTS::CMD_OrderValidity_DAY,CONSTANTS::CMD_ProductType_INTRADAY,
              CONSTANTS::CMD_OrderType_LIMIT,true
              );
        return true;
      }
      catch(API2::MarketDataSubscriptionFailedException e)
      {
        DEBUG_VARSHOW(reqQryDebugLog(), "Exception occured", e.what());
        return false;
      }

      return false;

    }

    void Context::onTimerEvent()
    {
      API2::DATA_TYPES::RiskStatus risk;

      DEBUG_MESSAGE(reqQryDebugLog(), __PRETTY_FUNCTION__ );
      DEBUG_FLUSH(reqQryDebugLog());

      if(_userParams._numLegs>=1)
        DEBUG_VARSHOW(reqQryDebugLog(), "Last Quoted Price Leg1: ", _orderWrapper.getLegOrder(_Instrument1->getSymbolId())->getLastQuotedPrice());
      if(_userParams._numLegs>=2)
        DEBUG_VARSHOW(reqQryDebugLog(), "Last Quoted Price Leg2: ", _orderWrapper.getLegOrder(_Instrument2->getSymbolId())->getLastQuotedPrice());
      if(_userParams._numLegs>=3)
        DEBUG_VARSHOW(reqQryDebugLog(), "Last Quoted Price Leg3: ", _orderWrapper.getLegOrder(_Instrument3->getSymbolId())->getLastQuotedPrice());
      DEBUG_FLUSH(reqQryDebugLog());

      if(_orderWrapper._isReset)
      {
        bool ordRet =false;
        if(_userParams._numLegs>1)
        {
          ordRet = _orderWrapper.newOrder(
              risk,
              _userParams._price1,_userParams._qty1,
              _userParams._price2,_userParams._qty2,
              _userParams._price3,_userParams._qty3
              );
        }
        else
        {
          ordRet = _orderWrapper.newOrder(
              risk,
              _userParams._price1,
              _userParams._qty1);
        }
        if(!ordRet)
        {
          DEBUG_VARSHOW(reqQryDebugLog(), "Failed Sending New Order, Reason:", risk);
          reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_RMS_FAILURE);
          reqTerminateStrategy(false);
        }
        else
        {
          DEBUG_VARSHOW(reqQryDebugLog(), "Sent New Order at price:", getPrice());
        }
      }
      else
      {
        DEBUG_VARSHOW(reqQryDebugLog(), "Order Status:", reqQryOrderStatus(_orderWrapper._orderId));
        DEBUG_FLUSH(reqQryDebugLog());

        switch(reqQryOrderStatus(_orderWrapper._orderId))
        {
          case API2::CONSTANTS::RSP_OrderStatus_PENDING:
            return;
          case API2::CONSTANTS::RSP_OrderStatus_FILLED:
          case API2::CONSTANTS::RSP_OrderStatus_CANCELED:
            DEBUG_MESSAGE(reqQryDebugLog(), "Status: Filled, resetting");
            DEBUG_VARSHOW(reqQryDebugLog(), "Orderwrapper status", _orderWrapper._isReset);
            DEBUG_FLUSH(reqQryDebugLog());
            _orderWrapper.reset();
            return;
          case API2::CONSTANTS::RSP_OrderStatus_CONFIRMED:
            {
              if(_userParams._numLegs ==1)
              {
                _orderWrapper.cancelOrder(risk);
                DEBUG_VARSHOW(reqQryDebugLog(),"Cancelled Order: Risk Status", risk);
              }
            }
          case API2::CONSTANTS::RSP_OrderStatus_PARTIALLY_FILLED:
            return;
        }

      }
    }

    void Context::onIOCCanceled(OrderConfirmation &Confirmation, COMMON::OrderId *orderId)
    {
      DEBUG_METHOD(reqQryDebugLog());
      reqAddStrategyComment(CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
      reqTerminateStrategy();
    }
    void Context::onCanceled(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
      DEBUG_METHOD(reqQryDebugLog());
      reqAddStrategyComment(CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
      reqTerminateStrategy();
      onTimerEvent();


    }

    API2::DATA_TYPES::PRICE Context::getPrice()
    {

    }

    void TestDriver(void *params)
    {
      API2::StrategyParameters *sgParams = (API2::StrategyParameters*)params;
      boost::shared_ptr<Context> context(new Context(sgParams));
      API2::SGContext::registerStrategy(context);
      context->reqStartAlgo(true,false);
      context->reqTimerEvent(2000000);
      DEBUG_FLUSH(context->reqQryDebugLog());
    }
  } // namespace MultiTest
} // namespace API2
