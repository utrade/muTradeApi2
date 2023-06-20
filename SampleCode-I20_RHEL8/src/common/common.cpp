/**
 * This file is provided to perform some common functions that are generally useful in algos.
 * User can change code as per their requirement and apply neccessary checks to minimize risk
 * and maximize performance of application.
 * These functions may not fullfill all the requirements. So, user should check the implementation and
 * documentation before use.
 *
 * Disclaimer: uTrade will not be responsible for any issue due to this code as implementation is also provided
 *
 */

#include "common.h"
#include <sgSymbolDataDefines.h>

namespace API2
{
  namespace COMMON
  {
    bool readFile(std::ifstream &file,std::string fileName,bool &isTbtEnabled,API2::DebugLog *debugLog)
    {
      int i;
      std::istringstream iss;
      iss.clear();
      std::string line="";
      if( !file.is_open() )
      {
        file.open(fileName);
      }
      while(!file.eof() )
      {
        getline(file,line);
        iss.str(line);
        iss>>i;
        if(i == 1)
          isTbtEnabled = true;
        else
          isTbtEnabled = false;
        DEBUG_VARSHOW(debugLog,"Value of Tbt Enables is:",isTbtEnabled);
        return true;
      }
      return false;
    }

    API2::COMMON::Instrument* registerSymbol(SIGNED_LONG symbolId,const bool &isTbtEnabled,SGContext *context)
    {
      API2::DATA_TYPES::ExchangeId exchangeId = getExchangeId(symbolId);
      if( ( exchangeId !=  API2::CONSTANTS::CMD_ExchangeId_NSEFO ) &&
          ( exchangeId != API2::CONSTANTS::CMD_ExchangeId_NSECM  ) &&
          ( exchangeId != API2::CONSTANTS::CMD_ExchangeId_NSECDS ) )
        return context->createNewInstrument(symbolId,true);
      return context->createNewInstrument(symbolId,true,!isTbtEnabled);
    }

    bool isPriceInTradeExecutionRange(API2::COMMON::Instrument* instrument,
        const SIGNED_LONG &orderPrice,
        DebugLog *debugLog
        )
    {
      if(instrument->getStaticData() == NULL)
      {
        DEBUG_MESSAGE(debugLog,"DATA IS NULL");
        return false;
      }

      if(instrument->getStaticData()->lowTradeExecutionRange == 0 ||
          instrument->getStaticData()->highTradeExecutionRange == 0)
        return true;

      if(orderPrice >= instrument->getStaticData()->lowTradeExecutionRange &&
          orderPrice <= instrument->getStaticData()->highTradeExecutionRange)
      {
        return true;
      }
      else
      {
        DEBUG_MESSAGE(debugLog,"trade execution check failed low high");
        DEBUG_VARSHOW(debugLog,"lowTradeExecutionRange",instrument->getStaticData()->lowTradeExecutionRange);
        DEBUG_VARSHOW(debugLog,"highTradeExecutionRange",instrument->getStaticData()->highTradeExecutionRange);
        DEBUG_VARSHOW(debugLog,"observed Price:",orderPrice);
        return false;
      }
    }
    bool getBestPrice(SIGNED_LONG symbolId,
        DATA_TYPES::OrderMode side,
        SIGNED_LONG &price,
        OrderWrapper &orderWrapper,
        SGContext *context,
        int tickFactor,
        bool pickOpportunityEnabled,
        bool &pickedOpportunity,
        const SIGNED_LONG &opportunityPrice,
        bool useBasePrice,
        const SIGNED_LONG &basePrice,
        bool bidInTop5,
        bool notBestBid
        )
    {
      MktData *mkData = context->reqQryMarketData(symbolId);
      if(mkData == NULL)
      {
        DEBUG_VARSHOW(context->reqQryDebugLog(),"----GOT NULL MARKET DATA FOR-----",symbolId);
        context->reqTerminateStrategy();
        return false;
      }

      int mode = 0;
      DATA_TYPES::OrderMode oppSide;

      if(side == CONSTANTS::CMD_OrderMode_BUY)
      {
        mode = 1;
        oppSide = CONSTANTS::CMD_OrderMode_SELL;
      }
      else
      {
        mode = -1;
        tickFactor = - tickFactor;
        oppSide = CONSTANTS::CMD_OrderMode_BUY;
      }

      if(pickOpportunityEnabled)
      {
        if(mkData->getQty(0,oppSide))
          if( (mode * opportunityPrice) >= (mode * mkData->getPrice(0,oppSide) ))
          {
            price = opportunityPrice ;
            pickedOpportunity = true;
            return true;
          }            
      }
      for(int i=0;i<5;i++)
      {
        if(orderWrapper.getLastQuotedPrice() == mkData->getPrice(i,side)
            &&
            orderWrapper.getLastQuantity() - orderWrapper.getLastFilledQuantity() == mkData->getQty(i,side))
          continue;

        // using getQty here as we can get price = 0 as in spread contracts
        if(mkData->getQty(i,side))
          price = mkData->getPrice(i,side) + tickFactor * orderWrapper._instrument->getStaticData()->tickSize;
        else
        {
          if(notBestBid)
          {
            price = basePrice;
            return true;
          }
          price = 0;
          return true;
        }

        if(!useBasePrice)
          return true;
        else
        {
          if( (mode * basePrice) > (mode * price) )
            return true;
          else
            price = 0;
        }

        if(!bidInTop5)
        {
          if(notBestBid)
            price = basePrice;

          return true;
        }
      }

      if(notBestBid)
      {
        price = basePrice;
        return true;
      }
      
      return true;
    }

