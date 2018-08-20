#ifndef API_CONSTANTS
#define API_CONSTANTS
#include <stddef.h>
namespace API2
{
  namespace CONSTANTS
  {

    /**
     * @brief MarketDepthArraySize
     */
    const size_t MarketDepthArraySize = 20;

    /**
     * @brief RSP_OrderStatus_PENDING
     */
    const unsigned short  RSP_OrderStatus_PENDING = 0;

    /**
     * @brief RSP_OrderStatus_CONFIRMED
     */
    const unsigned short  RSP_OrderStatus_CONFIRMED = 1;

    /**
     * @brief RSP_OrderStatus_FILLED
     */
    const unsigned short  RSP_OrderStatus_FILLED = 2;

    /**
     * @brief RSP_OrderStatus_CANCELED
     */
    const unsigned short  RSP_OrderStatus_CANCELED = 3;

    /**
     * @brief RSP_OrderStatus_REPLACED
     */
    const unsigned short  RSP_OrderStatus_REPLACED = 4;

    /**
     * @brief RSP_OrderStatus_NEW_REJECTED
     */
    const unsigned short  RSP_OrderStatus_NEW_REJECTED = 5;

    /**
     * @brief RSP_OrderStatus_CANCEL_REJECTED
     */
    const unsigned short  RSP_OrderStatus_CANCEL_REJECTED = 6;

    /**
     * @brief RSP_OrderStatus_REPLACE_REJECTED
     */
    const unsigned short  RSP_OrderStatus_REPLACE_REJECTED = 7;

    /**
     * @brief RSP_OrderStatus_FROZEN
     */
    const unsigned short  RSP_OrderStatus_FROZEN = 8;

    /**
     * @brief RSP_OrderStatus_MARKET_TO_LIMIT
     */
    const unsigned short  RSP_OrderStatus_MARKET_TO_LIMIT = 9;

    /**
     * @brief RSP_OrderStatus_TRIGGERED
     */
    const unsigned short  RSP_OrderStatus_TRIGGERED = 10;

    /**
     * @brief RSP_OrderStatus_PARTIALLY_FILLED
     */
    const unsigned short  RSP_OrderStatus_PARTIALLY_FILLED = 11;

    /**
     * @brief RSP_OrderStatus_CANCELED_OF_IOC
     */
    const unsigned short  RSP_OrderStatus_CANCELED_OF_IOC = 12;

    /**
     * @brief RSP_OrderStatus_RMS_REJECT
     */
    const unsigned short  RSP_OrderStatus_RMS_REJECT = 13;

    /**
     * @brief RSP_OrderStatus_TRADE_CANCEL
     */
    const unsigned short  RSP_OrderStatus_TRADE_CANCEL = 14;

    /**
     * @brief RSP_OrderStatus_TRADE_CORRECT
     */
    const unsigned short  RSP_OrderStatus_TRADE_CORRECT = 15;

    /**
     * @brief RSP_OrderStatus_TRADE_MODIFICATION
     */
    const unsigned short  RSP_OrderStatus_TRADE_MODIFICATION = 16;

    /**
     * @brief RSP_OrderStatus_RELAYED_TRADE
     */
    const unsigned short  RSP_OrderStatus_RELAYED_TRADE = 17;

    /**
     * @brief RSP_OrderStatus_RELAYED_MODIFIED_TRADE
     */
    const unsigned short  RSP_OrderStatus_RELAYED_MODIFIED_TRADE = 18;

    /**
     * @brief RSP_OrderStatus_GIVEUP_UPDATE
     */
    const unsigned short  RSP_OrderStatus_GIVEUP_UPDATE = 19;

    /**
     * @brief RSP_OrderStatus_PENDING_NEW
     */
    const unsigned short  RSP_OrderStatus_PENDING_NEW = 20;

    /**
     * @brief RSP_OrderStatus_PENDING_REPLACE
     */
    const unsigned short  RSP_OrderStatus_PENDING_REPLACE = 21;

    /**
     * @brief RSP_OrderStatus_PENDING_CANCEL
     */
    const unsigned short  RSP_OrderStatus_PENDING_CANCEL = 22;

    /**
     * @brief RSP_OrderStatus_FILEREPLAYER_TRADE
     */
    const unsigned short  RSP_OrderStatus_FILEREPLAYER_TRADE = 23;

    /**
     * @brief RSP_OrderStatus_FILEREPLAYER_MODIFIED_TRADE
     */
    const unsigned short  RSP_OrderStatus_FILEREPLAYER_MODIFIED_TRADE = 24;

    /**
     * @brief RSP_OrderStatus_BOD_POSITION
     */
    const unsigned short  RSP_OrderStatus_BOD_POSITION = 25;

    /**
     * @brief RSP_OrderStatus_SUSPENDED_CONFIRMED
     */
    const unsigned short  RSP_OrderStatus_SUSPENDED_CONFIRMED = 26;

    /**
     * @brief RSP_OrderStatus_SUSPENDED_REPLACED
     */
    const unsigned short  RSP_OrderStatus_SUSPENDED_REPLACED = 27;

    /**
     * @brief RSP_OrderStatus_RESTATED
     */
    const unsigned short  RSP_OrderStatus_RESTATED = 28;

    /**
     * @brief RSP_OrderStatus_FILLED_WITHOUT_POSITIONS
     */
    const unsigned short  RSP_OrderStatus_FILLED_WITHOUT_POSITIONS = 29;

    /**
     * @brief RSP_OrderStatus_TRADE_MODIFICATION_PENDING  - pending confirmation for trade modify
     */
    const unsigned short  RSP_OrderStatus_TRADE_MODIFICATION_PENDING = 30;

    /**
     * @brief OrderStatus_MAX
     */
    const unsigned short  RSP_OrderStatus_MAX = 31;

    /************************************************************************************************************************/
    /************************************************************************************************************************/

    /**
     * @brief RSP_StrategyComment_CIRCUIT_LIMIT_BREACH
     */
    const unsigned short RSP_StrategyComment_CIRCUIT_LIMIT_BREACH = 0; // = 0

    /**
     * @brief RSP_StrategyComment_HEDGE_MARKET_ORDER_CANCELLED
     */
    const unsigned short RSP_StrategyComment_HEDGE_MARKET_ORDER_CANCELLED = 1;

    /**
     * @brief RSP_StrategyComment_MAX_TRADABLE_LOTS_REACHED
     */
    const unsigned short RSP_StrategyComment_MAX_TRADABLE_LOTS_REACHED = 2;

    /**
     * @brief RSP_StrategyComment_RMS_FAILURE
     */
    const unsigned short RSP_StrategyComment_RMS_FAILURE = 3;

    /**
     * @brief RSP_StrategyComment_USER_INPUT
     */
    const unsigned short RSP_StrategyComment_USER_INPUT = 4;

    /**
     * @brief RSP_StrategyComment_SECOND_LEG_PRICE_CHECK_FAIL
     */
    const unsigned short RSP_StrategyComment_SECOND_LEG_PRICE_CHECK_FAIL = 5;

    /**
     * @brief RSP_StrategyComment_WRONG_REF_PRICE_IN_CASE_OF_STOCKS
     */
    const unsigned short RSP_StrategyComment_WRONG_REF_PRICE_IN_CASE_OF_STOCKS = 6;

    /**
     * @brief RSP_StrategyComment_PRICE_OF_HEDGING_INSTRUMENT_CALCULATED_ZERO
     */
    const unsigned short RSP_StrategyComment_PRICE_OF_HEDGING_INSTRUMENT_CALCULATED_ZERO = 7;

    /**
     * @brief RSP_StrategyComment_MARKET_DATA_ORDER_INST_NOT_FOUND
     */
    const unsigned short RSP_StrategyComment_MARKET_DATA_ORDER_INST_NOT_FOUND = 8;

