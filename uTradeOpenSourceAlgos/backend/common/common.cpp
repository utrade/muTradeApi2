#include "common.h"

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
      if((GET_EXCHANGE_ID(symbolId) !=  API2::CONSTANTS::CMD_ExchangeId_NSEFO) &&
          ( GET_EXCHANGE_ID(symbolId) != API2::CONSTANTS::CMD_ExchangeId_NSECM) &&
          ( GET_EXCHANGE_ID(symbolId) != API2::CONSTANTS::CMD_ExchangeId_NSECDS))
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
  }
}