    bool isCurrencyExchange(API2::DATA_TYPES::ExchangeId exchangeId)
    {
      switch(exchangeId)
      {
        case API2::CONSTANTS::CMD_ExchangeId_MOEX:
        case API2::CONSTANTS::CMD_ExchangeId_NSECDS:
        case API2::CONSTANTS::CMD_ExchangeId_BSECDS:
        case API2::CONSTANTS::CMD_ExchangeId_BSEINX:
        case API2::CONSTANTS::CMD_ExchangeId_SGXCUR:
          return true;
        default:
          return false;
      }
    }

    bool checkForHop(
        SIGNED_LONG &hopTradedLots,
        const SIGNED_LONG &hopLots,
        SIGNED_LONG &profitInTicks,
        const SIGNED_LONG &hopSpreadInTicks,
        DebugLog *debugLog )
    {
      if( hopLots <= 0 )
      {
        DEBUG_MESSAGE( debugLog, "API2::COMMON::checkForHop: error: hopLots <= 0" );
        return false;
      }
      SIGNED_LONG noOfHops = hopTradedLots / hopLots;
      if( noOfHops )
      {
        profitInTicks += hopSpreadInTicks * noOfHops;
        hopTradedLots %= hopLots;
        return true;
      }
      return false;
    }

    SIGNED_LONG getWeightedAveragePrice(API2::COMMON::MktData* mktData, SIGNED_LONG quantity, bool askOrBid ,API2::DebugLog *debugLog)
    {
      SIGNED_LONG amount             =  0;
      SIGNED_LONG positionalPrice    =  0;
      SIGNED_LONG positionalQuantity =  0;
      SIGNED_LONG averagePrice       =  0;
      size_t position                =  0;
      SIGNED_LONG totalQuantity      = quantity;
      if( debugLog )
      {
        DEBUG_MESSAGE(debugLog,"__________________________________________________");
        DEBUG_VARSHOW(debugLog,"EX:Qunatity for which average price to be calculated  ",quantity);
      }

      if( askOrBid )
      {
        while( quantity > 0 )
        {
          positionalPrice = mktData->getAskPrice( position );
          if( positionalPrice )
          {
            positionalQuantity = mktData->getAskQty( position++ );
            positionalQuantity = positionalQuantity > quantity ? quantity : positionalQuantity;
            amount            += (positionalQuantity * positionalPrice);
            quantity          -= positionalQuantity;
            if( debugLog )
            {
              DEBUG_VARSHOW(debugLog,"EX:Position                ",position );
              DEBUG_VARSHOW(debugLog,"EX:Price at position       ",positionalPrice);
              DEBUG_VARSHOW(debugLog,"EX:Quantity at position    ",positionalQuantity);
              DEBUG_VARSHOW(debugLog,"EX:Amount                  ",amount);
            }
          }
          else
          {
            if( debugLog )
            {
              DEBUG_VARSHOW(debugLog,"EX:Price does not exist at position  ",position);
            }
            break;
          }
        }
      }
      else
      {
        while( quantity > 0 )
        {
          positionalPrice = mktData->getBidPrice( position );
          if( positionalPrice )
          {
            positionalQuantity  = mktData->getBidQty( position++ );
            positionalQuantity  = positionalQuantity > quantity ? quantity : positionalQuantity;
            amount             += ( positionalQuantity * positionalPrice);
            quantity           -= positionalQuantity;
            if( debugLog )
            {
              DEBUG_VARSHOW(debugLog,"EX:Position                ",position );
              DEBUG_VARSHOW(debugLog,"EX:Price at position       ",positionalPrice);
              DEBUG_VARSHOW(debugLog,"EX:Quantity at position    ",positionalQuantity);
              DEBUG_VARSHOW(debugLog,"EX:Amount                  ",amount);
            }
          }
          else
          {
            if( debugLog )
            {
              DEBUG_VARSHOW(debugLog,"EX:Price does not exist at position  ",position);
            }
            break;
          }
        }
      }

      quantity = totalQuantity - quantity ;//quantity available in market.
      if(amount > 0)
      {
        averagePrice = amount / quantity;
      }
      else if( amount < 0)
      {
        if( debugLog )
          DEBUG_VARSHOW(debugLog,"EX:ERROR: Amount is negative ",amount);
        amount       = 0;
        averagePrice = 0;
      }

      if( debugLog )
      {
        DEBUG_VARSHOW(debugLog,"EX:Amount received is ",amount);
        DEBUG_VARSHOW(debugLog,"EX:Quantity used      ",quantity);
        DEBUG_VARSHOW(debugLog,"EX:Average Price       ",averagePrice);
        DEBUG_MESSAGE(debugLog,"__________________________________________________");
        DEBUG_FLUSH(debugLog);
      }
      return averagePrice;
    }