    /**
     * @brief RSP_StrategyComment_DELTA_CALCULATED_ZERO
     */
    const unsigned short RSP_StrategyComment_DELTA_CALCULATED_ZERO = 9;

    /**
     * @brief RSP_StrategyComment_PRICE_DIFFERENCE_IS_GREATER_THAN_TOTAL_SPREAD
     */
    const unsigned short RSP_StrategyComment_PRICE_DIFFERENCE_IS_GREATER_THAN_TOTAL_SPREAD = 10;

    /**
     * @brief RSP_StrategyComment_SELL_PRICE_SMALLER_THAN_BEST_BID_OR_BUY_PRICE_GREATER_THAN_BEST_ASK
     */
    const unsigned short RSP_StrategyComment_SELL_PRICE_SMALLER_THAN_BEST_BID_OR_BUY_PRICE_GREATER_THAN_BEST_ASK = 11; // = 11

    /**
     * @brief RSP_StrategyComment_MARKET_DATA_HEDGE_INST_NOT_FOUND
     */
    const unsigned short RSP_StrategyComment_MARKET_DATA_HEDGE_INST_NOT_FOUND = 12;

    /**
     * @brief RSP_StrategyComment_EXCHANGE_DISCONNECTED
     */
    const unsigned short RSP_StrategyComment_EXCHANGE_DISCONNECTED = 13;

    /**
     * @brief RSP_StrategyComment_ORDER_FROZEN
     */
    const unsigned short RSP_StrategyComment_ORDER_FROZEN = 14;

    /**
     * @brief RSP_StrategyComment_FIRST_LEG_TBT_SUBSCRIPTION_FAILED
     */
    const unsigned short RSP_StrategyComment_FIRST_LEG_TBT_SUBSCRIPTION_FAILED = 15;

    /**
     * @brief RSP_StrategyComment_SECOND_LEG_TBT_SUBSCRIPTION_FAILED
     */
    const unsigned short RSP_StrategyComment_SECOND_LEG_TBT_SUBSCRIPTION_FAILED = 16;

    /**
     * @brief RSP_StrategyComment_IDLE_TIMER_EXPIRED
     */
    const unsigned short RSP_StrategyComment_IDLE_TIMER_EXPIRED = 17;

    /**
     * @brief RSP_StrategyComment_ORDER_NOT_FILLED_OPEN_POSITIONS_CLOSED
     */
    const unsigned short RSP_StrategyComment_ORDER_NOT_FILLED_OPEN_POSITIONS_CLOSED = 18;

    /**
     * @brief RSP_StrategyComment_ORDER_NOT_FILLED_OPEN_POSITIONS_EXIST
     */
    const unsigned short RSP_StrategyComment_ORDER_NOT_FILLED_OPEN_POSITIONS_EXIST = 19;

    /**
     * @brief RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY
     */
    const unsigned short RSP_StrategyComment_STRATEGY_COMPLETED_SUCCESSFULLY = 20;

    /**
     * @brief RSP_StrategyComment_MARKET_MAKING_ORDER_LOTS_REDUCED
     */
    const unsigned short RSP_StrategyComment_MARKET_MAKING_ORDER_LOTS_REDUCED = 21;

    /**
     * @brief RSP_StrategyComment_MARKET_MAKING_REFERENCE_PRICE_PROTECTION_FAILED
     */
    const unsigned short RSP_StrategyComment_MARKET_MAKING_REFERENCE_PRICE_PROTECTION_FAILED = 22;

    /**
     * @brief RSP_StrategyComment_UNKNOWN_STATE
     */
    const unsigned short RSP_StrategyComment_UNKNOWN_STATE = 23;

    /**
     * @brief RSP_StrategyComment_THIRD_LEG_TBT_SUBSCRIPTION_FAILED
     */
    const unsigned short RSP_StrategyComment_THIRD_LEG_TBT_SUBSCRIPTION_FAILED = 24;

    /**
     * @brief RSP_StrategyComment_ORDER_NOT_FILLED_OR_PARTIALLY_FILLED
     */
    const unsigned short RSP_StrategyComment_ORDER_NOT_FILLED_OR_PARTIALLY_FILLED = 25;

    /**
     * @brief RSP_StrategyComment_SPREAD_NOT_FAVOURABLE
     */
    const unsigned short RSP_StrategyComment_SPREAD_NOT_FAVOURABLE = 26;

    /**
     * @brief RSP_StrategyComment_TRADES_COMPLETED
     */
    const unsigned short RSP_StrategyComment_TRADES_COMPLETED = 27; // = 27

    /**
     * @brief RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED
     */
    const unsigned short RSP_StrategyComment_TBT_SUBSCRIPTION_FAILED = 28; // = 28

    /**
     * @brief RSP_StrategyComment_TBTFO_DISCONNECTED
     */
    const unsigned short RSP_StrategyComment_TBTFO_DISCONNECTED = 29; // = 29

    /**
     * @brief RSP_StrategyComment_TBTCM_DISCONNECTED
     */
    const unsigned short RSP_StrategyComment_TBTCM_DISCONNECTED = 30; // = 30

    /**
     * @brief RSP_StrategyComment_TURNOVER_ROUNDS_COMPLETED
     */
    const unsigned short RSP_StrategyComment_TURNOVER_ROUNDS_COMPLETED = 31; // = 31

    /**
     * @brief RSP_StrategyComment_CURRENT_TIME_GREATER_THAN_ACTIVATION
     */
    const unsigned short RSP_StrategyComment_CURRENT_TIME_GREATER_THAN_ACTIVATION = 32; // = 32

    /**
     * @brief RSP_StrategyComment_TERMINATE_SPREAD_BREACHED
     */
    const unsigned short RSP_StrategyComment_TERMINATE_SPREAD_BREACHED = 33;//= 33

    /**
     * @brief RSP_StrategyComment_SYNTHETIC_POSITION_NOT_FILLED_OR_PARTIALLY_FILLED
     */
    const unsigned short RSP_StrategyComment_SYNTHETIC_POSITION_NOT_FILLED_OR_PARTIALLY_FILLED = 34;//= 34

    /**
     * @brief RSP_StrategyComment_FOURTH_LEG_TBT_SUBSCRIPTION_FAILED
     */
    const unsigned short RSP_StrategyComment_FOURTH_LEG_TBT_SUBSCRIPTION_FAILED = 35;

    /**
     * @brief RSP_StrategyComment_UNDERLYING_TBT_SUBSCRIPTION_FAILED
     */
    const unsigned short RSP_StrategyComment_UNDERLYING_TBT_SUBSCRIPTION_FAILED = 36;

    /**
     * @brief RSP_StrategyComment_HEDGING_TBT_SUBSCRIPTION_FAILED
     */
    const unsigned short RSP_StrategyComment_HEDGING_TBT_SUBSCRIPTION_FAILED = 37;

    /**
     * @brief RSP_StrategyComment_FIRST_SQUARE_OFF_WITH_TIMER_NOT_FILLED
     */
    const unsigned short RSP_StrategyComment_FIRST_SQUARE_OFF_WITH_TIMER_NOT_FILLED = 38;

    /**
     * @brief RSP_StrategyComment_STRATEGY_VERSION_DIFFERS
     */
    const unsigned short RSP_StrategyComment_STRATEGY_VERSION_DIFFERS = 39;

    /**
     * @brief RSP_StrategyComment_PAIRS_ERROR_STATE
     */
    const unsigned short RSP_StrategyComment_PAIRS_ERROR_STATE = 40;//=40

    /**
     * @brief RSP_StrategyComment_PAIRS_TARGET_ACHIEVED
     */
    const unsigned short RSP_StrategyComment_PAIRS_TARGET_ACHIEVED = 41;//=41


