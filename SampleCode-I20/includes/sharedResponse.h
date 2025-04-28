#ifndef SHARED_RESPONSE_H
#define SHARED_RESPONSE_H
#include <apiDataTypes.h>
#include <sharedCommands.h> 
#include <string>

namespace API2 
{
  /**
   * @brief The Strategy class contains response sent by strategy for different states like run, modify, terminate etc.
   */
  class Strategy
  {
    public:
      Strategy();
      explicit Strategy(const char* buf);
      int serialize(char* buf);

      DATA_TYPES::UCHAR getResponseType() const { return _responseType;}
      DATA_TYPES::UCHAR getRiskStatus() const { return _riskStatus;}
      DATA_TYPES::UCHAR getIsOffline() const { return _isOffline;}
      DATA_TYPES::UINTEGER32 getStrategyId() const { return _strategyId;}
      DATA_TYPES::UINTEGER32 getParentId() const { return _parentId;}
      /**
       * @brief Gets the admin token identifier
       * @return Admin token ID as 64-bit unsigned integer
       */
      DATA_TYPES::UINTEGER64 getAdminTokenId() const { return _adminTokenId;}
      /**
       * @brief Gets the sequence number of the response
       * @return Sequence number as 64-bit unsigned integer
       */
      DATA_TYPES::UINTEGER64 getSequenceNumber() const { return _sequenceNumber;}
      /**
       * @brief Gets the strategy comment indicator
       * @return Strategy comment as unsigned character
       */
      DATA_TYPES::UCHAR getStrategyComment() const { return _strategyComment; }
      /**
       * @brief Gets the termination reason type
       * @return Reason for termination as TerminationReasonType enum
       */
      DATA_TYPES::TerminationReasonType getTerminationReasonType() const { return _terminationReasonType; }
      /**
       * @brief Gets the custom comment string for the strategy
       * @return Constant reference to strategy custom comment string
       */
      const DATA_TYPES::String& getStrategyCustomComment() const { return _strategyCustomComment; }

      void setResponseType(DATA_TYPES::UCHAR responseType){ _responseType = responseType;}
      void setRiskStatus(DATA_TYPES::UCHAR riskStatus){ _riskStatus = riskStatus;}
      void setIsOffline(DATA_TYPES::UCHAR isOffline){ _isOffline = isOffline;}
      void setStrategyId(DATA_TYPES::UINTEGER32 strategyId) { _strategyId = strategyId;}
      /**
       * @brief Sets the parent identifier
       * @param pId Parent ID as 32-bit unsigned integer
       */
      void setParentId(DATA_TYPES::UINTEGER32 pId) { _parentId = pId;}
      /**
       * @brief Sets the admin token identifier
       * @param adminTokenId Admin token ID as 64-bit unsigned integer
       */
      void setAdminTokenId(DATA_TYPES::UINTEGER64 adminTokenId) { _adminTokenId = adminTokenId;}
      /**
       * @brief Sets the sequence number of the response
       * @param sequenceNumber Sequence number as 64-bit unsigned integer
       */
      void setSequenceNumber(DATA_TYPES::UINTEGER64 sequenceNumber) { _sequenceNumber = sequenceNumber;}
      /**
       * @brief Sets the strategy comment indicator
       * @param strategyComment Strategy comment as unsigned character
       */
      void setStrategyComment(DATA_TYPES::UCHAR strategyComment) { _strategyComment = strategyComment; }
      /**
       * @brief Sets the termination reason type
       * @param terminationReasonType Reason for termination as TerminationReasonType enum
       */
      void setTerminationReasonType(DATA_TYPES::TerminationReasonType terminationReasonType) { _terminationReasonType = terminationReasonType; }
      /**
       * @brief Sets the custom comment string for the strategy
       * @param strategyCustomComment Constant reference to strategy custom comment string
       */
      void setStrategyCustomComment(const DATA_TYPES::String &strategyCustomComment) { _strategyCustomComment = strategyCustomComment; }
      /**
       * @brief Dumps the contents of the shared response for debugging
       * @details Prints all member variables in a formatted manner
       */
      void dump();
    private:
      DATA_TYPES::UCHAR _responseType;    // Value (SUCCESS / FAILURE)
      DATA_TYPES::UCHAR _riskStatus;     // Reason for RMS Failure
      DATA_TYPES::UCHAR _strategyComment;
      DATA_TYPES::String _strategyCustomComment;
      DATA_TYPES::UCHAR _isOffline;
      DATA_TYPES::UINTEGER32 _strategyId;
      DATA_TYPES::UINTEGER32 _parentId; //Id of parent strategy(strategy from which another strategy is invoked)
      DATA_TYPES::UINTEGER64 _adminTokenId;
      DATA_TYPES::UINTEGER64 _sequenceNumber; // Sequence number to sync up offline responses to RMS/Admin screen
      DATA_TYPES::TerminationReasonType _terminationReasonType;         // Strategy termination reason
  };