    int64_t getTimeDifferenceFromNowTo(int64_t endTime)
    {
      struct timeval tp;
      gettimeofday( &tp, NULL );
      time_t currentTime  = tp.tv_sec * 1000 + tp.tv_usec/1000 ;
      return endTime - currentTime; 
    }

    bool placeOrReplaceOrder(OrderWrapper &orderWrapper,
        API2::DATA_TYPES::RiskStatus &riskStatus,
        const API2::DATA_TYPES::PRICE price,
        const API2::DATA_TYPES::QTY qty,
        const bool checkBasicChecks,
        const API2::DATA_TYPES::QTY freezeQty
        )
    {
      DebugLog *debugLog = orderWrapper._context->reqQryDebugLog();
      //If order is in pending state,then order cannot be replaced
      if(orderWrapper.isOrderPending())
      {
        return false;
      }
      //If last quantity exists,replaced order to be placed
      else if(orderWrapper.getLastQuantity())
      {
        //if enabled check basic checks like DPR check,TER check,freeze qty check
        if((isOrderPlaceable(price,qty,orderWrapper,checkBasicChecks,freezeQty)))
        {
          if(orderWrapper.replaceOrder(riskStatus,
                price,
                qty))
          {
            DEBUG_MESSAGE(  debugLog,"Replace order request Successful");
            DEBUG_VARSHOW(  debugLog, "Price: ", price );
            DEBUG_VARSHOW(  debugLog, "Quantity: ", qty );
            return true;
          }
          else
          {
            DEBUG_MESSAGE( debugLog,"Replace order request failed");
            DEBUG_VARSHOW( debugLog, "Price: ", price );
            DEBUG_VARSHOW( debugLog, "Quantity: ", qty );
            if(riskStatus != API2::CONSTANTS::RSP_RiskStatus_MAX)
              DEBUG_VARSHOW(debugLog,"Risk Status: ",riskStatus);
          }
        }
        return false;
      }

      //if enabled check basic checks like DPR check,TER check,freeze qty check
      if((isOrderPlaceable(price,qty,orderWrapper,checkBasicChecks,freezeQty)))
      {
        //reset orderwrapper
        if(!orderWrapper._isReset)
          orderWrapper.reset();
        if(orderWrapper.newOrder(riskStatus,
              price,
              qty))
        {
          DEBUG_MESSAGE(  debugLog,"New order request Successful");
          DEBUG_VARSHOW(  debugLog,"Price: ", price );
          DEBUG_VARSHOW(  debugLog,"Quantity: ", qty );
          return true;
        }
        else
        {
          DEBUG_MESSAGE(  debugLog,"New order request failed");
          DEBUG_VARSHOW(  debugLog,"Price: ", price );
          DEBUG_VARSHOW(  debugLog,"Quantity: ", qty);
          if(riskStatus != API2::CONSTANTS::RSP_RiskStatus_MAX)
            DEBUG_VARSHOW(debugLog,"Risk Status: ",riskStatus);
        }
      }
      return false;
    }

