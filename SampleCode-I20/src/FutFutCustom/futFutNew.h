#ifndef FUTFUTNEW_H
#define FUTFUTNEW_H

#include "../common/common.h"
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <sgContext.h>
#include <cmdDefines.h>
#include "structure.h"
#include "price.h"
#include "futFutNewHedging.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

namespace SampleFutFutArbitrage{

enum class HedgeMethod
{
  HedgeMethod_BEST_BID_ASK,
  HegdeMethod_MarketOrder,
  HedgeMethod_MAX
};

struct FrontEndParameters
{
  API2::DATA_TYPES::SYMBOL_ID symbol1;
  API2::DATA_TYPES::SYMBOL_ID symbol2;
  API2::DATA_TYPES::QTY totalQuantity;
  API2::DATA_TYPES::QTY perOrderQuantity;
  HedgeMethod hedgingMethod;
  SIGNED_LONG marketPercentage;
  SIGNED_LONG desiredSpread;
  API2::DATA_TYPES::OrderMode orderMode1;
  API2::DATA_TYPES::OrderMode orderMode2;
  char isTBT;
  API2::AccountDetail account1;
  API2::AccountDetail account2;
  SIGNED_INTEGER strategyID;
  FrontEndParameters():
    symbol1(0),
    symbol2(0),
    totalQuantity(0),
    perOrderQuantity(0),
    hedgingMethod(HedgeMethod::HedgeMethod_MAX),
    marketPercentage(0.0),
    desiredSpread(0.0),
    orderMode1(API2::CONSTANTS::CMD_OrderMode_MAX),
    orderMode2(API2::CONSTANTS::CMD_OrderMode_MAX),
    isTBT(0),
    strategyID(0)
  {
  }
};


  /**
 * @brief Derived from SGContext, this class Drives our strategy through callbacks
 * @brief Handle the Bidding leg
 * @brief FrontEndParameters Structure
 */

class FutFutArbitrage : public API2::SGContext
{

    /**
     * @brief Save Parameters Received from FrontEnd
     * @returnType FrontEndParameters Structure
     */
    FrontEndParameters _userParams;

    /**
     * @brief Save Modified Parameters Received from FronEnd
     * @returnType FrontEndParameters Structure
     */
    FrontEndParameters _modUserParams;

    /**
     * @brief riskStatus
     * @returnType riskStatus
     */
    API2::DATA_TYPES::RiskStatus _riskStatus;

    /**
     * @brief customResponse RowID
     * @returnType int
     */
    int _rowId;

    /**
     * @brief Bidding Order Wrapper
     * @returnType OrderWrapper
     */
    API2::COMMON::OrderWrapper _biddingOrderWrapper;

    /**
     * @brief Bidding Price
     * @returnType Price
     */
    API2::DATA_TYPES::PRICE _biddingPrice;

    /**
     * @brief Last Price
     * @returnType Price
     */
    API2::DATA_TYPES::PRICE _lastPrice;

    /**
     * @brief achieved Spread
     * @returnType Price
     */
    API2::DATA_TYPES::PRICE _achievedSpread;

    /**
     * @brief Hedging Class Object to access Hedging Members
     * @returnType Hedging Class Pointer
     */
    Hedging *_hedging;

    /**
     * @brief Flag to Maintain Terminate State
     * @returnType Boolean
     */
    bool _terminateCheck;

    /**
     * @brief Flag to infer if FrontEnd Parameters have Been Modified
     * @returnType Boolean
     */
    bool _isModify;

    /**
     * @brief Flag to infer if Strategy has been terminated from FrontEnd
     * @returnType boolean
     */
    bool _isTerminate;

    /**
     * @brief Utilities Structure Object to access common Utilities
     * @returnType  Utilities Structure
     */
    Utilities _commonUtilities;

    /**
     * @brief Last Order Quantity
     * @returnType PI2::DATA_TYPES::QTY
     */
    API2::DATA_TYPES::QTY _lastOrderQuantity;

    /**
     * @brief Object of sgTimer Class
     * @returnType Timer Class Object
     */
    API2::TIMER::Timer _timer;