  class OrderConfirmationImpl;

  /**
   * @brief The OrderConfirmation class contains the Exchange Order Confirmation Message data.
   */
  class OrderConfirmation
  {
    /**
     * @brief pimpl
     */
    //    OrderConfirmationImpl *pimpl;

    DATA_TYPES::CLORDER_ID _clOrderId;
    DATA_TYPES::SYMBOL_ID _symbolId;
    DATA_TYPES::QTY _lastFillQuantity;
    DATA_TYPES::PRICE  _lastFillPrice;
    DATA_TYPES::PRICE  _origLastFillPrice;

    /**
     * @brief _exchangeEntryTime  - for nse, it'll contain last activity reference time,
     *                              for other exchanges, it's entry time
     *                              Note : in case of NSE, in confirmed confirmation,
     *                                      entry time, last modify time, and last activity reference time
     *                                      all are same
     */
    DATA_TYPES::EXCHANGE_TIME  _exchangeEntryTime;
    DATA_TYPES::EXCHANGE_TIME  _exchangeModifyTime;
    TYPE_DEFS::STRATEGY_ID  _strategyId;
    TYPE_DEFS::CLIENT_ID  _clientId;
    // Limit price will come in Market to Limit order conversion
    DATA_TYPES::PRICE _limitPrice;
    DATA_TYPES::PRICE _origLimitPrice;
    UNSIGNED_CHARACTER _orderStatus;
    UNSIGNED_CHARACTER _orderMode;
    // Adding following two fields for market making
    DATA_TYPES::QTY _orderQuantity;
    DATA_TYPES::PRICE _orderPrice;
    DATA_TYPES::PRICE _origOrderPrice;
    DATA_TYPES::QTY _iocCanceledQuantity;
    DATA_TYPES::CLORDER_ID _originalClOrderId;
    TYPE_DEFS::ERROR_CODE _errorCode;
    DATA_TYPES::ENUM _orderCategory;
    DATA_TYPES::PRICE  _lastFillPrice1;
    DATA_TYPES::PRICE  _lastFillPrice2;
    char _exchangeOrderId[CONF_EXCHANGE_ORDERID_SIZE];
    char _tradeId[TRADEID_SIZE];
    char _strategyTypeSqnNo[STRATEGY_TYPE_SQNNO_SIZE];
    API2::TYPE_DEFS::OrderValidity _orderValidity;
    API2::TYPE_DEFS::GTD_Date _gtdDate;
    API2::TYPE_DEFS::ConfirmationType _confirmationType;
    char _fixClOrderId[FIX_ORDERID_SIZE];

    //Adding following two fields for Trade Backup
    DATA_TYPES::ENUM _bookType;
    char _openCloseFlag;

    //Adding following two fields for Stop Orders Support in OrderBook
    DATA_TYPES::PRICE _stopPrice;
    TYPE_DEFS::OrderType _orderType;
    
    //Adding this field to identify portfolio and client id for uhedge
    API2::TYPE_DEFS::STRATEGY_ID _childStrategyId;

    API2::TYPE_DEFS::STRATEGY_ID _parentStrategyId;

    CREATE_FIELD_ACCESS_SPECIFIER(API2::ExchangeAdapterDetails,ExchangeAdapterDetails,protected);

    TYPE_DEFS::ProductType _productType;

    TYPE_DEFS::PlatformType _platformType;

    CREATE_FIELD( DATA_TYPES::QTY, DisclosedQuantity );

    /**
     * @brief _algoId
     */
    DATA_TYPES::AlgoId  _algoId;

    /**
     * @brief _algoCategory
     */
    TYPE_DEFS::AlgoCategory _algoCategory;

    char _generatedOrderId[GENERATED_CLORDID_SIZE] = {0};

