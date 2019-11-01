#ifndef PRICE_H
#define PRICE_H
#include <ctime>
#include "../api_includes/sharedUtilities.h"
#include "structure.h"
#include "../api_includes/timer.h"

namespace SampleFutFutArbitrage{
class FutFutArbitrage;
enum class HedgeMethod;
struct FrontEndParameters;
class Timer;

class Price
{
    /**
     * @brief access commonUtilities object for instrument etc
     * @returnType Utilities struct pointer
     */
    const Utilities *_commonUtilities;

    /**
     * @brief Hedge order Mode
     * @returnType orderMode
     */
    API2::DATA_TYPES::OrderMode _orderMode;

    /**
     * @brief Market Percentae Provided from FrontEnd
     * @returnType SIGNED_LONG
     */
    SIGNED_LONG _marketPercentage;

    /**
     * @brief hedgeMethod Provided from FrontEnd
     * @returnType HedgeMethod
     */
    HedgeMethod _hedgeMethod;

    /**
     * @brief Custom Timer for Hedging
     * @returnType time_t
     */
    API2::TIMER::Timer _timer;

    /**
     * @brief Const Time for Hedge Timer
     * @returnType unsigned Int
     */
    const unsigned int _timeExpiry;


public:
   /**
    * @brief Price()
    * Default constructor
    */
    Price();
    
    /**
     * @brief number of Ticks to round to for Best Bid/ASk
     * @returnType int
     */

    int ticks;
/* ---------------------------------------------Workflow Functions --------------------------------------------------*/
    /**
     * @type WorkFlow Function
     * @brief Get Best Price based on Order Mode
     * @param orderValidity
     * @return API2::DATA_TYPES::PRICE
     */
    API2::DATA_TYPES::PRICE getHedgePrice(API2::DATA_TYPES::OrderValidity &orderValidity);

/* ---------------------------------------------Implementation Functions --------------------------------------------------*/
    /**
     * @type Implementation Function
     * @brief Called from the constructor of SGContext, which setup our startup values
     * @param commonUtilities
     * @param userParams
     * @return Boolean
     */
    bool setDefaultsOfPrice(const Utilities *commonUtilities, const FrontEndParameters *userParams);

    /**
     * @type Implementation Function
     * @brief Calculate Price After Processesing Market Percentage based on Order Mode
     * @param orderValidity
     * @return API2::DATA_TYPES::PRICE
     */
    API2::DATA_TYPES::PRICE calculatePriceAfterMarketPercentage(API2::DATA_TYPES::OrderValidity &orderValidity) const;

    /**
     * @type Implementation Function
     * @brief Get Best Bid/Ask Price based on Order Mode
     * @param orderValidity
     * @return API2::DATA_TYPES::PRICE
     */
    API2::DATA_TYPES::PRICE getHedgeBestPrice(API2::DATA_TYPES::OrderValidity &orderValidity);

    /**
     * @type Implementation Function
     * @brief recognize if the Hedge Timer has Expired to Switch HedgeMethod
     * @return Boolean
     */
    bool isHedgeTimerExpired();


    /**
     * type Implementation Function
     * @brief setTimer
     */
    void setTimer();

    /**
     * @type Implementation Function
     * @brief reset Timer
     * @return void
     */
    void resetTimer();




};
}
#endif //PRICE_H
