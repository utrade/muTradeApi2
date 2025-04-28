#ifndef SHARED_SINGLE_ORDER_H
#define SHARED_SINGLE_ORDER_H
#include <apiDataTypes.h>
#include <sgSymbolDataDefines.h>
#include <sharedCommands.h>
#include <sharedResponse.h>
#include <boost/shared_ptr.hpp>
#include <cmdDefines.h>

#ifndef FRONTEND_COMPILATION 
#include <money.h>
#endif 

extern "C"
{
  namespace API2
  {

    class SingleOrderImpl;
    class SpreadContractImpl;

    /**
     * @brief The SingleOrder class. This wrapper is used for sending Single Leg Orders.
     * Usage: Create an object for This using API2::SGContext::createNewOrder
     */
    class SingleOrder
    {

      protected:

        //    SingleOrderImpl *pimpl;

        /**
         * @brief _clOrdId
         */
        DATA_TYPES::CLORDER_ID _clOrdId;

        /**
         * @brief _origClientOrderId
         */
        DATA_TYPES::CLORDER_ID _origClientOrderId;

        /**
         * @brief _symbolId
         */
        DATA_TYPES::SYMBOL_ID _symbolId;  // From symbolId, exchange will infer which exchange

        /**
         * @brief _clientId
         */
        DATA_TYPES::CLIENT_ID _clientId;

        /**
         * @brief _quantity
         */
        DATA_TYPES::QTY _quantity;

        /**
         * @brief _disclosedQuantity
         */
        DATA_TYPES::QTY _disclosedQuantity;

        /**
         * @brief _filledQuantity
         */
        DATA_TYPES::QTY _filledQuantity;

        /**
         * @brief _oldQuantity
         */
        DATA_TYPES::QTY _oldQuantity;

        /**
         * @brief _price
         */
        DATA_TYPES::PRICE _price;

        /**
         * @brief _marketPriceProtection
         */
        DATA_TYPES::PRICE_PROTECTION _marketPriceProtection;

        /**
         * @brief _stopPrice
         */
        DATA_TYPES::PRICE _stopPrice;

        /**
         * @brief _exchangeEntryTime
         */
        DATA_TYPES::EXCHANGE_TIME _exchangeEntryTime;

        /**
         * @brief _exchangeModifyTime
         */
        DATA_TYPES::EXCHANGE_TIME  _exchangeModifyTime;

        /**
         * @brief _transactionType
         */
        DATA_TYPES::ENUM _transactionType;

        /**
         * @brief _orderMode
         */
        DATA_TYPES::ENUM _orderMode;

        /**
         * @brief _orderValidity
         */
        DATA_TYPES::ENUM _orderValidity;

        /**
         * @brief _gtdDate
         */
        DATA_TYPES::GTD_Date _gtdDate; 
        /**
         * @brief _productType
         */
        DATA_TYPES::ProductType _productType;

        /**
         * @brief _orderType
         */
        DATA_TYPES::ENUM _orderType;

        /**
         * @brief _settlementPeriod
         */
        DATA_TYPES::SETTLEMENT_PERIOD _settlementPeriod; // Default 10 days

        /**
         * @brief _orderStatus
         */
        DATA_TYPES::ENUM _orderStatus; // Needed for OMS

        //    /**
        //     * @brief _traderId
        //     */
        //    DATA_TYPES::TRADER_ID _traderId;

        /**
         * @brief _exchangeOrderId
         */
        char  _exchangeOrderId[EXCHANGE_ORDERID_SIZE];

#ifdef CTP_ORDER_CONTIGENCY_SUPPORT_ENABLED
        CREATE_FIELD(UNSIGNED_CHARACTER, OrderContigencyFlag);
#endif

        AccountDetail _AccountDetails;

        //    CREATE_FIELD(API2::AccountDetail, AccountDetails);
        //    boost::shared_ptr<AccountDetail> _AccountDetails;
        /**
         * @brief _orderCategory
         */
        DATA_TYPES::ENUM _orderCategory;

        /**
         * @brief strategy type mainly for MCX
         */

        short _strategyType;

#ifdef FRONTEND_COMPILATION

        /**
         * @brief book type for trade orders
         */
        DATA_TYPES::ENUM _bookType;

        /**
         * @brief Open Close Flag for trade orders
         */
        char _openCloseFlag;

#endif 

#ifdef MULTI_CURRENCY_SUPPORT
        CREATE_FIELD( Currency::Money, PriceCurrency);
#endif
        CREATE_FIELD(short, SelfTradeCancelFlag);

        /*
         * @brief : load balancing id, kind of a strategy id which is to be used in load balancing
         * */
        DATA_TYPES::STRATEGY_ID _loadBalancingId;

        /*
         * @brief : Fix Client OrderId
         * */
        CREATE_FIELD( std::string, FixClOrderId );
       
        /**
         * @brief PlatformType
         */
        CREATE_FIELD(API2::DATA_TYPES::PlatformType, PlatformType);

#ifndef FRONTEND_COMPILATION   
        /*
         * @brief : Price1 and Price2 used in case of Spread Orders
         * */
        CREATE_FIELD(SIGNED_INTEGER, Price1);
        CREATE_FIELD(SIGNED_INTEGER, Price2);

         /*
         * @brief : Is trigger order/not
         * */
        CREATE_FIELD( API2::DATA_TYPES::ENUM, IsTriggerOrder );
        
        /*
         * @brief : Is trade capture report/not
         * */
        CREATE_FIELD( API2::DATA_TYPES::ENUM, IsTradeCaptureReport );

        /*
         * @brief : Vector of Trading Session Ids
         * */
        std::vector<std::string> _vectorTradingSessIds;
#endif 

        /** 
         * @brief  ChildStrategyId - additional Strategy Id Currently being used to identify portfolios and client Ids
         * in orders placed by uHedge ( Strategy Id : 1 )
         **/
        CREATE_FIELD(DATA_TYPES::STRATEGY_ID, ChildStrategyId);
     
        /**
         * @brief ParentStrategyId - strategyId used in case of Invoked strategy
         */
        CREATE_FIELD(DATA_TYPES::STRATEGY_ID, ParentStrategyId);


        /**
         * @brief AlgoId , MarketSession
         */
        CREATE_FIELD(DATA_TYPES::AlgoId,AlgoId);
        CREATE_FIELD(DATA_TYPES::MarketSessionType,MarketSession);

        char _generatedOrderId[BUF_SIZE_60] = {0};
        /**
         * @brief _ExchangeAdapterDetails - adapter details for the order
         */
        CREATE_FIELD(ExchangeAdapterDetails,ExchangeAdapterDetails);

        /**
         * @brief MasterClientOrderId - Unique Order Id, same for all order states
         */
        CREATE_FIELD( DATA_TYPES::CLORDER_ID, MasterClientOrderId );

        /*
         * @brief ModifiedBy - Client Id of the user who is modifying/updating the order.
         *                     For example: Order placed by D1 and then modified by A1 then,
         *                     ModifiedBy = A1.
         */
        CREATE_FIELD( SIGNED_LONG, ModifiedBy );

        /**
         * @brief Customtraderid : Used to get custom traderId from API
         * strategy in case of NSE.
         */
        CREATE_FIELD( DATA_TYPES::CUSTOM_TRADER_ID, CustomTraderId) ;

        /**
         * @brief isSquareOffOrder : Used to differentiate square off orders triggered from stg
         */
        CREATE_FIELD( UNSIGNED_SHORT, IsSquareOffOrder) ;

        /**
         * @brief basketId : Used to get basketId from API
         */
        char  _basketId[BASKET_ID_SIZE];

      public :

        //    SingleOrderImpl *getImpl()const{return pimpl;}
        //    void setImpl(SingleOrderImpl *impl) {pimpl = impl;}

        SingleOrder(const SingleOrder& other);
        SingleOrder& operator =(const SingleOrder& );

        SingleOrder *clone();


        /**
         * @brief dump
         */
        virtual void dump() const ;

        virtual ~SingleOrder();

        /**
         * @brief ApiSingleOrder
         */
        SingleOrder();

        /**
         * @brief initialize
         */
        void initialize();

        /**
         * @brief ApiSingleOrder
         * @param symbolId
         * @param clientOrderId
         * @param staticData
         * @param clientId
         * @param quantity
         * @param disclosedQuantity
         * @param price
         * @param stopPrice
         * @param type
         * @param product
         * @param mode
         * @param validity
         * @param parentStrategyId
         * @param strategyType
         * @param accountDetail
         */
        SingleOrder(
            const DATA_TYPES::SYMBOL_ID& symbolId,
            const DATA_TYPES::CLORDER_ID& clientOrderId,
            const SymbolStaticData &staticData,
            const DATA_TYPES::CLIENT_ID& clientId,
            const DATA_TYPES::QTY& quantity,
            const DATA_TYPES::QTY& disclosedQuantity,
            const DATA_TYPES::PRICE& price,
            const DATA_TYPES::PRICE& stopPrice,
            DATA_TYPES::OrderType type,
            DATA_TYPES::ProductType product,
            DATA_TYPES::OrderMode mode,
            DATA_TYPES::OrderValidity validity,
            const DATA_TYPES::STRATEGY_ID& parentStrategyId,
            short strategyType,
            DATA_TYPES::AlgoId algoId,
            DATA_TYPES::MarketSessionType marketSession,
            const AccountDetail& accountDetails
            ); 

        /**
         * @brief ApiSingleOrder
         * @param symbolId
         * @param staticData
         * @param clientId
         * @param quantity
         * @param disclosedQuantity
         * @param price
         * @param stopPrice
         * @param type
         * @param product
         * @param mode
         * @param validity
         * @param traderId
         */
        SingleOrder(DATA_TYPES::SYMBOL_ID symbolId,
            const SymbolStaticData& staticData,
            DATA_TYPES::CLIENT_ID clientId,
            DATA_TYPES::QTY quantity,
            DATA_TYPES::QTY disclosedQuantity,
            DATA_TYPES::PRICE price,
            DATA_TYPES::PRICE stopPrice,
            DATA_TYPES::OrderType type, // Limit, Market, Stop, Stop Limit
            DATA_TYPES::ProductType product, // Intraday, Delivery
            DATA_TYPES::OrderMode mode, // Buy, Sell
            DATA_TYPES::OrderValidity validity, // GTD, FOK etc.
            DATA_TYPES::TRADER_ID traderId,
            DATA_TYPES::AlgoId algoId,
            DATA_TYPES::MarketSessionType marketSession,
            const AccountDetail &accountDetails=AccountDetail());

        SingleOrder(const DATA_TYPES::SYMBOL_ID &symbolId,
            DATA_TYPES::TransactionType transactionType,
            DATA_TYPES::PlatformType platformType);

        /**
         * @brief initialize
         * @param symbolId
         * @param clientOrderId
         * @param staticData
         * @param clientId
         * @param quantity
         * @param disclosedQuantity
         * @param price
         * @param stopPrice
         * @param type
         * @param product
         * @param mode
         * @param validity
         * @param parentStrategyId
         * @param strategyType
         * @return
         */
        int  initialize(DATA_TYPES::SYMBOL_ID symbolId,
            DATA_TYPES::CLORDER_ID clOrdId,
            const SymbolStaticData& staticData,
            DATA_TYPES::CLIENT_ID clientId,
            DATA_TYPES::QTY quantity,
            DATA_TYPES::QTY disclosedQuantity,
            DATA_TYPES::PRICE price,
            DATA_TYPES::PRICE stopPrice,
            DATA_TYPES::OrderType type, // Limit, Market, Stop, Stop Limit
            DATA_TYPES::ProductType product, // Intraday, Delivery
            DATA_TYPES::OrderMode mode, // Buy, Sell
            DATA_TYPES::OrderValidity validity, // GTD, FOK etc.
            DATA_TYPES::STRATEGY_ID parentStrategyId,
            short strategyType,
            DATA_TYPES::AlgoId algoId,
            DATA_TYPES::MarketSessionType marketSession,
            const AccountDetail &accountDetails= AccountDetail());

        /**
         * @brief getExchangeSecurityId
         * @return ExchangeSecurityId
         */
        SIGNED_LONG getExchangeSecurityId() const ;

        /**
         * @brief getExchangeId returns Exchange ID
         * @return API2::DATA_TYPES::ExchangeId
         */
        DATA_TYPES::ExchangeId getExchangeId() const;

        /**
         * @brief getClOrdId To get the unique Client Order Id (unique to the system)
         * @return API2::DATA_TYPES::CLORDER_ID
         */
        DATA_TYPES::CLORDER_ID getClOrdId() const ;

        /**
         * @brief getOrigClientOrderId  If the order is modified, it returns the Parent Order's ClientOrderId
         * @return API2::DATA_TYPES::CLORDER_ID
         */
        DATA_TYPES::CLORDER_ID getOrigClientOrderId() const ;

        /**
         * @brief getExchangeOrderId It returns Exchange's Order Id
         * @return const char pointer to ExchangeOrderId
         */
        const char* getExchangeOrderId() const ;

        /**
         * @brief getSymbolId To get SymbolId
         * @return
         */
        DATA_TYPES::SYMBOL_ID getSymbolId() const ;

        /**
         * @brief getClientId
         * @return API2::DATA_TYPES::CLIENT_ID
         */
        DATA_TYPES::CLIENT_ID getClientId() const ;

        /**
         * @brief getQuantity To get Order quantity
         * @return API2::DATA_TYPES::QTY
         */
        DATA_TYPES::QTY getQuantity() const ;

        /**
         * @brief getDisclosedQuantity To get Disclosed Order Qty
         * @return API2::DATA_TYPES::QTY
         */
        DATA_TYPES::QTY getDisclosedQuantity() const ;

        /**
         * @brief getFilledQuantity To get Filled Quantity
         * @return API2::DATA_TYPES::QTY
         */
        DATA_TYPES::QTY getFilledQuantity() const ;

        /**
         * @brief getOldQuantity
         * @return
         */
        DATA_TYPES::QTY getOldQuantity() const ;

        /**
         * @brief getPrice To get the Limit price provided for order
         * @return API2::DATA_TYPES::PRICE
         */
        DATA_TYPES::PRICE getPrice() const ;

        /**
         * @brief getMarketPriceProtection To get the Limit price provided for order
         * @return API2::DATA_TYPES::PRICE_PROTECTION
         */
        DATA_TYPES::PRICE_PROTECTION getMarketPriceProtection() const ;

        /**
         * @brief getStopPrice To get the stop Price provided for Order
         * @return API2::DATA_TYPES::PRICE
         */
        DATA_TYPES::PRICE getStopPrice() const ;

        /**
         * @brief getExchangeEntryTime To get the Time for Order entry at Exchange
         * @return API2::DATA_TYPES::EXCHANGE_TIME (epoch_time)
         */
        DATA_TYPES::EXCHANGE_TIME getExchangeEntryTime() const ;

        /**
         * @brief getExchangeModifyTime To get the Time for Order modification at Exchange
         * @return API2::DATA_TYPES::EXCHANGE_TIME
         */
        DATA_TYPES::EXCHANGE_TIME getExchangeModifyTime() const ;

        /**
         * @brief getTransactionType To get thr transaction type for the Order
         * tbd
         * @return The API2::DATA_TYPES::Transaction_TYPE
         */
        DATA_TYPES::TransactionType getTransactionType() const ;

        /**
         * @brief getOrderMode To get the Order Mode
         * @return
         */
        DATA_TYPES::OrderMode getOrderMode() const ;

        /**
         * @brief getOrderValidity
         * @return
         */
        DATA_TYPES::OrderValidity getOrderValidity() const ;

        /**
         * @brief getGTDDate
         * @return
         */
        DATA_TYPES::GTD_Date getGTDDate() const;

        /**
         * @brief getProductType
         * @return
         */
        DATA_TYPES::ProductType getProductType() const ;

        /**
         * @brief getOrderType
         * @return
         */
        DATA_TYPES::OrderType getOrderType() const ;

        /**
         * @brief getSettlementPeriod
         * @return
         */
        DATA_TYPES::SETTLEMENT_PERIOD getSettlementPeriod() const;

        /**
         * @brief getOrderStatus
         * @return
         */
        DATA_TYPES::OrderStatus getOrderStatus() const;

        // Required for BSE

        /**
         * @brief getDeltaQty
         * @return
         */
        int getDeltaQty() const;

        /**
         * @brief getTraderId
         * @return
         */
        DATA_TYPES::TRADER_ID getTraderId() const;
        
        /**
         * @brief getStrategyType
         * @return
         */
        short  getStrategyType() const;

        /**
         * @brief getLoadBalancingId
         * @return
         */
        DATA_TYPES::STRATEGY_ID getLoadBalancingId() const;

        /**
         * @brief setStrategyType
         * @return
         */
        void   setStrategyType( short );

        /**
         * @brief setClOrdId
         * @param clOrdId
         */
        void setClOrdId(DATA_TYPES::CLORDER_ID clOrdId);

        /**
         * @brief setOrigClientOrderId
         * @param origClientOrderId
         */
        void setOrigClientOrderId(DATA_TYPES::CLORDER_ID origClientOrderId) ;

        /**
         * @brief setExchangeOrderId
         * @param exchangeOrderId
         */
        void setExchangeOrderId(char exchangeOrderId[]);

        /**
         * @brief setExchangeOrderId
         * @param exchangeOrderId
         */
        void setExchangeOrderId(const char *exchangeOrderId);

        /**
         * @brief setExchangeOrderId
         * @param exchangeOrderId
         */
        void setExchangeOrderId(const std::string& exchangeOrderId);

        /**
         * @brief setSymbolId
         * @param symbolId
         */
        void setSymbolId(DATA_TYPES::SYMBOL_ID symbolId);

        /**
         * @brief setClientId
         * @param clientId
         */
        void setClientId(DATA_TYPES::CLIENT_ID clientId);

        /**
         * @brief setQuantity
         * @param quantity
         */
        void setQuantity(DATA_TYPES::QTY quantity) ;

        /**
         * @brief setDisclosedQuantity
         * @param disclosedQuantity
         */
        void setDisclosedQuantity(DATA_TYPES::QTY disclosedQuantity);

        /**
         * @brief setFilledQuantity
         * @param filledQuantity
         */
        void setFilledQuantity(DATA_TYPES::QTY filledQuantity);

        /**
         * @brief setOldQuantity
         * @param oldQuantity
         */
        void setOldQuantity(DATA_TYPES::QTY oldQuantity) ;

        /**
         * @brief setPrice
         * @param price
         */
        void setPrice(DATA_TYPES::PRICE price);

        /**
         * @brief setMarketPriceProtection
         * @param marketPriceProtection
         */
        void setMarketPriceProtection(DATA_TYPES::PRICE_PROTECTION marketPriceProtection);

        /**
         * @brief setStopPrice
         * @param stopPrice
         */
        void setStopPrice(DATA_TYPES::PRICE stopPrice) ;

        /**
         * @brief setExchangeEntryTime
         * @param exchangeEntryTime
         */
        void setExchangeEntryTime(DATA_TYPES::EXCHANGE_TIME exchangeEntryTime) ;

        /**
         * @brief setExchangeModifyTime
         * @param exchangeModifyTime
         */
        void setExchangeModifyTime(DATA_TYPES::EXCHANGE_TIME exchangeModifyTime) ;

        /**
         * @brief setTransactionType
         * @param transactionType
         */
        void setTransactionType(DATA_TYPES::TransactionType transactionType);

        /**
         * @brief setOrderMode
         * @param orderMode
         */
        void setOrderMode(DATA_TYPES::OrderMode orderMode) ;

        /**
         * @brief setOrderValidity
         * @param orderValidity
         */
        void setOrderValidity(DATA_TYPES::OrderValidity orderValidity) ;

        /**
         * @brief setGTDDate
         * @param gtdDate
         */
        void setGTDDate(DATA_TYPES::GTD_Date gtdDate);

        /**
         * @brief setProductType
         * @param productType
         */
        void setProductType(DATA_TYPES::ProductType productType) ;

        /**
         * @brief setOrderType
         * @param orderType
         */
        void setOrderType(DATA_TYPES::OrderType orderType) ;

        /**
         * @brief setSettlementPeriod
         * @param settlementPeriod
         */
        void setSettlementPeriod(DATA_TYPES::SETTLEMENT_PERIOD settlementPeriod) ;

        /**
         * @brief setOrderStatus
         * @param orderStatus
         */
        void setOrderStatus(DATA_TYPES::OrderStatus orderStatus) ;

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

#ifdef FRONTEND_COMPILATION

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
         * @param bookType
         */
        void setBookType(DATA_TYPES::ENUM bookType);

        /**
         * @brief setOpenCloseFlag
         * @param openCloseFlag
         */
        void setOpenCloseFlag(char openCloseFlag);

#endif 

        /**
         * @brief getAccountDetails
         * @return
         */
        AccountDetail getAccountDetails() const;

        /**
         * @brief getRefAccountDetails
         * @return
         */
        AccountDetail &getRefAccountDetails();

        /**
         * @brief setAccountDetails
         * @param detail
         */
        void setAccountDetails(const AccountDetail& detail);

        /**
         * @brief setLoadBalancingId
         * @param detail
         */
        void setLoadBalancingId(DATA_TYPES::STRATEGY_ID loadBalancingId);
        
        /**
         * @brief insertTradingSessId
         * @return
         */
        void insertTradingSessionId( const std::string tradingSessId );

        /**
         * @brief deleteTradingSessId
         * @return
         */
        void deleteTradingSessionId( std::string tradingSessId );

        /**
         * @brief setVectorTradingSessId
         * @return
         */
        void setVectorTradingSessId( const std::vector<std::string>& vecTradingSessId );

        /**
         * @brief getLocationId
         * @return
         */
        long getLocationId() const;

        /**
         * @brief getOrderCategory
         * @return
         */
        DATA_TYPES::ENUM getOrderCategory() const;
        
        /**
         * @brief getVectorTradingSessionIds
         * @return
         */
        std::vector<std::string> getVectorTradingSessionIds() const ;
        
        /**
         * @brief getRefVectorTradingSessionIds
         * @return
         */
        std::vector<std::string>& getRefVectorTradingSessionIds() ;

        /**
         * @brief getBasketId
         * @return const char pointer to BasketId
         */
        const char* getBasketId() const ;

        /**
         * @brief setBasketId
         * @param basketId
         */
        void setBasketId(char basketId[]);

        /**
         * @brief setBasketId
         * @param basketId
         */
        void setBasketId(const std::string& basketId);

        /**
         * @brief setBasketId
         * @param basketId
         */
        void setBasketId(const char *basketId);


    };


  }
}
#endif