    /**
     * @brief RSP_StrategyComment_PAIRS_STRATEGY_TERMINATING
     */
    const unsigned short RSP_StrategyComment_PAIRS_STRATEGY_TERMINATING = 42;//=42

    /**
     * @brief RSP_StrategyComment_PAIRS_STOP_LOSS_HIT
     */
    const unsigned short RSP_StrategyComment_PAIRS_STOP_LOSS_HIT = 43; //=43

    /**
     * @brief RSP_StrategyComment_PAIRS_MAX_CYCLES_COMPLETED
     */
    const unsigned short RSP_StrategyComment_PAIRS_MAX_CYCLES_COMPLETED = 44; //=44

    /**
     * @brief RSP_StrategyComment_PAIRS_RESTORE_FAILED
     */
    const unsigned short RSP_StrategyComment_PAIRS_RESTORE_FAILED = 45; //=45

    /**
     * @brief RSP_StrategyComment_TBTCDS_DISCONNECTED
     */
    const unsigned short RSP_StrategyComment_TBTCDS_DISCONNECTED = 46; //=46

    /**
     * @brief RSP_StrategyComment_INCREASE_COUNTER
     */
    const unsigned short RSP_StrategyComment_INCREASE_COUNTER = 47; //=47

    /**
     * @brief RSP_StrategyComment_FORCE_TERMINATE
     */
    const unsigned short RSP_StrategyComment_FORCE_TERMINATE = 48;

    /**
     * @brief RSP_StrategyComment_STRATEGY_ALREADY_TERMINATED
     */
    const unsigned short RSP_StrategyComment_STRATEGY_ALREADY_TERMINATED = 49;

    /**
     * @brief RSP_StrategyComment_STRATEGY_ERROR_STATE
     */
    const unsigned short RSP_StrategyComment_STRATEGY_ERROR_STATE = 50;

    /**
     * @brief RSP_StrategyComment_STRATEGY_API_NOT_FOUND
     */
    const unsigned short RSP_StrategyComment_STRATEGY_API_NOT_FOUND = 51;

    /**
     * @brief RSP_StrategyComment_OHLC_SUBSCRIPTION_FAILED
     */
    const unsigned short RSP_StrategyComment_OHLC_SUBSCRIPTION_FAILED =52;

    /**
     * @brief RSP_StrategyComment_SELF_TRADE
     */
    const unsigned short RSP_StrategyComment_SELF_TRADE =53;

    /**
     * @brief RSP_StrategyComment_EXECUTION_STYLE_TIMER_EXPIRED
     */
    const unsigned short RSP_StrategyComment_EXECUTION_STYLE_TIMER_EXPIRED = 54;

    /**
     * @brief RSP_StrategyComment_CMP_BREACHED
     */
    const unsigned short RSP_StrategyComment_CMP_BREACHED = 55;

    /**
     * @brief RSP_StrategyComment_REJECT_COUNTER_BREACHED
     */
    const unsigned short RSP_StrategyComment_REJECT_COUNTER_BREACHED = 56;

    /**
     * @brief RSP_StrategyComment_ITM_LTP_BREACHED
     */
    const unsigned short RSP_StrategyComment_ITM_LTP_BREACHED = 57;
 
    /**
     * @brief RSP_StrategyComment_TBTIFSC_DISCONNECTED
     */
    const unsigned short RSP_StrategyComment_TBTIFSC_DISCONNECTED = 58;

    /**
     * @brief RSP_StrategyComment_STRATEGY_END
     */
    const unsigned short RSP_StrategyComment_MAX = 59;

    /************************************************************************************************************************/
    /************************************************************************************************************************/


    /**
     * @brief RSP_ResponseType_SUCCESS
     */
    const unsigned short RSP_ResponseType_SUCCESS = 0;

    /**
     * @brief RSP_ResponseType_FAILURE
     */
    const unsigned short RSP_ResponseType_FAILURE = 1;

    /**
     * @brief RSP_ResponseType_TERMINATE_SUCCESS
     */
    const unsigned short RSP_ResponseType_TERMINATE_SUCCESS = 2;

    /**
     * @brief RSP_ResponseType_TERMINATE_FAILURE
     */
    const unsigned short RSP_ResponseType_TERMINATE_FAILURE = 3;

    /**
     * @brief RSP_ResponseType_TERMINATE_SQUAREOFF_SUCCESS
     */
    const unsigned short RSP_ResponseType_TERMINATE_SQUAREOFF_SUCCESS = 4;

    /**
     * @brief RSP_ResponseType_TERMINATE_SQUAREOFF_FAILURE
     */
    const unsigned short RSP_ResponseType_TERMINATE_SQUAREOFF_FAILURE = 5;

    /**
     * @brief RSP_ResponseType_PAUSE_STRATEGY_SUCCESS
     */
    const unsigned short RSP_ResponseType_PAUSE_STRATEGY_SUCCESS = 6;

    /**
     * @brief RSP_ResponseType_PAUSE_STRATEGY_FAILURE
     */
    const unsigned short RSP_ResponseType_PAUSE_STRATEGY_FAILURE = 7;

    /**
     * @brief RSP_ResponseType_STRATEGY_RUNNING
     */
    const unsigned short RSP_ResponseType_STRATEGY_RUNNING = 8; // = 8

    /**
     * @brief RSP_ResponseType_TERMINATE_SPREAD_BREACHED
     */
    const unsigned short RSP_ResponseType_TERMINATE_SPREAD_BREACHED = 9;

    /**
     * @brief RSP_ResponseType_ALGO_NOT_ALLOWED
     */
    const unsigned short RSP_ResponseType_ALGO_NOT_ALLOWED = 10;

    /**
     * @brief RSP_ResponseType_INCREASE_COUNTER
     */
    const unsigned short RSP_ResponseType_INCREASE_COUNTER = 11;

    /**
     * @brief RSP_ResponseType_STRATEGY_ALREADY_TERMINATED
     */
    const unsigned short RSP_ResponseType_STRATEGY_ALREADY_TERMINATED = 12;

    /**
     * @brief RSP_ResponseType_STRATEGY_API_NOT_FOUND
     */
    const unsigned short RSP_ResponseType_STRATEGY_API_NOT_FOUND = 13;

    /**
     * @brief RSP_ResponseType_STRATEGY_COMPLETED
     */
    const unsigned short RSP_ResponseType_STRATEGY_COMPLETED = 15;

    const unsigned short RSP_ResponseType_STRATEGY_WAIT = 16;

    const unsigned short RSP_ResponseType_MAX = 17;

    /************************************************************************************************************************/
    /************************************************************************************************************************/

    /**
     * @brief RSP_RiskStatus_SUCCESS
     */
    const unsigned short RSP_RiskStatus_SUCCESS = 0; // = 0

    /**
     * @brief RSP_RiskStatus_WRONG_QUANTITY
     */
    const unsigned short RSP_RiskStatus_WRONG_QUANTITY = 1;

    /**
     * @brief RSP_RiskStatus_NOT_CONFIGURED
     */
    const unsigned short RSP_RiskStatus_NOT_CONFIGURED = 2;

    /**
     * @brief RSP_RiskStatus_MAX_SINGLE_ORDER_QTY_VIOLATED
     */
    const unsigned short RSP_RiskStatus_MAX_SINGLE_ORDER_QTY_VIOLATED = 3;

    /**
     * @brief RSP_RiskStatus_MAX_SINGLE_ORDER_VALUE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_MAX_SINGLE_ORDER_VALUE_VIOLATED = 4;

    /**
     * @brief RSP_RiskStatus_TOTAL_BUY_QUANTITY_VIOLATED
     */
    const unsigned short RSP_RiskStatus_TOTAL_BUY_QUANTITY_VIOLATED = 5;

