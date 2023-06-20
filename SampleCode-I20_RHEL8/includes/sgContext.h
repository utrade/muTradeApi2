#ifndef SGCONTEXT_H
#define SGCONTEXT_H

#include "sgCommon.h"
#include <sharedSingleOrder.h>
#include <sgApiParameters.h>
#include <sgDebugLogDefines.h>
#include <baseCommands.h>
#include <apiPositionStruct.h>
#include <strategyInfo.h>
#include <unordered_map>
#include <boost/unordered_set.hpp>
#include <unordered_set>
#include <string>


namespace SG
{
  struct SymbolStaticData;
}

namespace API2
{


  /**
 * \mainpage
 *
 * <h1> muTrade API Version 2.0.1 </h1>
 *
 * <p>muTrades API 2.0.1 provides algo infrastructure, which allows you to create your own latency sensitive strategies and host them in uTrade's infrastructure in exchange co-location or non co-location environment.</p>
 * <p>New custom strategies can be integrated and run in the platform on the fly with no effect on the already running strategies. They can be run from the same front-end. The user can also use any uTrade's inbuilt arbitrage, market making, and various other strategies through the same platform.</p>
 * <p>Risk Management features is also available, same as the trading platform.</p>
 * <p>Custom strategy can be run with both TBT and snapshot feed. Latest data (order book) is provided to the strategy on request-basis.</p>
 * <h1><a class="anchor" id="External"></a>
 * Links</h1>
 * <p><a href="http://utrade.github.io/muTradeApi2/apiUserManual.pdf">User Manual</a><br/>
 *  <a href="http://utrade.github.io/muTradeApi2/strategyFlow.pdf">Strategy Flow</a><br/>
 *  <a href="https://github.com/utrade/muTradeApi2/tree/master/SampleCode">Sample Strategy</a><br/>
 * <a href="http://utrade.github.io/muTradeApi2/faq.pdf">FAQ</a><br/>
 * </p>
 */

  class SGContextImpl;
 
  class CustomData;
  typedef std::shared_ptr<CustomData> CustomDataPtr;
  /**
   * @brief The SGContext class The main class to be inherited for creating a new Strategy
   */
  class SGContext
  { 
    public:

    /**
     * @brief ~SGContext
     * A destructor
     */
    virtual ~SGContext();


    /**
       * @brief SGContext Constructor
       * @param params API2::StrategyParameters
       * @param sgName Unique String for Strategy Name
       * @param useDumpingMethod : optimize debug log dumping
       */
    SGContext(StrategyParameters *params, const std::string &sgName,
        bool useDumpingMethod = false);

    static void registerStrategy(boost::shared_ptr<SGContext>);
    SGContextImpl * getSGContextImpl();
    /***********************************************************/
    /************************ Factory Calls ********************/
    /***********************************************************/

    /**
     * @brief sendCustomDataToStrategiesDealerWise - send custom data for all
     * active strategies for a dealer and provides callback for all startegies.
     * If passed dealerId is zero, then custom data will sent to all strategy
     * @param dealerId
     * @param customDataPtr shared pointer to base class CustomData
     */
    void sendCustomDataToStrategiesDealerWise(const DATA_TYPES::CLIENT_ID dealerId , 
        CustomDataPtr customDataPtr);

    /**
     * @brief receiveCustomData - CallBack to this function will be received by
     * all API strategies of a particular dealer. The function
     * sendCustomDataToStrategiesDealerWise is used to generate callback on the
     * specific dealer with specific custom data. User need to further typecast
     * the customDataPtr into its derived class.
     * @param customDataPtr shared pointer to base class CustomData
     */
    virtual void receiveCustomData(CustomDataPtr customDataPtr);

    /**
       * @brief createNewInstrument To add a new Instrument in the strategy \n
       *    The Pointer to the added Instrument is set in instrument passed as reference
       * @param symbolId System Unique ID for the Instrument as API2::DATA_TYPES::SYMBOL_ID
       * @param regMktData set True to register for Market Data for the Instrument
       * @param useSnapShot Set True if Snapshot Feed is to be used
       * @param useTbt Set True to use TBT-Feed
       * both can be registered together 
       * if both UseSnapshot and UseTbt are passed false then we will create snapshot marketData by default 
       * @param useOhlc Set True if OHLC Heed is also required
       * @param depthSize depth which need to be processed during algo execution
       * @throw MarketDataSubscriptionFailedException
       * @return COMMON::Instrument Pointer
       *
       * NOTE: In case of Indices,by default it will read data from snapshot whether strategy is running on tbt or on snapshot.
       */
      COMMON::Instrument *createNewInstrument(UNSIGNED_LONG symbolId,
                                              bool regMktData, 
                                              bool useSnapShot=true, 
                                              bool useTbt=false, 
                                              bool useOhlc=false,
                                              size_t depthSize = CONSTANTS::MarketDepthArraySize);

    /**
       * @brief createNewInstrument To add a new Instrument in the strategy \n
       *    The Pointer to the added Instrument is set in instrument passed as reference
       * @param instrumentName Instrument Name

       *        Format:
       * 				Normal Contracts and Securities
       *        [SOURCE] [EXCHANGE] [Symbol] [Expiry(YYYYMMDD)] [StrikePrice] [C/P(For Call/Put)]
       *        Example:
       *        Cash Segment: 
       *            for NSE EQ -> DEFAULT NSECM RELIANCE
       *            Other than EQ say IL -> DEFAULT NSECM RELIANCE IL
       *            for BSE A -> DEFAULT BSECM RELIANCE
       *            Other than A say BE -> DEFAULT BSECM RELIANCE BE
       *            For all other exchages, it will be "EXCH SYMBOL GR"
       *        Futures Segment: DEFAULT NSEFO RELIANCE 20140828
       *        Options Segment: DEFAULT NSEFO RELIANCE 20140828 98000 C
       *
       * 				Spread Contracts
       * 				[SOURCE] [EXCHANGE] [SYMBOL] [Expiry1(YYYYMMDD)] [Expiry2(YYYYMMDD)]
       * 				Example:
       * 				DEFAULT BSEFO RELIANCE 20151126 20151231
       *
       * 				Pair, Straddle Contracts
       * 				[SOURCE] [EXCHANGE] [SYMBOL] [Expiry1(YYYYMMDD)] [Expiry2(YYYYMMDD)] [StrikePrice] [C/P(For Call/Put)]
       * 				Example:
       * 				DEFAULT BSEFO RELIANCE 20151126 20151231 98000 C
       *
       * 				For Indices
       *        [SOURCE] [EXCHANGE] [IndexSymbolName]
       * 				Example:
       * 				DEFAULT NSECM CNX Nifty, DEFAULT NSECM BANK Nifty, DEFAULT BSECM BSE100
       *
       * @param regMktData set True to register for Market Data for the Instrument
       * @param useSnapShot Set True if Snapshot Feed is to be used
       * @param useTbt Set True to use TBT-Feed
       * both can be registered together
       * @param useOhlc Set True if OHLC Heed is also required
       * @param depthSize depth which need to be processed during algo exxecution
       * @return COMMON::Instrument Pointer
       * @throw MarketDataSubscriptionFailedException
       *
       * DEFAULT source will be replaced with TT, IB, OT etc (whichever applicable) if connecting through different broker
       *
       * NOTE: In case of Indices,by default it will read data from snapshot whether strategy is running on tbt or on snapshot.
       *
       * For esm, use ESMNSE as exchange
       * Example: DEFAULT ESMNSE RELIANCE EQ
       * NOTE:
       * There's a difference in esm and normal exchanges for cash contracts,
       * In case of ESMNSE, group name always required to be added when subscribing or getting unique id
       * In NSECM, for EQ contracts, 'EQ' will not be added in end
       * In BSECM, for A contracts, 'A' will not be added in end
       */
      COMMON::Instrument * createNewInstrument(const std::string &instrumentName,
                                               bool regMktData=false, 
                                               bool useSnapShot=true, 
                                               bool useTbt=false, 
                                               bool useOhlc=false,
                                               size_t depthSize = CONSTANTS:: MarketDepthArraySize);