    /**
     * @brief checkBasicChecks
     * check Basic checks before placing order like DPR check,TER check,freeze qty check
     */
    bool _checkBasicChecks;

    /**
     * @brief DO we bypass for Interexhange
     * @returnType short
     */
    short _bypass;

    /**
     * @brief const Timer Expiry
     * @returnType unsigned int
     */
    const unsigned int _timeExpiry;
 
    /**
     * @brief Bidding Freeze Qty
     */
    API2::DATA_TYPES::QTY _biddingFreezeQty;

public:

    /**
     * @brief Constructor
     * @param pointer to StrategyParameters
     */
    FutFutArbitrage(API2::StrategyParameters* params);

    /**
     * @brief Destructor
     */
    ~FutFutArbitrage()
    {
      if(_hedging)
      {
        delete _hedging;
        _hedging = nullptr;
      }
    }


/* ---------------------------------------------Implementation Functions --------------------------------------------------*/

    /**
     * @type Implementation Function
     * @brief Register Our Strategy with shared Object of this class
     * @param Void Pointer
     * @return void
     */
    static void bidDriver(void *);

    /**
     * @type Implementation Function
     * @brief Maps Values from Frontend to our Structure Object of FrontEndParameters
     * @param customParams
     * @param userParams
     * @return Boolean
     */
    bool setInternalParameters(API2::UserParams *customParams,FrontEndParameters &userParams);

    /**
     * @type Implementation Function
     * @brief Maps Values from Frontend to our Structure Object of FrontEndParameters
     * @param customParams
     * @param userParams
     * @return Boolean
     */
    bool setModifiedInternalParameters(API2::UserParams *customParams,FrontEndParameters &userParams);

    /**
     * @type Implementation Function
     * @brief Initialize and subscribe our, Instrument and Market Data
     * @return Boolean
     */
    bool init();

    /**
     * @type Implementation Function
     * @brief Terminate Strategy and turn _terminateCheck to True
     * @param StrategyComment
     * @return void
     */
    void terminateStrategyComment(API2::DATA_TYPES::StrategyComment comment);

    /**
     * @type Implementation Function
     * @brief Initialize Modifying Strategy, when signaled from FrontEnd
     * @param newParams
     * @return void
     */
    void onCMDModifyStrategy(API2::AbstractUserParams* newParams) override;

    /**
     * @type Implementation Function
     * @brief Calculate and Initialize Ratio based on Lot Sizes of Both the Symbols
     * @return void
     */
    void calculateRatio();

    /**
     * @type Implementation Function
     * @brief Calculate and Check if current spread is greater or equal to desired Spread
     * @return Boolean
     */
    bool checkSpread();

    /**
     * @type Implementation Function
     * @brief Map Modified Params to our current FrontEndParams Structure Object
     * @return void
     */
    bool mapModParameters();

    /**
     * @type Implementation Function
     * @brief Checks if confirmation from any leg is yet to Happen
     * @return Boolean
     */
    bool isAnyOrderConfirmationPending();

    /**
     * @type Implementation Function
     * @brief Checks if all the lots are traded of Bid Leg and in equal Proportion to Hedging Leg
     * @return Boolean
     */
    bool isAllLotsTraded();

    /**
     * @type Implementation Function
     * @brief Checks if the Order is of Bidding Leg
     * @param OrderId
     * @return Boolean
     */
    bool isBiddingOrder(API2::COMMON::OrderId *orderId);

    /**
     * @type Implementation Function
     * @brief Checks if bidding Order is in open state
     * @return Boolean
     */
    bool isOpenOrder();

    /**
     * @type Implementation Function
     * @brief Checks if any order is Open
     * @return Boolean
     */
    bool isAnyOrderOpen();

    /**
     * @type Implementation Function
     * @brief Checks if iteration is complete
     * @return Boolean
     */
    bool isIterationComplete();
    
    /**
     * @type Implementation Function
     * @brief Dump the current saved FrontEnd values
     */
    void dump(FrontEndParameters &params);

    /**
     * @type Implementation Function
     * @brief Send Updated Custom Response
     * @return void
     */
    void sendUpdateResponse();

