#ifndef SGCONTEXT_H
#define SGCONTEXT_H

#include "sgCommon.h"
#include <sharedSingleOrder.h>
#include <sgApiParameters.h>
#include <sgDebugLogDefines.h>
#include <baseCommands.h>

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
       */
      SGContext(StrategyParameters *params, const std::string sgName);

      static void registerStrategy(boost::shared_ptr<SGContext>);
      SGContextImpl * getSGContextImpl();
      /***********************************************************/
      /************************ Factory Calls ********************/
      /***********************************************************/


      /**
       * @brief createNewInstrument To add a new Instrument in the strategy \n
       *    The Pointer to the added Instrument is set in instrument passed as reference
       * @param symbolId System Unique ID for the Instrument as API2::DATA_TYPES::SYMBOL_ID
       * @param regMktData set True to register for Market Data for the Instrument
       * @param useSnapShot Set True if Snapshot Feed is to be used and False to use TBT-Feed
       * @param useOhlc Set True if OHLC Heed is also required
       * @throw MarketDataSubscriptionFailedException
       * @return COMMON::Instrument Pointer
       */
      COMMON::Instrument *createNewInstrument(UNSIGNED_LONG symbolId,bool regMktData, bool useSnapShot=true, bool useOhlc=false);

      /**
       * @brief createNewInstrument To add a new Instrument in the strategy \n
       *    The Pointer to the added Instrument is set in instrument passed as reference
       * @param instrumentName Instrument Name
       *        Format:
       *        [ExchangeName] [Symbol] [Expiry(YYYYMMDD)] [StrikePrice] [C/P(For Call/Put)]
       *        Example:
       *        Cash Segment: NSE RELIANCE
       *        Futures Segment: NSE RELIANCE 20140828
       *        Options Segment: NSE RELIANCE 20140828 980.00 C
       * @param regMktData set True to register for Market Data for the Instrument
       * @param useSnapShot Set True if Snapshot Feed is to be used and False to use TBT-Feed
       * @param useOhlc Set True if OHLC Heed is also required
       * @return COMMON::Instrument Pointer
       * @throw MarketDataSubscriptionFailedException
       */
      COMMON::Instrument * createNewInstrument(const std::string &instrumentName, bool regMktData=false, bool useSnapShot=true, bool useOhlc=false);

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
          const DATA_TYPES::ProductType &product = CONSTANTS::CMD_ProductType_DELIVERY,
          const UNSIGNED_LONG &price=0,
          const UNSIGNED_LONG &stopPrice=0
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
       * @param riskStatus
       * @param instrument
       * @param order
       * @param orderId
       * @return
       */
      bool reqNewSingleOrder(DATA_TYPES::RiskStatus &riskStatus,
          COMMON::Instrument *instrument,
          SingleOrder *&order,
          COMMON::OrderId *orderId,
          bool isSpreadOrder=false);

      class OrderLegData{

        public:
          COMMON::Instrument *instrument;
          SingleOrder *order;
          COMMON::OrderId *orderId;
          OrderLegData(COMMON::Instrument *instrument):
            instrument(instrument),
            order(0),
            orderId(0){}

          OrderLegData():
            instrument(0),
            order(0),
            orderId(0){}
      };

      ///
      /// \brief reqNewMultilegOrder
      /// \param riskStatus
      /// \param data
      /// \return
      ///
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
       * @return
       */
      bool reqReplaceOrder(DATA_TYPES::RiskStatus &riskStatus,
          COMMON::Instrument *instrument,
          SingleOrder *&order,
          COMMON::OrderId *orderId);

      /**
       * @brief reqCancelOrder To Cancel Order
       * @param riskStatus passed by reference This is the risk status for sending Canceled Order
       * @param orderId
       * @return
       */
      bool reqCancelOrder(DATA_TYPES::RiskStatus &riskStatus, COMMON::OrderId *orderId);


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
       * @brief reqStartAlgo function call to Start the Strategy
       * @param marketDataEventRequired Set True to register for call-backs on Market-Data Event on registered Instruments
       * @param tradeTicksEventRequired Set True to register for call-backs on Trade Tick Events on registered Instruments
       * @return
       */
      void *reqStartAlgo(bool marketDataEventRequired, bool tradeTicksEventRequired);

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
       * @brief reqAddStrategyComment To set the current Startegy Comment Whenever a strategy Response is sent to frontend this will be the  sent as the strategy Comment
       * @param com
       */
      void reqAddStrategyComment(DATA_TYPES::StrategyComment com);

      /**
       * @brief reqSendStrategyResponse To send a Response to the frontend
       * @param responseType the response Type as DATA_TYPES::ResponseType
       * @param riskStatus the Risk Status as DATA_TYPES::RiskStatus
       * @param strategyComment the Strategy Comment as DATA_TYPES::StrategyComment
       */
      void reqSendStrategyResponse(
          DATA_TYPES::ResponseType responseType,
          DATA_TYPES::RiskStatus riskStatus,
          DATA_TYPES::StrategyComment strategyComment = CONSTANTS::RSP_StrategyComment_MAX
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
       * @brief reqQryMarketData This function call will return the Pointer to API2::COMMON::MktData structure \n Here it will contain the last updated Market Snapshot
       * @param symbolId
       * @return
       */
      COMMON::MktData *reqQryMarketData(SYMBOL_ID symbolId);


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
       *        Format:
       *        [ExchangeName] [Symbol] [Expiry(YYYYMMDD)] [StrikePrice] [C/P(For Call/Put)]
       *        Example:
       *        Cash Segment: NSE RELIANCE
       *        Futures Segment: NSE RELIANCE 20140828
       *        Options Segment: NSE RELIANCE 20140828 980.00 C
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
      API2::SingleOrder* reqQryOrder(long clOrderId);


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
       * @brief reqQrySendCustomResponse
       * @param customData
       * @param uiDataPair
       * @param rowId
       * @return
       */
      bool reqQrySendCustomResponse(const std::string &customData, const std::list<std::string> &uiDataPair, const int rowId);

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


      /***NOTE ** Disconnection type to be created inside Data_TYPES and constants to be added */
      /**
       * @brief onCMDDisconnection Called whenever a disconnection is received disconnected entity to be determined from CommandCategory
       * @param command
       */
      virtual void onCMDDisconnection(const DATA_TYPES::CommandCategory &command);

      /**
       * @brief onCMDModifyStrategy  Called when strategy modify command is received
       */
      virtual void onCMDModifyStrategy(AbstractUserParams *newParams) =0;

      /**
       * @brief onCMDTerminateStartegy Called when strategy receives Terminate Command from Frontend
       */
      virtual void onCMDTerminateStartegy();

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
       * @brief onFrozen Call back when an order gets frozen by exchange
       * @param confirmation Contains the information received from Exchange
       * @param orderId Pointer to the API2::COMMON::OrderId type
       */
      virtual void onFrozen(API2::OrderConfirmation &confirmation, API2::COMMON::OrderId *orderId){}

      /**
       * @brief onTimerEvent Call back when an timer set by strategy expires
       * This would be idle time to reset the timer if needed
       */
      virtual void onTimerEvent(){}


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
