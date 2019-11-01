#include "futFutNew.h"
#include "apiConstants.h"

/*
 *Class FutFutArbtriage is the Driver Class, derived from SGContext to let us inherit
 *Order Callback and Debugging Functionalities
 *This Holds pointer to all self created included Classes; Heading and Price
 *This class is responsible for Strategy State Management, Bidding and to Start Hedging
*/

namespace SampleFutFutArbitrage
{

  //FutFutArbitrage Arbitrage Class Constructor
  //It Recieves the Parameter Structure from the Bid Driver Function
  //Where it Type Casts them to user Params type for FILL_PARAMS Macro to work
  //And Initiaze our Common Utilities
  FutFutArbitrage::FutFutArbitrage(API2::StrategyParameters* params):
    API2::SGContext(params, "DemoStrategy"),
    _riskStatus(API2::CONSTANTS::RSP_RiskStatus_MAX),
    _rowId(0),
    _biddingPrice(0),
    _lastPrice(0),
    _achievedSpread(0),
    _hedging(nullptr),
    _terminateCheck(false),
    _isModify(false),
    _isTerminate(false),
    _lastOrderQuantity(0),
    _checkBasicChecks(false),
    _bypass(0),
    _timeExpiry(5),
    _biddingFreezeQty(0)
  {
    //Set Parameters
    API2::UserParams* customParams = (API2::UserParams*) params->getInfo();
    if( !setInternalParameters(customParams,_userParams) )
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Parameters not set from front end");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return;
    }

