#ifndef SHARED_RESPONSE_H
#define SHARED_RESPONSE_H
#include <apiDataTypes.h>
#include <sharedCommands.h> 
#include <string>
namespace API2 
{


class OrderConfirmationImpl;

/**
 * @brief The OrderConfirmation class contains the Exchange Order Confirmation Message data.
 */
class OrderConfirmation
{
    /**
     * @brief pimpl
     */
    OrderConfirmationImpl *pimpl;

public:

    /**
     * @brief OrderConfirmation Constructor
     */
    OrderConfirmation();

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
     * @return StrategyId as API2::DATA_TYPES::STRATEGY_ID
     */
    DATA_TYPES::STRATEGY_ID  getStrategyId() const ;

    /**
     * @brief getClientId To get the client Id for which this Order belongs
     * @return ClientId as API2::DATA_TYPES::CLIENT_ID
     */
    DATA_TYPES::CLIENT_ID  getClientId() const ;

    /**
     * @brief getLimitPrice To get Limit Price set for Order
     * @return LimitPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getLimitPrice() const;

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
    DATA_TYPES::ERROR_CODE getErrorCode() const ;

    /**
     * @brief getTraderId
     * @return
     */
    DATA_TYPES::TRADER_ID getTraderId() const ;

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
    void setStrategyId(DATA_TYPES::STRATEGY_ID strategyId) ;

    /**
     * @brief setClientId
     * @param clientId
     */
    void setClientId(DATA_TYPES::CLIENT_ID clientId);

    /**
     * @brief setLimitPrice
     * @param limitPrice
     */
    void setLimitPrice(DATA_TYPES::PRICE limitPrice);

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
    void setErrorCode(DATA_TYPES::ERROR_CODE errorCode);

    /**
     * @brief setTraderId
     * @param traderId
     */
    void setTraderId(DATA_TYPES::TRADER_ID traderId);

    /**
     * @brief dump
     */
    void dump();
};

}
#endif 