    /**
       * @brief createNewOrder To create a New Order for an instrument
       * @param order Reference to Pointer of API2::SingleOrder Pointer to created object will be set into this. For creating an Order
       * @param instrument Pointer to the Instrument for which a new SingleOrder is to be created
       * @param qty Order Quantity
       * @param discQty Diclosed Order Quantity
       * @param mode OrderMode as API2::CONSTANTS::CMD_OrderMode_BUY or API2::CONSTANTS::CMD_OrderMode_SELL
       * @param type OrderType as API2::DATA_TYPES::OrderType
       * @param validity Order Validity
       * @param product Product
       * @param price Price
       * @param stopPrice Stop Price
       * @return SingleOrder Pointer
       */
    SingleOrder * createNewOrder(
                        COMMON::Instrument *instrument,
                        const UNSIGNED_LONG &qty=0,
                        const UNSIGNED_LONG &discQty=0,
                        const DATA_TYPES::OrderMode &mode=CONSTANTS::CMD_OrderMode_BUY,
                        const DATA_TYPES::OrderType &type = CONSTANTS::CMD_OrderType_LIMIT,
                        const DATA_TYPES::OrderValidity &validity = CONSTANTS::CMD_OrderValidity_DAY,
                        const DATA_TYPES::ProductType &product = CONSTANTS::CMD_ProductType_INTRADAY,
                        const SIGNED_LONG &price=0,
                        const SIGNED_LONG &stopPrice=0,
                        const UNSIGNED_INTEGER &clientId = 0
        );

    /**
       * @brief createNewOrderId Creates and Inserts a new OrderId Instance to the Instrument \n
       * for the requested OrderMode and sets the pointer to orderId
       * @param instrument should be valid and Not null
       * @param mode should be valid API2::CONSTANTS::CMD_OrderMode_BUY or API2::CONSTANTS::CMD_OrderMode_SELL
       * @return COMMON::OrderId Ptr
       */
    COMMON::OrderId * createNewOrderId(
            COMMON::Instrument *instrument,
            const API2::AccountDetail &accountDetail,
            const DATA_TYPES::OrderMode &mode
            );

    /***********************************************************/
    /************************ Request Calls ********************/
    /***********************************************************/

    /**
     * @brief reqNewSingleOrder To Send a new Order
     * @param riskStatus  - returns risk status : contains info on which rms check failed
     * @param instrument  - instrument containing symbol info on which to send order
     * @param order       - single order
     * @param orderId     - order id
     * @param isSpreadOrder - true if spread order, false otherwise
     * @param validateAccountDetail - true if account detail validation required in rms, false otherwise
     * @return
     */
    bool reqNewSingleOrder(DATA_TYPES::RiskStatus &riskStatus,
        COMMON::Instrument *instrument,
        SingleOrder *order,
        COMMON::OrderId *orderId,
        bool isSpreadOrder = false,
        const bool validateAccountDetail = true);

    /**
     * @brief validateAccountDetail               - validate account detail for dealer and client code present in exchangeAdapterDetails,
     *                                              also populate exchangeAdapterDetails with other details if required
     * @param accountDetail                       - account detail corresponding to which exchange adapter detail required
     * @param staticData                          - static data of the leg for which getting the details
     * @param dealerId                            - dealer id
     * @param exchangeAdapterDetailsToBeReturned  - adapter details to be returned
     * @return                                    - whether validation is successful
     */
    const bool validateAccountDetail(
        const API2::AccountDetail& accountDetail,
        const API2::SymbolStaticData& staticData,
        const int dealerId,
        const API2::ExchangeAdapterDetails*& exchangeAdapterDetailsToBeReturned);

    /**
     *@brief onPendingNewOrder
     * Overload this method to receive manual order from frontend to strategy
     *
     * @param Single Order to be placed in market
     */
    virtual void onPendingNewOrder( SingleOrder* singleOrder );

    /**
     *@brief onPendingReplaceOrder 
     * To Send a Pending Replace Order manually from from frontend to strategy
     *
     * @param Single Order to be replaced in market.
     */
    virtual void onPendingReplaceOrder( SingleOrder* singleOrder );

    /**
     *@brief onPendingCancelOrder 
     * To Send a Pending cancel Order manually from from frontend to strategy.
     *
     * @param Single Order to be cancelled in market.
     */
    virtual void onPendingCancelOrder( SingleOrder* singleOrder );

    /**
     * @brief reqHistoricalData To request Historical Data
     * @param symbolId
     * @param errorCode
     * @param barSize
     * @param duration
     * @param endTime
       * @return
       **/
    bool reqHistoricalData( const SIGNED_LONG &symbolId,
        int &errorCode,
        int &reqId,
        const int &barSize,
        const long &duration,
        long endTime = 0 );

    class OrderLegData{

      public:
        COMMON::Instrument *instrument;
        SingleOrder *order;
        COMMON::OrderId *orderId;
        explicit OrderLegData(COMMON::Instrument *instrument):
          instrument(instrument),
          order(0),
          orderId(0){}

        OrderLegData():
          instrument(0),
          order(0),
          orderId(0){}
    };

    /**
      @brief reqNewMultilegOrder
      @param riskStatus
      @param data
      @return
      */
    bool reqNewMultilegOrder(DATA_TYPES::RiskStatus &riskStatus,
        std::vector<OrderLegData> &data
        );


    /**
     * @brief reqReplaceOrder To send a replace Order
     * @param riskStatus
     * @param instrument
     * @param order
     * @param updateQuantity
     * @param orderId
     * @param isSpreadOrder
     * @return true if order is replaced sucessfully
     *         else false(Also it return false if order type is IOC because there is no sense to cancel/replace IOC order)
     * Note: If modification of IOC order is requested, then false is returned without any processing.
     *       As there is no meaning to modify IOC order
     **/
    bool reqReplaceOrder(DATA_TYPES::RiskStatus &riskStatus,
                          COMMON::Instrument *instrument,
                          SingleOrder *order,
                          COMMON::OrderId *orderId,
                          bool isSpreadOrder = false);

    /**
       * @brief reqCancelOrder To Cancel Order
       * @param riskStatus passed by reference This is the risk status for sending Canceled Order
       * @param orderId
       * @param ignorePendingState : send cancel request to exchange even if order is in panding state.
       * @param modifiedBy
       * @return true if order is cancelled sucessfully
       *              else false (Also it return false if order type is IOC because there is no sense to cancel/replace IOC order)
       * Note: If cancellation of IOC order is requested, then false is returned without any processing.
       *       As there is no meaning to cancel IOC order.
       */
    bool reqCancelOrder(DATA_TYPES::RiskStatus &riskStatus, COMMON::OrderId *orderId, const bool ignorePendingState = false,
                        const SIGNED_LONG modifiedBy = API2::CONSTANTS::Default_Modified_By_Id);


    /**
       * @brief reqCancelAllOrders To cancel all Orders ( Confirmed or Partial Filled )
       */
    void reqCancelAllOrders();


    /**
       * @brief reqTerminateSquareOffStrategy Called to Terminate strategy and Square-Off all  Positions\n
       * Can be overriden \n
       * Default behaviour: \n
       * 1) Cancel All Orders \n
       * 2) Send Opposite Orders for closing Position \n
       * 3) Terminate the strategy \n
       */
    virtual void reqTerminateSquareOffStrategy();

    /**
       * @brief reqTerminateStrategy Called to Terminate Strategy\n
       * Can be overriden \n
       * Default behaviour: \n
       * 1) Cancel All Pending Orders \n
       * 3) Terminate the strategy \n
       */
    virtual void reqTerminateStrategy(bool reqCancelAllOrders=true);

    /**
       * @brief reqForceTerminateStrategy Called to Terminate Strategy\n
       * @param isWait - whether strategy will wait untill all the orders gets cancelled before terminating.
       * Default behaviour: \n
       * 1) Cancel All Pending Orders \n
       * 2) Terminate the strategy \n
       */
    void reqForceTerminateStrategy( const bool isWait = true );

    /**
     * @brief reqStartAlgo function call to Start the Strategy
     * @param marketDataEventRequired Set True to register for call-backs on Market-Data Event on registered Instruments
     * @param tradeTicksEventRequired Set True to register for call-backs on Trade Tick Events on registered Instruments
     * @param preTradeEventRequired Set True to register for call-backs for pre trade confirmations
     * @param isConvertToManualOrder Set True if you want your open order's to persist after termination of algo. Order will start behaving like manual order.
     * @param childConfirmationEvent Set True to register for call-backs for confirmations coming from child strategy
     * * @return
     */
    void *reqStartAlgo( bool marketDataEventRequired, 
                        bool tradeTicksEventRequired, 
                        bool preTradeEventRequired = false , 
                        bool isConvertToManualOrder = false,
                        bool childConfirmationEvent = false );
    
    /**
     * @brief registerAlgoDetail : set AlgoId and AlgoCatagory in SGContextImpl object
     * @param algoId
     * @param algoCategory
     * @return false if algoId,algoCategory are invalid
     */
    bool registerAlgoDetail(const SIGNED_LONG algoId = 0, short  algoCategory = 0);

    /**
     * @brief validateAlgoDetail function to check AlgoId
     */
    bool validateAlgoDetail();

    /**
     * @brief validateSorPermission : This function will validate whether a user is allowed 
     * to run a sor strategy or not.
     * @param userStr : client code on which strategy will be run
     * @return false if user is not given sor permissions.
     */
    bool validateSorPermission( const API2::DATA_TYPES::USER_ID_STR &userStr );