    if(_userParams.orderMode1 ==  _userParams.orderMode2)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"OrderMode of First leg and second leg is same");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return;
    }
    if( (!_userParams.perOrderQuantity) ||  _userParams.perOrderQuantity > _userParams.totalQuantity)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Order Quantity is incorrect");
      DEBUG_VARSHOW(reqQryDebugLog(),"Per Order Quantity",_userParams.perOrderQuantity);
      DEBUG_VARSHOW(reqQryDebugLog(),"Total Quantity",_userParams.totalQuantity);
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return;
    }

    //Initialize our CommonUtilities  structure Object
    _commonUtilities.init(this, reqQryDebugLog());


    //Init Function to Create our Instrument, Subscribe to Market Data and Create Order Wrapper with exception handeling
    if(!init())
    {
      _terminateCheck = true;
      return;

    }


    //Create Object of Hedging Class with it's Parameterized Constructor
    _hedging = new Hedging(&_userParams,&_commonUtilities,_isTerminate);
    if(_isTerminate)
    {
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return;
    }
    calculateRatio();

    _algoIdSet.insert(_commonUtilities.instrument1->getStaticData()->marketId);
    _algoIdSet.insert(_commonUtilities.instrument2->getStaticData()->marketId);

    //Read Algo ID from Conf File
    readConfForAlgoid("FUT_FUT_ARBITRAGE", "FutFutArbitrage.txt", "_ALGO_ID", true);
    readParamsFromFile();
    _commonUtilities.checkBasicChecks = _checkBasicChecks;

    //Enable Bypass if One leg is Nse and Another Leg is not of NSE
    API2::DATA_TYPES::ExchangeId exchangeIdForInstrument1 = _commonUtilities.instrument1->getStaticData()->exchangeId;
    API2::DATA_TYPES::ExchangeId exchangeIdForInstrument2 = _commonUtilities.instrument2->getStaticData()->exchangeId;
    if((API2::COMMON::isNseMarket(exchangeIdForInstrument1) ||
        API2::COMMON::isNseMarket(exchangeIdForInstrument2))&&
      (!API2::COMMON::isNseMarket(exchangeIdForInstrument1) ||
       !API2::COMMON::isNseMarket(exchangeIdForInstrument2)))
    {
      if(_bypass)
      {
        setStrategyType(API2::CONSTANTS::STRATEGY_TYPE_DEFAULT_VALUE, API2::DATA_TYPES::BYPASS_NNFID_ENABLED);
      }
    }
    _timer.setTimer(_timeExpiry);
  }


  /* ---------------------------------------------Workflow Functions --------------------------------------------------*/

  //Recieve Callbacks on Every Market Data Event
  void SampleFutFutArbitrage::FutFutArbitrage::onMarketDataEvent(UNSIGNED_LONG symbolId)
  {
    onDefaultEvent();
  }

  //Recieve Callbacks from reqTimerEvent
  void FutFutArbitrage::onTimerEvent()
  {
    reqTimerEvent(10000);
    onDefaultEvent();
  }


  //Our Strategy Driver Event
  void FutFutArbitrage::onDefaultEvent()
  {
    //Update Current Spread on FrontEnd after Timer is Expired
    if(isTimerExpired())
    {
      sendSpreadResponse();
      setTimer();
    }

    //Modify Strategy if the Flag is true and no Order is Pending
    if(_isModify && isIterationComplete())
    {
      if(!modifyStrategy())
      {
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
        return;
      }

    }

    //Terminate if the Flag is true and no Order is Pending
    if(( _terminateCheck && isIterationComplete())
        || (_isTerminate && isIterationComplete() ))
    {

      terminateStrategyComment(API2::CONSTANTS::CMD_CommandCategory_TERMINATE_STRATEGY );
      return;

    }

    //Terminate if the Quantity Entered from FrontEnd is Traded
    if(isAllLotsTraded())
    {
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
      return;
    }

    //Return is Market Data is Empty
    if ( !_hedging->isMarketDepthAvailableForHedge())
    {
      return;
    }

    //Hedging Driver
    if(!_hedging->startHedge())
    {
      //DEBUG_MESSAGE( reqQryDebugLog(),"Hedging failed");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return;
    }

    //Checks before Bid
    if((!isIterationComplete()) ||
        _hedging->hedgeOrderWrapper.getLastQuantity())
    {
      return;
    }

    if (getSpread() == 0)
      return;

    //Bidding Driver
    if(!startBidding())
    {
      //DEBUG_MESSAGE( reqQryDebugLog(),"Bidding failed");
    }
  }

  //CallBack for When an Order is Confirmed
  void FutFutArbitrage::onConfirmed(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId)
  {
    reqQryDebugLog()->saveConfirmation(confirmation);
    if(isBiddingOrder(orderId))
    {
      _biddingOrderWrapper.processConfirmation(confirmation);
    }
    else if(_hedging->isHedgeOrder(orderId))
    {
      _hedging->hedgeOrderWrapper.processConfirmation(confirmation);
    }
    else
    {
      DEBUG_VARSHOW(reqQryDebugLog(),"Order confirmed for unknown OrderId",orderId);
    }
  }

  //CallBack for When an Order is Filled
  void FutFutArbitrage::onFilled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {

    reqQryDebugLog()->saveConfirmation(confirmation);

    if(isBiddingOrder(orderId))
    {
      DEBUG_MESSAGE(reqQryDebugLog(),
          "Bid Order Filled");
      DEBUG_VARSHOW(reqQryDebugLog(),
          "Traded Quantity of Bid Leg:  ",
          _commonUtilities.instrument1->getPosition()->getTradedQty(_userParams.orderMode1));

      DEBUG_VARSHOW(reqQryDebugLog(),
          "Bidding Price:  ",
          _biddingOrderWrapper.getLastQuotedPrice());
      DEBUG_MESSAGE(reqQryDebugLog(),
          dumpMktDepth(_commonUtilities.mktData1));

      _biddingOrderWrapper.processConfirmation(confirmation);
      DEBUG_FLUSH(reqQryDebugLog());
      _biddingPrice = 0;
      _lastPrice = 0;
      //Start Hedging as soon as the Bid Order is Filled
      onDefaultEvent();
    }
    else if(_hedging->isHedgeOrder(orderId))
    {
      _hedging->lastPrice = 0;
      DEBUG_MESSAGE(reqQryDebugLog(),
          "Hedge Order Filled  ");
      DEBUG_VARSHOW(reqQryDebugLog(), "Traded Quantity of Hedge Leg:  ",
          _commonUtilities.instrument2->getPosition()->getTradedQty(_userParams.orderMode2));

      DEBUG_VARSHOW(reqQryDebugLog(),
          "Hedge Price:  ",
          _hedging->hedgeOrderWrapper.getLastQuotedPrice());
      DEBUG_MESSAGE(reqQryDebugLog(),
          dumpMktDepth(_commonUtilities.mktData2));
      _hedging->hedgeOrderWrapper.processConfirmation(confirmation);
      //Update Custom Tracker
      sendUpdateResponse();
      _hedging->hedgingPrice.resetTimer();

    }
    else
    {
      DEBUG_VARSHOW(reqQryDebugLog(),"Order filled for unknown OrderId",orderId);
    }

    //Terminate if all the lots are traded
    if(( (_hedging->getHedgePositions() * _commonUtilities.ratio1) >=
          (_userParams.totalQuantity * _commonUtilities.ratio2)) )
    {
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY);
      return;
    }
  }

  //CallBack for When an Order is Partially Filled
  void FutFutArbitrage::onPartialFill(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    reqQryDebugLog()->saveConfirmation(confirmation);
    if(isBiddingOrder(orderId))
    {
      _biddingOrderWrapper.processConfirmation(confirmation);
      DEBUG_MESSAGE(reqQryDebugLog(), "Bid Order Partial Filled  ");
    }
    else if(_hedging->isHedgeOrder(orderId))
    {
      _hedging->hedgeOrderWrapper.processConfirmation(confirmation);
      DEBUG_MESSAGE(reqQryDebugLog(), "Hedge Order Partial Filled  ");
    }
    else
    {
      DEBUG_VARSHOW(reqQryDebugLog(),"Order partial filled for unknown OrderId",orderId);
    }
  }

  //CallBack for When an Order is Canceled
  void FutFutArbitrage::onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    reqQryDebugLog()->saveConfirmation(confirmation);
    //Modify Strategy if Flag is True and the Bid Leg Confirmed Order Was cancelled
    if(isBiddingOrder(orderId))
    {
      _lastPrice = 0;
      _biddingOrderWrapper.processConfirmation(confirmation);
    }
    else if(_hedging->isHedgeOrder(orderId))
    {
      _hedging->lastPrice = 0;
      DEBUG_MESSAGE(reqQryDebugLog(), "Hedge Order Cancelled  ");
      _hedging->hedgeOrderWrapper.processConfirmation(confirmation);
      if(_hedging->orderValidity == API2::CONSTANTS::CMD_OrderValidity_DAY)
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Place market order");
        _hedging->orderValidity = API2::CONSTANTS::CMD_OrderValidity_IOC;
      }
      else
      {
        DEBUG_MESSAGE(reqQryDebugLog(), "Terminate strategy due to cancelled order");
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
      }
    }
    else
    {
      DEBUG_VARSHOW(reqQryDebugLog(),"Order cancelled for unknown OrderId",orderId);
    }
  }

  //CallBack for When an Order is Replaced
  void FutFutArbitrage::onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    reqQryDebugLog()->saveConfirmation(confirmation);
    if(isBiddingOrder(orderId))
    {
      _biddingOrderWrapper.processConfirmation(confirmation);
    }
    else if(_hedging->isHedgeOrder(orderId))
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Hedge Order Replaced  ");
      _hedging->hedgeOrderWrapper.processConfirmation(confirmation);
      _hedging->hedgeOrderWrapper._orderValidity = API2::CONSTANTS::CMD_OrderValidity_DAY;
    }
    else
    {
      DEBUG_VARSHOW(reqQryDebugLog(),"Order replaced for unknown OrderId",orderId);
    }

  }

  //CallBack for When an Order's Replace Request is rejected
  void FutFutArbitrage::onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    if(isBiddingOrder(orderId))
    {
      _lastPrice = _biddingOrderWrapper.getLastPrice();
      _biddingOrderWrapper.processConfirmation(confirmation);
    }
    else if(_hedging->isHedgeOrder(orderId))
    {
      _hedging->lastPrice = _hedging->hedgeOrderWrapper.getLastPrice();
      DEBUG_MESSAGE(reqQryDebugLog(), "Hedge Order Replace Rejected  ");
      _hedging->hedgeOrderWrapper.processConfirmation(confirmation);
    }
    else
    {
      DEBUG_VARSHOW(reqQryDebugLog(),"Order replace reejcted for unknown OrderId",orderId);
    }
  }

  //CallBack for When an Order's Cancel Request is rejected
  void FutFutArbitrage::onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    reqQryDebugLog()->saveConfirmation(confirmation);
    if(isBiddingOrder(orderId))
    {
      _biddingOrderWrapper.processConfirmation(confirmation);
    }
    else if(_hedging->isHedgeOrder(orderId))
    {
      DEBUG_MESSAGE(reqQryDebugLog(), "Hedge Order Cancel Rejected  ");
      _hedging->hedgeOrderWrapper.processConfirmation(confirmation);
    }
    else
    {
      DEBUG_VARSHOW(reqQryDebugLog(),"Order cancel rejected for unknown OrderId",orderId);
    }

  }

  //CallBack for When a new Order is Rejected
  void FutFutArbitrage::onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId)
  {
    reqQryDebugLog()->saveConfirmation(confirmation);
    if(isBiddingOrder(orderId))
    {
      _biddingOrderWrapper.processConfirmation(confirmation);
    }
    else if(_hedging->isHedgeOrder(orderId))
    {
      _hedging->hedgeOrderWrapper.processConfirmation(confirmation);
    }
    else
    {
      DEBUG_VARSHOW(reqQryDebugLog(),"Order rejected for unknown OrderId",orderId);
    }
    DEBUG_MESSAGE(reqQryDebugLog(),"On New Reject,terminate strategy");
    terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
  }

  //Strategy is Terminated from Front End
  void FutFutArbitrage::onCMDTerminateStartegy()
  {
    DEBUG_MESSAGE(reqQryDebugLog()," Received Terminate Command from Frontend");
    //if bid Order is confirmed but not filled
    if(_biddingOrderWrapper.getLastQuantity() &&
        _biddingOrderWrapper.getLastFilledQuantity())
    {
      _isTerminate = true;
      _biddingOrderWrapper.cancelOrder(_riskStatus);
      return;
    }

    //if Bid Order is Pending
    //if Bid Order is Partially Filled
    //if Hedge Order is Not Confirmed
    //if Hedge Order is Parially Filled
    else if(_biddingOrderWrapper.isOrderOpen() ||
        _hedging->hedgeOrderWrapper.isOrderPending() ||
        !isIterationComplete())
    {
      _isTerminate = true;
      return;
    }
    terminateStrategyComment(API2::CONSTANTS::CMD_CommandCategory_TERMINATE_STRATEGY);
  }


  //Start Bidding
  bool FutFutArbitrage::startBidding()
  {
    if(_biddingOrderWrapper.isOrderPending())
      return true;

    _biddingPrice = getBiddingPrice();
    if(_biddingPrice < 0 || !checkSpread())
    {
      if(_biddingOrderWrapper.getLastQuantity())
      {
        if(_biddingOrderWrapper.cancelOrder(_riskStatus))
        {
          DEBUG_MESSAGE(  reqQryDebugLog(),"Bid order Cancel request Sucess");
        }
        else
        {
          if(_riskStatus != API2::CONSTANTS::RSP_RiskStatus_MAX)
            DEBUG_VARSHOW(reqQryDebugLog(),"Risk Status: ",_riskStatus);
          DEBUG_MESSAGE( reqQryDebugLog(),"Bid order Cancel request failed");
        }
      }
    }

    API2::DATA_TYPES::QTY iterationQty = _userParams.perOrderQuantity;
    if(iterationQty > (_userParams.totalQuantity - getBidPositions()))
      iterationQty = _userParams.totalQuantity - getBidPositions() + _biddingOrderWrapper.getLastFilledQuantity();
    
    if((_biddingPrice != _lastPrice))
    {
      if(API2::COMMON::placeOrReplaceOrder(_biddingOrderWrapper,
            _riskStatus,
            _biddingPrice,
            iterationQty,
            _commonUtilities.checkBasicChecks,
            _biddingFreezeQty) )
      {
        _lastPrice = _biddingPrice ;
        DEBUG_MESSAGE(  reqQryDebugLog(),"Bid order request Successful");
        return true;
      }
      else
      {
        DEBUG_MESSAGE( reqQryDebugLog(),"Bid order request failed");
        terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
        return false;
      }
    }
    return false;

  }

  //Modify Strategy
  bool FutFutArbitrage::modifyStrategy()
  {
    _isModify = false;
    if(!mapModParameters())
    {
      dump(_userParams);
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return false;
    }
    dump(_userParams);
    if(!_hedging->hedgingPrice.setDefaultsOfPrice(&_commonUtilities,&_userParams))
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"_commonUtilities was NULL while Modify");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return false;
    }
    return true;

  }


  /* ---------------------------------------------Implementation Functions --------------------------------------------------*/


  //The First Callback is Recieved here, and our Strategy is Registered
  void FutFutArbitrage::bidDriver(void *params)
  {

    API2::StrategyParameters *sgParams = (API2::StrategyParameters *) params;
    boost::shared_ptr<API2::SGContext> obj (new FutFutArbitrage(sgParams));
    /**
     * @brief reqStartAlgo function call to Start the Strategy
     * @param marketDataEventRequired Set True to register for call-backs on Market-Data Event on registered Instruments [Required]
     * @param tradeTicksEventRequired Set True to register for call-backs on Trade Tick Events on registered Instruments [Required]
     * @param preTradeEventRequired Set True to register for call-backs for pre trade confirmations [Default is false]
     * @param isConvertToManualOrder Set True if you want your open order's to persist after termination of algo. Order will start behaving like manual order. [Default is false]
     * @param childConfirmationEvent Set True to register for call-backs for confirmations coming from child strategy [Default is false]
     * * @return
     */
    obj->reqStartAlgo(true, false);
    API2::SGContext::registerStrategy(obj);
    DEBUG_MESSAGE(obj->reqQryDebugLog(),"Strategy Registered!");
    // DEBUG_FLUSH(obj->reqQryDebugLog());

    obj->reqTimerEvent(10000);
  }

  //Set modified Internal parameters
  bool FutFutArbitrage::setModifiedInternalParameters(API2::UserParams *customParams, FrontEndParameters &userParams)
  {
    FILL_PARAMS("TotalQuantity",userParams.totalQuantity);
    FILL_PARAMS("OrderQuantity",userParams.perOrderQuantity);
    FILL_PARAMS("Market Percentage",userParams.marketPercentage);
    FILL_PARAMS("Desired Spread",userParams.desiredSpread);
    DEBUG_VARSHOW(reqQryDebugLog(),"TotalQuantity",userParams.totalQuantity);
    DEBUG_VARSHOW(reqQryDebugLog(),"OrderQuantity",userParams.perOrderQuantity);
    DEBUG_VARSHOW(reqQryDebugLog(),"Market Percentage",userParams.marketPercentage);
    DEBUG_VARSHOW(reqQryDebugLog(),"Desired Spread",userParams.desiredSpread);
    return true;
  }

  //Set our Parameter Structure
  bool FutFutArbitrage::setInternalParameters(API2::UserParams *customParams, FrontEndParameters &userParams)
  {
    char tempValue;
    FILL_PARAMS("SYMBOL LEG1",userParams.symbol1);
    FILL_PARAMS("Order Mode 1",tempValue);
    userParams.orderMode1 = (API2::DATA_TYPES::OrderMode)tempValue;
    FILL_PARAMS("SYMBOL LEG2",userParams.symbol2);
    FILL_PARAMS("Order Mode 2",tempValue);
    userParams.orderMode2 = (API2::DATA_TYPES::OrderMode)tempValue;
    FILL_PARAMS("TotalQuantity",userParams.totalQuantity);
    FILL_PARAMS("OrderQuantity",userParams.perOrderQuantity);
    FILL_PARAMS("Market Percentage",userParams.marketPercentage);
    FILL_PARAMS("Desired Spread",userParams.desiredSpread);
    FILL_PARAMS("Hedge Method",tempValue);
    userParams.hedgingMethod = (HedgeMethod)tempValue;
    FILL_PARAMS("isTBT",userParams.isTBT);
    FILL_PARAMS("Acc Detail 1",userParams.account1);
    FILL_PARAMS("Acc Detail 2",userParams.account2);
    userParams.strategyID = customParams->getStrategyId();
    dump(userParams);
    return true;
  }

  //FutFutArbitrage Init Function
  bool FutFutArbitrage::init()
  {
    try
    {
      // Create Instrument, Subscribe to it's Market Data and Create an OrderWrapper for it

      /*
         Parameters for createNewInstrument
         [Required](Symbol, (bool)reqMarketData, (bool) Subscribe to Snapshot Feed), (bool) Subscribe to TBT Data,
         */

      _commonUtilities.instrument1 =  createNewInstrument(_userParams.symbol1,
          true,
          !_userParams.isTBT,                                                      
          _userParams.isTBT);

      _commonUtilities.mktData1 =  reqQryUpdateMarketData(_userParams.symbol1);

      /*
         Parameters for Order Wrapper
         [Required](Instrument, OrderMode Buy/Sell, pointer object of SGContext, Account)
         [Optional/Check API to see Default Values](Order Type Limit/Market, Order Validity Day/IOC, etc)
         */
      _biddingOrderWrapper = API2::COMMON::OrderWrapper(_commonUtilities.instrument1,
          _userParams.orderMode1,
          this,
          _userParams.account1
          );
      if(_commonUtilities.checkBasicChecks)
      {
        _biddingFreezeQty = getFreezeQty( 
            _commonUtilities.instrument1->getStaticData()->symbol,
            _commonUtilities.instrument1->getStaticData()->exchangeId ,
            _commonUtilities.instrument1->getStaticData()->securityType,
            _commonUtilities.instrument1->getStaticData()->groupName );
      }

    }
    catch(API2::MarketDataSubscriptionFailedException& e)
    {
      DEBUG_VARSHOW(reqQryDebugLog(), "Symbol ID: ", _userParams.symbol1);
      if(_userParams.isTBT)
      {
        DEBUG_MESSAGE(reqQryDebugLog(),"TBT subscription Failed For Leg1");
      }
      else
      {
        DEBUG_MESSAGE(reqQryDebugLog(),"Snapshot subscription Failed For Leg1");
      }
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return false;
    }
    catch(API2::InstrumentNotFoundException &e)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Instrument Not Found For Leg1");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return false;
    }

    catch(std::exception &e)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"standard exception raised with Bidding");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
      return false;
    }
    return true;
  }


  //dump function to flush our FrontEnd Values
  void FutFutArbitrage::dump(FrontEndParameters &params)
  {
    DEBUG_VARSHOW(reqQryDebugLog(),"SYMBOL LEG1",(int)params.symbol1);
    DEBUG_VARSHOW(reqQryDebugLog(),"SYMBOL LEG2",params.symbol2);
    DEBUG_VARSHOW(reqQryDebugLog(),"TotalQuantity",params.totalQuantity);
    DEBUG_VARSHOW(reqQryDebugLog(),"OrderQuantity",params.perOrderQuantity);
    DEBUG_VARSHOW(reqQryDebugLog(),"Market Percentage",params.marketPercentage);
    DEBUG_VARSHOW(reqQryDebugLog(),"Desired Spread",params.desiredSpread);
    DEBUG_VARSHOW(reqQryDebugLog(),"Order Mode 1",(API2::DATA_TYPES::OrderMode)params.orderMode1);
    DEBUG_VARSHOW(reqQryDebugLog(),"Order Mode 2",(API2::DATA_TYPES::OrderMode)params.orderMode2);
    DEBUG_VARSHOW(reqQryDebugLog(),"Hedge Method",int(params.hedgingMethod));
  }

  //Strategy modified from FrontEnd
  void FutFutArbitrage::onCMDModifyStrategy(API2::AbstractUserParams* newParams)
  {
    if(_terminateCheck) return;

    API2::UserParams* customParams = (API2::UserParams*) newParams;
    DEBUG_MESSAGE(reqQryDebugLog(),"Modifying strategy");
    if(!setModifiedInternalParameters(customParams, _modUserParams))
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Parameters not set from front end");
      dump( _modUserParams );
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
      return;
    }

    //if bid Order is confirmed but not filled
    if(_biddingOrderWrapper.getLastFilledQuantity() == 0 &&
        _biddingOrderWrapper.getLastQuantity())
    {
      _isModify = true;
      _biddingOrderWrapper.cancelOrder(_riskStatus);
    }

    //if Bid Order is Pending
    //if Bid Order is Partially Filled
    //if Hedge Order is Not Confirmed
    //if Hedge Order is Parially Filled
    else if(_biddingOrderWrapper.isOrderOpen() ||
        _hedging->hedgeOrderWrapper.isOrderPending() ||
        !isIterationComplete())
    {
      _isModify = true;
    }
    reqSendStrategyResponse(
        API2::CONSTANTS::RSP_ResponseType_STRATEGY_RUNNING,
        API2::CONSTANTS::RSP_RiskStatus_SUCCESS,
        API2::CONSTANTS::RSP_StrategyComment_USER_INPUT);
  }

  bool FutFutArbitrage::mapModParameters()
  {
    if(getBidPositions() > _modUserParams.totalQuantity ||
        _modUserParams.perOrderQuantity > _modUserParams.totalQuantity)
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Order Quantity is incorrect");
      return false;
    }
    _userParams.totalQuantity = _modUserParams.totalQuantity;
    _userParams.perOrderQuantity = _modUserParams.perOrderQuantity;
    _userParams.desiredSpread = _modUserParams.desiredSpread;
    _userParams.marketPercentage = _modUserParams.marketPercentage;
    return true;
  }

  //Get bid instrument Positions
  API2::DATA_TYPES::QTY FutFutArbitrage::getBidPositions() const
  {
    return _commonUtilities.instrument1->getPosition()->getTradedQty( _userParams.orderMode1);
  }

  //Check if any order Confirmation is Pending
  bool FutFutArbitrage::isAnyOrderConfirmationPending()
  {
    return ( (_biddingOrderWrapper.isOrderPending()) ||
        (_hedging->hedgeOrderWrapper.isOrderPending()) );
  }

  //Check is all lots are traded
  bool FutFutArbitrage::isAllLotsTraded()
  {
    return ((_hedging->getHedgePositions() >=
          (_userParams.totalQuantity * _commonUtilities.ratio2) / _commonUtilities.ratio1) &&
        (getBidPositions() == _userParams.totalQuantity));
  }

  //Calculate Ratio of Bid Qty and hedge Quantity
  void FutFutArbitrage::calculateRatio()
  {
    _commonUtilities.ratio1 = getBiddingLotSize() / std::__gcd( getBiddingLotSize(),_hedging->getLotSize());
    DEBUG_VARSHOW(reqQryDebugLog(), "ratio1: ", _commonUtilities.ratio1);
    _commonUtilities.ratio2 = _hedging->getLotSize() / std::__gcd(getBiddingLotSize(),_hedging->getLotSize());
    DEBUG_VARSHOW(reqQryDebugLog(), "ratio2: ", _commonUtilities.ratio2)

  }

  //Terminate Strategy Comment
  void FutFutArbitrage::terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment)
  {
    if(_terminateCheck) return;

    _terminateCheck = true;

    reqAddStrategyComment(comment);

    reqTerminateStrategy(true);
  }

  //check the Spread Value
  bool FutFutArbitrage::checkSpread()
  {
    API2::DATA_TYPES::PRICE temp = getSpread();
    if( !((temp) > _userParams.desiredSpread) ||
        !((temp) > -_userParams.desiredSpread ) )
    {
      _achievedSpread = temp;
      return true;
    }
    return false;
  }


  //return spread
  API2::DATA_TYPES::PRICE FutFutArbitrage::getSpread()
  {
    if(_userParams.orderMode1 == API2::CONSTANTS::CMD_OrderMode_BUY)
    {
      return  _commonUtilities.mktData2->getBidPrice(0) - _commonUtilities.mktData1->getAskPrice(0);
    }
    else
    {
      return _commonUtilities.mktData1->getBidPrice(0) - _commonUtilities.mktData2->getAskPrice(0)  ;
    }
    return 0;
  }

  //Check if order Id is of Bidding
  bool FutFutArbitrage::isBiddingOrder(API2::COMMON::OrderId *orderId)
  {
    return (orderId == _biddingOrderWrapper._orderId);
  }

  //Update our Custom Tracker
  void FutFutArbitrage::sendUpdateResponse()
  {
    std::list <std::string> list;
    double desiredSpread = _userParams.desiredSpread / pow(10,_commonUtilities.instrument1->getStaticData()->scripPrecision);
    double achievedSpread = _achievedSpread / pow(10,_commonUtilities.instrument1->getStaticData()->scripPrecision);
    std::string str =
      std::to_string(desiredSpread) +
      "," +
      std::to_string(achievedSpread);
    std::string customData = str;
    if( !reqQrySendCustomResponse( customData, list, _rowId++ ) )
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Unable to send custom response to frontend");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
    }

  }

  //Update our FrontEnd Spread Viewer
  void FutFutArbitrage::sendSpreadResponse()
  {
    std::list< std::string > list;

    std::string str = "currentSpread:" + std::to_string( (long long) getSpread()) ;
    list.push_back( str );
    std::string customData;
    if( !reqQrySendCustomResponse( customData, list, 0 ) )
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Unable to send custom response to frontend");
      terminateStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE );
    }

  }


  //return lot size of the bidding instrument
  API2::DATA_TYPES::QTY FutFutArbitrage::getBiddingLotSize() const
  {
    return _commonUtilities.instrument1->getStaticData()->marketLot;
  }


  //return price at which to order
  API2::DATA_TYPES::PRICE FutFutArbitrage::getBiddingPrice()
  {
    API2::DATA_TYPES::PRICE temp =  0;
    _commonUtilities.mktData2 = reqQryUpdateMarketData(_userParams.symbol2);
    if( _userParams.orderMode1 == API2::CONSTANTS::CMD_OrderMode_BUY)
    {
      temp  = (_commonUtilities.mktData2->getBidPrice(0) - _userParams.desiredSpread);
    }

    else
    {
      temp  = (_commonUtilities.mktData2->getAskPrice(0) + _userParams.desiredSpread);
    }

    if(temp > 0)
    {
      API2::SharedUtilities::roundPriceToTick(temp,
          _userParams.orderMode1,
          *(_commonUtilities.instrument1->getStaticData()));
      return temp;
    }
    else if (temp <= 0) 
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Bidding price is negative or zero");
      return 0;
    }
    return temp;

  }

  //Set Timer for sendSpreadResponse
  void FutFutArbitrage::setTimer()
  {
    _timer.clearTimer();
    _timer.setTimer(_timeExpiry);
  }

  //check if the Timer is Expired
  bool FutFutArbitrage::isTimerExpired()
  {
    return _timer.isTimerExpired();
  }


  //check if the Market Depth/Data is Available
  bool FutFutArbitrage::isMarketDepthAvailableForBid()
  {
    if(API2::COMMON::isMarketDepthAvailable(_commonUtilities.mktData1))
      return true;
    else
    {
      DEBUG_MESSAGE(reqQryDebugLog(),"Wait!, Market Depth is Empty of Bid");
      //DEBUG_FLUSH(reqQryDebugLog());
      return false;
    }
  }

  //check if the Bid Order is in Pending State
  bool FutFutArbitrage::isOpenOrder()
  {
    return _biddingOrderWrapper.getLastFilledQuantity();
  }


  //Check if any Order is in Open State
  bool FutFutArbitrage::isAnyOrderOpen()
  {
    return (isOpenOrder() ||
        _hedging->isOpenOrder());
  }

  //check if an iteration is complete
  bool FutFutArbitrage::isIterationComplete()
  {
    return ((getBidPositions()*_commonUtilities.ratio2) ==
        (_hedging->getHedgePositions()*_commonUtilities.ratio1));
  }

  //Dump Market Depth
  std::string FutFutArbitrage::dumpMktDepth(API2::COMMON::MktData *mktData)
  {
    std::ostringstream oss;
    auto &quote = mktData->getRefQuote();
    for(size_t i=0; i< API2::CONSTANTS::MarketDepthArraySize;i++)
    {
      oss<<quote.MarketDepth[i].toString();
    }
    return oss.str();
  }

  //read Parameters from a file
  //For Bypass and the NUmber of Ticks for Hedge Leg
  void FutFutArbitrage::readParamsFromFile()
  {
    namespace bpo=boost::program_options;
    bpo::options_description config("FutFutArbitrage-conf");
    config.add_options()
      ("FUT_FUT_ARBITRAGE.BYPASS_NNFID" , 
       bpo::value<short> ( & _bypass )->default_value(0),
       "If enabled ByPass NNFID for InterExchange strategy w.r.t NSE")
      ("FUT_FUT_ARBITRAGE.TICKS" , 
       bpo::value<int> ( & _hedging->hedgingPrice.ticks )->default_value(1),
       "Number of Ticks for Best Bid/ASk Hedge")
      ("FUT_FUT_ARBITRAGE.CHECK_BASIC_CHECKS" , 
       bpo::value<bool> ( & _checkBasicChecks )->default_value(0),
       "Check Basic Checks before placing order like DPR check,TER check,freeze qty check")
      ;
    std::string configFile = "./config/FutFutArbitrage.txt";
    bpo::options_description configFileOptions;
    configFileOptions.add(config);

    bpo::variables_map variableMap;
    std::ifstream file(configFile.c_str());
    store ( parse_config_file ( file, configFileOptions, true), variableMap);
    bpo::notify( variableMap );
  }

}