    /**
     * @brief MasterClientOrderId - Unique Order Id, same for all order states
     */
    CREATE_FIELD( DATA_TYPES::CLORDER_ID, MasterClientOrderId );

    /**
     * @brief MktPriceProtection - Market Price Protection
     */
    CREATE_FIELD( DATA_TYPES::PERCENTAGE, MktPriceProtection );

    /**
     * @brief SelfTradeFlag
     */
    CREATE_FIELD( DATA_TYPES::SelfTradeOrderFlag, SelfTradeFlag );

    /**
     * @brief GiveupFlag: this response is recieved from exchange, if participant code is set for client
     *            Default value is P(Pending).
     *            A(Approved), R(Rejected)  will be recieved from exchange.
     */
    CREATE_FIELD_WITH_DEFAULT_VALUE(DATA_TYPES::GiveUpFlag, GiveupFlag, 0);

    /*
     * @brief ModifiedBy - Client Id of the user who is modifying/updating the order.
     *                               For example: Order placed by D1 and then modified by A1 then,
     *                               ModifiedBy = A1.
     */
    CREATE_FIELD( SIGNED_LONG, ModifiedBy );

    /**
     * @brief CREATE_FIELD - Store Throttle End time
     */
    CREATE_FIELD(SIGNED_LONG, ThrottleEndTime);
        
    /**
     * @brief IsSquareOffOrder - To identify if the order is square off order triggered from strategy
     */
    CREATE_FIELD( UNSIGNED_SHORT, IsSquareOffOrder) ;

    UNSIGNED_SHORT _errorTextSize = 0;

    char* _errorText = nullptr;

    UNSIGNED_SHORT _basketIdSize = 0;

    char* _basketId = nullptr;

    public:

    UNSIGNED_SHORT getErrorTextSize() const;
    void setErrorTextSize(UNSIGNED_SHORT errorTextSize);
    
    const char *getErrorText() const;  
    
    std::string getErrorTextAsString() const;
    
    char * getRefErrorText(); 
    
    void setErrorText(const std::string &value );
    
    void initializeErrorText();

    void clearErrorText();

    void resetErrorText();

    OrderConfirmation(const OrderConfirmation& other);
    OrderConfirmation &operator =(const OrderConfirmation& );

    void clone(const OrderConfirmation& other);


    /**
     * @brief ~OrderConfirmation
     */
    virtual ~OrderConfirmation();

    /**
     * @brief OrderConfirmation Constructor
     */
    OrderConfirmation();

    OrderConfirmation(
        DATA_TYPES::CLORDER_ID &clientOrderId,
        DATA_TYPES::SYMBOL_ID &symbolId,
        TYPE_DEFS::STRATEGY_ID &strategyId,
        TYPE_DEFS::CLIENT_ID &clientId,
        DATA_TYPES::OrderStatus &orderStatus,
        DATA_TYPES::OrderMode &orderMode,
        DATA_TYPES::QTY &orderQty,
        DATA_TYPES::PRICE &orderPrice,
        DATA_TYPES::CLORDER_ID &origClOrdId);


    /**
     * @brief OrderConfirmation
     * @param clientOrderId
     * @param symbolId
     * @param strategyId
     * @param clientId
     * @param orderStatus
     * @param orderMode
     * @param orderType
     * @param orderQty
     * @param orderPrice
     * @param origClOrdId
     * @param stopPrice
     * @param productType
     * @param platformType
     */
    OrderConfirmation(
        DATA_TYPES::CLORDER_ID &clientOrderId,
        DATA_TYPES::SYMBOL_ID &symbolId,
        TYPE_DEFS::STRATEGY_ID &strategyId,
        TYPE_DEFS::CLIENT_ID &clientId,
        DATA_TYPES::OrderStatus &orderStatus,
        DATA_TYPES::OrderMode &orderMode,
        TYPE_DEFS::OrderType &orderType,
        DATA_TYPES::QTY &orderQty,
        DATA_TYPES::PRICE &orderPrice,
        DATA_TYPES::CLORDER_ID &origClOrdId,
        const DATA_TYPES::PRICE &stopPrice,
        const TYPE_DEFS::ProductType &productType,
        const TYPE_DEFS::PlatformType &platformType);


    /**
     * @brief initialize
     */
    void initialize();