    /**
     * @brief reqStartOHLCAlgo function call to Start the Strategy listening to OHLC update events
     * @return
     */
    void *reqStartOHLCAlgo();

    /**
     * @brief reqProcessTradeTicks
     * @param error
     * @param symbolId
     * @return
     */
    bool reqProcessTradeTicks(bool &error, SYMBOL_ID symbolId);

    /**
       * @brief reqRemoveInstrument To remove Instrument from the context. \n
       * Removing will remove all the data relating the Instrument's Position
       * @param instrument
       */
    void reqRemoveInstrument(COMMON::Instrument *instrument);

    /**
       * @brief reqRemoveAllInstruments This will remove all Instrument from the registered Instrument list
       */
    void reqRemoveAllInstruments();

    /**
       * @brief reqUpdateMarketData To manually update Market Feed for all registered Instruments.\n
       * Not required if marketDataEventRequired is set to be True while starting the strategy using API2::SGContext::reqStartAlgo()
       * @return True if there is a new updation in Market Data. False if no new updation.
       */
    bool reqUpdateMarketData();

    /**
       * @brief reqUpdateMarketData To manually update Market Feed for requested API2::DATA_TYPES::SYMBOL_ID.\n
       * Not required if marketDataEventRequired is set to be True while starting the strategy using API2::SGContext::reqStartAlgo()
       * @return True if there is a new updation in Market Data. False if no new updation.
       */
    bool reqUpdateMarketData(UNSIGNED_LONG symbolId);

      /**
       * @brief reqRegisterMarketData
       * @param symbolId
       * @param isSnapshot
       * @param isTbt
       * @param isOhlc
       * @param depthSize Max depth to process
       * @return
       *
       * NOTE: In case of Indices,it can read data only from snapshot,so register index instrument for snapshot.
       */
      bool reqRegisterMarketData(
          DATA_TYPES::SYMBOL_ID symbolId,
          bool isSnapshot = true,
          bool isTbt = false,
          bool isOhlc = false,
          size_t depthSize = CONSTANTS::MarketDepthArraySize
          );

      /**
       * @brief reqRegisterMarketData
       * @param instrumentName
       * @param instrumentName Instrument Name
       *
       *        Format:
       * 				Normal Contracts and Securities
       *        [SOURCE] [EXCHANGE] [Symbol] [Expiry(YYYYMMDD)] [StrikePrice] [C/P(For Call/Put)]
       *        Example:
       *        Cash Segment: 
       *            for NSE EQ -> DEFAULT NSECM RELIANCE
       *            Other than EQ say IL -> DEFAULT NSECM RELIANCE IL
       *            for BSE A -> DEFAULT BSECM RELIANCE
       *            Other than A say BE -> DEFAULT BSECM RELIANCE BE
       *            For all other exchages, it will be "EXCH SYMBOL GR"
       *        Futures Segment: DEFAULT NSEFO RELIANCE 20140828
       *        Options Segment: DEFAULT NSEFO RELIANCE 20140828 98000 C
       *
       * 				Spread Contracts
       * 				[SOURCE] [EXCHANGE] [SYMBOL] [Expiry1(YYYYMMDD)] [Expiry2(YYYYMMDD)]
       * 				Example:
       * 				DEFAULT BSEFO RELIANCE 20151126 20151231
       *
       * 				Pair, Straddle Contracts
       * 				[SOURCE] [EXCHANGE] [SYMBOL] [Expiry1(YYYYMMDD)] [Expiry2(YYYYMMDD)] [StrikePrice] [C/P(For Call/Put)]
       * 				Example:
       * 				DEFAULT BSEFO RELIANCE 20151126 20151231 98000 C
       *
       * 				For Indices
       *        [SOURCE] [EXCHANGE] [IndexSymbolName]
       * 				Example:
       * 				DEFAULT NSECM CNX Nifty, NSECM BANK Nifty, BSECM BSE100
       *
       * @param isSnapshot
       * @param isTbt
       * Both Can be subscribed simultaneously
       * @param isOhlc
       * @param depthSize Max depth to process
       * @return
       *
       * DEFAULT source will be replaced with TT, IB, OT etc (whichever applicable) if connecting through different broker
       *
       * NOTE: In case of Indices,it can read data only from snapshot,so register index instrument for snapshot.
       *
       * For esm, use ESMNSE as exchange
       * Example: DEFAULT ESMNSE RELIANCE EQ
       * NOTE:
       * There's a difference in esm and normal exchanges for cash contracts,
       * In case of ESMNSE, group name always required to be added when subscribing or getting unique id
       * In NSECM, for EQ contracts, 'EQ' will not be added in end
       * In BSECM, for A contracts, 'A' will not be added in end
       */

      bool reqRegisterMarketData(
          const std::string &instrumentName,
          bool isSnapshot = true,
          bool isTbt = false,
          bool isOhlc = false,
          size_t depthSize = CONSTANTS::MarketDepthArraySize
          );

      /**
       * @brief reqAddStrategyComment To set the current Startegy Comment Whenever a strategy Response is sent to frontend 
       * this will be the  sent as the strategy Comment
       * @param com
       */
      void reqAddStrategyComment(DATA_TYPES::StrategyComment com);

      /**
       * @brief reqAddStrategyComment To set the current Startegy Comment Whenever a strategy Response is sent to frontend
       * this will be the sent as the custom strategy comment and will be shown as it is at frontend.
       * @param com
       */
      void reqAddStrategyComment(const DATA_TYPES::String &com);

    /**
       * @brief reqSendStrategyResponse To send a Response to the frontend
       * @param responseType the response Type as DATA_TYPES::ResponseType
       * @param riskStatus the Risk Status as DATA_TYPES::RiskStatus
       * @param strategyComment the Strategy Comment as DATA_TYPES::StrategyComment
       * @param terminationReasonType The reason due to which the strategy is terminated
       *                              for eg. if it is terminated front-end, automatically etc.
       */
    void reqSendStrategyResponse(
        DATA_TYPES::ResponseType responseType,
        DATA_TYPES::RiskStatus riskStatus,
        DATA_TYPES::StrategyComment strategyComment = CONSTANTS::RSP_StrategyComment_MAX,
        DATA_TYPES::TerminationReasonType terminationReasonType = CONSTANTS::RSP_TerminationReasonType_AUTO,
        const DATA_TYPES::String &strategyCustomComment = ""
        );

    /**
       * @brief reqExitStrategy To exit a strategy terminates the Strategy thread and returns the StrategyDriver.
       */
    void reqExitStrategy();

    /**
       * @brief reqExitStrategy To exit a strategy terminates the Strategy thread and returns the StrategyDriver.
       * returns if timer was set or not
       */
    bool reqTimerEvent(DATA_TYPES::TimerMicroSecondInterval timerMicroSecondInterval);

    /***********************************************************/
    /************************ Query Calls ********************/
    /***********************************************************/


    /**
     * @brief reqQryTestSegment To know whether a given exchange segment is being used in the strategy or not
     * @param exch The DATA_TYPES::ExchangeId
     * @param securityType The DATA_TYPES::SecurityType
     * @return
     */
    virtual bool reqQryTestSegment(
        const DATA_TYPES::ExchangeId &exch,
        const DATA_TYPES::SecurityType &securityType = CONSTANTS::CMD_SecurityType_MAX
        );


    /**
       * @brief reqQryClientID To get ClientId
       * @return
       */
    int reqQryClientID();

    /**
       * @brief reqQryAdminTokenId To get AdminTokenId
       * @return
       */
    int reqQryAdminTokenId();

    /**
       * @brief reqQryStrategyParams To get StartegyParameters
       * @return
       */
    StrategyParameters *reqQryStrategyParams();

    /**
       * @brief reqQryUpdateMarketData This function call will return the Pointer to API2::COMMON::MktData structure after updating it.\n
       * Not required if marketDataEventRequired is set to be True while starting the strategy using API2::SGContext::reqStartAlgo()
       * @param symbolId SymbolId for which MarketData is required
       * @return
       */
    COMMON::MktData *reqQryUpdateMarketData(SYMBOL_ID symbolId);

      /**
       * @brief reqQryUpdateTbtMarketData This function call will return the Pointer to API2::COMMON::MktData structure after updating it.\n
       * Not required if marketDataEventRequired is set to be True while starting the strategy using API2::SGContext::reqStartAlgo()
       * @param symbolId SymbolId for which MarketData is required
       * @return will return market data if symbol is registered for Tbt else return NULL
       */
      COMMON::MktData *reqQryUpdateTbtMarketData(SYMBOL_ID symbolId);