    /**
     * @brief RSP_RiskStatus_TOTAL_BUY_VALUE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_TOTAL_BUY_VALUE_VIOLATED = 6;

    /**
     * @brief RSP_RiskStatus_TOTAL_SELL_QUANTITY_VIOLATED
     */
    const unsigned short RSP_RiskStatus_TOTAL_SELL_QUANTITY_VIOLATED = 7;

    /**
     * @brief RSP_RiskStatus_TOTAL_SELL_VALUE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_TOTAL_SELL_VALUE_VIOLATED = 8;

    /**
     * @brief RSP_RiskStatus_MAX_NET_QUANTITY_VIOLATED
     */
    const unsigned short RSP_RiskStatus_MAX_NET_QUANTITY_VIOLATED = 9;

    /**
     * @brief RSP_RiskStatus_MAX_NET_VALUE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_MAX_NET_VALUE_VIOLATED = 10;

    /**
     * @brief RSP_RiskStatus_PRICE_PROTECTION_CHECK_VIOLATED
     */
    const unsigned short RSP_RiskStatus_PRICE_PROTECTION_CHECK_VIOLATED = 11;

    /**
     * @brief RSP_RiskStatus_MAX_MTM_LOSS_VIOLATED
     */
    const unsigned short RSP_RiskStatus_MAX_MTM_LOSS_VIOLATED = 12;

    /**
     * @brief RSP_RiskStatus_MAX_ORDERS_PER_SECOND_VIOLATED
     */
    const unsigned short RSP_RiskStatus_MAX_ORDERS_PER_SECOND_VIOLATED = 13;

    /**
     * @brief RSP_RiskStatus_EXCHANGE_DISCONNECTED
     */
    const unsigned short RSP_RiskStatus_EXCHANGE_DISCONNECTED = 14; // = 14

    /**
     * @brief RSP_RiskStatus_OUTSTANDING_TOTAL_BUY_QUANTITY_VIOLATED
     */
    const unsigned short RSP_RiskStatus_OUTSTANDING_TOTAL_BUY_QUANTITY_VIOLATED = 15;

    /**
     * @brief RSP_RiskStatus_OUTSTANDING_TOTAL_BUY_VALUE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_OUTSTANDING_TOTAL_BUY_VALUE_VIOLATED = 16;

    /**
     * @brief RSP_RiskStatus_OUTSTANDING_TOTAL_SELL_QUANTITY_VIOLATED
     */
    const unsigned short RSP_RiskStatus_OUTSTANDING_TOTAL_SELL_QUANTITY_VIOLATED = 17;

    /**
     * @brief RSP_RiskStatus_OUTSTANDING_TOTAL_SELL_VALUE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_OUTSTANDING_TOTAL_SELL_VALUE_VIOLATED = 18; // 18

    /**
     * @brief RSP_RiskStatus_INDEX_PROTECTION_NSE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_INDEX_PROTECTION_NSE_VIOLATED = 19;// = 19

    /**
     * @brief RSP_RiskStatus_INDEX_PROTECTION_BSE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_INDEX_PROTECTION_BSE_VIOLATED = 20;// = 20

    /**
     * @brief RSP_RiskStatus_SECURITY_LIMITS_VIOLATED_BUY_QTY
     */
    const unsigned short RSP_RiskStatus_SECURITY_LIMITS_VIOLATED_BUY_QTY = 21;// = 21

    /**
     * @brief RSP_RiskStatus_SECURITY_LIMITS_VIOLATED_BUY_VALUE
     */
    const unsigned short RSP_RiskStatus_SECURITY_LIMITS_VIOLATED_BUY_VALUE = 22;// = 22

    /**
     * @brief RSP_RiskStatus_SECURITY_LIMITS_VIOLATED_SELL_QTY
     */
    const unsigned short RSP_RiskStatus_SECURITY_LIMITS_VIOLATED_SELL_QTY = 23;// = 23

    /**
     * @brief RSP_RiskStatus_SECURITY_LIMITS_VIOLATED_SELL_VALUE
     */
    const unsigned short RSP_RiskStatus_SECURITY_LIMITS_VIOLATED_SELL_VALUE = 24;// = 24

    /**
     * @brief RSP_RiskStatus_TRADER_OR_CLIENT_MARGIN_INSUFFICIENT
     */
    const unsigned short RSP_RiskStatus_TRADER_OR_CLIENT_MARGIN_INSUFFICIENT = 25;// = 25

    /**
     * @brief RSP_RiskStatus_MEMBER_NSE_MARGIN_INSUFFICIENT
     */
    const unsigned short RSP_RiskStatus_MEMBER_NSE_MARGIN_INSUFFICIENT = 26;// = 26

    /**
     * @brief RSP_RiskStatus_MEMBER_BSE_MARGIN_INSUFFICIENT
     */
    const unsigned short RSP_RiskStatus_MEMBER_BSE_MARGIN_INSUFFICIENT = 27;// = 27

    /**
     * @brief RSP_RiskStatus_PRICE_NOT_WITHIN_CIRCUIT_RANGE
     */
    const unsigned short RSP_RiskStatus_PRICE_NOT_WITHIN_CIRCUIT_RANGE = 28;

    /**
     * @brief RSP_RiskStatus_CLOSE_PRICE_PROTECTION_FAILED
     */
    const unsigned short RSP_RiskStatus_CLOSE_PRICE_PROTECTION_FAILED = 29;

    /**
     * @brief RSP_RiskStatus_BAD_TRADE_PRICE_CHECK_FAILED
     */
    const unsigned short RSP_RiskStatus_BAD_TRADE_PRICE_CHECK_FAILED = 30;

    /**
     * @brief RSP_RiskStatus_MARKET_NOT_OPEN
     */
    const unsigned short RSP_RiskStatus_MARKET_NOT_OPEN = 31; // = 31
    const unsigned short RSP_RiskStatus_STATIC_DATA_CORRUPTED =  32;
    const unsigned short RSP_RiskStatus_CLIENT_CODE_NOT_FOUND =  33;
    const unsigned short RSP_RiskStatus_CLIENT_CODE_MAPPING_NOT_FOUND = 34;
    const unsigned short RSP_RiskStatus_RISK_INFO_NOT_FOUND_FOR_CLIENT = 35;
    const unsigned short RSP_RiskStatus_SEGMENT_TYPE_INVALID_ACCOUNT_DETAIL = 36;
    const unsigned short RSP_RiskStatus_DEALER_SECURITY_NOT_ALLOWED = 37;
    const unsigned short RSP_RiskStatus_GLOBAL_SECURITY_NOT_ALLOWED = 38;
    const unsigned short RSP_RiskStatus_SECURITY_WISE_GROSS_LOTS_VIOLATED = 39;
    const unsigned short RSP_RiskStatus_SECURITY_WISE_GROSS_VALUE_VIOLATED = 40;
    const unsigned short RSP_RiskStatus_SYMBOL_WISE_GROSS_LOTS_VIOLATED = 41;
    const unsigned short RSP_RiskStatus_SYMBOL_WISE_GROSS_VALUE_VIOLATED = 42;
    const unsigned short RSP_RiskStatus_TRADE_MODIFICATION_NOT_SENT = 43;
    const unsigned short RSP_RiskStatus_ANTIWASH_ORDER_DELETED = 44;
    const unsigned short RSP_RiskStatus_ORDER_OUT_OF_DPR_RANGE = 45;
    const unsigned short RSP_RiskStatus_DEALER_EXPIRY_NOT_ALLOWED = 46;
    const unsigned short RSP_RiskStatus_GLOBAL_EXPIRY_NOT_ALLOWED = 47;
    const unsigned short RSP_RiskStatus_THROTTLE_LIMIT_BREACHED = 48;
    const unsigned short RSP_RiskStatus_IV_CHECK_FAILED = 49;
    const unsigned short RSP_RiskStatus_QUANTITY_FREEZE_LIMIT_BREACHED = 50;
    