/*
 *@brief This is a demo strategy to Demonstrate how a basic strategy is created and proceeds
 *@brief This is a Sample for support of Arbitrage with two Future Instruments
 *
 *@features-strategy The Strategy Works on Interexchange, Reads Config file for Algo Id
 *@features-orderPlacing There is a common Function for a New Order or a Replace order
 *@features-orderPlacing It Contains of Common Checks like if order is pending, Daily Price Range, Trade Execution Range and Freeze Quantity breach
 *@features-Bidding If no order is complete or our hedging is Complete, the strategy Places a Bid order for the quantity Provided from FrontEnd
 *@features-Hedging If the Bid order is Filled Strategy Starts Hedging
 *@features-Hedging Two Hedge Methods are supported, Best Bid/Ask and Market Percentage
 *@features-Hedging For BBA, if the hedge Timer Expires, the method is switched to Market Percentage till the order is filled.
 *@features-terminate If the Strategy is terminated from frontend, the strategy Waits for the iteration to complete
 *@features-terminate If Any order is pending or partially Filled, only if Bid order is in Confirmation State
 *@features-terminate The Order is canceled and the strategy is terminated
 *@features-modify If the Strategy is modified from frontend, the strategy Waits for the iteration to complete
 *@features-modify If Any order is pending or partially Filled, only if Bid order is in Confirmation State
 *@features-modify The Order is canceled and the strategy is terminated
 *@features-tracker After each iteration, the custom Tracker is updated which shows the spread at which the arbitrage was done
 *@features-spreadValue In the GUI form, After every 10secs the current spread is updated for the User to know the Market Spread
 *
 *@workflow When the strategy is registered, an initial request to TimerEvent is Made, which in return loops the request to Timer Event
 *@workflow and call onDefaultEvent which handles our Bidding and Headging, it checks if the strategy is Complete, if marketData is available etc.
 *@workflow When a Bid order is Filled, strategy is supposed to start Headging based on the hedge method selected from FrontEnd
 *
 *@example Symbol1 = Reliance, Symbol2 = Axis Bank, LotSize1=1000,LotSize2=1200, Total Order Quantity 5000
 *@example Symbol1 Price Rs102.00, Symbol2 Price Rs100.00, desiredSpread = Rs 1.00, Current Spread  Rs2.0
 *@example Our Strategy Starts bidding and places a bid order for (Bid Price of Axis - Desired Spread) i.e Rs 99.0
 *@example When the Bid Order is Filled the strategy starts to hedge. Suppose the Hedge Method is Best Bid/Ask
 *@example price at which hedge order is made is (Ask of Symbol2 - (staticTickSize * No. of ticks entered from Frotend))
 *@example which is 99.95 assuming defaults, the strategy waits for this to fill, if not; the hedge method Changes
 *@example and a replace order is placed for Rs 99, thinking 1% was entered from frontend and waits for the Order to Fill on 1200 quantity
 *@example Suppose a partial fill was recieved, but the strategy waits for the hedge to complete before bidding and vice versa
 *@example so, the strategy goes untill all the lots are traded, i.e 5000 Reliance and 6000Axis bank
 *
 *note For the support of multi-threading, please keep the strategy workflow to a single thread, like order placing
 *note receiveing, registering strategy and marketData, creating objects, instruments, etc
 *note Other Modular functions like price calculation, Timer or other implementation can be multi-threaded
 *
 */