    /**
     * @brief getClOrderId To get Unique Client Order Id, sent to exchange at the time of Order Sending
     * @return ClientOrderId as API2::DATA_TYPES::CLORDER_ID
     */
    DATA_TYPES::CLORDER_ID getClOrderId() const;

    /**
     * @brief getExchangeOrderId To get Exchange Order Id of the Order.
     * @return exchangeOrderId as API2::DATA_TYPES::String
     */
    DATA_TYPES::String getExchangeOrderId() const ;

    /**
     * @brief getSymbolId To get unique SymbolID, which is a unique Identifier for an Instrument in the system.
     * @return SymbolId as API2::DATA_TYPES::SYMBOL_ID
     */
    DATA_TYPES::SYMBOL_ID getSymbolId() const ;

    /**
     * @brief getLastFillQuantity To get Last filled quantity
     * @return LastFillQuantity as API2::DATA_TYPES::QTY
     */
    DATA_TYPES::QTY  getLastFillQuantity() const;

    /**
     * @brief getOrigLastFillPrice To get last filled Price
     * @return origLastFillPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrigLastFillPrice() const;

    /**
     * @brief getLastFillPrice To get last filled Price
     * @return LastFillPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getLastFillPrice() const;

    /**
     * @brief getExchangeEntryTime To get Time of Order Entry in the exchange
     * @return ExchangeEntryTime as API2::DATA_TYPES::EXCHANGE_TIME
     */
    DATA_TYPES::EXCHANGE_TIME  getExchangeEntryTime() const;

    /**
     * @brief getExchangeModifyTime To get Time of Order Modification in the exchange
     * @return ExchangeModifyTime as API2::DATA_TYPES::EXCHANGE_TIME
     */
    DATA_TYPES::EXCHANGE_TIME  getExchangeModifyTime() const;

    /**
     * @brief getStrategyId To get The Strategy Id to which this Order belongs to
     * @return StrategyId as API2::TYPE_DEFS::STRATEGY_ID
     */
    TYPE_DEFS::STRATEGY_ID  getStrategyId() const ;

    /**
     * @brief getClientId To get the client Id for which this Order belongs
     * @return ClientId as API2::TYPE_DEFS::CLIENT_ID
     */
    TYPE_DEFS::CLIENT_ID  getClientId() const ;

    /**
     * @brief getLimitPrice To get Limit Price set for Order
     * @return LimitPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getLimitPrice() const;


#ifdef FRONTEND_COMPILATION

    /**
     * @brief getOrigLastFillPrice To get last filled Price
     * @return origLastFillPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrigLastFillPrice() const;

    /**
     * @brief getOrigLimitPrice To get Limit Price set for Order
     * @return LimitPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrigLimitPrice() const;

    /**
     * @brief getOrigOrderPrice To get the Original Order Price
     * @return OrderPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrigOrderPrice() const;

    /**
     * @brief setOrigLastFillPrice
     * @param price
     */
    void setOrigLastFillPrice(DATA_TYPES::PRICE price);

    /**
     * @brief setLimitPrice
     * @param limitPrice
     */
    void setOrigLimitPrice(DATA_TYPES::PRICE limitPrice);

    /**
     * @brief setOrigOrderPrice
     * @param price
     */
    void setOrigOrderPrice(DATA_TYPES::PRICE price) ;

#endif

    /**
     * @brief getOrigLimitPrice To get Limit Price set for Order
     * @return LimitPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrigLimitPrice() const;

    /**
     * @brief getOrderStatus To get the OrderStatus
     * @return returns OrderStatus as API2::DATA_TYPES::OrderStatus
     */
    DATA_TYPES::OrderStatus getOrderStatus() const ;

    /**
     * @brief getOrderMode To getOrderMode (Buy/Sell) for the order
     * @return OrderMode as API2::DATA_TYPES::OrderMode
     */
    DATA_TYPES::OrderMode getOrderMode() const ;

    /**
     * @brief getOrderQuantity To get th Order Quantity
     * @return OrderQuantity as API2::DATA_TYPES::QTY
     */
    DATA_TYPES::QTY  getOrderQuantity() const ;

    /**
     * @brief getOrderPrice To get the Order Price
     * @return OrderPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrderPrice() const;

    /**
     * @brief getOrigOrderPrice To get the Original Order Price
     * @return OrderPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrigOrderPrice() const;

    /**
     * @brief getIOCCanceledQuantity
     * @return
     */
    DATA_TYPES::QTY getIOCCanceledQuantity() const ;