      /**
       * @brief reqQryUpdateSnapshotMarketData This function call will return the Pointer to API2::COMMON::MktData structure after updating it.\n
       * Not required if marketDataEventRequired is set to be True while starting the strategy using API2::SGContext::reqStartAlgo()
       * @param symbolId SymbolId for which MarketData is required
       * @return will return market data if symbol is registered for Snapshot else return NULL
       */
      COMMON::MktData *reqQryUpdateSnapshotMarketData(SYMBOL_ID symbolId);
      
      /**
       * @brief reqQryMarketData This function call will return the Pointer to API2::COMMON::MktData structure \n Here it will contain the last updated Market Snapshot
       * @param symbolId
       * @return
       */
    COMMON::MktData *reqQryMarketData(SYMBOL_ID symbolId);

      /**
       * @brief reqQrySnapshotMarketData provides last updated snapshot data for requestd symbol 
       * @param symbolId symbol for which we require market data
       * @return returns pointer to  API2::COMMON::MktData structure if symbol is registered for snapshot else returns NULL
       */
      COMMON::MktData *reqQrySnapshotMarketData(SYMBOL_ID symbolId);
      
      /**
       * @brief reqQryTbtMarketData provides last updated Tbt data for requestd symbol 
       * @param symbolId symbol for which we require market data
       * @return returns pointer to  API2::COMMON::MktData structure if symbol is registered for TBT else returns NULL
       */
      COMMON::MktData *reqQryTbtMarketData(SYMBOL_ID symbolId);

    /**
     * @brief reqQryOHLCQuote
     * @param error
     * @param symbolId
     * @return
     */
    COMMON::OhlcQuote *reqQryOHLCQuote(bool &error, SYMBOL_ID symbolId);


    /**
       * @brief reqQryNetMarkToMarkPL This function will return net Mark To Market Profit and Loss for the strategy( sum of all Instruments being traded)
       * @return
       */
    SIGNED_LONG reqQryNetMarkToMarkPL();

    /**
       * @brief reqQryNetBookedPL This function will return net Booked Profit and Loss for the strategy( sum of all Instruments being traded)
       * @return
       */
    SIGNED_LONG reqQryNetBookedPL();

    /**
       * @brief reqQrySymbolID This function will return System Unique ID for the Instrument as API2::DATA_TYPES::SYMBOL_ID
       * @param instrumentName Instrument Name
       *
       *        Format:
       * 				Normal Contracts and Securities
       *        [SOURCE] [EXCHANGE] [Symbol] [Expiry(YYYYMMDD)] [StrikePrice] [C/P(For Call/Put)]
       *        Example:
       *        Cash Segment: 
       *            for NSE EQ -> DEFAULT NSECM RELIANCE
       *            Other than EQ say IL -> DEFAULT NSECM RELIANCE IL
       *            for BSE A -> DEFAULT BSECM RELIANCE
       *            Other than A say BE -> DEFAULT BSECM RELIANCE BE
       *            For all other exchages, it will be "EXCH SYMBOL GR"
       *        Futures Segment: DEFAULT NSEFO RELIANCE 20140828
       *        Options Segment: DEFAULT NSEFO RELIANCE 20140828 98000 C
       *
       * 				Spread Contracts
       * 				[SOURCE] [EXCHANGE] [SYMBOL] [Expiry1(YYYYMMDD)] [Expiry2(YYYYMMDD)]
       * 				Example:
       * 				DEFAULT BSEFO RELIANCE 20151126 20151231
       *
       * 				Pair, Straddle Contracts
       * 				[SOURCE] [EXCHANGE] [SYMBOL] [Expiry1(YYYYMMDD)] [Expiry2(YYYYMMDD)] [StrikePrice] [C/P(For Call/Put)]
       * 				Example:
       * 				DEFAULT BSEFO RELIANCE 20151126 20151231 98000 C
       *
       * 				For Indices
       *        [SOURCE] [EXCHANGE] [IndexSymbolName]
       * 				Example:
       * 				DEFAULT NSECM CNX Nifty, DEFAULT NSECM BANK Nifty, DEFAULT BSECM BSE100
       *
       * DEFAULT source will be replaced with TT, IB, OT etc (whichever applicable) if connecting through different broker
       *
       * For esm, use ESMNSE as exchange
       * Example: DEFAULT ESMNSE RELIANCE EQ
       * NOTE:
       * There's a difference in esm and normal exchanges for cash contracts,
       * In case of ESMNSE, group name always required to be added when subscribing or getting unique id
       * In NSECM, for EQ contracts, 'EQ' will not be added in end
       * In BSECM, for A contracts, 'A' will not be added in end
      */
     
    static DATA_TYPES::SYMBOL_ID reqQrySymbolID(std::string instrumentName);



    /**
       * @brief reqQryInstrumentList To get list of all Instruments added for the requested SymbolId
       * @param symbolId System Unique Id for the Instrument
       * @return
       */
    std::list<API2::COMMON::Instrument *> reqQryInstrumentList(UNSIGNED_LONG symbolId);


    /**
     * @brief reqQryOrder To get Pointer to Single Order using a clientOrderId
     * @param clOrderId
     * @return
     */
    API2::SingleOrder* reqQryOrder(DATA_TYPES::CLORDER_ID clOrderId);


    /**
       * @brief reqQryStrategyId To get StartegyId of current running Strategy.
       * @return
       */
    API2::DATA_TYPES::STRATEGY_ID reqQryStrategyId();



    /**
       * @brief reqQryDebugLog To get Pointer to the DebugLog Object used to dump debug messages. \n Sample Usage:\n
       *  DEBUG_MESSAGE(reqQryDebugLog()"<Message>");
       * @return
       */
    DebugLog *reqQryDebugLog();

    /**
       * @brief reqQryPendingQty To get Pending Quantity of an Instrument
       * @param instrument API2::COMMON::Instrument
       * @param mode Ordermode as API2::CONSTANTS::CMD_OrderMode_BUY or API2::CONSTANTS::CMD_OrderMode_SELL
       * @return
       */
    UNSIGNED_LONG reqQryPendingQty(COMMON::Instrument* instrument,
                                DATA_TYPES::OrderMode mode);

    /**
       * @brief reqQryPendingQty To get Pending Quantity of requested Order as orderId
       * @param orderId
       * @return
       */
    DATA_TYPES::QTY reqQryPendingQty(COMMON::OrderId *orderId);

    /**
       * @brief reqQryClientOrderId To get ClientOrderId of requested Order
       * @param orderId
       * @return
       */
    DATA_TYPES::CLORDER_ID reqQryClientOrderId(COMMON::OrderId *orderId);

    /**
       * @brief reqQryOrderStatus To get OrderStatus of requested Order
       * @param orderId
       * @return
       */
    DATA_TYPES::OrderStatus reqQryOrderStatus(COMMON::OrderId *orderId);

    /**
       * @brief reqQryExchangeOrderId To get Exchange OrderId of requested Order
       * @param orderId
       * @return
       */
    DATA_TYPES::String reqQryExchangeOrderId(COMMON::OrderId *orderId);

    /**
     * @brief reqQryLastQuotedPrice
     * @param orderId
     * @return Price as DATA_TYPES::SIGNED_LONG in Paisa ( to convert in Rupee, convert to float/double and divide by 100)
     */
    DATA_TYPES::PRICE reqQryLastQuotedPrice(COMMON::OrderId *orderId);

    /**
     * @brief reqQrySendCustomResponse - for sending custom data for frontend internally created api2 strategy from using design string 
     * @param customData
     * @param uiDataPair
     * @param rowId
     * @return
     */
    bool reqQrySendCustomResponse(const std::string &customData, const std::list<std::string> &uiDataPair, const int rowId, int clientId=0);
    
    /**
     * @brief reqQrySendCustomResponseEx - for sending custom data for frontend externally created api2 strategy from
     * @param customData
     * @param uiDataPair
     * @param rowId
     * @return
     */
    bool reqQrySendCustomResponseEx(const std::string &customData, const std::list<std::string> &uiDataPair, const int rowId, int clientId=0);
  
    /**
     * @brief reqQryCMDDisconnection - returns true if exchange corresponding to any of strategy's symbol got disconnected.\n 
     * Can be used while overriding onCMDDisconnection to know if exchange corresponding to any of strategy's symbol got disconnected.
     * @param command
     * @return
     */
    bool reqQryCMDDisconnection(const DATA_TYPES::CommandCategory &command);

    /**
     * @brief reqQryStrategyInfo - return the information of Invoked strategy
     */
    INVOKING::StrategyInfo* reqQryStrategyInfo(int childId);

     /**
       * @brief reqQryChildRunningStatus - return true if strategy is running else returns false
       */
     bool reqQryChildRunningStatus(int childId);

    /***********************************************************/
    /************************ Get Dump String Calls ********************/
    /***********************************************************/


