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
 *  muTrade API Version 2.0
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
       * @brief SGContext, Constructor
       * @param params, API2::StrategyParameters
       * @param sgName, Unique String for Strategy Name
       */
    SGContext(StrategyParameters *params, const std::string sgName);

    /**
       * @brief terminateSquareOffStrategy, Called to Terminate strategy and Square-Off all  Positions\n
       * Can be overriden \n
       * Default behaviour: \n
       * 1) Cancel All Orders \n
       * 2) Send Opposite Orders for closing Position \n
       * 3) Terminate the strategy \n
       */
    virtual void terminateSquareOffStrategy();

    /**
       * @brief terminateStrategy, Called to Terminate Strategy\n
       * Can be overriden \n
       * Default behaviour: \n
       * 1) Cancel All Pending Orders \n
       * 3) Terminate the strategy \n
       */
    virtual void terminateStrategy(bool cancelOrders=true);

    /***
       *May be removed
       */

    /**
     * @brief recoverInstrumentOrderId
     * @param confirmation
     * @param orderId
     * @return
     */
    virtual bool recoverInstrumentOrderId(const OrderConfirmation &confirmation, COMMON::InstrumentOrderId *orderId);


    /**
     * @brief usingSegment, To know whether a given exchange segment is being used in the strategy or not
     * @param exch, The DATA_TYPES::ExchangeId
     * @param securityType, The DATA_TYPES::SecurityType
     * @return
     */
    virtual bool usingSegment(
            const DATA_TYPES::ExchangeId &exch,
            const DATA_TYPES::SecurityType &securityType = CONSTANTS::CMD_SecurityType_MAX
            );

    /**
     * @brief startAlgo, function call to Start the Strategy
     * @param marketDataEventRequired, Set True to register for call-backs on Market-Data Event on registered Instruments
     * @return
     */
    void *startAlgo(bool marketDataEventRequired);


    /**
       * @brief getClientId, To get ClientId
       * @return
       */
    int getClientId();

    /**
       * @brief getParams, To get StartegyParameters
       * @return
       */
    StrategyParameters *getParams();

    /**
       * @brief getUpdateMktData, This function call will return the Pointer to API2::COMMON::MktData structure after updating it.\n
       * Not required if marketDataEventRequired is set to be True while starting the strategy using API2::SGContext::startAlgo()
       * @param symbolId, SymbolId for which MarketData is required
       * @return
       */
    COMMON::MktData *getUpdateMktData(SYMBOL_ID symbolId);

    /**
       * @brief getMktData, This function call will return the Pointer to API2::COMMON::MktData structure \n Here it will contain the last updated Market Snapshot
       * @param symbolId
       * @return
       */
    COMMON::MktData *getMktData(SYMBOL_ID symbolId);

    /**
       * @brief getNetMTM, This function will return net Mark To Market Profit and Loss for the strategy( sum of all Instruments being traded)
       * @return
       */
    SIGNED_LONG getNetMTM();

    /**
       * @brief getNetBookedPnl, This function will return net Booked Profit and Loss for the strategy( sum of all Instruments being traded)
       * @return
       */
    SIGNED_LONG getNetBookedPnl();

    /**
       * @brief getAddInstrument, To add a new Instrument in the strategy \n
       *    The Pointer to the added Instrument is set in instrument, passed as reference
       * @param instrument, Reference to the pointer to API2::COMMON::Instrument
       * @param symbolId, System Unique ID for the Instrument as API2::DATA_TYPES::SYMBOL_ID
       * @param regMktData, set True to register for Market Data for the Instrument
       * @param useSnapShot, Set True if Snapshot Feed is to be used and False to use TBT-Feed
       * @throw MarketDataSubscriptionFailedException
       */
    void getAddInstrument(COMMON::Instrument *&instrument,UNSIGNED_LONG symbolId, bool regMktData=false, bool useSnapShot=true);


    /**
     * @brief addInstrument, To add a new Instrument in the strategy \n
     * @param symbolId, System Unique ID for the Instrument
     * @param regMktData, If Market Feed required
     * @throw MarketDataSubscriptionFailedException
     */
    void addInstrument(UNSIGNED_LONG symbolId, bool regMktData=false);


    /**
     * @brief addInstrument, To add Instrument, Internal Method,not to be used.
     * @param instrument
     * @param regMktData
     * @throw MarketDataSubscriptionFailedException
     */
    void addInstrument(COMMON::Instrument *instrument, bool regMktData=false);


    /**
       * @brief getInstrumentList, To get list of all Instruments added for the requested SymbolId
       * @param instrumentList, reference to List of API2::COMMON::Instrument
       * @param symbolId, System Unique Id for the Instrument
       * @return
       */
    bool getInstrumentList(std::list<COMMON::Instrument *>&instrumentList, UNSIGNED_LONG symbolId);

    /**
       * @brief removeInstrument, To remove Instrument from the context. \n
       * Removing will remove all the data relating the Instrument's Position
       * @param instrument
       */
    void removeInstrument(COMMON::Instrument *instrument);

    /**
       * @brief removeAllInstruments, This will remove all Instrument from the registered Instrument list
       */
    void removeAllInstruments();

    /**
       * @brief registerSymbol, Register a API2::DATA_TYPES::SYMBOL_ID for market Data
       * @param symbolId, System Unique Id for the Instrument
       * @param isSnapShot, Set True if Snapshot Feed is to be used and False to use TBT-Feed
       */
    void registerSymbol(SYMBOL_ID symbolID, bool isSnapshot=true);

    /**
       * @brief registerSymbol, UnRegister a API2::DATA_TYPES::SYMBOL_ID for market Data
       * @param symbolId, System Unique Id for the Instrument
       * @throw MarketDataSubscriptionFailedException
       */
    void unregisterSymbol(SYMBOL_ID symbolId);

    /**
       * @brief unregisterAllSymbols, To unregister all Instruments for market feed.
       */
    void unregisterAllSymbols();

    /**
       * @brief updateQuote, To manually update Market Feed for all registered Instruments.\n
       * Not required if marketDataEventRequired is set to be True while starting the strategy using API2::SGContext::startAlgo()
       * @return, return True if there is a new updation in Market Data. False if no new updation.
       */
    bool updateQuote();

    /**
       * @brief updateQuote, To manually update Market Feed for requested API2::DATA_TYPES::SYMBOL_ID.\n
       * Not required if marketDataEventRequired is set to be True while starting the strategy using API2::SGContext::startAlgo()
       * @return, return True if there is a new updation in Market Data. False if no new updation.
       */
    bool updateQuote(UNSIGNED_LONG symbolId);

    /**
     * @brief getOrder, To get Pointer to Single Order using a clientOrderId
     * @param clOrderId
     * @return
     */
    API2::SingleOrder* getOrder(long clOrderId);


    /**
       * @brief getStrategyId, To get StartegyId of current running Strategy.
       * @return
       */
    API2::DATA_TYPES::STRATEGY_ID getStrategyId();

    /**
       * @brief setSGParameters, To set the pointer to StrategyParameters
       * @param params, Pointer to API2::StrategyParameters
       */
    void setSGParameters(StrategyParameters *params);

    /**
       * @brief getAdminTokenId
       * @return
       */
    UNSIGNED_LONG getAdminTokenId();

    /**
       * @brief setAdminTokenId
       * @param id
       */
    void setAdminTokenId(UNSIGNED_LONG id);

    /**
       * @brief sendStrategyResponse, To send a Response to the frontend
       * @param responseType, the response Type as DATA_TYPES::ResponseType
       * @param riskStatus, the Risk Status as DATA_TYPES::RiskStatus
       * @param strategyComment, the Strategy Comment as DATA_TYPES::StrategyComment
       */
    void sendStrategyResponse(
            DATA_TYPES::ResponseType responseType,
            DATA_TYPES::RiskStatus riskStatus,
            DATA_TYPES::StrategyComment strategyComment = CONSTANTS::RSP_StrategyComment_MAX
            );

    /**
       * @brief exitStrategy, To exit a strategy, terminates the Strategy thread and returns the StrategyDriver.
       */
    void exitStrategy();


    /**
       * @brief getDebugLog, To get Pointer to the DebugLog Object, used to dump debug messages. \n Sample Usage:\n
       *  DEBUG_MESSAGE(getDebugLog(),"<Message>");
       * @return
       */
    DebugLog *getDebugLog();

    /**
       * @brief getPendingQty, To get Pending Quantity of an Instrument
       * @param instrument, API2::COMMON::Instrument
       * @param mode, Ordermode as API2::CONSTANTS::CMD_OrderMode_BUY or API2::CONSTANTS::CMD_OrderMode_SELL
       * @return
       */
    UNSIGNED_LONG getPendingQty(COMMON::Instrument* instrument,
                                DATA_TYPES::OrderMode mode);

    /**
       * @brief getPendingQty, To get Pending Quantity of requested Order as orderId
       * @param orderId
       * @return
       */
    DATA_TYPES::QTY getPendingQty(COMMON::InstrumentOrderId *orderId);

    /**
       * @brief getClientOrderId, To get ClientOrderId of requested Order
       * @param orderId
       * @return
       */
    DATA_TYPES::CLORDER_ID getClientOrderId(COMMON::InstrumentOrderId *orderId);

    /**
       * @brief getOrderStatus, To get OrderStatus of requested Order
       * @param orderId
       * @return
       */
    DATA_TYPES::OrderStatus getOrderStatus(COMMON::InstrumentOrderId *orderId);

    /**
       * @brief getExchangeOrderId, To get Exchange OrderId of requested Order
       * @param orderId
       * @return
       */
    DATA_TYPES::String getExchangeOrderId(COMMON::InstrumentOrderId *orderId);



    /**
       * @brief run
       * @param marketDataEventRequired
       * @return
       */
    void* run(bool marketDataEventRequired);

    /**
       * @brief createNewOrder, To create a New Order for an instrument
       * @param order, Reference to Pointer of API2::SingleOrder, Pointer to created object will be set into this. For creating an Order
       * @param instrument, Pointer to the Instrument for which a new SingleOrder is to be created
       * @param qty, Order Quantity
       * @param discQty, Diclosed Order Quantity
       * @param mode, OrderMode as API2::CONSTANTS::CMD_OrderMode_BUY or API2::CONSTANTS::CMD_OrderMode_SELL
       * @param type, OrderType as API2::DATA_TYPES::OrderType
       * @param validity, Order Validity
       * @param product, Product
       * @param price, Price
       * @param stopPrice, Stop Price
       */
    void createNewOrder(SingleOrder *&order,
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
     * @brief setStrategyComment, To set the current Startegy Comment, Whenever a strategy Response is sent to frontend, this will be the  sent as the strategy Comment
     * @param com
     */
    void setStrategyComment(DATA_TYPES::StrategyComment com);
    /**
       * @brief sendNewOrder, To Send a new Order
       * @param riskStatus
       * @param instrument
       * @param order
       * @param orderId
       * @return
       */
    bool sendNewOrder(DATA_TYPES::RiskStatus &riskStatus,
                      COMMON::Instrument *instrument,
                      SingleOrder *&order,
                      COMMON::InstrumentOrderId *orderId=0);


    /**
       * @brief sendReplaceOrder, To send a replace Order
       * @param riskStatus
       * @param instrument
       * @param order
       * @param updateQuantity
       * @param orderId
       * @return
       */
    bool sendReplaceOrder(DATA_TYPES::RiskStatus &riskStatus,
                          COMMON::Instrument *instrument,
                          SingleOrder *&order,
                          bool updateQuantity=true,
                          COMMON::InstrumentOrderId *orderId=0);


    /**
       * @brief cancelOrder, To cancel an Order
       * @param orderId
       * @return
       */
    bool cancelOrder(COMMON::InstrumentOrderId *orderId);

    /**
       * @brief cancelOrders, To cancel all Orders ( Confirmed or Partial Filled )
       */
    void cancelOrders();

    /**
       * @brief sendCancelOrder, To Cancel Order
       * @param riskStatus, passed by reference, This is the risk status for sending Canceled Order
       * @param orderId
       * @return
       */
    bool sendCancelOrder(DATA_TYPES::RiskStatus &riskStatus, COMMON::InstrumentOrderId *orderId);

    /**
       * @brief insertNewOrderId, Creates and Inserts a new InstrumentOrderId Instance to the Instrument \n
       * for the requested OrderMode and sets the pointer to orderId
       * @param instrument, should be valid and Not null
       * @param orderId, should be NULL
       * @param mode, should be valid API2::CONSTANTS::CMD_OrderMode_BUY or API2::CONSTANTS::CMD_OrderMode_SELL
       */
    void insertNewOrderId(COMMON::Instrument *instrument,
                          COMMON::InstrumentOrderId *&orderId,
                          const DATA_TYPES::OrderMode &mode);

    /**
       * @brief dumpLogOrderConfirmation. Prints OrderConfirmation fields
       * @param confirmation
       */
    void dumpLogOrderConfirmation(const OrderConfirmation &confirmation);

    /**
       * @brief dumpLogSingleOrder. Prints Single Order fields
       * @param order
       */
    void dumpLogSingleOrder(SingleOrder *order);

    /**
       * @brief dumpLogInstrumentOrderId. Prints InstrumentOrderId Fields
       * @param orderId
       */
    void dumpLogInstrumentOrderId(const COMMON::InstrumentOrderId *orderId);

    /**
       * @brief processCurrentState Called as an event if Not configured to received marketData Event while Running Algo
       */
    virtual void processCurrentState();

    /**
       * @brief onDerivedMarketDataEvent Called if Configured to received marketData Event while Running Algo
       * @param symbolId    SymbolId of the Instrument that received marketData, SymbolId should be subscribed for Market Data while initializing
       */
    virtual void onDerivedMarketDataEvent(UNSIGNED_LONG symbolId);

    /**
       * @brief processAdminCommand Called when ever a command from frontend is issued.
       * @param command
       */
    virtual void processAdminCommand(DATA_TYPES::CommandCategory command){}


    /***NOTE ** Disconnection type to be created inside Data_TYPES and constants to be added */
    /**
       * @brief processDisconnection Called whenever a disconnection is received, disconnected entity to be determined from CommandCategory
       * @param command
       */
    virtual void processDisconnection(const DATA_TYPES::CommandCategory &command);

    /**
       * @brief onModifyStrategy  Called when strategy modify command is received
       */
    virtual void onModifyStrategy(AbstractUserParams *newParams) =0;

    /**
       * @brief onCommandTerminateStartegy Called when strategy receives Terminate Command from Frontend
       */
    virtual void onCommandTerminateStartegy();

    /**
       * @brief onCommandTerminateSqOffStrategy Called when strategy receives Terminate SqOff Command from Frontend
       */
    virtual void onCommandTerminateSqOffStrategy();

    /**
       * @brief onCommandPauseStartegy Called when strategy receives Pause Command from Frontend
       */
    virtual void onCommandPauseStartegy();

    /**
       * @brief onCommandRunStrategy Called when strategy receives Run Command from Frontend
       */
    virtual void onCommandRunStrategy();

    /**
       * @brief setInitState, To Set Initial state of the algo
       */
    virtual void setInitState(){}

    /**
       * @brief processOrderConfirmation, Call back after OrderConfirmation Processing is done, \n
       * Not necessary to override this, \n
       * To be overridden only If any additional Processing is reqd at the algo end
       * @param confirmation, Reference to the API2::OrderConformation
       */
    virtual void processOrderConfirmation(OrderConfirmation &confirmation){}


    /**
     * @brief onNewConfirmed, Call back when a new Order gets confirmed by exchange.
     * @param confirmation, Contains the information received from Exchange
     * @param orderId, Pointer to the API2::COMMON::InstrumentOrderId type
     */
    virtual void onNewConfirmed(OrderConfirmation &confirmation, COMMON::InstrumentOrderId *orderId){}

    /**
     * @brief onReplaceRejected, Call back when a replace order gets rejected by the exchange
     * @param confirmation, Contains the information received from Exchange
     * @param orderId, Pointer to the API2::COMMON::InstrumentOrderId type
     */
    virtual void onReplaceRejected(OrderConfirmation &confirmation, COMMON::InstrumentOrderId *orderId){}

    /**
     * @brief onCanceled, Call back when a cancel order gets accepted by the exchange
     * @param confirmation, Contains the information received from Exchange
     * @param orderId, Pointer to the API2::COMMON::InstrumentOrderId type
     */
    virtual void onCanceled(OrderConfirmation &confirmation, COMMON::InstrumentOrderId *orderId){}

    /**
     * @brief onCancelRejected, Call back when a cancel order gets rejected by the exchange
     * @param confirmation, Contains the information received from Exchange
     * @param orderId, Pointer to the API2::COMMON::InstrumentOrderId type
     */
    virtual void onCancelRejected(OrderConfirmation &confirmation, COMMON::InstrumentOrderId *orderId){}

    /**
     * @brief onReplaced, Call back when a Order gets replaced sucessfully at the exchange.
     * @param confirmation, Contains the information received from Exchange
     * @param orderId, Pointer to the API2::COMMON::InstrumentOrderId type
     */
    virtual void onReplaced(OrderConfirmation &confirmation, COMMON::InstrumentOrderId *orderId){}

    /**
     * @brief onNewRejected, Call back when a new order gets rejected by the exchange
     * @param confirmation, Contains the information received from Exchange
     * @param orderId, Pointer to the API2::COMMON::InstrumentOrderId type
     */
    virtual void onNewReject(OrderConfirmation &confirmation, COMMON::InstrumentOrderId *orderId){}

    /**
     * @brief onIOCCanceled, Call back when an IOC order gets canceled the exchange
     * @param confirmation, Contains the information received from Exchange
     * @param orderId, Pointer to the API2::COMMON::InstrumentOrderId type
     */
    virtual void onIOCCanceled(OrderConfirmation &Confirmation, COMMON::InstrumentOrderId *orderId){}

    /**
     * @brief onFilled, Call back when an order gets filled at the exchange
     * @param confirmation, Contains the information received from Exchange
     * @param orderId, Pointer to the API2::COMMON::InstrumentOrderId type
     */
    virtual void onFilled(OrderConfirmation &confirmation, COMMON::InstrumentOrderId *orderId){}

    /**
     * @brief onPartialFill, Call back when an order gets partially filled at the exchange
     * @param confirmation, Contains the information received from Exchange
     * @param orderId, Pointer to the API2::COMMON::InstrumentOrderId type
     */
    virtual void onPartialFill(OrderConfirmation &confirmation, COMMON::InstrumentOrderId *orderId){}


    /*********************************************************************/
    //----------------------Event Calllback Functions--------------------//

private:

    /**
       * @brief SGContext, Private Default Constructor
       */
    SGContext();

    /**
       * @brief SGContext, Private Copy Constructor, Non-Construction-Copyable
       * @param other
       */
    SGContext( const SGContext& other ); // non construction-copyable

    /**
       * @brief operator =, Non copyable
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