    /**
     * @brief RSP_RiskStatus_CLIENT_MARGIN_INSUFFICIENT
     */
    const unsigned short RSP_RiskStatus_CLIENT_MARGIN_INSUFFICIENT = 51;

    /**
     * @brief RSP_RiskStatus_CURRENCY_CONVERSION_FACTOR_NOT_FOUND
     */
    const unsigned short RSP_RiskStatus_CURRENCY_CONVERSION_FACTOR_NOT_FOUND = 52;

    /**
     * @brief RSP_RiskStatus_RMS_INTERNAL_REJECT
     */
    const unsigned short RSP_RiskStatus_RMS_INTERNAL_REJECT = 53;

    /**
     * @brief RSP_RiskStatus_MAX
     */
    const unsigned short RSP_RiskStatus_MAX = 54;


    /************************************************************************************************************************/
    /************************************************************************************************************************/

    /**
     * @brief RSP_ResponseCategory_API2_REQUEST
     */
    const unsigned short RSP_ResponseCategory_API2_REQUEST = 47;

    /**
     * @brief RSP_ResponseCategory_API2_STRATEGY
     */
    const unsigned short RSP_ResponseCategory_API2_STRATEGY = 48;

    /**
     * @brief RSP_ResponseCategory_PROTO_RESPONSE_MESSAGE
     */
    const unsigned short RSP_ResponseCategory_PROTO_RESPONSE_MESSAGE = 6000;

    /************************************************************************************************************************/
    /************************************************************************************************************************/


    /**
     * @brief CMD_OrderMode_BUY
     */
    const unsigned short CMD_OrderMode_BUY = 0;

    /**
     * @brief CMD_OrderMode_SELL
     */
    const unsigned short CMD_OrderMode_SELL = 1;

    /**
     * @brief CMD_OrderMode_MAX
     */
    const unsigned short CMD_OrderMode_MAX = 2;



    /************************************************************************************************************************/
    /************************************************************************************************************************/


    /**
     * @brief CMD_ExchangeId_BSECM
     */
    const unsigned short CMD_ExchangeId_BSECM = 1;
    const unsigned short CMD_ExchangeId_BSEFO = 2;
    const unsigned short CMD_ExchangeId_NSECM = 3;
    const unsigned short CMD_ExchangeId_NSEFO = 4;

#ifdef FRONTEND_COMPILATION
    const unsigned short CMD_ExchangeId_ESM = 5;
#else
    const unsigned short CMD_ExchangeId_ESMNSE = 5;
#endif

    const unsigned short CMD_ExchangeId_NSECDS = 6;
    const unsigned short CMD_ExchangeId_BSECDS = 7;
    const unsigned short CMD_ExchangeId_SGX = 8;
    const unsigned short CMD_ExchangeId_CFH = 9;
    const unsigned short CMD_ExchangeId_MAREX = 10;
    const unsigned short CMD_ExchangeId_MCX = 11;
    const unsigned short CMD_ExchangeId_DGCX = 12;
    const unsigned short CMD_ExchangeId_DGCXCD = 13;
    const unsigned short CMD_ExchangeId_LME = 14;
    const unsigned short CMD_ExchangeId_CME = 15;
    const unsigned short CMD_ExchangeId_CFFEX = 16;
    const unsigned short CMD_ExchangeId_CZCE = 17;
    const unsigned short CMD_ExchangeId_DCE = 18;
    const unsigned short CMD_ExchangeId_SHFE = 19;
    const unsigned short CMD_ExchangeId_SGXCUR = 20;
    const unsigned short CMD_ExchangeId_SMART  = 21;
    const unsigned short CMD_ExchangeId_ALPHA  = 22;
    const unsigned short CMD_ExchangeId_AMEX  = 23;
    const unsigned short CMD_ExchangeId_ARCA  = 24;
    const unsigned short CMD_ExchangeId_ASX  = 25;
    const unsigned short CMD_ExchangeId_BATS  = 26;
    const unsigned short CMD_ExchangeId_BEX  = 27;
    const unsigned short CMD_ExchangeId_BTRADE = 28;
    const unsigned short CMD_ExchangeId_BYX  = 29;
    const unsigned short CMD_ExchangeId_CHX  = 30;
    const unsigned short CMD_ExchangeId_DRCTEDGE = 31;
    const unsigned short CMD_ExchangeId_EBS  = 32;
    const unsigned short CMD_ExchangeId_EDGEA  = 33;
    const unsigned short CMD_ExchangeId_FWB  = 34;
    const unsigned short CMD_ExchangeId_FWB2  = 35;
    const unsigned short CMD_ExchangeId_IEX  = 36;
    const unsigned short CMD_ExchangeId_INET  = 37;
    const unsigned short CMD_ExchangeId_ISLAND = 38;
    const unsigned short CMD_ExchangeId_LAVA  = 39;
    const unsigned short CMD_ExchangeId_LSE  = 40;
    const unsigned short CMD_ExchangeId_MEXI  = 41;
    const unsigned short CMD_ExchangeId_NASDAQ = 42;
    const unsigned short CMD_ExchangeId_NYSE  = 43;
    const unsigned short CMD_ExchangeId_NYMEX  = 44;
    const unsigned short CMD_ExchangeId_OMEGA  = 45;
    const unsigned short CMD_ExchangeId_PINK  = 46;
    const unsigned short CMD_ExchangeId_PSX  = 47;
    const unsigned short CMD_ExchangeId_PURE  = 48;
    const unsigned short CMD_ExchangeId_SBF  = 49;
    const unsigned short CMD_ExchangeId_SEHK  = 50;
    const unsigned short CMD_ExchangeId_SELECT = 51;
    const unsigned short CMD_ExchangeId_SWB  = 52;
    const unsigned short CMD_ExchangeId_SWB2  = 53;
    const unsigned short CMD_ExchangeId_TSE  = 54;
    const unsigned short CMD_ExchangeId_VWAP  = 55;
    const unsigned short CMD_ExchangeId_ONE  = 56;
    const unsigned short CMD_ExchangeId_ECBOT  = 57;
    const unsigned short CMD_ExchangeId_IDEALPRO = 58;
    const unsigned short CMD_ExchangeId_NASDAQOM = 59;
    const unsigned short CMD_ExchangeId_GLOBEX = 60;
    const unsigned short CMD_ExchangeId_ISE  = 61;
    const unsigned short CMD_ExchangeId_EXOTIC = 62;
    const unsigned short CMD_ExchangeId_MSECM = 63;
    const unsigned short CMD_ExchangeId_MOEXFO = 64;
    const unsigned short CMD_ExchangeId_MOEX = 65;
    const unsigned short CMD_ExchangeId_IFLL = 66;
    const unsigned short CMD_ExchangeId_CBT = 67;
    const unsigned short CMD_ExchangeId_FXALL = 68;
    const unsigned short CMD_ExchangeId_PLUS = 69;
    const unsigned short CMD_ExchangeId_NCDEX = 70;
    const unsigned short CMD_ExchangeId_COMEX = 71;
    const unsigned short CMD_ExchangeId_BSEINX = 72;
    const unsigned short CMD_ExchangeId_MSEFO = 73;
    const unsigned short CMD_ExchangeId_MSECD = 74;
    const unsigned short CMD_ExchangeId_BIST = 75;
    const unsigned short CMD_ExchangeId_PXM = 76;
    const unsigned short CMD_ExchangeId_NYBOT = 77;
    const unsigned short CMD_ExchangeId_NYSELIFFE = 78;
    const unsigned short CMD_ExchangeId_NSEIFSC = 79;
    const unsigned short CMD_ExchangeId_MAX = 80;

    /************************************************************************************************************************/
    /************************************************************************************************************************/


