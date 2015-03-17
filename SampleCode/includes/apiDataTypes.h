#ifndef API_DATA_TYPES
#define API_DATA_TYPES
#include <sharedDefines.h>
#include <string>
namespace API2
{
  namespace DATA_TYPES
  {

    /**
     * @typedef
     * @brief PRICE
     */
    typedef SIGNED_LONG PRICE;

    /**
     * @typedef
     * @brief QTY
     */
    typedef SIGNED_LONG QTY;

    /**
     * @typedef
     * @brief VOLUME
     */
    typedef SIGNED_LONG VOLUME;

    /**
     * @typedef
     * @brief SYMBOL_ID
     */
    typedef SIGNED_LONG SYMBOL_ID;


    /**
     * @typedef
     * @brief CLORDER_ID
     */
    typedef UNSIGNED_LONG CLORDER_ID;

    /**
     * @typedef
     * @brief EXCHANGE_TIME
     */
    typedef UNSIGNED_LONG EXCHANGE_TIME;

    /**
     * @typedef
     * @brief STRATEGY_ID
     */
    typedef UNSIGNED_LONG STRATEGY_ID;

    /**
     * @typedef
     * @brief CLIENT_ID
     */
    typedef UNSIGNED_LONG CLIENT_ID;

    /**
     * @typedef
     * @brief DEPTH_POSITION
     */
    typedef UNSIGNED_SHORT DEPTH_POSITION;

    /**
     * @typedef
     * @brief EXCHANGE_TIME
     */
    typedef UNSIGNED_LONG EXCHANGE_TIME;

    /**
     * @typedef
     * @brief SEQUENCE_NUMBER
     */
    typedef UNSIGNED_LONG SEQUENCE_NUMBER;

    /**
     * @typedef
     * @brief TRADER_ID
     */
    typedef SIGNED_LONG TRADER_ID;

    /**
     * @typedef
     * @brief ERROR_CODE
     */
    typedef UNSIGNED_LONG ERROR_CODE;

    /**
     * @typedef
     * @brief EXPIRY_DATE
     */
    typedef UNSIGNED_INTEGER EXPIRY_DATE;

    /**
     * @typedef
     * @brief ENUM
     */
    typedef UNSIGNED_CHARACTER ENUM;

    /**
     * @typedef
     * @brief SETTLEMENT_PERIOD
     */
    typedef UNSIGNED_CHARACTER SETTLEMENT_PERIOD;

    /**
     * @typedef
     * @brief OrderStatus
     */
    typedef UNSIGNED_SHORT OrderStatus;

    /**
     * @typedef
     * @brief StrategyComment
     */
    typedef UNSIGNED_SHORT StrategyComment;

/**
 * @typedef
 * @brief TimerMicroSecondInterval
 */
    typedef long long TimerMicroSecondInterval;

    /**
     * @typedef
     * @brief ResponseType
     */
    typedef UNSIGNED_SHORT ResponseType;

    /**
     * @typedef
     * @brief RiskStatus
     */
    typedef UNSIGNED_SHORT RiskStatus;

    /**
     * @typedef
     * @brief ResponseCategory
     */
    typedef UNSIGNED_SHORT ResponseCategory;


    /**
     * @typedef
     * @brief OrderMode
     */
    typedef UNSIGNED_SHORT OrderMode;

    /**
     * @typedef
     * @brief ExchangeId
     */
    typedef UNSIGNED_SHORT ExchangeId;

    /**
     * @typedef
     * @brief SecurityType
     */
    typedef UNSIGNED_SHORT SecurityType;

    /**
     * @typedef
     * @brief OrderType
     */
    typedef UNSIGNED_SHORT OrderType;

    /**
     * @typedef
     * @brief OrderValidity
     */
    typedef UNSIGNED_SHORT OrderValidity;

    /**
     * @typedef
     * @brief ProductType
     */
    typedef UNSIGNED_SHORT ProductType;

    /**
     * @typedef
     * @brief OptionMode
     */
    typedef UNSIGNED_SHORT OptionMode;

    /**
     * @typedef
     * @brief OptionAttribute
     */
    typedef UNSIGNED_SHORT OptionAttribute;

    /**
     * @typedef
     * @brief InstrumentType
     */
    typedef UNSIGNED_SHORT InstrumentType;

    /**
     * @typedef
     * @brief TransactionType
     */
    typedef UNSIGNED_SHORT TransactionType;

    /**
     * @typedef
     * @brief CommandCategory
     */
    typedef UNSIGNED_SHORT CommandCategory;

    /**
     * @typedef
     * @brief String
     */
    typedef std::string String;

  }
}
#endif
