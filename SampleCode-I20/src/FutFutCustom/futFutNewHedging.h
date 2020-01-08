#ifndef FUTFUTNEWHEDGING_H
#define FUTFUTNEWHEDGING_H
#include"price.h"
#include"structure.h"



namespace SampleFutFutArbitrage{

struct FrontEndParameters;
class FutFutArbitrage;
class Price;

/**
 * @brief Hedging Class, handles Hedge Methods and Variables
 */
class Hedging
{

    /**
     * @brief Pointer to Store address of commonUtilities of the SGContext Class
     * @returnType Utilities Structure Pointer
     */
    Utilities* _commonUtilities;

    /**
     * @brief pointer to a const stuct FrontEnd Parameters
     * @returnType pointer
     */
    const struct FrontEndParameters* _userParams;

    /**
     * @brief riskStatus
     * @returnType riskStatus
     */
    API2::DATA_TYPES::RiskStatus _riskStatus;

    /**
     * @brief Kept as reference of _terminateCheck in Derived SGContext Class
     * @returnType Boolean
     */
    bool _isTerminate;

    /**
     * @brief last Order Quantity
     * @returnType Boolean
     */
    API2::DATA_TYPES::QTY _lastOrderQuantity;
    
    /**
     * @brief hedge Freeze qty
     */
    API2::DATA_TYPES::QTY _hedgingFreezeQty;

public:

    /**
     * @brief Pointer to accesss Price Methods for Hedging
     * @returnType Price Class Pointer
     */
    Price hedgingPrice;

    /**
     * @brief Constructor
     * @param userParams
     * @param commonUtilities
     * @param isTerminate
     */
    Hedging(const FrontEndParameters *userParams,
            Utilities *commonUtilities,
            bool &isTerminate);

    /**
     * @brief OrderWrapper for Hedging
     * @returnType orderWrapper
     */
    API2::COMMON::OrderWrapper hedgeOrderWrapper;

    /**
     * @brief OrderValidity for Reverse hedge
     * @returnType orderWrapper
     */
    API2::DATA_TYPES::OrderValidity orderValidity;

    /**
     * @brief last Price
     * @returnType Boolean
     */
    API2::DATA_TYPES::PRICE lastPrice;


/* ---------------------------------------------Workflow Functions --------------------------------------------------*/

    /**
     * @type WorkFlow Function
     * @brief Start Hedging Orders
     * @return Boolean
     */
    bool startHedge();


/* ---------------------------------------------Implementation Functions --------------------------------------------------*/

    /**
     * @type Implementation Function
     * @brief Initialize and subscribe our, Instrument and Market Data
     * @return Boolean
     */
    bool init();

    /**
     * @type Implementation Function
     * @brief recognize if the Order is of Hedging Leg
     * @param orderId
     * @return Boolean
     */
    bool isHedgeOrder(API2::COMMON::OrderId *orderId) const;

    /**
     * @type Implementation Function
     * @brief recognize if the Hedge Order is pending
     * @return Boolean
     */
    bool isHedgeOrderReplaceable();

    /**
     * @type Implementation Function/Getter
     * @brief retrives the static LotSize of the Subscribed Symbol
     * @return Quantity
     */
    API2::DATA_TYPES::QTY getLotSize() const;

    /**
     * @type Implementation Function/Getter
     * @brief retrives the Positions Made from the Instrument of the Subscribed Symbol
     * @return Quantity
     */
    API2::DATA_TYPES::QTY getHedgePositions() const ;

    /**
     * @type Implementation Function/Getter
     * @brief Get/Calculate total quantity traded of hedge leg
     * @return API2::DATA_TYPES::QTY
     */
    API2::DATA_TYPES::QTY getTradedQuantity() const;

    /**
     * @type Implementation Function/Getter
     * @brief retrives calculated lots of the Subscribed Symbol for NewOrder
     * @return Quantity
     */
    API2::DATA_TYPES::QTY getCalculateLots() const;
    
    /**
     * @type Implementation Function
     * @brief checks if Hedge Order is in open state
     * @return bool
     */
    bool isOpenOrder();

    /**
     * @type Implementation Function
     * @brief checks if Market Depth is Available for Hedge
     * @return bool
     */
    bool isMarketDepthAvailableForHedge() const;

    /**
     * @type Implementation Function/Setter
     * @brief sets _lastPrice
     * @param price
     * @return void
     */
    void setLastPrice(const API2::DATA_TYPES::PRICE &price);

};

}
#endif // FUTFUTNEWHEDGING_H
