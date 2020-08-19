#include "hedging.h"
#include "apiConstants.h"
#include "futFutNew.h"
/*
 *This Class is Responsible for the Overall Hedging that has to to place
 *It uses the Price Class To Determine the Price at which the Hedge Order is to be placed
*/

namespace SampleFutFutArbitrage
{
  //Hedging class Parametrized Constructor
  Hedging::Hedging(const FrontEndParameters *userParams, Utilities *commonUtilities, bool &isTerminate):
    _commonUtilities(commonUtilities),
    _userParams(userParams),
    _riskStatus(API2::CONSTANTS::RSP_RiskStatus_MAX),
    _lastOrderQuantity(0),
    _hedgingFreezeQty(0),
    orderValidity(API2::CONSTANTS::CMD_OrderValidity_DAY),
    lastPrice(0)

  {
    //Init Function to Create OrderWrapper, Instrument and subscribe to Market Data with Exception Handeling
    if(!init())
    {
      _isTerminate = true;
      return;
    }

    DEBUG_MESSAGE(_commonUtilities->context->reqQryDebugLog(),"Created hedge leg object");
  }


  /* ---------------------------------------------Workflow Functions --------------------------------------------------*/


  //Hedge Order Driver/Workflow Function
  bool Hedging::startHedge()
  {

    //Calculate Lots to place Order
    //rounding off is not required,because for different lot size or partial filled ,validations are there
    API2::DATA_TYPES::QTY quantity = getCalculateLots();
  
    quantity = quantity +  hedgeOrderWrapper.getLastFilledQuantity();
      if(quantity ==  0)
      return true;

    API2::DATA_TYPES::PRICE price =  hedgingPrice.getHedgePrice(orderValidity);
    hedgeOrderWrapper._orderValidity = orderValidity;
    API2::SharedUtilities::roundPriceToTick(price,
        _userParams->orderMode2,
        *( _commonUtilities->instrument2->getStaticData()));

    if(price == lastPrice)
      return true;

    if(( (_commonUtilities->mktData2->getPrice(0,_userParams->orderMode2)) == lastPrice ) && 
        (hedgeOrderWrapper._orderValidity != API2::CONSTANTS::CMD_OrderValidity_IOC ))
      return true;

    if(API2::COMMON::placeOrReplaceOrder(hedgeOrderWrapper,
          _riskStatus,
          price,
          quantity,
          _commonUtilities->checkBasicChecks,
          _hedgingFreezeQty))
    {
      DEBUG_MESSAGE( _commonUtilities->context->reqQryDebugLog(),
          "Hedge order request Successful");
      setLastPrice(price);
      return true;
    }
    else
    {
      DEBUG_MESSAGE( _commonUtilities->context->reqQryDebugLog(),
          "Hedge order request failed");
      return false;
    }

    return false;
  }



  /* ---------------------------------------------Implementation Functions --------------------------------------------------*/

  bool Hedging::init()
  {
    try
    {
      // Create Instrument, Subscribe to it's Market Data and Create an OrderWrapper for it

      /*
         Parameters for createNewInstrument
         [Required](Symbol, (bool)reqMarketData, (bool) Subscribe to TBT Data, (bool) Subscribe to Snapshot Feed)
         */

      _commonUtilities->instrument2 = _commonUtilities->context->createNewInstrument(_userParams->symbol2,
          true,
          !_userParams->isTBT,
          _userParams->isTBT);
      _commonUtilities->mktData2 = _commonUtilities->context->reqQryUpdateMarketData(_userParams->symbol2);
      /*
         Parameters for Order Wrapper
         [Required](Instrument, OrderMode Buy/Sell, pointer object of SGContext, Account)
         [Optional/Check API to see Default Values](Order Type Limit/Market, Order Validity Day/IOC, etc)
         */
      hedgeOrderWrapper = API2::COMMON::OrderWrapper(_commonUtilities->instrument2,
          _userParams->orderMode2,
          _commonUtilities->context,
          _userParams->account2);

      if(_commonUtilities->checkBasicChecks)
      {
        _hedgingFreezeQty = _commonUtilities->context->getFreezeQty(
            _commonUtilities->instrument2->getStaticData()->symbol,
            _commonUtilities->instrument2->getStaticData()->exchangeId ,
            _commonUtilities->instrument2->getStaticData()->securityType,
            _commonUtilities->instrument2->getStaticData()->groupName );
      }


    }
    catch(API2::MarketDataSubscriptionFailedException& e)
    {
      DEBUG_VARSHOW(_commonUtilities->context->reqQryDebugLog(), "Symbol ID: ", _userParams->symbol2);
      if(_userParams->isTBT)
      {
        DEBUG_MESSAGE(_commonUtilities->context->reqQryDebugLog(),"TBT subscription Failed For Symbol 2");
      }
      else
      {
        DEBUG_MESSAGE(_commonUtilities->context->reqQryDebugLog(),"Snapshot subscription Failed For Symbol 2");
      }
      return false;
    }
    catch(API2::InstrumentNotFoundException &e)
    {
      DEBUG_MESSAGE(_commonUtilities->context->reqQryDebugLog(),"Instrument Not Found For Symbol 2");
      return false;
    }

    catch(std::exception &e)
    {
      DEBUG_MESSAGE(_commonUtilities->context->reqQryDebugLog(),"standard exception raised with Hedging");
      return false;
    }


    if(!hedgingPrice.setDefaultsOfPrice(_commonUtilities,_userParams))
    {
      DEBUG_MESSAGE(_commonUtilities->context->reqQryDebugLog(),"_commonUtilities was NULL");
      return false;
    }

    return true;
  }

  //Check is the Order is of Hedging
  bool Hedging::isHedgeOrder(API2::COMMON::OrderId *orderId) const
  {
    return (orderId == hedgeOrderWrapper._orderId );
  }



  //Get Calculated Lots
  API2::DATA_TYPES::QTY  Hedging::getCalculateLots() const
  {
    API2::DATA_TYPES::QTY temp = _commonUtilities->instrument1->getPosition()->getTradedQty(_userParams->orderMode1);

    return (((temp * _commonUtilities->ratio2)/_commonUtilities->ratio1) - getHedgePositions());
  }


  //Get the Static Lot Size of the Instrument
  API2::DATA_TYPES::QTY Hedging::getLotSize() const
  {
    return _commonUtilities->instrument2->getStaticData()->marketLot;
  }

  //Get Number of Positions Made by the Instrument
  API2::DATA_TYPES::QTY Hedging::getHedgePositions() const
  {
    return _commonUtilities->instrument2->getPosition()->getTradedQty( _userParams->orderMode2);
  }

  //Check if the Order is in Open State
  bool Hedging::isOpenOrder()
  {
    return hedgeOrderWrapper.getLastFilledQuantity();
  }

  //Check if Market Depth is available for the Symbol subscribed to
  bool Hedging::isMarketDepthAvailableForHedge() const
  {
    if(!API2::COMMON::isMarketDepthAvailable(_commonUtilities->mktData2))
    {
      DEBUG_MESSAGE(_commonUtilities->context->reqQryDebugLog(),
          "Wait!, Market Depth is Empty of Hedge");
      DEBUG_FLUSH(_commonUtilities->context->reqQryDebugLog());
      return false;
    }
    return true;
  }

  void Hedging::setLastPrice(const API2::DATA_TYPES::PRICE &price)
  {
    lastPrice = price;
  }

}