    /**
     * @brief getOriginalClOrderId
     * @return
     */
    DATA_TYPES::CLORDER_ID getOriginalClOrderId() const ;

    /**
     * @brief getTradeId
     * @return Trade Id as API2::DATA_TYPES::String
     */
    DATA_TYPES::String getTradeId() const ;

    const char *getTradeIdCharPtr() const;

    const char *getExchangeOrderIdCharPtr() const;

    /**
     * @brief getErrorCode
     * @return
     */
    TYPE_DEFS::ERROR_CODE getErrorCode() const ;

    /**
     * @brief getTraderId
     * @return
     */
    DATA_TYPES::TRADER_ID getTraderId() const ;

    /**
     * @brief getStrategyTypeSqnNo
     * @return
     */
    DATA_TYPES::String getStrategyTypeSqnNo() const ;

    /**
     * @brief getOrderValidity
     * @return
     */
    API2::TYPE_DEFS::OrderValidity getOrderValidity() const ;

    /**
     * @brief getGTDDate
     * @return
     */
    API2::TYPE_DEFS::GTD_Date getGTDDate() const ;

    /**
     * @brief getConfirmationType To get whether the confirmation is self made or from exchange
     * @return API2::TYPE_DEFS::ConfirmationType
     */
    API2::TYPE_DEFS::ConfirmationType getConfirmationType() const;

    /**
     * @brief getFixClOrderId To get Fix Client OrderId of the order
     * @return FixClOrderId as API2::DATA_TYPES::String
     */
    DATA_TYPES::String getFixClOrderId() const ;

    /**
     * @brief getFixClOrderIdCharPtr To get Fix Client OrderId of the order
     * @return FixClOrderId as char*
     */
    char* getFixClOrderIdCharPtr() ;

    /**
     * @brief getAlgoId 
     * @return 
     */
    API2::DATA_TYPES::AlgoId getAlgoId() const;


    /**
     * @brief getAlgoCategory
     * @return
     */
    API2::TYPE_DEFS::AlgoCategory getAlgoCategory() const;

    /**
     * @brief getGeneratedOrderId
     * @return
     */
    std::string getGeneratedOrderId() const ;

    const char* getGeneratedOrderIdPtr() const;

    /**
     * @brief setStrategytypeSqnNo
     * @param strategyTypeSqnNo
     */
    void setStrategyTypeSqnNo( char strategyTypeSqnNo[]);

    /**
     * @brief setStrategytypeSqnNo
     * @param strategyTypeSqnNo
     */
    void setStrategyTypeSqnNo( std::string strategyTypeSqnNo);
    /**
     * @brief setStrategytypeSqnNo
     * @param strategyTypeSqnNo
     */
    void setStrategyTypeSqnNo( const char * strategyTypeSqnNo);

    /**
     * @brief setClOrderId
     * @param clOrderId
     */

    void setClOrderId(DATA_TYPES::CLORDER_ID clOrderId);

    /**
     * @brief setExchangeOrderId
     * @param exchangeOrderId
     */
    void setExchangeOrderId(char exchangeOrderId[]);

    /**
     * @brief setExchangeOrderId
     * @param exchangeOrderId
     */
    void setExchangeOrderId(std::string exchangeOrderId);

    /**
     * @brief setSymbolId
     * @param symbolId
     */
    void setSymbolId(DATA_TYPES::SYMBOL_ID symbolId);

    /**
     * @brief setLastFillQuantity
     * @param qty
     */
    void setLastFillQuantity(DATA_TYPES::QTY qty);

    /**
     * @brief setOrigLastFillPrice
     * @param price
     */
    void setOrigLastFillPrice(DATA_TYPES::PRICE price);

    /**
     * @brief setLastFillPrice
     * @param price
     */
    void setLastFillPrice(DATA_TYPES::PRICE price);

    /**
     * @brief setExchangeEntryTime
     * @param exchangeEntryTime
     */
    void setExchangeEntryTime(DATA_TYPES::EXCHANGE_TIME exchangeEntryTime);

    /**
     * @brief setExchangeModifyTime
     * @param exchangeModifyTime
     */
    void setExchangeModifyTime(DATA_TYPES::EXCHANGE_TIME exchangeModifyTime);