    /**
       * @brief getStrConfirmation. Prints OrderConfirmation fields
       * @param confirmation
       */
    DATA_TYPES::String getStrConfirmation(const OrderConfirmation &confirmation);

    /**
       * @brief getStrSingleOrder. Prints Single Order fields
       * @param order
       */
    DATA_TYPES::String getStrSingleOrder(SingleOrder *order);

    /**
       * @brief getStrOrderId. Prints OrderId Fields
       * @param orderId
       */
    DATA_TYPES::String getStrOrderId(const COMMON::OrderId *orderId);


    /***********************************************************/
    /************************ Command Call-Backs ********************/
    /***********************************************************/


    /**
       * @brief onCMDAdminCommand Called when ever a command from frontend is issued.
       * @param command
       */
    virtual void onCMDAdminCommand(DATA_TYPES::CommandCategory command){}

    /**
     * @brief onCMDInternalMessage 
     * This method is being used for internal command handling. User need not overload this in their algo.
     * @param command
     */
    virtual void onCMDInternalMessage(const DATA_TYPES:: CommandCategory &command);

    /***NOTE ** Disconnection type to be created inside Data_TYPES and constants to be added */
    /**
       * @brief onCMDDisconnection Called whenever a disconnection is received disconnected entity to be determined from CommandCategory
       * @param command
       */
    virtual void onCMDDisconnection(const DATA_TYPES::CommandCategory &command);

    /**
     * @brief onCMDReconnection Called whenever TBT reconnects after a while
     * @param command
     */
    virtual void onCMDReconnection(const DATA_TYPES::CommandCategory &command);


    /**
       * @brief onCMDModifyStrategy  Called when strategy modify command is received
       */
    virtual void onCMDModifyStrategy(AbstractUserParams *newParams) =0;

    /**
       * @brief onCMDTerminateStartegy Called when strategy receives Terminate Command from Frontend
       */
    virtual void onCMDTerminateStartegy();

    /**
     * @brief onCMDDmsDisconnection - This method needs to be called when DMS gets disconnected from
     *                                hft or front-end gets disconnected from DMS.
     */
    virtual void onCMDDmsDisconnection();

    /**
       * @brief onCMDTerminateSqOffStrategy Called when strategy receives Terminate SqOff Command from Frontend
       */
    virtual void onCMDTerminateSqOffStrategy();

    /**
       * @brief onCMDPauseStartegy Called when strategy receives Pause Command from Frontend
       */
    virtual void onCMDPauseStartegy();

    /**
       * @brief onCMDRunStrategy Called when strategy receives Run Command from Frontend
       */
    virtual void onCMDRunStrategy();

    /**
       * @brief OnCMDInit To Set Initial state of the algo
       */
    virtual void onCMDInit(){}

    /***********************************************************/
    /************************ Event Call-Backs ********************/
    /***********************************************************/


    /**
       * @brief onDefaultEvent Called as an event if Not configured to received marketData Event while Running Algo
       */
    virtual void onDefaultEvent();

    /**
       * @brief onMarketDataEvent Called if Configured to received marketData Event while Running Algo
       * @param symbolId    SymbolId of the Instrument that received marketData SymbolId should be subscribed for Market Data while initializing
       */
    virtual void onMarketDataEvent(UNSIGNED_LONG symbolId);

    /**
       * @brief onOhlcTimeOutEvent Called if Configured to received OHLC update Event while Running Algo \n
       *  Callback is provided each time the OHLC Data is updated
       */
    virtual void onOhlcTimeOutEvent();

    /**
       * @brief onTradeTickEvent Called if Configured to received Trade Ticks update Event while Running Algo \n
       *  Callback is provided each time the Trade Tick is received through the TBT Server
       *  This event is specific to NSE-TBT Trade Tick currently
       * @param symbolId SymbolID
       * @param tradeTick
       */
    virtual void onTradeTickEvent(API2::DATA_TYPES::SYMBOL_ID, COMMON::TradeTick tradeTick);

    /**
       * @brief onProcessPreTradeConfirmation Call back when trade received at system level but yet to process and pass to whole infra and algo, full confirmation will always follow after pre-trade confirmation \n
       * Not necessary to override this \n
       * To be overridden only If any additional Processing is reqd at the algo end
       * @param confirmation Reference to the API2::PreTradeConfirmation
       */

    virtual void onProcessPreTradeConfirmation(API2::PreTradeConfirmation& preTradeConfirmation){}
    /**
       * @brief onTradeTickEvent Called if Configured to received Trade Ticks update Event while Running Algo \n
       *  Callback is provided each time the Trade Tick is received through the TBT Server.
       *  This event is specific to NSE-TBT Trade Tick currently.
       *  To be overridden if trade tick is to be reqd at algo end.
       *
       * @param symbolId SymbolID for which trade has taken place.
       */
    virtual void onTradeTickEvent(API2::DATA_TYPES::SYMBOL_ID);

    /**
       * @brief onProcessOrderConfirmation Call back after OrderConfirmation Processing is done \n
       * Not necessary to override this \n
       * To be overridden only If any additional Processing is reqd at the algo end
       * @param confirmation Reference to the API2::OrderConformation
       */
    virtual void onProcessOrderConfirmation(OrderConfirmation &confirmation){}


    /**
     * @brief onConfirmed Call back when a new Order gets confirmed by exchange.
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onConfirmed(OrderConfirmation &confirmation, COMMON::OrderId *orderId){}

    /**
     * @brief onReplaceRejected Call back when a replace order gets rejected by the exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onReplaceRejected(OrderConfirmation &confirmation, COMMON::OrderId *orderId){}

    /**
     * @brief onCanceled Call back when a cancel order gets accepted by the exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onCanceled(OrderConfirmation &confirmation, COMMON::OrderId *orderId){}

    /**
     * @brief onCancelRejected Call back when a cancel order gets rejected by the exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onCancelRejected(OrderConfirmation &confirmation, COMMON::OrderId *orderId){}

    /**
     * @brief onReplaced Call back when a Order gets replaced sucessfully at the exchange.
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onReplaced(OrderConfirmation &confirmation, COMMON::OrderId *orderId){}

    /**
     * @brief onNewRejected Call back when a new order gets rejected by the exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onNewReject(OrderConfirmation &confirmation, COMMON::OrderId *orderId){}

    /**
     * @brief onIOCCanceled Call back when an IOC order gets canceled the exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onIOCCanceled(OrderConfirmation &Confirmation, COMMON::OrderId *orderId){}

    /**
     * @brief onFilled Call back when an order gets filled at the exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onFilled(OrderConfirmation &confirmation, COMMON::OrderId *orderId){}

    /**
     * @brief onPartialFill Call back when an order gets partially filled at the exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onPartialFill(OrderConfirmation &confirmation, COMMON::OrderId *orderId){}

    /**
     * @brief onMarketToLimit Call back when Orderstatus changes from Market To Limit by exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onMarketToLimit(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId){}
    
    /**
     * @brief onTriggered Call back when stop loss or stop limit order triggered by exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onTriggered(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId){}

    /**
     * @brief onFrozen Call back when an order gets frozen by exchange
     * @param confirmation Contains the information received from Exchange
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onFrozen(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId){}

    /**
     * @brief onRmsReject Call back when an order gets rejected by HFT(DMA)
     * @param confirmation Contains the information received from HFT(DMA) 
     * @param orderId Pointer to the API2::COMMON::OrderId type
     */
    virtual void onRmsReject(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId){}

    /**
     * @brief onChildConfirmation Call back when an orderConfirmation from child strategy gets filled,
     * for now this event is generated only in case of fill and partial fill.
     * @param confirmation Contains the information of child filled order received from Exchange
     */
    virtual void onChildConfirmation( const UNSIGNED_LONG childId )
    {
    }

    /**
     * @brief onTimerEvent Call back when an timer set by strategy expires
     * This would be idle time to reset the timer if needed
     */
    virtual void onTimerEvent(){}

    /**
     * @brief onStrategyCustomCommand Call back when there is any custom command or
     * extra information (i.e. generated at infra) will sent to strategy.
     * @param command
     */
    virtual void onStrategyCustomCommand( const API2::CONSTANTS::CUSTOM_STRATEGY_COMMAND command ){}

    /***********************************************************/
    /************************ RMS Getters ********************/
    /***********************************************************/

    /**
     * @brief getFreezeQty
     * @param symbol - ACC, TATASTEEL
     * @param exchangeId - NSEFO, NSECM
     * @param securityType - future, stock
     * @param groupName - BE, EQ
     * @param staticData
     */
    SIGNED_LONG getFreezeQty(const std::string &symbol,
        const DATA_TYPES::ExchangeId exchangeId,
        const char securityType,
        const std::string &groupName = " ",
        const API2::SymbolStaticData *const staticData = nullptr );