    /**
     * @brief CMD_SourceId_DEFAULT
     */
    const unsigned short CMD_SourceId_DEFAULT = 1;

    /**
     * @brief CMD_SourceId_MAREX
     */
    const unsigned short CMD_SourceId_MAREX = 2;

    /**
     * @brief CMD_SourceId_TT
     */
    const unsigned short CMD_SourceId_TT = 3;

    /**
     * @brief CMD_SourceId_CTP
     */
    const unsigned short CMD_SourceId_CTP= 4;

    /**
     * @brief CMD_SourceId_IB
     */
    const unsigned short CMD_SourceId_IB = 5;

    /**
     * @brief CMD_SourceId_OT 
     */
    const unsigned short CMD_SourceId_OT = 6;

    const unsigned short CMD_SourceId_MAX = 7;

    /************************************************************************************************************************/
    /************************************************************************************************************************/



    /**
     * @brief CMD_SecurityType_COMMON_STOCK
     */
    const unsigned short CMD_SecurityType_COMMON_STOCK = 0;

    /**
     * @brief CMD_SecurityType_FUTURE
     */
    const unsigned short CMD_SecurityType_FUTURE = 1;

    /**
     * @brief CMD_SecurityType_OPTION
     */
    const unsigned short CMD_SecurityType_OPTION = 2;

    /**
     * @brief CMD_SecurityType_SPREAD
     */
    const unsigned short CMD_SecurityType_SPREAD = 3;

    /**
     * @brief CMD_SecurityType_MAX
     */
    const unsigned short CMD_SecurityType_MAX = 4;


    /************************************************************************************************************************/
    /************************************************************************************************************************/

    /**
     *  @brief CMD_SelfTradeOrderFlag_CANCEL_ACTIVE
     */
    const unsigned short CMD_SelfTradeOrderFlag_CANCEL_ACTIVE = 0;

    /**
     *  @brief CMD_SelfTradeOrderFlag_CANCEL_PASSIVE
     */
    const unsigned short CMD_SelfTradeOrderFlag_CANCEL_PASSIVE = 1;


    /************************************************************************************************************************/
    /************************************************************************************************************************/

    /**
     * @brief CMD_OrderType_LIMIT
     */
    const unsigned short CMD_OrderType_LIMIT = 0;

    /**
     * @brief CMD_OrderType_MARKET
     */
    const unsigned short CMD_OrderType_MARKET = 1;

    /**
     * @brief CMD_OrderType_STOP_LIMIT
     */
    const unsigned short CMD_OrderType_STOP_LIMIT = 2;

    /**
     * @brief CMD_OrderType_STOP
     */
    const unsigned short CMD_OrderType_STOP = 3;

    /**
     * @brief CMD_OrderType_BestPrice
     */
    const unsigned short CMD_OrderType_BestPrice = 4;

    /**
     * @brief CMD_OrderType_Ask1
     */
    const unsigned short CMD_OrderType_Ask1 = 5;

    /**
     * @brief CMD_OrderType_Bid1
     */
    const unsigned short CMD_OrderType_Bid1 = 6;

    /**
     * @brief CMD_OrderType_Ask1P1
     */
    const unsigned short CMD_OrderType_Ask1P1 = 7;

    /**
     * @brief CMD_OrderType_Ask1P2
     */
    const unsigned short CMD_OrderType_Ask1P2 = 8;

    /**
     * @brief CMD_OrderType_Ask1P3
     */
    const unsigned short CMD_OrderType_Ask1P3 = 9;

    /**
     * @brief CMD_OrderType_Bid1P1
     */
    const unsigned short CMD_OrderType_Bid1P1 = 10;

    /**
     * @brief CMD_OrderType_Bid1P2
     */
    const unsigned short CMD_OrderType_Bid1P2 = 11;

    /**
     * @brief CMD_OrderType_Bid1P3
     */
    const unsigned short CMD_OrderType_Bid1P3 = 12;

    /**
     * @brief CMD_OrderType_MAX
     */
    const unsigned short CMD_OrderType_MAX = 13;



    /************************************************************************************************************************/
    /************************************************************************************************************************/

    /**
     * @brief CMD_OrderValidity_DAY
     */
    const unsigned short CMD_OrderValidity_DAY = 0;

    /**
     * @brief CMD_OrderValidity_IOC
     */
    const unsigned short CMD_OrderValidity_IOC = 1;

    /**
     * @brief CMD_OrderValidity_FOK
     */
    const unsigned short CMD_OrderValidity_FOK = 2;

    /**
     * @brief CMD_OrderValidity_GTD
     */
    const unsigned short CMD_OrderValidity_GTD = 5;

    /**
     * @brief CMD_OrderValidity_GTC
     */
    const unsigned short CMD_OrderValidity_GTC = 6;


    /************************************************************************************************************************/
    /************************************************************************************************************************/

    /**
     * @brief CMD_OptionMode_PUT
     */
    const unsigned short CMD_OptionMode_PUT = 0;

    /**
     * @brief CMD_OptionMode_CALL
     */
    const unsigned short CMD_OptionMode_CALL = 1;

    /**
     * @brief CMD_OptionMode_MAX
     */
    const unsigned short CMD_OptionMode_MAX = 2;




    /************************************************************************************************************************/
    /************************************************************************************************************************/


    /**
     * @brief CMD_OptionAttribute_AMERICAN
     */
    const unsigned short CMD_OptionAttribute_AMERICAN = 0;

    /**
     * @brief CMD_OptionAttribute_EUROPEAN
     */
    const unsigned short CMD_OptionAttribute_EUROPEAN = 1;

    /**
     * @brief CMD_OptionAttribute_MAX
     */
    const unsigned short CMD_OptionAttribute_MAX = 2;



    /************************************************************************************************************************/
    /************************************************************************************************************************/


    /**
     * @brief CMD_ProductType_DELIVERY
     */
    const unsigned short CMD_ProductType_DELIVERY = 0;

    /**
     * @brief CMD_ProductType_INTRADAY
     */
    const unsigned short CMD_ProductType_INTRADAY = 1;



    /************************************************************************************************************************/
    /************************************************************************************************************************/


    /**
     * @brief CMD_InstrumentType_INDEX
     */
    const unsigned short CMD_InstrumentType_INDEX = 0;

    /**
     * @brief CMD_InstrumentType_STOCK
     */
    const unsigned short CMD_InstrumentType_STOCK = 1;

    /**
     * @brief CMD_InstrumentType_CURRENCY
     */
    const unsigned short CMD_InstrumentType_CURRENCY = 2; // Currency Future option = 2; NOT used

    /**
     * @brief CMD_InstrumentType_IRD
     */
    const unsigned short CMD_InstrumentType_IRD = 3; // Interest Rate derivative

    /**
     * @brief CMD_InstrumentType_IVX
     */
    const unsigned short CMD_InstrumentType_IVX = 4; // NSE new instrument type



    /************************************************************************************************************************/
    /************************************************************************************************************************/


    /**
     * @brief CMD_TransactionType_NEW
     */
    const unsigned short CMD_TransactionType_NEW = 0;

    /**
     * @brief CMD_TransactionType_MODIFY
     */
    const unsigned short CMD_TransactionType_MODIFY = 1;

    /**
     * @brief CMD_TransactionType_CANCEL
     */
    const unsigned short CMD_TransactionType_CANCEL = 2;

    const unsigned short CMD_TransactionType_WAIT = 3;

    /**
     * @brief CMD_TransactionType_MAX
     */
    const unsigned short CMD_TransactionType_MAX = 4;



    /************************************************************************************************************************/
    /************************************************************************************************************************/


    /**
     * @brief CMD_CommandCategory_API2_REQUEST
     */
    const unsigned short CMD_CommandCategory_API2_REQUEST = 67;