    /**
     * @brief setStrategyId
     * @param strategyId
     */
    void setStrategyId(TYPE_DEFS::STRATEGY_ID strategyId) ;

    /**
     * @brief setClientId
     * @param clientId
     */
    void setClientId(TYPE_DEFS::CLIENT_ID clientId);

    /**
     * @brief setLimitPrice
     * @param limitPrice
     */
    void setLimitPrice(DATA_TYPES::PRICE limitPrice);

    /**
     * @brief setLimitPrice
     * @param limitPrice
     */
    void setOrigLimitPrice(DATA_TYPES::PRICE limitPrice);

    /**
     * @brief setOrderStatus
     * @param orderStatus
     */
    void setOrderStatus(DATA_TYPES::OrderStatus orderStatus) ;

    /**
     * @brief setOrderMode
     * @param orderMode
     */
    void setOrderMode(DATA_TYPES::OrderMode orderMode) ;

    /**
     * @brief setOrderQuantity
     * @param quantity
     */
    void setOrderQuantity(DATA_TYPES::QTY quantity);

    /**
     * @brief setOrderPrice
     * @param price
     */
    void setOrderPrice(DATA_TYPES::PRICE price) ;

    /**
     * @brief setOrigOrderPrice
     * @param price
     */
    void setOrigOrderPrice(DATA_TYPES::PRICE price) ;

    /**
     * @brief setIOCCanceledQuantity
     * @param quantity
     */
    void setIOCCanceledQuantity(DATA_TYPES::QTY quantity) ;

    /**
     * @brief setOriginalClOrderId
     * @param originalClOrderId
     */
    void setOriginalClOrderId(DATA_TYPES::CLORDER_ID originalClOrderId);

    /**
     * @brief setSequenceNumber
     * @param sequenceNumber
     */
    void setSequenceNumber(DATA_TYPES::SEQUENCE_NUMBER sequenceNumber);

    /**
     * @brief setTradeId
     * @param tradeId
     */
    void setTradeId(char tradeId[]);

    /**
     * @brief setTradeId
     * @param tradeId
     */
    void setTradeId(std::string tradeId);

    /**
     * @brief setErrorCode
     * @param errorCode
     */
    void setErrorCode(TYPE_DEFS::ERROR_CODE errorCode);

    /**
     * @brief setTraderId
     * @param traderId
     */
    void setTraderId(DATA_TYPES::TRADER_ID traderId);

    /**
     * @brief setOrderCategory
     * @param orderCategory
     */
    void setOrderCategory(DATA_TYPES::ENUM orderCategory);

    /**
     * @brief setLastFillPrice1
     * @param lastFillPrice1
     */
    void setLastFillPrice1(DATA_TYPES::PRICE lastFillPrice1);

    /**
     * @brief setLastFillPrice2
     * @param lastFillPrice2
     */
    void setLastFillPrice2(DATA_TYPES::PRICE lastFillPrice2);

    /**
     * @brief setOrderValidity
     * @param orderValidity
     */
    void setOrderValidity( API2::TYPE_DEFS::OrderValidity orderValidity );

    /**
     * @brief getGTDDate
     * @param gtdDate
     */
    void setGTDDate( TYPE_DEFS::GTD_Date gtdDate );

    /**
     * @brief setConfirmationType To set the confirmation is self made or from exchange
     * @param API2::TYPE_DEFS::ConfirmationType
     */
    void setConfirmationType( API2::TYPE_DEFS::ConfirmationType confType ) ;

    /**
     * @brief setFixClOrderId To set Fix Client OrderId of the order
     * @return
     */
    void setFixClOrderId( char fixOrderId[]) ;

    /**
     * @brief setFixClOrderId To set Fix Client OrderId of the order
     * @return
     */
    void setFixClOrderId(std::string fixOrderId);

    /**
     * @brief dump
     */
    void dump() const;

    /**
     * @brief getOrderCategory
     * @return
     */
    DATA_TYPES::ENUM getOrderCategory() const;

    /**
     * @brief getLastFillPrice1
     * @return
     */
    DATA_TYPES::PRICE getLastFillPrice1() const;

    /**
     * @brief getLastFillPrice2
     * @return
     */
    DATA_TYPES::PRICE getLastFillPrice2() const;