    /**
     * @brief getMaxOrderQtyFromFreezeQty
     * @param staticData
     * @return return max single order qty allowed from exchange.
     */
    SIGNED_LONG getMaxOrderQtyFromFreezeQty(const API2::SymbolStaticData *const staticData);

    /**
     * @brief getApiPositionBySymbolId This function will be used for getting the positions for multiple symbol ids.
     * @return SymbolIdAndPositionStructHash - This is a boost unordered map where key will be symbol id 
     *         and value will be position struct. 
     *
     * @param symbolIdVec vector of symbol ids for those we need to get positions.
     * @return true, if any of passed symbol position is found
     *         otherwise return false
     *
     * Note:
     * In case using new RMS :
     * - If margin revert on trade give up is enabled in the system, the same shall impact this position.
     * - For old positions, if ignore old position(of client with a mapped cp code) is enabled in the system,
     *   then those old positions will not be present in this position as they are assumed to be reverted
     *   and shall not impact current day's trading.
     */
    bool getApiPositionBySymbolId(
        SymbolIdAndPositionStructHash& hashSymbolIdAndPositionStruct,
        const std::vector< SIGNED_LONG >& symbolIdVec );

    /**
     * @brief getApiPositionBySymbolId it is an overload function for getting the position for one symbol id
     *
     * @return True if position exists for symbol id and set the position in PositionStruct, 
     *         false if position does not exist. 
     *
     * @param symbolId symbol id for which we need to get position.
     * @return true : if position(buy + sell  + old) is exist in the system otherwise false.
     *
     * Note:
     * In case using new RMS :
     * - If margin revert on trade give up is enabled in the system, the same shall impact this position.
     * - For old positions, if ignore old position(of client with a mapped cp code) is enabled in the system,
     *   then those old positions will not be present in this position as they are assumed to be reverted
     *   and shall not impact current day's trading.
     */
    bool getApiPositionBySymbolId( 
        API2::PositionStruct &outPos, 
        const SIGNED_LONG symbolId );

    /**
     * @brief getApiPositionForDealer This function will be used for getting the dealer wise positions for a single dealer id.
     * @return SymbolIdAndPositionStructHash - This is boost unordered map where key will be symbol id 
     *         and value will be position struct.
     *
     * @param dealerId Dealer id for which we need to get positions.
     * @param symbolIdVec vector of symbol ids for those we need to find out positions.
     *        - Default value is empty and in this case dealer wise positions for all symbols under one input dealer will be return 
     *        - If we need dealer wise positions for some specific symbol ids for input dealer then we pass those symbol ids in this vector.
     * @return For OLD RMS : it will always return true for now
     *               For NEW RMS: it will return true if position found for any of the symbol, otherwise return false.
     *
     * Note:
     * In case using new RMS :
     * - If margin revert on trade give up is enabled in the system, the same shall impact this position.
     * - For old positions, if ignore old position(of client with a mapped cp code) is enabled in the system,
     *   then those old positions will not be present in this position as they are assumed to be reverted
     *   and shall not impact current day's trading.
     */
    bool getApiPositionForDealer(
        API2::SymbolIdAndPositionStructHash& hashSymbolIdAndPositionStruct,
        SIGNED_INTEGER dealerId,
        const boost::unordered_set< SIGNED_LONG >& symbolIdSet = boost::unordered_set< SIGNED_LONG >() );

    /**
     * @brief getApiPositionForDealer This function will be used for getting the positions for a multiple dealer ids.
     * @return DealerIdVsSymbolIdAndPositionStructHash - This is boost unordered map where key will be dealer id 
     *         and value will be another unordered map of symbolId( key ) and position struct ( value ).
     *
     * @param dealerIdVec Vector of Dealer ids for those we need to get positions.
     *        - Default vause is empty and in this case dealer wise positions for all dealers will be returned
     *        - Otherwise dealer wise positions for input dealers will be returned.  
     *
     * @param symbolIdVec vector of symbol ids for those we need to find out positions.
     *        - Default value is empty and in this case dealer wise positions for all symbols 
     *          under all input/all dealers will be returned. 
     *        - If we need dealer wise positions for some specific symbol ids 
     *          for all input/all dealers then we pass those symbol ids in this vector.
     * @return it will always return true for now
     *
     * Note:
     * In case using new RMS :
     * - If margin revert on trade give up is enabled in the system, the same shall impact this position.
     * - For old positions, if ignore old position(of client with a mapped cp code) is enabled in the system,
     *   then those old positions will not be present in this position as they are assumed to be reverted
     *   and shall not impact current day's trading.
     */
    bool getApiPositionForDealer(
        API2::DealerIdVsSymbolIdAndPositionStructHash& hashDealerIdSymbolIdPositionStruct,
        const std::vector< SIGNED_INTEGER >& dealerIdVec = std::vector< SIGNED_INTEGER >(),
        const boost::unordered_set< SIGNED_LONG >& symbolIdSet = boost::unordered_set< SIGNED_LONG >() );

    /**
     * @brief getApiPositionForClient - This function will be used for getting the client  + symbolId wise positions
     *                                - for the symbols provided in symbolIdSet.
     *
     * @return hashSymbolIdAndPositionStruct - This is an unordered map where key will be symbol id
     *                                       - and value will be position struct and symbol Id will come
     *                                       - from symbolIdSet which will be provided when this method is called.
     *
     * @param primaryClientCode - primary client code ( Can get from AccountDetails )
     *
     * @param exchangeId - Exchange Id ( Can get from symbolStatic Data ):
     *                     For Old RMS this value should be valid, because in Client wise position not supported
     *                     For New RMS: this value could be anything, because there is only client code wise position
     *                     Not Considered in New RMS .
     *
     * @param segmentType - Segment Type ( Can get from symbolStatic Data )
     *                     For Old RMS this value should be valid, because in Client wise position not supported
     *                     For New RMS: this value could be anything, because there is only client code wise position.
     *                     Not Considered in New RMS
     *
     * @param symbolIdVec vector of symbol ids for those we need to find out positions.
     *        - If there is no position created on the symbol Id it will return PositionStruct with default values ( i.e. 0 ).
     *
     * @example - Returned Structure Diagram (i.e. API2::SymbolIdAndPositionStructHash)
     *
     *               Client + Exchange + Segment (e.g. Client( C1 ) + Exchange( NSECM ) + Segment( CASH ) )
     *       ------------------------------------------
     *       |     Symbol Id     |    PositionStruct  |
     *       ------------------------------------------
     *       |     11504375      |        P1          |  Where P1,P2....PN are PositionStruct.
     *       |     11504376      |        P2          |
     *       |       ....        |       ....         |
     *       |     11601234      |        PN          |
     *       ------------------------------------------
     *
     * @note - If there is no position created for the given inputs it will return an empty position structure
     *         same goes for the invalid inputs.
     *       - Positions are coming with RMS_PRECISION_POSITION can be normalize to actual price using getRmsPositionPrecision() method
     *       - For New RMS : client + exchange + segment not supported
     *
     * @return : true if position exist in system for primaryClientCode
     *                In case of OLD RMS : it will return false if exchangeId ==MAX or segmentType == MAX or symbolIdSet is empty
     *                In case of NEW RMS: It will return false, setting not provided by admin.
     * Note:
     * In case using new RMS :
     * - If margin revert on trade give up is enabled in the system, the same shall impact this position.
     * - For old positions, if ignore old position(of client with a mapped cp code) is enabled in the system,
     *   then those old positions will not be present in this position as they are assumed to be reverted
     *   and shall not impact current day's trading.
     */
    bool getApiPositionForClient(
        API2::SymbolIdAndPositionStructHash& hashSymbolIdAndPositionStruct,
        const API2::DATA_TYPES::String& primaryClientCode,
        const boost::unordered_set< API2::DATA_TYPES::SYMBOL_ID >& symbolIdSet,
        const API2::DATA_TYPES::ExchangeId exchangeId = API2::CONSTANTS::CMD_ExchangeId_MAX,
        const API2::DATA_TYPES::ClientSegmentType segmentType = API2::DATA_TYPES::ClientSegmentType::MAX);