    bool isOrderPlaceable(const API2::DATA_TYPES::PRICE price,
        const API2::DATA_TYPES::QTY qty,
        OrderWrapper &orderWrapper,
        const bool checkBasicChecks,
        const API2::DATA_TYPES::QTY freezeQty)
    {
      if(checkBasicChecks)
      {
        DebugLog *debugLog = orderWrapper._context->reqQryDebugLog();
        bool ret = true;
        //upperBandPrice means upper DPR
        //lowerBandPrice means lower DPR
        if ((orderWrapper._instrument->getStaticData()->upperBandPrice != 0 &&
              orderWrapper._instrument->getStaticData()->lowerBandPrice != 0) ||
            (orderWrapper._instrument->getStaticData()->upperBandPrice > price &&
             orderWrapper._instrument->getStaticData()->lowerBandPrice < price))
        {
          ret = true;
        }
        else
        {

          DEBUG_MESSAGE(  debugLog,"DPR Breached");
          DEBUG_VARSHOW(  debugLog, "Price: ",
              price );
          DEBUG_VARSHOW(  debugLog,
              "upperBandPrice: ",
              orderWrapper._instrument->getStaticData()->upperBandPrice);
          DEBUG_VARSHOW(  debugLog,
              "lowerBandPrice: ",
              orderWrapper._instrument->getStaticData()->lowerBandPrice);
          return false;
        }
        //highTradeExecutionRange and lowTradeExecutionRange means upper and lower TER range respectively
        if((orderWrapper._instrument->getStaticData()->highTradeExecutionRange == 0 &&
              orderWrapper._instrument->getStaticData()->lowTradeExecutionRange == 0) ||
            ((orderWrapper._instrument->getStaticData()->highTradeExecutionRange > price &&
              orderWrapper._instrument->getStaticData()->lowTradeExecutionRange < price)))
        {
          ret = true;
        }
        else
        {

          DEBUG_MESSAGE(  debugLog,"TER Breached");
          DEBUG_VARSHOW(  debugLog,"Price: ", price );
          DEBUG_VARSHOW(  debugLog,"highTradeExecutionRange: ",
              orderWrapper._instrument->getStaticData()->highTradeExecutionRange);
          DEBUG_VARSHOW(  debugLog,"lowTradeExecutionRange: ",
              orderWrapper._instrument->getStaticData()->lowTradeExecutionRange);
          return false;
        }
        if(qty < freezeQty ||freezeQty == 0)
        {
          ret = true;
        }
        else
        {
          DEBUG_MESSAGE(  debugLog,"Order Quantity Entered is Above Freeze Quantity");
          DEBUG_VARSHOW(  debugLog,"Order Quantity: " , qty );
          DEBUG_VARSHOW(  debugLog,"Freeze Quantity: ", freezeQty);
          return false;
        }
        return ret;
      }
      return true;
    }

    bool isMarketDepthAvailable(API2::COMMON::MktData *mktData)
    {
      return (mktData->getAskQty(0) != 0 &&
          mktData->getBidQty(0) != 0);
    }

    bool isNseMarket(const API2::DATA_TYPES::ExchangeId exchangeId)
    {
      switch(exchangeId)
      {
        case API2::CONSTANTS::CMD_ExchangeId_NSECM:
        case API2::CONSTANTS::CMD_ExchangeId_NSEFO:
        case API2::CONSTANTS::CMD_ExchangeId_NSECDS:
        case API2::CONSTANTS::CMD_ExchangeId_NSEIFSC:
        case API2::CONSTANTS::CMD_ExchangeId_NSECOM:
          return true;
        default:
          break;
      }
      return false;
    }

    double applyPercentage(const double value, const API2::DATA_TYPES::PERCENTAGE percentage)
    {
      return value * percentage/10000.0;
    }


  }
}