    /**
     * @brief getBookType
     * @return DATA_TYPES::ENUM
     */
    DATA_TYPES::ENUM getBookType() const;

    /**
     * @brief getOpenCloseFlag
     * @return char
     */
    char getOpenCloseFlag() const;

    /**
     * @brief setBookType
     * @param DATA_TYPES::ENUM
     */
    void setBookType(DATA_TYPES::ENUM bookType);

    /**
     * @brief setOpenCloseFlag
     * @param char
     */
    void setOpenCloseFlag(char openCloseFlag);

    /**
     * @brief getStopPrice
     * @return DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE getStopPrice() const;

    /**
     * @brief getOrderType
     * @return TYPE_DEFS::OrderType
     */
    TYPE_DEFS::OrderType getOrderType() const;

    /**
     * @brief setStopPrice
     * @param DATAT_TYPES::PRICE
     */
    void setStopPrice(DATA_TYPES::PRICE stopPrice);

    /**
     * @brief setOrderType
     * @param TYPE_DEFS::OrderType
     */
    void setOrderType(TYPE_DEFS::OrderType orderType);

    /* @brief getChildStrategyId
     *  @return
     **/
    TYPE_DEFS::STRATEGY_ID getChildStrategyId() const;


    /* @brief getParentStrategyId
     * @return
     */
    TYPE_DEFS::STRATEGY_ID getParentStrategyId() const;
      
    /**
     * @brief setParentStrategyId
     * @param strategyId
     */
    void setParentStrategyId(TYPE_DEFS::STRATEGY_ID strategyId);

    /**
     * @brief setChildStrategyId
     * @param strategyId
     **/
    void setChildStrategyId(TYPE_DEFS::STRATEGY_ID strategyId);

    /**
     * @brief getProductType
     * @return TYPE_DEFS::ProductType
     */
    TYPE_DEFS::ProductType getProductType() const;

    /**
     * @brief getPlatformType
     * @return TYPE_DEFS::PlatformType
     */
    TYPE_DEFS::PlatformType getPlatformType() const;

    /**
     * @brief setPlatformType
     * @param platformType
     */
    void setPlatformType(TYPE_DEFS::PlatformType platformType);

    /**
     * @brief setProductType
     * @param productType
     */
    void setProductType(TYPE_DEFS::ProductType productType);

    /**
     * @brief setAlgoId
     * @param algoId
     */
    void setAlgoId(const DATA_TYPES::AlgoId algoId);

    /**
     * @brief setAlgoCategory
     * @param AlgoCategory
     */
    void setAlgoCategory(const TYPE_DEFS::AlgoCategory AlgoCategory);

    /**
     * @brief setGeneratedOrderId
     * @param generatedOrderId
     */
    void setGeneratedOrderId(const std::string  &generatedOrderId);

    /**
     * @brief setGeneratedOrderId
     * @param generatedOrderId
     */
    void setGeneratedOrderId( const char generatedOrderId[] );

    /**
     * @brief getString - This method returns string for confirmation dump.
     * @return
     */
    const std::string getString() const;

    /**
     * @brief getExchangeModifyTimeEpoch  - get modify time in epoch
     * @return
     */
    const ::API2::DATA_TYPES::EXCHANGE_TIME getExchangeModifyTimeEpoch() const;

    /**
     * @brief getExchangeEntryTimeEpoch - get entry time in epoch
     * @return
     */
    const ::API2::DATA_TYPES::EXCHANGE_TIME getExchangeEntryTimeEpoch() const;

    UNSIGNED_SHORT getBasketIdSize() const;
    void setBasketIdSize(UNSIGNED_SHORT basketIdSize);
    
    const char *getBasketId() const;
    
    std::string getBasketIdAsString() const;
    
    char * getRefBasketId();
    
    void setBasketId(const std::string &value );
    
    void initializeBasketId();

    void clearBasketId();

    void resetBasketId();
  };


#ifndef FRONTEND_COMPILATION

  class PreTradeConfirmation
  {
    DATA_TYPES::CLORDER_ID _clOrderId;
    std::string _exchangeOrderId;
    DATA_TYPES::SYMBOL_ID _symbolId;
    DATA_TYPES::QTY _orderQuantity;
    DATA_TYPES::PRICE _orderPrice;
    DATA_TYPES::QTY _lastFillQuantity;
    DATA_TYPES::PRICE _lastFillPrice;
    DATA_TYPES::EXCHANGE_TIME _exchangeModifyTime;
    DATA_TYPES::STRATEGY_ID _strategyId;
    DATA_TYPES::CLIENT_ID _clientId;
    UNSIGNED_CHARACTER _orderMode;