    /**
     * @brief getApiPositionForDealerClient - This function will be used for getting the Dealer + Client + SymbolId wise positions
     *                                      - for the symbols provided in symbolIdSet.
     *
     * @return hashSymbolIdAndPositionStruct - This is an unordered map where key will be symbol id
     *                                       - and value will be position struct and symbol Id will come
     *                                       - from symbolIdSet which will be provided when this method is called.
     *                                       - (For NEW RMS for now)if symbolIdSet is passed empty, all symbol positions
     *                                       - will be returned
     *
     * @param dealerId - dealerId
     * @param primaryClientCode - primary client code ( Can get from AccountDetails )
     * @param exchangeId - Exchange Id ( Can get from symbolStatic Data )
     *                     For  New RMS: It can be  MAX.
     * @param segmentType - Segment Type ( Can get from symbolStatic Data )
     *                      For New RMS: It can be MAX
     *  For New RMS if Exchangeid and  segment both are MAX than all symbol position will be return.
     *
     * @param symbolIdVec vector of symbol ids for those we need to find out positions.
     *        - For Old RMS: If there is no position created on the symbol Id it will return PositionStruct with default values ( i.e. 0 ).
     *
     * @example - Returned Structure Diagram (i.e. API2::SymbolIdAndPositionStructHash)
     *
     *          Dealer + Client + Exchange + Segment (e.g. Dealer( D1 ) + Client( C1 ) + Exchange( NSECM ) + Segment( CASH ) )
     *       ------------------------------------------
     *       |     Symbol Id     |    PositionStruct  |
     *       ------------------------------------------
     *       |     11504375      |        P1          |  Where P1,P2....PN are PositionStruct.
     *       |     11504376      |        P2          |
     *       |       ....        |       ....         |
     *       |     11601234      |        PN          |
     *       ------------------------------------------
     *
     * @note - If there is no position created for the given inputs it will return an empty position structure
     *         same goes for the invalid inputs.
     *       - Positions are coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     *  @return : For OLD RMS: If exchange id or segment type is MAX it will return false, other wise return true
     *                 For NEW RMS : Value of exchange id and segment type should be valid or invalid.
     *                          If  exchanege id is valid and segment type is invalid  or  vice versa then it will return false.
     *                          also if dealer not found then it will return false.
     *                          Otherwise return true
     *  Note: This method will return position and old position of Dealer+Client+Symbol same as shown in the net position book.
     *         - Trade give up has no impact on this position
     */
    bool getApiPositionForDealerClient(
        API2::SymbolIdAndPositionStructHash& hashSymbolIdAndPositionStruct,
        const API2::DATA_TYPES::CLIENT_ID dealerId,
        const API2::DATA_TYPES::String& primaryClientCode,
        const API2::DATA_TYPES::ExchangeId exchangeId = API2::CONSTANTS::CMD_ExchangeId_MAX,
        const API2::DATA_TYPES::ClientSegmentType segmentType = API2::DATA_TYPES::ClientSegmentType::MAX,
        const boost::unordered_set< API2::DATA_TYPES::SYMBOL_ID >& symbolIdSet = boost::unordered_set< API2::DATA_TYPES::SYMBOL_ID >());

    /**
     * @brief getApiDepositForClient - This function will get clientUsedDeposit for a particular client.
     *                                 In Case of OLD RMS it will return Deposit by CLIENT+ExchangeId+Segment
     *                                 In Case of NEW RMS it will return by CLIENT ID
     * @return clientUsedDeposit - Use to get the client used deposit.
     * @param primaryClientCode  - primary client code ( Can get from AccountDetails )
     * @param exchangeId         - exchangeId ( Can get from symbolStatic Data )
     *                             For OLD RMS: Value should be valid otherwise return false.
     *                             For NEW RMS:Value Does not matters, Only supported for Client level,
     * @param securityType       - securityType ( Can get from symbolStatic Data )
     *                             For OLD RMS: Value should be valid otherwise return false.
     *                             For NEW RMS:Value Does not matters, Only supported for Client level,
     * @description - Exchange Id and security type is required to apply the margin percentage
     *              - on the used deposit which varies w.r.t exchange and security type.
     *
     * @note - Will return clientUsedDeposit as it is if inputs are invalid.
     *       - clientUsedDeposit is coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     * @return false : if position not exist in the system or exchange id or security type is max otherwise return true.
     */
    bool getApiDepositForClient(
        API2::DATA_TYPES::INTEGER64& clientUsedDeposit,
        const API2::DATA_TYPES::String& primaryClientCode,
        const API2::DATA_TYPES::ExchangeId exchangeId = API2::CONSTANTS::CMD_ExchangeId_MAX,
        const API2::DATA_TYPES::SecurityType securityType  = API2::CONSTANTS::CMD_SecurityType_MAX );

    /**
     * @brief getApiDepositForDealer - This function will get dealerUsedDeposit for a particular dealer.
     * @return dealerUsedDeposit - Use to get the dealer used deposit.
     * @param dealerId          - Dealer Id
     * @param exchangeId        - exchangeId ( Can get from symbolStatic Data )
     * @param securityType      - securityType ( Can get from symbolStatic Data )
     * @description - Exchange Id and security type is required to apply the margin percentage
     *              - on the used deposit which varies w.r.t exchange and security type.
     *
     * @note - Will return dealerUsedDeposit as it is if inputs are invalid.
     *       - dealerUsedDeposit is coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     *      --- Will return false in case of NEW RMS(Not Handled), otherwise true
     */
    bool getApiDepositForDealer(
        API2::DATA_TYPES::INTEGER64& dealerUsedDeposit,
        const API2::DATA_TYPES::CLIENT_ID dealerId,
        const API2::DATA_TYPES::ExchangeId exchangeId,
        const API2::DATA_TYPES::SecurityType securityType );

    /**
     * @brief getApiOrderLimitsForClient - This function will get client order Limits for a client.
     *                                     In Case of OLD RMS it will return order limit by CLIENT+ExchangeId+Segment
     *                                     In Case of NEW RMS it will return by CLIENT ID
     * @return clientOrderLimitsApiStruct - Return order limits for the given client.
     * @param primaryClientCode - primary client code ( Can get from AccountDetails )
     * @param exchangeId - Exchange Id ( Can get from symbolStatic Data )
     * @param segmentType - Segment Type ( Can get from symbolStatic Data )
     *
     * @note - Will return clientOrderLimitsApiStruct as it is if inputs are invalid.
     *       - values are coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     * @return For OLD RMS: it will return false if Exchange id or segment will MAX, otherwise return true;
     *         For NEW RMS: Return false if limits not given from FE. otherwise false.
     */
    bool getApiOrderLimitsForClient(
        API2::COMMON::OrderLimitsApiStruct& clientOrderLimitsApiStruct,
        const API2::DATA_TYPES::String& primaryClientCode,
        const API2::DATA_TYPES::ExchangeId exchangeId = API2::CONSTANTS::CMD_ExchangeId_MAX,
        const API2::DATA_TYPES::ClientSegmentType segmentType = API2::DATA_TYPES::ClientSegmentType::MAX);

    /**
     * @brief getApiOrderLimitsForDealer - This function will get client order Limits for a dealer.
     * @param dealerOrderLimitsApiStruct - Return order limits for the given dealer.
     * @param dealerId - Dealer Id for which we need to get limits.
     *
     * @note - Will return dealerOrderLimitsApiStruct as it is if inputs are invalid.
     *       - values are coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     *        - For New RMS : Value of AggregateDeposit will be zero, because dealer level AggregateDeposit is not supported
     *
     * @return false if settings not given from FE or system error.
     */
    bool getApiOrderLimitsForDealer(
        API2::COMMON::OrderLimitsApiStruct& dealerOrderLimitsApiStruct,
        const API2::DATA_TYPES::CLIENT_ID dealerId );

    /**
     * @brief getApiGlobalClientPosition - Will get the global client wise position.
     *                                In Case of OLD RMS it will return Position by CLIENT+ExchangeId+Segment
     *                                In Case of NEW RMS it will return by CLIENT ID
     * @return outPos - Return the global client position.
     * @param primaryClientCode ( Can get from AccountDetails )
     * @param exchangeId (Not used in NEW RMS)( Can get from symbolStatic Data )
     * @param segmentType (Not used in NEW RMS)( Can get from symbolStatic Data )
     *
     * @note - If there is no position created for the given inputs it will return position structure as it is
     *         same goes for the invalid inputs.
     *       - Positions are coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     *       - In case using new RMS :
     *         - If margin revert on trade give up is enabled in the system, the same shall impact this position.
     *         - For old positions, if ignore old position(of client with a mapped cp code) is enabled in the system,
     *           then those old positions will not be present in this position as they are assumed to be reverted
     *           and shall not impact current day's trading.
     *
     * @return return false  if Invalid Client code or Position not found in the system
     *                     Otherwise return true
     *              For OLD RMS : it will return false if Exchange id or segment is MAX or
     *                   Invalid CLient code or Position not found in the system,
     *                   otherwise return true;
     */
    bool getApiGlobalClientPosition(
        API2::PositionStruct& outPos,
        const API2::DATA_TYPES::String& primaryClientCode,
        const API2::DATA_TYPES::ExchangeId exchangeId = API2::CONSTANTS::CMD_ExchangeId_MAX,
        const API2::DATA_TYPES::ClientSegmentType segmentType = API2::DATA_TYPES::ClientSegmentType::MAX);

