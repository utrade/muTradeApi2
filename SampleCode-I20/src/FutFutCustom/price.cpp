#include "price.h"
#include "futFutNew.h"

/*
 *This Class is Responsible for the Price Calculation, used by Hedging class
 *Supported Methods are Best Bid/Ask && Market Percentage
 *If the selected Method is Best Bid/Ask and the Timer expires,
 *the Method is changed from Best Bid to Market Percentage
 */

namespace SampleFutFutArbitrage
{
  //Default constructor
  Price::Price():
    _commonUtilities(0),
    _orderMode(API2::CONSTANTS::CMD_OrderMode_MAX),
    _marketPercentage(0),
    _hedgeMethod(HedgeMethod::HedgeMethod_MAX),
    _timeExpiry(15),
    ticks(0)
  {
  }

  // Driver/Init function of Price Class
  bool Price::setDefaultsOfPrice(const Utilities *commonUtilities,const FrontEndParameters *userParams)
  {

    if(commonUtilities == nullptr)
    {
      return false;
    }
    _commonUtilities = commonUtilities;
    _orderMode = userParams->orderMode2;
    _hedgeMethod = (HedgeMethod)userParams->hedgingMethod;
    _marketPercentage = userParams->marketPercentage;
    return true;
  }

  /* ---------------------------------------------Workflow Functions --------------------------------------------------*/

  //Switch on the Hedge Method Reccieved from FrontEnd
  API2::DATA_TYPES::PRICE Price::getHedgePrice(API2::DATA_TYPES::OrderValidity &orderValidity)
  {
    switch(_hedgeMethod)
    {
      case HedgeMethod::HedgeMethod_BEST_BID_ASK:
        return getHedgeBestPrice(orderValidity);
      case HedgeMethod::HegdeMethod_MarketOrder:
        return calculatePriceAfterMarketPercentage(orderValidity);
      default:
        DEBUG_MESSAGE(_commonUtilities->context->reqQryDebugLog(),"Incorrect hedge method");
        return 0;
    }
    return 0;
  }


  /* ---------------------------------------------Implementation Functions --------------------------------------------------*/


  //Calculate Price for Market Percentage Method
  API2::DATA_TYPES::PRICE Price::calculatePriceAfterMarketPercentage(API2::DATA_TYPES::OrderValidity &orderValidity) const
  {
    orderValidity = API2::CONSTANTS::CMD_OrderValidity_IOC;
    if(_orderMode == API2::CONSTANTS::CMD_OrderMode_SELL)
    {

      return (   _commonUtilities->mktData2->getLastTradePrice() -
          ((_commonUtilities->mktData2->getLastTradePrice() *
            (_marketPercentage))) / 100.0);
    }

    else
    {
      return (   _commonUtilities->mktData2->getLastTradePrice() +
          ((_commonUtilities->mktData2->getLastTradePrice() *
            (_marketPercentage))) / 100.0);

    }

  }

  //Calculate Price for Best Price Method
  API2::DATA_TYPES::PRICE Price::getHedgeBestPrice(API2::DATA_TYPES::OrderValidity &orderValidity)
  {
    if(isHedgeTimerExpired())
    {
      DEBUG_MESSAGE(_commonUtilities->context->reqQryDebugLog(),"hedge timer expired");
      _hedgeMethod = HedgeMethod::HegdeMethod_MarketOrder;
      return calculatePriceAfterMarketPercentage(orderValidity);
    }

    if(_orderMode == API2::CONSTANTS::CMD_OrderMode_SELL)
    {
      orderValidity = API2::CONSTANTS::CMD_OrderValidity_DAY;
      setTimer();
      return _commonUtilities->mktData2->getAskPrice(0) - (ticks * _commonUtilities->instrument2->getStaticData()->tickSize);
    }
    else
    {
      orderValidity = API2::CONSTANTS::CMD_OrderValidity_DAY;
      setTimer();
      return _commonUtilities->mktData2->getBidPrice(0) + (ticks * _commonUtilities->instrument2->getStaticData()->tickSize);
    }
  }

  //Check if the Timer is Expired
  bool Price::isHedgeTimerExpired()
  {
    return _timer.isTimerSet() &&_timer.isTimerExpired();
  }
  //Set Timer
  void Price::setTimer()
  {
    if(!_timer.isTimerSet())
      _timer.setTimer(_timeExpiry);
  }
  //Reset Timer
  void Price::resetTimer()
  {
    _timer.clearTimer();
  }

}