    public:
    PreTradeConfirmation();
    PreTradeConfirmation(
        const DATA_TYPES::CLORDER_ID& clOrderId,
        const std::string& exchangeOrderId,
        const DATA_TYPES::SYMBOL_ID& symbolId,
        const DATA_TYPES::QTY& orderQuantity,
        const DATA_TYPES::PRICE& orderPrice,
        const DATA_TYPES::QTY& lastFillQuantity,
        const DATA_TYPES::PRICE& lastFillPrice,
        const DATA_TYPES::EXCHANGE_TIME& exchangeModifyTime,
        const DATA_TYPES::STRATEGY_ID& strategyId,
        const DATA_TYPES::CLIENT_ID& clientId,
        UNSIGNED_CHARACTER orderMode
        );

    std::string getString();

    void setClOrderId(DATA_TYPES::CLORDER_ID clOrderId);
    void setExchangeOrderId(const std::string& exchangeOrderId);
    void setSymbolId(DATA_TYPES::SYMBOL_ID symbolId);
    void setOrderQuantity(DATA_TYPES::QTY orderQuantity);
    void setOrderPrice(DATA_TYPES::PRICE orderPrice);
    void setLastFillQuantity(DATA_TYPES::QTY lastFillQuantity);
    void setLastFillPrice(DATA_TYPES::PRICE lastFillPrice);
    void setExchangeModifyTime(DATA_TYPES::EXCHANGE_TIME exchangeModifyTime);
    void setStrategyId(DATA_TYPES::STRATEGY_ID strategyId);
    void setClientId(DATA_TYPES::CLIENT_ID clientId);
    void setOrderMode(UNSIGNED_CHARACTER orderMode);

    DATA_TYPES::CLORDER_ID getClOrderId() const;
    std::string getExchangeOrderId() const;
    const std::string& getRefExchangeOrderId() const;
    DATA_TYPES::SYMBOL_ID getSymbolId() const;
    DATA_TYPES::QTY getOrderQuantity() const;
    DATA_TYPES::PRICE getOrderPrice() const;
    DATA_TYPES::QTY getLastFillQuantity() const;
    DATA_TYPES::PRICE getLastFillPrice() const;
    DATA_TYPES::EXCHANGE_TIME getExchangeModifyTime() const;
    DATA_TYPES::STRATEGY_ID getStrategyId() const;
    DATA_TYPES::CLIENT_ID getClientId() const;
    UNSIGNED_CHARACTER getOrderMode() const;
  };

#endif 

  /////////////////////////////////////////////////////////////////////////

  /**
   * @brief The UnhedgeTrackerCustomData class : Manages custom data which is to be sent to Front_end
   *                                             to show undhedged qty.
   */
  class UnhedgeTrackerCustomData
  {
    CREATE_FIELD( DATA_TYPES::STRATEGY_ID, StrategyId );
    CREATE_FIELD( DATA_TYPES::STRATEGY_ID, AdminTokenId );
    CREATE_FIELD( DATA_TYPES::OrderMode, OrderMode );
    CREATE_FIELD( DATA_TYPES::SYMBOL_ID, SymbolId );
    CREATE_FIELD( DATA_TYPES::PRICE, UnhedgePrice );
    CREATE_FIELD( DATA_TYPES::QTY, UnhedgeQuantity );
    CREATE_FIELD( DATA_TYPES::TransactionType, TransactionType );
    CREATE_FIELD( DATA_TYPES::String, RemarksStr );
    CREATE_FIELD( UNSIGNED_INTEGER,  LegType);
    CREATE_FIELD( DATA_TYPES::String, PrimaryClientCode);
    CREATE_FIELD( DATA_TYPES::String, UniqueIdForUnhedgeTracker);
    CREATE_FIELD( UNSIGNED_SHORT, UnhedgeStrategyType);

    public:
    UnhedgeTrackerCustomData();
    explicit UnhedgeTrackerCustomData(const char* buf);
    int serialize(char* buf);
    void dump() const;
  };

  /////////////////////////////////////////////////////////////////////////
}
#endif 