    /**
     * @type Implementation Function/Getter
     * @brief retrive the static lotSize of the Subscribed Symbol
     * @return Quantity
     */
    API2::DATA_TYPES::QTY getBiddingLotSize() const;

    /**
     * @type Implementation Function
     * @brief Get/Calculate our Bidding Price based on Spread
     * @return Price
     */
    API2::DATA_TYPES::PRICE getBiddingPrice();

    /**
     * @type Implementation Function/Getter
     * @brief Get/Calculate total quantity traded of bid leg
     * @return API2::DATA_TYPES::QTY
     */
    API2::DATA_TYPES::QTY getBidPositions() const;
    
    /**
     * @type Implementation Function/getter
     * @brief get currentSpread
     * @return void
     */
    API2::DATA_TYPES::PRICE getSpread();

    /**
     * @type Implementation Function
     * @brief send custom Response for SPread
     * @return void
     */
    void sendSpreadResponse();

    /**
     *
     * @type Implementation Function
     * @brief setTimer
     */
    void setTimer();

    /**
     * @type Implementation Function
     * @brief checks if 10seconds has passed
     * @return bool
     */
    bool isTimerExpired();

    /**
     * @type Implementation Function
     * @brief checks if Market Depth is Available for Bid
     * @return bool
     */
    bool isMarketDepthAvailableForBid();

    /**
     * @type Implementation Function
     * @brief Dump Market Depth
     * @params mkData
     * @return void
     */
    std::string dumpMktDepth(API2::COMMON::MktData *mktData);

    /**
     * @type Implementation Function
     * @brief Read Params for Interexchange from File
     * @return void
     */
    void readParamsFromFile();

    /**
     * @type Implementation Function
     * @brief dumpOrderLimits
     * @return void
     */
    void dumpOrderLimits();

    /**
     * @type Implementation Function
     * @brief dumpPositions
     * @return void
     */
    void dumpPositions();

    /**
     * @brief isInstrumentCreated
     * @description check if both instruments(instrument1 and instrument1) created in commonUtilities
     * @return bool
     */
    bool isInstrumentCreated();



/* ---------------------------------------------Workflow Functions --------------------------------------------------*/

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever a MarketEvent is Generated, on Subscribed Symbols via TBT or SnapShot
     * @param symbolId
     * @return void
     */
    void onMarketDataEvent(UNSIGNED_LONG symbolId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever Timer has expired of reqTimerEvent
     * @return void
     */
    void onTimerEvent() override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback from Most of the events
     * @return void
     */
    void onDefaultEvent() override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Order is Confirmed
     * @param OrderConfirmation
     * @param orderId
     * @return void
     */
    void onConfirmed(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Order is Completely Filled
     * @param OrderConfirmation
     * @param orderId
     * @return void
     */
    void onFilled(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Order is Partially  Filled
     * @param OrderConfirmation
     * @param orderId
     * @return void
     */
    void onPartialFill(API2::OrderConfirmation &confirmation,API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Order is Canceled
     * @param OrderConfirmation
     * @param orderId
     * @return void
     */
    void onCanceled(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Replace Order is Confirmed
     * @param OrderConfirmation
     * @param orderId
     * @return void
     */
    void onReplaced(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Replace Order is Confirmed
     * @param OrderConfirmation
     * @param orderId
     * @return void
     */
    void onReplaceRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an Cancel Order is Rejected
     * @param OrderConfirmation
     * @param orderId
     * @return void
     */
    void onCancelRejected(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId) override;
    
    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever an New Order is Rejected
     * @param OrderConfirmation
     * @param orderId
     * @return void
     */
    void onNewReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId) override;

    /**
     * @type WorkFlow Function/CallBack Function
     * @brief Receive a callback whenever a Strategy is terminated from FrontEnd
     * @return void
     */
    void onCMDTerminateStartegy() override;

    /**
     * @type WorkFlow Function
     * @brief Starts Bidding
     * @return Boolean
     */
    bool startBidding();
    
    /**
     * @type WorkFlow Function
     * @brief Start Modifying Strategy
     * @return Boolean
     */
    bool modifyStrategy();


};
}
#endif // FUTFUTNEW_H