    /**
     * @brief getApiGlobalDealerPosition - Will get global dealer wise position.
     * @return outPos - Return the global dealer wise position.
     * @param dealerId
     * @note - If there is no position created for the given inputs it will return position structure as it is
     *         same goes for the invalid inputs.
     *       - Positions are coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     *       - In case using new RMS :
     *         - If margin revert on trade give up is enabled in the system, the same shall impact this position.
     *         - For old positions, if ignore old position(of client with a mapped cp code) is enabled in the system,
     *           then those old positions will not be present in this position as they are assumed to be reverted
     *           and shall not impact current day's trading.
     *
     * @return true if dealer is valid and position exist in the system.
     *                Otherwise false.
     */

    bool getApiGlobalDealerPosition(
        API2::PositionStruct& outPos,
        const API2::DATA_TYPES::CLIENT_ID dealerId );

    /**
     * @brief getNetPnlForSymbolId - This function will be used for getting the
     *                                  Net Profit Loss for one symbol id.
     * @param netPnl - Returns the net profit loss of symbol id
     * @param symbolId - symbol id for which we need to get net profit loss.
     *
     * @note - Will return netPnl = 0 if inputs are invalid or if net profit loss is 0
     *       - netPnl is coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     */
    void getNetPnlForSymbolId(
        API2::DATA_TYPES::PRICE &netPnl,
        const API2::DATA_TYPES::SYMBOL_ID symbolId);

    /**
     * @brief getNetPnlForClient - This function will be used for getting the
     *                                  Net Profit Loss for client.
     * @param netPnl - Returns the net profit loss of client
     * @param primaryClientCode - client for which we need to get net profit loss.
     *
     *
     * @note - Will return netPnl = 0 if inputs are invalid or if net profit loss is 0
     *       - netPnl is coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     */
    void getNetPnlForClient(
        API2::DATA_TYPES::PRICE &netPnl,
        const API2::DATA_TYPES::String &primaryClientCode);

    /**
     * @brief getNetPnlForDealer - This function will be used for getting the
     *                                  Net Profit Loss for dealer.
     * @param netPnl - Returns the net profit loss of dealer
     * @param dealerId - dealer for which we need to get net profit loss.
     *
     *
     * @note - Will return netPnl = 0 if inputs are invalid or if net profit loss is 0
     *       - netPnl is coming with RMS_PRECISION_POSITION can be normalize to actual price
     *         using getRmsPositionPrecision() method.
     */
    void getNetPnlForDealer(
        API2::DATA_TYPES::PRICE &netPnl,
        const API2::DATA_TYPES::CLIENT_ID dealerId);

    /**
     * @brief getRmsPositionPrecision
     * @description - Return the RMS position precision in terms of multiplier
     *                For e.g.
     *                 - In Position for buy or sell value the price will
     *                   be adjusted according to RMS position precision.
     *
     *                 - If buy value is 234500 and RMS position precision is 10000
     *                 - then the actual value will be 23.45 i.e. ( 234500 / 10000 )
     *
     * @return API2::DATA_TYPES::RMS_POSITION_PRECISION
     */
    API2::DATA_TYPES::RMS_POSITION_PRECISION getRmsPositionPrecision();
    
    /**
     * @brief readConfForAlgoid - read AlgoId from conf file.
     * @param blockName - specify the strategy blockName
     * @param fileName - specify the fileName from where function reads the algoId 
     * @param strategy - specify the key from where algoId has to be taken
     * @param useExchName - strategyName will be prefixed with exchange 
     * @param useExchNameWithSegment - strategyName will be prefixed with exchange and segment
     *
     * Example : 
     *
     * Parameters passed ::
     *
     * blockName = OrderOnTime
     * strategy = _ALGO_ID
     * useExchName is true and useExchNameWithSegment is false
     * then exchangeName = NSE
     *
     * Corresponding block in file ::
     *
     * [OrderOnTime] 
     * NSE_ALGO_ID = 12345
     *
     * Example :
     *
     * Parameters passed ::
     *
     * blockName = FUT-FUT-RATIO
     * strategy = _FUT_FUT_RATIO_ALGO_ID
     * useExchName is true and useExchNameWithSegment is true
     * then exchangeName = NSEFO
     *
     * Corresponding block in file ::
     *
     * [FUT-FUT-RATIO] 
     * NSEFO_FUT_FUT_RATIO_ALGO_ID = 12345
     *
     * NOTE : useExchNameWithSegment will work if useExchName is true
     */
    void readConfForAlgoid(
        const std::string &blockName,
        const std::string &fileName,
        const std::string &strategy = "_ALGO_ID",
        bool useExchName = true,
        bool useExchNameWithSegment = false); 

    /**
     * @brief Used to make exchange name segment independent
     */
    std::string getExchNameSegmentIndependent(const std::string &exchangeName);

    /**
     * @brief reqSessionTimer - This function will return session time ( i.e Preopen, Open, PostClose )
     * @param marketId
     * @param session
     * Exchanges supported : NSECM, NSEFO, NSECDS, MCX
     * It will return 0 if not supported {exchange,session} pair is passed.
     */
    const DATA_TYPES::MicroTimeStamp reqSessionTimer(const DATA_TYPES::ExchangeId exchangeId,
        const API2::DATA_TYPES::TimerType timerType ) const ;

    std::unordered_set< std::string > _algoIdSet;

    /**
     * @brief setStrategyType -set the StrategyType in ImplStrategyType in of SGContextImpl
     * @description - take 2 arguments(vendorCode, isByPassNNFID) append and set to ImplStrategyType.
     * @param vendorCode
     * @param ByPassNNFID with default BYPASS_NNFID_DISABLED (It tell to bypass 13th digit of location id with '4' in case of NSE)
     * @return bool - If VendorCode is greater than 2 digits return false
     *              - or if ByPassNNFID is greater or equal to BYPASS_NNFID_MAX then return false.
     */
    bool setStrategyType(const short vendorCode, const API2::DATA_TYPES::BYPASS_NNFID byPassNNFID = API2::DATA_TYPES::BYPASS_NNFID_DISABLED );

    /**
     * @brief getClientCodesDealerExchangeSegmentWise
     * @description - This method will return all the clients mapped with the dealer + Exchange + segment
     *              - which is passed in the method arguments.
     *
     * @param clientCodeVec - This vector will be returned with client codes
     * @param dealerId    - Dealer Id
     * @param exchangeId  - Exchange Id ( Can get from symbolStatic Data )
     * @param segmentType - Segment Type ( Can get from symbolStatic Data )
     */

    void getClientCodesDealerExchangeSegmentWise(
        std::vector< API2::DATA_TYPES::String > &clientCodeVec,
        const API2::DATA_TYPES::CLIENT_ID dealerId,
        const API2::DATA_TYPES::ExchangeId exchangeId,
        const API2::DATA_TYPES::ClientSegmentType segmentType );
     
    /**
     * @brief This function will be used internally for strategies which will be using
     * execution style and have some spread types that are not supported in execution
     * style. Then execution style will call this function of the strategy to determine
     * if pov mandate is satisfied or not.
     */
    virtual bool isMandateSatisfiesGetFromStrategy();

    /**
    * @brief getRestApiMsg: Returns a string message to a rest API call.
    *                       When a rest API requesting an API msg is called,
    *                       then hft will provide callback to this function.
    *                       Client need to override this function in his API
    *                       strategy and return the string msg he want to send,
    *                       or else by default it will pass empty string.
    */
    virtual const std::string getRestApiMsg(){ return ""; };

    /**
     * @brief getClientId from strategy to save latency
     * @return 0
     */
    virtual int getClientId();

    /**
     * @brief isUnhedgeTrackerRequired To be removed from the strategy whose unhedge tracker handling is done
     *                added on temporary basis to save latency
     * @return true
     */
    virtual bool isUnhedgeTrackerRequired() const ;

    /**
     * @brief getStaticDataFromStrategy
     * @param symbolId
     * @return  nullptr
     */
    virtual  SG::SymbolStaticData* getStaticDataFromStrategy(API2::DATA_TYPES::SYMBOL_ID symbolId) const ;

  private:

    /**
       * @brief SGContext Private Default Constructor
       */
    SGContext();

    /**
       * @brief SGContext Private Copy Constructor Non-Construction-Copyable
       * @param other
       */
    SGContext( const SGContext& other ); // non construction-copyable

    /**
       * @brief operator = Non copyable
       * @return
       */
    SGContext& operator=( const SGContext& ); // non copyable

    /**
       * @brief pimpl
       */
    SGContextImpl *pimpl;


  };

} //namespace  API2
#endif // SGCONTEXT_H
