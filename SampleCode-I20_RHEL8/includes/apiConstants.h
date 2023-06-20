#ifndef API_CONSTANTS
#define API_CONSTANTS
#include <stddef.h>
#include <string>
#include "apiDataTypes.h"

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
     * @brief RSP_OrderStatus_TRADE_MODIFICATION_REJECTED trade modification request rejection.
     */
    const unsigned short RSP_OrderStatus_TRADE_MODIFICATION_REJECTED = 31;

    /**
     * @brief RSP_OrderStatus_AMO_CONFIRMED After Market Order Confirmed.
     */
    const unsigned short RSP_OrderStatus_AMO_CONFIRMED = 32;

    /**
     * @brief RSP_OrderStatus_AMO_REPLACED After Market Order Replaced.
     */
    const unsigned short RSP_OrderStatus_AMO_REPLACED = 33;

    /**
     * @brief RSP_OrderStatus_AMO_CANCELED After Market Order Canceled.
     */
    const unsigned short RSP_OrderStatus_AMO_CANCELED = 34;

    /**
     * @brief RSP_OrderStatus_AMO_REJECTED After Market Order Rejection.
     */
    const unsigned short RSP_OrderStatus_AMO_REJECTED = 35;

    /**
     * @brief RSP_OrderStatus_AMO_REPLACE_REJECTED After Market Order replace request rejected.
     */
    const unsigned short RSP_OrderStatus_AMO_REPLACE_REJECTED = 36;

    /**
     * @brief RSP_OrderStatus_CONVERTED_ORDER_STRATEGY_TO_MANUAL strategy order moved to manual order.
     */
    const unsigned short RSP_OrderStatus_CONVERTED_ORDER_STRATEGY_TO_MANUAL = 37;

    /**
     * @brief RSP_OrderStatus_QUEUED_CONFIRMED
     */
    const unsigned short RSP_OrderStatus_QUEUED_CONFIRMED = 38;

    /**
     * @brief RSP_OrderStatus_QUEUED_EXECUTED
     */
    const unsigned short RSP_OrderStatus_QUEUED_EXECUTED = 39;

    /**
     * @brief RSP_OrderStatus_QUEUED_CANCELED
     */
    const unsigned short RSP_OrderStatus_QUEUED_CANCELED = 40;

    /**
     * @brief RSP_OrderStatus_AMO_CANCEL_REJECTED After Market Order cancel request rejected.
     */
    const unsigned short RSP_OrderStatus_AMO_CANCEL_REJECTED = 41;

    /**
     * @brief OrderStatus_MAX
     */
    const unsigned short  RSP_OrderStatus_MAX = 42;

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
     * @brief RSP_StrategyComment_IOC_COUNTER_BREACHED
     */
    const unsigned short RSP_StrategyComment_IOC_COUNTER_BREACHED = 59;

    /**
     * @brief RSP_StrategyComment_NO_OPEN_POSITIONS_EXIST_IN_CURRENT_ITERATION
     */
    const unsigned short RSP_StrategyComment_NO_OPEN_POSITIONS_EXIST_IN_CURRENT_ITERATION = 60;

    /**
     * @brief RSP_StrategyComment_INVALID_ALGO_ID_RECEIVED
     */
    const unsigned short RSP_StrategyComment_INVALID_ALGO_ID_RECEIVED = 61;

    /**
     * @brief RSP_StrategyComment_SELF_TRADE_ORDER_NOT_FILLED_OPEN_POSITIONS_CLOSED
     */
    const unsigned short RSP_StrategyComment_SELF_TRADE_ORDER_NOT_FILLED_OPEN_POSITIONS_CLOSED = 62;

    /**
     * @brief RSP_StrategyComment_SELF_TRADE_ORDER_NOT_FILLED_OPEN_POSITIONS_EXIST
     */
    const unsigned short RSP_StrategyComment_SELF_TRADE_ORDER_NOT_FILLED_OPEN_POSITIONS_EXIST = 63;

    /**
     * @brief RSP_StrategyComment_SELF_TRADE_NO_OPEN_POSITIONS_EXIST_IN_CURRENT_ITERATION
     */

    const unsigned short RSP_StrategyComment_SELF_TRADE_NO_OPEN_POSITIONS_EXIST_IN_CURRENT_ITERATION = 64;

    /**
     * @brief RSP_StrategyComment_MCX_ERROR_FILE_NOT_CONFIGURED
     */
    const unsigned short RSP_StrategyComment_MCX_ERROR_FILE_NOT_CONFIGURED = 65;

    /**
     * @brief RSP_StrategyComment_INVALID_VENDOR_CODE_RECEIVED
     */
    const unsigned short RSP_StrategyComment_INVALID_VENDOR_CODE_RECEIVED = 66;
 
    /**
     * @brief RSP_StrategyComment_HEDGE_NEW_ORDER_REJECTED
     */
    const unsigned short RSP_StrategyComment_HEDGE_NEW_ORDER_REJECTED = 67;

    /**
     * @brief RSP_StrategyComment_DMS_DISCONNECTED
     */
    const unsigned short RSP_StrategyComment_DMS_DISCONNECTED = 68;

    /**
     * @brief RSP_StrategyComment_AUTO_TIMER_EXPIRED
     */
    const unsigned short RSP_StrategyComment_AUTO_TIMER_EXPIRED = 69;

    /**
     * @brief RSP_StrategyComment_TERMINATE_MAX_SLIPPAGE_BREACHED
     */
    const unsigned short RSP_StrategyComment_TERMINATE_MAX_SLIPPAGE_BREACHED = 70;

    /**
     * @brief RSP_StrategyComment_TERMINATE_MAX_DEVIATION_BREACHED
     */
    const unsigned short RSP_StrategyComment_TERMINATE_MAX_DEVIATION_BREACHED = 71;

    /**
     * @brief RSP_StrategyComment_STRATEGY_NOT_TERMINATE
     */
    const unsigned short RSP_StrategyComment_NO_TERMINATE = 72;

    /**
     * @brief RSP_StrategyComment_STRATEGY_END
     */
    const unsigned short RSP_StrategyComment_MAX = 73;

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

    /**
     * @brief RSP_ResponseType_STRATEGY_WAIT
     */
    const unsigned short RSP_ResponseType_STRATEGY_WAIT = 16;

    /**
     * @brief RSP_ResponseType_DMS_DISCONNECTED
     */
    const unsigned short RSP_ResponseType_DMS_DISCONNECTED = 17;

    /**
     * @brief RSP_ResponseType_MAX
     */
    const unsigned short RSP_ResponseType_MAX = 18;

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
     * @brief RSP_RiskStatus_MAX_TURNOVER_VALUE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_MAX_TURNOVER_VALUE_VIOLATED = 54;

    /**
     * @brief RSP_RiskStatus_MAX_OUTSTANDING_VALUE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_MAX_OUTSTANDING_VALUE_VIOLATED = 55;

    /**
     * @brief RSP_RiskStatus_SCRIP_GROUP_GROSS_LOTS_VIOLATED
     */
    const unsigned short RSP_RiskStatus_SCRIP_GROUP_GROSS_LOTS_VIOLATED = 56;

    /**
     * @brief RSP_RiskStatus_SCRIP_GROUP_GROSS_VALUE_VIOLATED
     */
    const unsigned short RSP_RiskStatus_SCRIP_GROUP_GROSS_VALUE_VIOLATED = 57;

    /**
     * @brief RSP_RiskStatus_PAN_ID_NOT_FOUND
     */
    const unsigned short RSP_RiskStatus_PAN_ID_NOT_FOUND = 58;

    /**
     * @brief RSP_RiskStatus_MULTILEG_REJECTED
     */
    const unsigned short RSP_RiskStatus_MULTILEG_REJECTED = 59;

    /**
     * @brief RiskStatus_NSECM_PARTICIPATION_CODE_DIFFERENT
     */
    const unsigned short RSP_RiskStatus_NSECM_PARTICIPATION_CODE_DIFFERENT = 60;

    /**
     * @brief RiskStatus_DISCLOSED_QTY_FOR_IOC_NOT_ALLOWED
     */
    const unsigned short RiskStatus_DISCLOSED_QTY_FOR_IOC_NOT_ALLOWED = 61;

    /**
     * @brief RiskStatus_DISCLOSED_QTY_IS_MORE_THAN_ORDER_QTY
     */
    const unsigned short RiskStatus_DISCLOSED_QTY_IS_MORE_THAN_ORDER_QTY = 62;

    /**
     * @brief RiskStatus_DISCLOSED_QTY_IS_NOT_IN_MARKET_LOT
     */
    const unsigned short RiskStatus_DISCLOSED_QTY_IS_NOT_IN_MARKET_LOT = 63;

    /**
     * @brief RiskStatus_QUANTITY_NOT_IN_LOT_SIZE
     */
    const unsigned short  RiskStatus_QUANTITY_NOT_IN_LOT_SIZE = 64;

    /**
     * @brief RiskStatus_INVALID_EXCHANGE_ORDER_ID
     */
    const unsigned short RiskStatus_INVALID_EXCHANGE_ORDER_ID = 65;
    
    /**
     * @brief RiskStatus_INVALID_ALGO_ID
     */
    const unsigned short RiskStatus_INVALID_ALGO_ID = 66;
    
    /**
     * @brief RiskStatus_ORDER_VALUE_EXCEEDED
     */
    const unsigned short RiskStatus_ORDER_VALUE_EXCEEDED = 67;

    /**
     * @brief RiskStatus_NO_LTP_AVAILABLE
     */
    const unsigned short RiskStatus_NO_LTP_AVAILABLE = 68;

    /**
     * @brief RiskStatus_LIMIT_PRICE_PROTECTION
     */
    const unsigned short RiskStatus_LIMIT_PRICE_PROTECTION = 69;

    /**
     * @brief RiskStatus_SL_TRIGGER_PRICE_DIFF_EXCEEDED
     */
    const unsigned short RiskStatus_SL_TRIGGER_PRICE_DIFF_EXCEEDED = 70;

    /**
     * @brief RSP_RiskStatus_MAX
     */
    const unsigned short RSP_RiskStatus_MAX = 71;


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

    /**
     * @brief RSP_ResponseCategory_MAX
     */
    const unsigned short RSP_ResponseCategory_MAX = 6001;

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
    const unsigned short CMD_ExchangeId_NSECOM = 80;
    const unsigned short CMD_ExchangeId_BSECOM = 81;
    const unsigned short CMD_ExchangeId_ICEX = 82;
    const unsigned short CMD_ExchangeId_MFX = 83;
    const unsigned short CMD_ExchangeId_EQUITY_IO = 84;
    const unsigned short CMD_ExchangeId_DERIVATIVE_IO = 85;
    const unsigned short CMD_ExchangeId_CURRENCY_IO = 86;
    const unsigned short CMD_ExchangeId_BINANCE = 87 ;   //This is added because of License portal dependency
    const unsigned short CMD_ExchangeId_KRAKEN = 88 ;    //This is added because of License portal dependency
    const unsigned short CMD_ExchangeId_MAX = 89;

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
     * @brief CMD_SecurityType_AUCTION
     */
    const unsigned short CMD_SecurityType_AUCTION = 4;

    /**
     * @brief CMD_SecurityType_MAX
     */
    const unsigned short CMD_SecurityType_MAX = 5;


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
     * @brief CMD_OrderType_MARKET_TO_LIMIT
     */
    const unsigned short CMD_OrderType_MARKET_TO_LIMIT = 13;

    /**
     * @brief CMD_OrderType_2L
     */
    const unsigned short CMD_OrderType_2L = 14;

    /**
     * @brief CMD_OrderType_3L
     */
    const unsigned short CMD_OrderType_3L = 15;

    /**
     * @brief CMD_OrderType_4L
     */
    const unsigned short CMD_OrderType_4L = 16;

    /**
     * @brief CMD_OrderType_SPREAD
     */
    const unsigned short CMD_OrderType_SPREAD = 17;

    /**
     * @brief CMD_OrderType_MAX
     */
    const unsigned short CMD_OrderType_MAX = 18;



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

    /**
     * @brief CMD_OrderValidity_EOS
     */
    const unsigned short CMD_OrderValidity_EOS = 11;

    /**
     * @brief CMD_OrderValidity_COL
     */
    const unsigned short CMD_OrderValidity_COL = 12;

    /**
     * @brief CMD_OrderValidity_MAX
     */
    const unsigned short CMD_OrderValidity_MAX = 13;


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

    /**
     * @brief CMD_ProductType_MAX
     */
    const unsigned short CMD_ProductType_MAX = 100;



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

    /**
     * @brief CMD_InstrumentType_ENERGY
     */
    const unsigned short CMD_InstrumentType_ENERGY = 5;

    /**
     * @brief CMD_InstrumentType_METAL
     */
    const unsigned short CMD_InstrumentType_METAL = 6;

    /**
     * @brief CMD_InstrumentType_BULLION
     */
    const unsigned short CMD_InstrumentType_BULLION = 7;

    /**
     * @brief CMD_InstrumentType_BASE_METAL
     */
    const unsigned short CMD_InstrumentType_BASE_METAL = 8;

    /**
     * @brief InstrumentType_PRECIOUS_METAL
     */
    const unsigned short CMD_InstrumentType_PRECIOUS_METAL = 9;

    /**
     * @brief CMD_InstrumentType_COMMODITY
     */
    const unsigned short CMD_InstrumentType_COMMODITY = 10;

    /**
     * @brief CMD_InstrumentType_IRT
     */
    const unsigned short CMD_InstrumentType_IRT = 11;

    /**
     * @brief CMD_InstrumentType_AUCTION
     */
    const unsigned short CMD_InstrumentType_AUCTION = 12;
    
    /**
     * @brief CMD_InstrumentType_AGR
     */
    const unsigned short CMD_InstrumentType_AGR = 13; 
    
    /**
     * @brief CMD_InstrumentType_BAS
     */
    const unsigned short CMD_InstrumentType_BAS = 14; 
     
    /**
     * @brief CMD_InstrumentType_YDR
     */
    const unsigned short CMD_InstrumentType_YDR = 15;

    /**
     * @brief CMD_InstrumentType_OPTFUT
     */
    const unsigned short CMD_InstrumentType_OPTFUT = 16;

    /**
     * @brief CMD_InstrumentType_IRC
     */
    const unsigned short CMD_InstrumentType_IRC = 17;

    /**
     * @brief CMD_InstrumentType_MAX
     */
    const unsigned short CMD_InstrumentType_MAX = 18;

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
     * @brief CMD_CommandCategory_NSECOM_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_NSECOM_DISCONNECTED = 152;

    /**
     * @brief CMD_CommandCategory_BSECOM_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_BSECOM_DISCONNECTED = 154;

    /**
     * @brief CMD_CommandCategory_NSECM_MarketSession_PREOPEN
     */
    const unsigned short CMD_CommandCategory_NSECM_MARKETSESSION_PREOPEN = 157;

    /**
     * @brief CMD_CommandCategory_NSECM_MarketSession_OPEN
     */
    const unsigned short CMD_CommandCategory_NSECM_MARKETSESSION_OPEN = 158;

    /**
     * @brief CMD_CommandCategory_NSECM_MarketSession_PREOPEN_CLOSED
     */
    const unsigned short CMD_CommandCategory_NSECM_MARKETSESSION_PREOPEN_CLOSED=159;

    /**
     * @brief CMD_CommandCategory_NSECM_MarketSession_POST_CLOSED
     */
    const unsigned short CMD_CommandCategory_NSECM_MARKETSESSION_POST_CLOSED=160;

    /**
     * @brief CMD_CommandCategory_NSEFO_MarketSession_OPEN
     */
    const unsigned short CMD_CommandCategory_NSEFO_MARKETSESSION_OPEN=161;

    /**
     * @brief CMD_CommandCategory_NSECDS_MarketSession_OPEN
     */
    const unsigned short CMD_CommandCategory_NSECDS_MARKETSESSION_OPEN=162;

    /**
     * @brief CMD_CommandCategory_IV_STRATEGY
     */
    const unsigned short CMD_CommandCategory_IV_STRATEGY=163;

    /**
     * @brief CMD_CommandCategory_MANUAL_DPR_UPDATE
     */
    const unsigned short CMD_CommandCategory_MANUAL_DPR_UPDATE=164;

    /**
     * @brief CMD_CommandCategory_UPDATE_CONNECTIVITY_STATUS
     */
    const unsigned short CMD_CommandCategory_UPDATE_CONNECTIVITY_STATUS = 165;

    /**
     * @brief CMD_CommandCategory_SUBSCRIBE_FEED
     */
    const unsigned short CMD_CommandCategory_SUBSCRIBE_FEED = 166;

    /**
     * @brief CMD_CommandCategory_REQUEST_PARTICIPANT_CODES
     */
    const unsigned short CMD_CommandCategory_REQUEST_PARTICIPANT_CODES = 167;

    /**
     * @brief CMD_CommandCategory_DMS_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_DMS_DISCONNECTED = 168;

    /**
     * @brief CMD_CommandCategory_ICEX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_ICEX_DISCONNECTED=169;

    /**
     * @brief CMD_CommandCategory_CONF_BACKEND_PARAMETERS
     */
    const unsigned short CMD_CommandCategory_CONF_BACKEND_PARAMETERS = 170;

    /**
     * @brief CMD_CommandCategory_BOCO
     */
    const unsigned short CMD_CommandCategory_BOCO = 171;

    /**
     * @brief CMD_CommandCategory_BOCO_OFFLINE_REPLAY
     */
    const unsigned short CMD_CommandCategory_BOCO_OFFLINE_REPLAY = 172;

    /**
     * @brief CMD_CommandCategory_CLIENT_CATEGORY_BAN
     */
    const unsigned short CMD_CommandCategory_CLIENT_CATEGORY_BAN = 173;

    /**
     * @brief CMD_CommandCategory_ASM_GSM_BAN
     */
    const unsigned short CMD_CommandCategory_ASM_GSM_BAN = 174;

    /**
     * @brief CMD_CommandCategory_PHYSICAL_DELIVERY_BAN
     */
    const unsigned short CMD_CommandCategory_PHYSICAL_DELIVERY_BAN = 175;

    /**
     * @brief CMD_CommandCategory_MTM_ALERT_BREACH_ACTION
     */
    const unsigned short CMD_CommandCategory_MTM_ALERT_BREACH_ACTION = 176;

    /**
     * @brief CMD_CommandCategory_AUTO_SQUAREOFF_POPUP_ACTION
     */
    const unsigned short CMD_CommandCategory_AUTO_SQUAREOFF_POPUP_ACTION = 177;

    /**
     * @brief CMD_CommandCategory_MULTI_LEG_ORDER
     */
    const unsigned short CMD_CommandCategory_MULTI_LEG_ORDER = 178;

    /**
     * @brief CMD_CommandCategory_OPTIONS_WIDGET_UPDATE
     */
    const unsigned short CMD_CommandCategory_OPTIONS_WIDGET_UPDATE = 179;

    /**
     * @brief CMD_CommandCategory_MFX_DISCONNECTED
     */
    const unsigned short CMD_CommandCategory_MFX_DISCONNECTED=180;

    /**
     * @brief CMD_CommandCategory_WAVE_SINGLE_ORDER
     */
    const unsigned short CMD_CommandCategory_WAVE_SINGLE_ORDER = 181;

    /**
     * @brief CMD_CommandCategory_FIX_SENDER_COMP_ID_LIST
     */
    const unsigned short CMD_CommandCategory_FIX_SENDER_COMP_ID_LIST = 182;

    /**
     * @brief CMD_CommandCategory_SOR_UNMAPPED
     */
    const unsigned short CMD_CommandCategory_SOR_UNMAPPED = 183; 

    /**
     * @brief CMD_CommandCategory_BOCO_SETTINGS_UPDATE
     */
    const unsigned short CMD_CommandCategory_BOCO_SETTINGS_UPDATE = 184;

    /**
     * @brief CMD_CommandCategory_AMO_ORDER
     */
    const unsigned short CMD_CommandCategory_AMO_ORDER = 185;

    /**
     * @brief CMD_CommandCategory_AMO_MANUAL_TRIGGER
     */
    const unsigned short CMD_CommandCategory_AMO_MANUAL_TRIGGER = 186;

    /**
     * @brief CMD_CommandCategory_CMD_LINE_API2_STRATEGY
     */
    const unsigned short CMD_CommandCategory_CMD_LINE_API2_STRATEGY = 187;

    /**
     * @brief CommandCategory_TWO_LEG_THREE_LEG_RATIO_IOC
     */
    const unsigned short CommandCategory_TWO_LEG_THREE_LEG_RATIO_IOC = 188;
    /**
     * @brief CMD_CommandCategory_UNHEDGE_TRACKER_DATA_REQUEST
     */
    const unsigned short CMD_CommandCategory_UNHEDGE_TRACKER_DATA_REQUEST = 189;
    
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
    const unsigned short CMD_OrderCateGory_MAX = 9;

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

    /**
     * @brief RSP_ErrorCode_PR_REJECTION_BSE
     */
    const short RSP_ErrorCode_PR_REJECTION_BSE = 10001;

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

    const uint64_t SECONDS_PER_DAY = 86400;
    const uint64_t SECONDS_PER_HOUR = 3600;
    const uint64_t SECONDS_PER_MINUTE = 60;
    const uint64_t SECONDS_TO_NANOSECONDS = 1000000000;

    /**
     * @brief MAX_ORDER_VALUE - value of 10 cr to check for total order value
     */
    const int64_t MAX_ORDER_VALUE = 100000000;

    /**
     * @brief BL_SYMBOL_SERIES - Series of the symbol is BL i.e. BlockDeal
     */
    const std::string BL_SYMBOL_SERIES = "BL";

    const time_t BASE = 0;
    const uint32_t UTC   = 0;
    const uint32_t LOCAL = localtime(&BASE)->tm_gmtoff;
    const uint32_t IST = 19800;

    const std::string ISO_TIME_FORMAT = "%T";
    const std::string STANDARD_DATE_FORMAT = "%d/%m/%Y";
    const std::string TWELVE_HOUR_TIME_FORMAT = "%r";
    const std::string DATE_TIME_FORMAT = "%m/%d/%Y %X";

    /**
     * @brief RSP_ErrorCode_ORDER_CANNOT_BE_MODIFIED_NSE
     * Comes If Some Parameter is wrong while sending an order
     */
    const DATA_TYPES::ERROR_CODE RSP_ErrorCode_ORDER_CANNOT_BE_MODIFIED_NSE = 16346;

    /**
     * @brief CMD_ExchangeId_NSE - for exchange NSE
     */
    const std::string CMD_ExchangeId_NSE = "NSE";

    /**
     * @brief CMD_ExchangeId_BSE - for exchange BSE
     */
    const std::string CMD_ExchangeId_BSE = "BSE";

    /**
     * @brief CMD_ExchangeId_MSE - for exchange MSE
     */
    const std::string CMD_ExchangeId_MSE = "MSE";

    /**
     * @brief CMD_ExchangeId_MCX - for exchange MCX
     */
    const std::string CMD_Exchange_MCX = "MCX";
     
    /**
     * @brief ScripGroup_CASH
     */
    const short ScripGroup_CASH = 0;

    /**
     * @brief ScripGroup_FUTSTK - group consisting futures on stock
     */
    const short ScripGroup_FUTSTK = 1;

    /**
     * @brief ScripGroup_FUTIDX - group consisting futures on index
     */
    const short ScripGroup_FUTIDX = 2;

    /**
     * @brief ScripGroup_FUTCUR - group consisting futures on currency
     */
    const short ScripGroup_FUTCUR = 3;

    /**
     * @brief ScripGroup_FUTIRD - group consisting interest rate future derivatives
     */
    const short ScripGroup_FUTIRD = 4;

    /**
     * @brief ScripGroup_FUTIVX - group consisting futures on volatility index
     */
    const short ScripGroup_FUTIVX = 5;

    /**
     * @brief ScripGroup_FUTCOM - group consisting comodities
     */
    const short ScripGroup_FUTCOM = 6;

    /**
     * @brief ScripGroup_OPTSTK - group consisting options on stock
     */
    const short ScripGroup_OPTSTK = 7;

    /**
     * @brief ScripGroup_OPTIDX - group consisting options on index
     */
    const short ScripGroup_OPTIDX = 8;

    /**
     * @brief ScripGroup_OPTCUR - group consisting options on currency
     */
    const short ScripGroup_OPTCUR = 9;

    /**
     * @brief ScripGroup_OPTIRD - group consisting interest rate option derivatives
     */
    const short ScripGroup_OPTIRD = 10;

    /**
     * @brief ScripGroup_OPTIVX - group consisting options on volatility index
     */
    const short ScripGroup_OPTIVX = 11;

    /**
     * @brief ScripGroup_OPTCOM - group consisting comodities
     */
    const short ScripGroup_OPTCOM = 12;

    /**
     * @brief ScripGroup_OPTIRT
     */
    const short ScripGroup_OPTIRT = 13;

    /**
     * @brief ScripGroup_FUTIRT
     */
    const short ScripGroup_FUTIRT = 14;

    const short ScripGroup_EQTYDR = 15;

    const short ScripGroup_FUTBLN = 16;

    const short ScripGroup_OPTBLN = 17;

    const short ScripGroup_FUTENR = 18;

    const short ScripGroup_OPTENR = 19;

    const short ScripGroup_FUTAGR = 20;

    const short ScripGroup_FUTBAS = 21;

    const short ScripGroup_OPTBAS = 22;

    const short ScripGroup_OPTFUT = 23;

    const short ScripGroup_FUTIRC = 24;

    const short ScripGroup_OPTIRC = 25;

    const short ScripGroup_UNDCUR = 26;

    const short ScripGroup_USAIDR = 27;

    const short ScripGroup_UNDSTK = 28;

    const short ScripGroup_UNDCOM = 29;

    /**
     * @brief ScripGroup_MAX
     */
    const short ScripGroup_MAX = 30;

    /**
     * @brief API params buffer header(4(command category) + 4(packet length) + 4(apiId) )
     */
    const short API_BUFFER_HEADER = 12;

    const short CMD_QUEUED_SESSION_NORMAL = 0;

    const short CMD_QUEUED_SESSION_PREOPEN = 1;

    const short CMD_QUEUED_SESSION_PREOPEN_CLOSED = 2;

    const short CMD_QUEUED_SESSION_OPEN = 3;

    const short CMD_QUEUED_SESSION_CLOSE = 4;

    const short CMD_QUEUED_SESSION_POSTCLOSE = 5;

    const short CMD_QUEUED_SESSION_MAX = 6;

    /**
     * @brief STRATEGY_TYPE_DEFAULT_VALUE
     * @description -Default value is the combination of ByPassNNF(default '0') + NNF_SUFFIX(default '01') = 001
     *              - If BYPASS_NNFID is enabled in strategyBlock and the strategy is running
     *              - interexchange then set 13th digit of location Id with '4' in case of NSE orders.
     *              - NNF_SUFFIX is in strategy Block with default value '01' means the vendorcode set in RMS should pass in the order
     *              - If value other then '01' it should bypass RMS vendorCode and Pass NNF_SUFFIX from strategy Block in the order
     */
    const short STRATEGY_TYPE_DEFAULT_VALUE = 1;

    /************************************************************************************************************
     ***********************************Strategy Logs Messages***************************************************
     ************************************************************************************************************/
    namespace STRATEGY_CONSTANTS
    {
      const std::string STATIC_DATA_NOT_FOUND_SYMBOL1 = "Some error in reading static data for first symbol";
      const std::string STATIC_DATA_NOT_FOUND_SYMBOL2 = "Some error in reading static data for second symbol";
      const std::string STATIC_DATA_NOT_FOUND_SYMBOL3 = "Some error in reading static data for third symbol";
      const std::string STATIC_DATA_NOT_FOUND_SYMBOL4 = "Some error in reading static data for fourth symbol";
      const std::string TIME_TO_REACT = "TTR";
      const std::string TIME_TO_SEND = "TTS";
      const std::string TOTAL_TIME = "TT";
      const std::string PARAMETERS_DUMP = " Dump of strategy parameters";
      const std::string MODIFY_PARAMETERS_DUMP = "Dump of strategy parameters on modification";
      const std::string INVALID_CLIENTCODE_OR_ADAPTER_DETAIL = "Invalid client code or adapter details. Exiting strategy.";
      const std::string RISK_STATUS = "Risk status";
      const std::string EXCHANGE_DETAIL_LEG1 = "Exchange adapter detail for leg1";
      const std::string EXCHANGE_DETAIL_LEG2 = "Exchange adapter detail for leg2";
      const std::string EXCHANGE_DETAIL_LEG3 = "Exchange adapter detail for leg3";
      const std::string EXCHANGE_DETAIL_LEG4 = "Exchange adapter detail for leg4";
      const std::string STRATEGY_VERSION_DIFFERS = "Strategy version differs";
      const std::string BACKEND_STRATEGY_VERSION = "Backend strategy version";
      const std::string FRONTEND_STRATEGY_VERSION = "Frontend strategy version";
      const std::string INVALID_ALGO_ID = "Invalid algo id received";
      const std::string INVALID_ALGO_CATEGORY = "Invalid algo category";
      const std::string STRATEGY_STARTED = "Strategy started";
      const std::string MODIFY_COMMANDCATEGORY = "Strategy received Modify_STRATEGY command.";
      const std::string WRONGPARAM = "Error : Wrong Parameter";
      const std::string LEG1_TBT_FAILED = "Leg-1 symbol: FAILED subscribing to TBT";
      const std::string LEG2_TBT_FAILED = "Leg-2 symbol: FAILED subscribing to TBT";
      const std::string LEG3_TBT_FAILED = "Leg-3 symbol: FAILED subscribing to TBT";
      const std::string LEG4_TBT_FAILED = "Leg-4 symbol: FAILED subscribing to TBT";
      const std::string MAX_REPLACE_COUNTER_BREACHED = "Max allowed replace counter breached, cancelling current bid";
      const std::string MAX_REPLACE_COUNTER = "Max Allowed replace counter";
      const std::string CURRENT_REPLACE_COUNTER = "Current replace Counter";
      const std::string LTP = "Last traded price is";
      const std::string SPREAD_LIMIT_BREACHED = "Spread limit breached. Exiting strategy.";
      const std::string STRATEGY_COMPLETED = "Strategy completed.";
      const std::string STRATEGY_TERMINATED = "Strategy terminated.";
      const std::string STRATEGY_EXIT = "Exiting strategy.";
      const std::string STRATEGY_UNKNOWN_STATE = "Strategy is in unknown state. Exiting strategy.";
      const std::string LEG1_ORDER_FILLED_QTY = "First leg order filled, Quantity";
      const std::string LEG2_ORDER_FILLED_QTY = "Second leg order filled, Quantity";
      const std::string LEG3_ORDER_FILLED_QTY = "Third leg order filled, Quantity";
      const std::string LEG4_ORDER_FILLED_QTY = "Fourth leg order filled, Quantity";
      const std::string LEG1_ORDER_FILLED_PRICE = "First leg order filled, Price";
      const std::string LEG2_ORDER_FILLED_PRICE = "Second leg order filled, Price";
      const std::string LEG3_ORDER_FILLED_PRICE = "Third leg order filled, Price";
      const std::string LEG4_ORDER_FILLED_PRICE = "Fourth leg order filled, Price";
      const std::string LEG1_LAST_ORD_REJECT = "Leg-1 last order is rejected";
      const std::string LEG2_LAST_ORD_REJECT = "Leg-2 last order is rejected";
      const std::string LEG3_LAST_ORD_REJECT = "Leg-3 last order is rejected";
      const std::string LEG4_LAST_ORD_REJECT = "Leg-4 last order is rejected";
      const std::string LEG1_ORDER_CANCELED = "Leg-1 order cancelled";
      const std::string LEG2_ORDER_CANCELED = "Leg-2 order cancelled";
      const std::string LEG3_ORDER_CANCELED = "Leg-3 order cancelled";
      const std::string LEG4_ORDER_CANCELED = "Leg-4 order cancelled";
      const std::string ORDER_CONFRIMATION_RCVD = "Order confirmation received.";
      const std::string STRATEGY_TERMINATED_FRONT_END = "Strategy terminated from front-end.";
      const std::string FORCE_TERMINATE = "Received force terminate command from front-end.";
      const std::string ORDER_NOT_FOUND = "Order not found";
      const std::string LEG1_DEPTH_ONE_SIDE = "Order depth first leg one side";
      const std::string LEG1_DEPTH_OTHER_SIDE = "Order depth first leg other side";
      const std::string LEG2_DEPTH_ONE_SIDE = "Order depth second leg one side";
      const std::string LEG2_DEPTH_OTHER_SIDE = "Order depth second leg other side";
      const std::string LEG3_DEPTH_ONE_SIDE = "Order depth third leg one side";
      const std::string LEG3_DEPTH_OTHER_SIDE = "Order depth third leg other side";
      const std::string LEG4_DEPTH_ONE_SIDE = "Order depth fourth leg one side";
      const std::string LEG4_DEPTH_OTHER_SIDE = "Order depth fourth leg other side";
      const std::string TOTAL_QTY_ZERO = "Total quantity is zero. Exiting strategy.";
      const std::string ITERATION_TOTAL_QTY_ZERO = "Iteration quantity is zero. Exiting strategy.";
      const std::string RATIO_MISMATCH = " Ratio mismatch occured. Exiting strategy.";
      const std::string RATIO1 = "Ratio1";
      const std::string RATIO2 = "Ratio2";
      const std::string RATIO3 = "Ratio3";
      const std::string RATIO4 = "Ratio4";
      const std::string LEG1_DATA_ERROR = "Error in leg-1 data. Exiting strategy.";
      const std::string LEG2_DATA_ERROR = "Error in leg-2 data. Exiting strategy.";
      const std::string LEG3_DATA_ERROR = "Error in leg-3 data. Exiting strategy.";
      const std::string LEG4_DATA_ERROR = "Error in leg-4 data. Exiting strategy.";
      const std::string HCF_ZERO = " HCF is zero. Some error in calculation. Exiting strategy.";
      const std::string CIRCULAR_QUEUE_FALSE = "Circular queue returned false";
      const std::string CANCELLING_PREV_BID = "Cancelling previous bid.";
      const std::string TURNAROUNDTIME_LEG1 = "TAT Leg-1";
      const std::string TURNAROUNDTIME_LEG2 = "TAT Leg-4";
      const std::string TURNAROUNDTIME_LEG3 = "TAT Leg-3";
      const std::string TURNAROUNDTIME = "TAT";
      const std::string ORDER_FILLED = "Order filled";
      const std::string PARTIALLY_FILLED = "Order partially filled";
      const std::string RMS_FAILED = "RMS Failed";
      const std::string ORDER_MODIFIED_PRICE = "Order modified to price";
      const std::string ORDER_MODIFIED_QTY= "Order modified to quantity";
      const std::string LEG1_BID_ORDER_PRICE = "Leg-1 bid price";
      const std::string LEG1_BID_ORDER_QTY = "Leg-1 bid quantity";
      const std::string LEG1_MODIFY_ORDER_PRICE = "Leg-1 modify price";
      const std::string LEG1_ORIGINAL_ORDER_QTY = "Leg-1 original order quantity";
      const std::string LEG1_MODIFY_ORDER_REPLACE_QTY = "Leg 1 modify order replace quantity";
      const std::string FILLED_QTY = "Filled Quantity";
      const std::string ORDER_PLACED_SUCCESSFULLY = "Order placed successfully";
      const std::string INVALID_VENDOR_CODE = "Invalid Vendor Code";
      const std::string DMS_DISCONNECTED = "DMS disconnected. Terminating strategy.";

    } // STRATEGY_CONSTANTS

    /************************************************************************************************************
     ************************************************************************************************************/
    /**
     * @brief RSP_TerminationReasonType_AUTO
     */
    const unsigned short RSP_TerminationReasonType_AUTO = 0;

    /**
     * @brief RSP_TerminationReasonType_FRONT_END
     */
    const unsigned short RSP_TerminationReasonType_FRONT_END = 1;

    /**
     * @brief RSP_TerminationReasonType_DMS_DISCONNECTION
     */
    const unsigned short RSP_TerminationReasonType_DMS_DISCONNECTION = 2;

    /**
     * @brief RSP_TerminationReasonType_EXCHANGE_DISCONNECTION
     */
    const unsigned short RSP_TerminationReasonType_EXCHANGE_DISCONNECTION = 3;

    /**
     * @brief RSP_TerminationReasonType_AUTO_TIMER_EXPIRED
     */
    const unsigned short RSP_TerminationReasonType_AUTO_TIMER_EXPIRED = 4;

    /**
     * @brief RSP_TerminationReasonType_MAX
     */
    const unsigned short RSP_TerminationReasonType_MAX = 5;

    /** Service Types for care orders.
     *  Same enums exist in sales trader proto structures.
     *  If any changes are done here should also be updated 
     *  in those structures too.
     */
    const short Service_OPEN = 0;
    const short Service_DISPLAY_SIZE = 1;
    const short Service_LIQUIDITY_SEEKER = 2;
    const short Service_INCOGNITO = 3;
    const short Service_TWAP = 4;
    const short Service_POV = 5;
    const short Service_MANUAL_ORDER = 6;
    const short Service_FORKWAVE = 7;
    const short Srvce_MAX = 8;

    /**
     * @brief CUSTOM_STRATEGY_COMMAND -Will store custom commands will need to
     * handle in strategy if needed.
     */
    enum class CUSTOM_STRATEGY_COMMAND
    {
      AUTO_TERMINATE, // This event is going to push when AUTO_TERMINATE_TIME is achieved.
      MAX
    };

    /**
     * @brief NSE_SOR_STRATEGY_TYPE_DIGIT : This is 3rd last digit of location id for nse
     * when a strategy is running in sor mode.
     */
    const short NSE_SOR_STRATEGY_TYPE_DIGIT = 2;

    /**
     * @brief BSE_SOR_STRATEGY_TYPE_DIGIT : This is 3rd last digit of location id for bse
     * when a strategy is running in sor mode.
     */
    const short BSE_SOR_STRATEGY_TYPE_DIGIT = 4;

    /**
     * @brief CMD_ExpiryDay_INCLUDE
     */
    const short CMD_ExpiryDay_INCLUDE = 0;

    /**
     * @brief CMD_ExpiryDay_HALF_INCLUDE
     */
    const short CMD_ExpiryDay_HALF_INCLUDE = 1;

    /**
     * @brief CMD_ExpiryDay_EXCLUDE
     */
    const short CMD_ExpiryDay_EXCLUDE = 2;

    /**
     * @brief CMD_ExpiryDay_INCLUDE_ON_EXPIRY
     */
    const short CMD_ExpiryDay_INCLUDE_ON_EXPIRY = 3;

    /**
     * @brief CMD_ExpiryDay_MAX
     */
    const short CMD_ExpiryDay_MAX = 4;

    /**
     * @brief ReferenceSpotPrice_BID
     */
    const short ReferenceSpotPrice_BID = 0;

    /**
     * @brief ReferenceSpotPrice_ASK
     */
    const short ReferenceSpotPrice_ASK = 1;

    /**
     * @brief ReferenceSpotPrice_LTP
     */
    const short ReferenceSpotPrice_LTP = 2;

    /**
     * @brief Default_Modified_By_Id
     */
    const signed long Default_Modified_By_Id = -1;

    const API2::TYPE_DEFS::AssetType AssetType_Default  = 0;
    const API2::TYPE_DEFS::AssetType AssetType_Agri     = 1;
    const API2::TYPE_DEFS::AssetType AssetType_Non_Agri = 2;
    const API2::TYPE_DEFS::AssetType AssetType_Intl     = 3;
    const API2::TYPE_DEFS::AssetType AssetType_Max      = 4;

    const std::string ASSET_CODE_OILSEEDS = "OILSEEDS";
    const std::string ASSET_CODE_SPICES = "SPICES";
    const std::string ASSET_CODE_OTHERS = "OTHERS";
    const std::string ASSET_CODE_AGRO_PRODUCTS = "AGRO PRODUCTS";
    const std::string ASSET_CODE_PLANTATION = "PLANTATION";
    const std::string ASSET_CODE_OIL = "Oil";

  }
}
#endif