    /**
     * @brief CMD_CommandCategory_API2_STRATEGY
     */
    const unsigned short CMD_CommandCategory_API2_STRATEGY = 68;

    /**
     * @brief CMD_CommandCategory_BSE_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_BSE_DISCONNECTED = 17;

    /**
     * @brief CMD_CommandCategory_NSECM_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_NSECM_DISCONNECTED = 18;
    /**
     * @brief CMD_CommandCategory_NSEFO_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_NSEFO_DISCONNECTED = 19;
    /**
     * @brief CMD_CommandCategory_TBTCM_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_TBTCM_DISCONNECTED = 20;
    /**
     * @brief CMD_CommandCategory_TBTFO_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_TBTFO_DISCONNECTED = 21;
    /**
     * @brief CMD_CommandCategory_BSE_SNAPSHOTFEED_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_BSE_SNAPSHOTFEED_DISCONNECTED =22;
    /**
     * @brief CMD_CommandCategory_NSEFO_SNAPSHOTFEED_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_NSEFO_SNAPSHOTFEED_DISCONNECTED =23;
    /**
     * @brief CMD_CommandCategory_NSECM_SNAPSHOTFEED_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_NSECM_SNAPSHOTFEED_DISCONNECTED =24;
    /**
     * @brief CMD_CommandCategory_TBTCDS_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_TBTCDS_DISCONNECTED = 48;
    /**
     * @brief CMD_CommandCategory_NSECDS_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_NSECDS_DISCONNECTED = 49;
    /**
     * @brief CMD_CommandCategory_BSEETI_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_BSEETI_DISCONNECTED = 50;
    /**
     * @brief CMD_CommandCategory_SGX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_SGX_DISCONNECTED = 51;
    /**
     * @brief CMD_CommandCategory_CFH_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_CFH_DISCONNECTED = 56;
    /**
     * @brief CMD_CommandCategory_BSEFO_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_BSEFO_DISCONNECTED = 57;
    /**
     * @brief CMD_CommandCategory_CTP_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_CTP_DISCONNECTED = 71;
    /**
     * @brief CMD_CommandCategory_CTP_CFFEX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_CTP_CFFEX_DISCONNECTED = 72;
    /**
     * @brief CMD_CommandCategory_CTP_CZCE_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_CTP_CZCE_DISCONNECTED = 73;
    /**
     * @brief CMD_CommandCategory_CTP_DCE_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_CTP_DCE_DISCONNECTED = 74;
    /**
     * @brief CMD_CommandCategory_CTP_SHFE_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_CTP_SHFE_DISCONNECTED = 75;
    /**
     * @brief CMD_CommandCategory_DGCX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_DGCX_DISCONNECTED = 76;
    /**
     * @brief CMD_CommandCategory_MCX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_MCX_DISCONNECTED = 77;
    /**
     * @brief CMD_CommandCategory_IB_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_IB_DISCONNECTED = 79;
    /**
     * @brief CMD_CommandCategory_EXOTIC_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_EXOTIC_DISCONNECTED =81;
    /**
     * @brief CMD_CommandCategory_MSECM_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_MSECM_DISCONNECTED = 94;
    /**
     * @brief CMD_CommandCategory_MOEXFO_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_MOEXFO_DISCONNECTED = 95;
    /**
     * @brief CMD_CommandCategory_MOEX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_MOEX_DISCONNECTED = 96;
    /**
     * @brief CMD_CommandCategory_BANNED_EXPIRY
     */
    const unsigned short CMD_CommandCategory_BANNED_EXPIRY = 97;


    /**
     * @brief CMD_CommandCategory_ESM_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_ESM_DISCONNECTED=99;
    /**
     * @brief CMD_CommandCategory_SGX_MCL_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_SGX_MCL_DISCONNECTED=102;

    /**
     * @brief CMD_CommandCategory_OT_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_OT_DISCONNECTED = 103;
    /**
     * @brief CMD_CommandCategory_OT_CME_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_OT_CME_DISCONNECTED = 104;
    /**
     * @brief CMD_CommandCategory_OT_LME_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_OT_LME_DISCONNECTED = 105;
    /**
     * @brief CMD_CommandCategory_OT_IFLL_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_OT_IFLL_DISCONNECTED = 106;
    /**
     * @brief CMD_CommandCategory_OT_CBT_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_OT_CBT_DISCONNECTED = 107;
    /**
     * @brief CMD_CommandCategory_OT_NYMEX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_OT_NYMEX_DISCONNECTED = 108;
    /**
     * @brief CMD_CommandCategory_TT_SGX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_TT_SGX_DISCONNECTED = 109;
    /**
     * @brief CMD_CommandCategory_TT_CME_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_TT_CME_DISCONNECTED = 110;
    /**
     * @brief CMD_CommandCategory_TT_LME_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_TT_LME_DISCONNECTED = 111;
    /**
     * @brief CMD_CommandCategory_TT_ICE_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_TT_ICE_DISCONNECTED = 112;
    /**
     * @brief CMD_CommandCategory_FXALL_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_FXALL_DISCONNECTED=113;
    /**
     * @brief CMD_CommandCategory_PLUS_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_PLUS_DISCONNECTED=114;
    /**
     * @brief CMD_CommandCategory_NCDEX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_NCDEX_DISCONNECTED=115;
    /**
     * @brief CMD_CommandCategory_OT_COMEX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_OT_COMEX_DISCONNECTED = 116;
    /**
     * @brief CMD_CommandCategory_BSEINX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_BSEINX_DISCONNECTED = 118;
    /**
     * @brief CMD_CommandCategory_MSEFO_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_MSEFO_DISCONNECTED = 119;
    /**
     * @brief CMD_CommandCategory_MSECD_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_MSECD_DISCONNECTED = 120;
    /**
     * @brief CMD_CommandCategory_TT_NYSE_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_TT_NYSE_DISCONNECTED=121;
    /**
     * @brief CMD_CommandCategory_TT_NASDAQ_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_TT_NASDAQ_DISCONNECTED=122;
    /**
     * @brief CMD_CommandCategory_PXM_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_PXM_DISCONNECTED=123;

    /**
     * @brief CMD_CommandCategory_MARKET_MAKING_STRATEGY_GENERIC
     */
    const unsigned short CMD_CommandCategory_MARKET_MAKING_STRATEGY_GENERIC = 124;

    /**
     * * @brief CMD_CommandCategory_NSEIFSC_DISCONNECTED
     * */
    const unsigned short CMD_CommandCategory_NSEIFSC_DISCONNECTED=127;

    /**
     * * @brief CMD_CommandCategory_TBTIFSC_DISCONNECTED
     * */
    const unsigned short CMD_CommandCategory_TBTIFSC_DISCONNECTED = 128;

    /**
     * @brief CMD_CommandCategory_BIST_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_BIST_DISCONNECTED = 129;

    /**
     * @brief CMD_CommandCategory_TERMINATE_STRATEGY
     */
    const unsigned int CMD_CommandCategory_TERMINATE_STRATEGY = 7; 

    /**
     * @brief CMD_CommandCategory_MAX
     */
    const unsigned int CMD_CommandCategory_MAX = 6001;


    /************************************************************************************************************************/
    /************************************************************************************************************************/

    const unsigned short CMD_OrderCateGory_SINGLE = 0;
    const unsigned short CMD_OrderCateGory_SPREAD = 1;
    const unsigned short CMD_OrderCateGory_PAIRED = 2;
    const unsigned short CMD_OrderCateGory_STRADDLE = 3;
    const unsigned short CMD_OrderCateGory_MULTILEG = 4;
    const unsigned short CMD_OrderCateGory_MAX = 5;

    /**
     * @brief CMD_ContractType_NORMAL
     */
    const unsigned short CMD_ContractType_NORMAL = 0;

    /**
     * @brief CMD_ContractType_SPREAD
     */
    const unsigned short CMD_ContractType_SPREAD = 1;

    /**
     * @brief CMD_ContractType_PAIRED
     */
    const unsigned short CMD_ContractType_PAIRED = 2;

    /**
     * @brief CMD_ContractType_STRADDLE
     */
    const unsigned short CMD_ContractType_STRADDLE = 3;

    /**
     * @brief CMD_ContractType_MAX
     */
    const unsigned short CMD_ContractType_MAX = 4;


    /************************************************************************************************************************/
    /************************************************************************************************************************/
    /**
     * @brief RSP_ErrorCode_TRADE_EXECUTION_RANGE Error Code For NSE
     * */ 
    const unsigned short RSP_ErrorCode_TRADE_EXECUTION_RANGE = 17070;

    /**
     * @brief RSP_ErrorCode_SELF_TRADE Error Code For NSE
     * */ 
    const short RSP_ErrorCode_SELF_TRADE = 17071;
    /**
     * @brief RSP_ErrorCode_SELF_TRADE Error Code For NSECM
     * */ 
    const unsigned short RSP_ErrorCode_SELF_TRADE_NSECM = 17080;
    /**
     * @brief RSP_ErrorCode_CANCEL_ORDER_NOT_FOUND MOEXFO
     * */ 
    const unsigned short RSP_ErrorCode_CANCEL_ORDER_NOT_FOUND_MOEXFO = 14;
    /**
     * @brief RSP_ErrorCode_REPLACE_ORDER_NOT_FOUND MOEXFO
     * */ 
    const unsigned short RSP_ErrorCode_REPLACE_ORDER_NOT_FOUND_MOEXFO = 50;
    /**
     * @brief RSP_ErrorCode_ORDER_NOT_FOUND MOEX - used for both cancel and replace
     * */
    const unsigned short RSP_ErrorCode_ORDER_NOT_FOUND_MOEX = 0;
    /**
     * @brief RSP_ErrorCode_SELF_TRADE Error Code For BSECM
     * */
    const short RSP_ErrorCode_SELF_TRADE_BSECM = 246;
    /**
     * @brief RSP_ErrorCode_TRADE_REVERSAL Error Code For BSECM
     * */ 
    const unsigned short RSP_ErrorCode_TRADE_REVERSAL_BSECM = 247;
    /**
     * @brief RSP_ErrorCode_SELF_TRADE Error Code For MCX 
     * */
    const short RSP_ErrorCode_SELF_TRADE_MCX = 103;

    /**
     * @brief RSP_ErrorCode_SELF_TRADE Error Code For BSEINX
     * */
    const short RSP_ErrorCode_SELF_TRADE_BSEINX = 246;

    /**
     * @brief RSP_ErrorCode_RECORD_DOES_NOT_EXIST Error Code For NSE
     * */
    const short RSP_ErrorCode_RECORD_DOES_NOT_EXIST_NSE = 16273;

    /**
     * @brief RSP_ErrorCode_THROTTLE_BREACH
     * */
    const short RSP_ErrorCode_THROTTLE_BREACH = 48;

    /**
     * @brief RSP_ErrorCode_BSE_VALIDATION_ERROR
     */
    const short RSP_ErrorCode_BSE_VALIDATION_ERROR = 210;

    /**
     * @brief RSP_ErrorCode_TRADING_SYSTEM_NOT_AVAILABLE_FOR_TRADING
     * */
    const short RSP_ErrorCode_TRADING_SYSTEM_NOT_AVAILABLE_FOR_TRADING = 16000;

    /**
     * @brief RSP_ErrorCode_MARKET_NOT_OPEN
     * */
    const short RSP_ErrorCode_MARKET_NOT_OPEN = 16278;

    /**
     * @brief RSP_ErrorCode_ORDER_NOT_ALLOWED_IN_PREOPEN
     * */
    const short RSP_ErrorCode_ORDER_NOT_ALLOWED_IN_PREOPEN = 16447;

    /**
     * @brief RSP_ErrorCode_SPREAD_ORDER_ALLOWED_ONLY_WHEN_MARKET_IS_OPEN
     * */
    const short RSP_ErrorCode_SPREAD_ORDER_ALLOWED_ONLY_WHEN_MARKET_IS_OPEN = 16608;

    /**
     * @brief RSP_ErrorCode_SECURITY_IS_NOT_ALLOWED_TO_TRADE_IN_THIS_MARKET
     * */
    const short RSP_ErrorCode_SECURITY_IS_NOT_ALLOWED_TO_TRADE_IN_THIS_MARKET = 16387;

    /**
     * @brief RSP_ErrorCode_SELF_TRADE_MSE_PASSIVE Error Code For MSE (passive)
     * */
    const short RSP_ErrorCode_SELF_TRADE_MSE_PASSIVE = 104;

    /**
     * @brief RSP_ErrorCode_SELF_TRADE_MSE_ACTIVE Error Code For  MSE (active)
     * */
    const short RSP_ErrorCode_SELF_TRADE_MSE_ACTIVE = 103;

    /**
     * @brief RSP_ErrorCode_USER_TRD_MOD_DISABLED
     */
    const short RSP_ErrorCode_USER_TRD_MOD_DISABLED = 17048;

    /**
     * @brief RSP_ErrorCode_INVALID_PARTICIPANT_NSEFO
     */
    const short RSP_ErrorCode_INVALID_PARTICIPANT_NSEFO = 16541;

    /**
     * @brief RSP_ErrorCode_PARTICIPANT_AND_VOLUME_CHANGED_NSEFO
     */
    const short RSP_ErrorCode_PARTICIPANT_AND_VOLUME_CHANGED_NSEFO = 16577;

    /**
     * @brief RSP_ErrorCode_INVALID_PARTICIPANT_NSECDS
     */
    const short RSP_ErrorCode_INVALID_PARTICIPANT_NSECDS = 16541;

    /**
     * @brief RSP_ErrorCode_PARTICIPANT_AND_VOLUME_CHANGED_NSECDS
     */
    const short RSP_ErrorCode_PARTICIPANT_AND_VOLUME_CHANGED_NSECDS = 16577;

    /**
     * @brief RSP_ErrorCode_USER_TRD_MOD_DISABLED_NSECDS
     */
    const short RSP_ErrorCode_USER_TRD_MOD_DISABLED_NSECDS = 17048;

    /**
     * @brief RSP_ErrorCode_USER_TYPE_TRD_MOD_DISABLED_NSECDS
     */
    const short RSP_ErrorCode_USER_TYPE_TRD_MOD_DISABLED_NSECDS= 17046;

    /**
     * @brief RSP_ErrorCode_TM_TRD_MOD_DISABLED_NSECDS
     */
    const short RSP_ErrorCode_TM_TRD_MOD_DISABLED_NSECDS = 17047;

    /************************************************************************************************************************/
    /************************************************************************************************************************/

    /**
     * @brief  Continuous Hedging order mode
     * */
    const short CMD_CONT_HEDGING_MODE_SAME_SIDE = 0;
    const short CMD_CONT_HEDGING_MODE_BOTH_SIDE = 1;
    const short CMD_CONT_HEDGING_MODE_MAX = 2;

    /**
     * @brief CMD_CONFIRMATION_TYPE_EXCH  - for exchange confirmation
     */
    const short CMD_CONFIRMATION_TYPE_EXCH = 0;

    /**
     * @brief CMD_CONFIRMATION_TYPE_SELF  - for hold orders confirmations
     */
    const short CMD_CONFIRMATION_TYPE_SELF = 1;

    /**
     * @brief CMD_CONFIRMATION_TYPE_MAX - invalid confirmation type
     */
    const short CMD_CONFIRMATION_TYPE_MAX = 2;
  }
}
#endif
