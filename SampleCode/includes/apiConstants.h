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
    const size_t MarketDepthArraySize = 5;

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
     * @brief RSP_StrategyComment_STRATEGY_END
     */
    const unsigned short RSP_StrategyComment_OHLC_SUBSCRIPTION_FAILED =52;

    /**
     * @brief RSP_StrategyComment_SELF_TRADE
     */
    const unsigned short RSP_StrategyComment_SELF_TRADE =53;

    /**
     * @brief RSP_StrategyComment_STRATEGY_END
     */
    const unsigned short RSP_StrategyComment_MAX = 54;

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

    /**
     * @brief RSP_RiskStatus_MAX
     */
    const unsigned short RSP_RiskStatus_MAX = 32; // = 31


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
     * @brief CMD_ExchangeId_BSE
     */
    const unsigned short CMD_ExchangeId_BSE = 1;

    /**
     * @brief CMD_ExchangeId_NSE
     */
    const unsigned short CMD_ExchangeId_NSE = 2;

    /**
     * @brief CMD_ExchangeId_ESMNSE
     */
    const unsigned short CMD_ExchangeId_ESMNSE = 3;

    /**
     * @brief CMD_ExchangeId_SGX
     */
    const unsigned short CMD_ExchangeId_SGX = 4;

    /**
     * @brief CMD_ExchangeId_NSECDS
     */
    const unsigned short CMD_ExchangeId_NSECDS = 5;

    /**
     * @brief CMD_ExchangeId_BSEETI
     */
    const unsigned short CMD_ExchangeId_BSEETI = 6;

    /**
     * @brief CMD_ExchangeId_CFH
     */
    const unsigned short CMD_ExchangeId_CFH = 7;

    /**
     * @brief CMD_ExchangeId_MAREX
     */
    const unsigned short CMD_ExchangeId_MAREX = 9;

    /**
     * @brief CMD_ExchangeId_MCX
     */
    const unsigned short CMD_ExchangeId_MCX = 10;

    /**
     * @brief CMD_ExchangeId_DGCX
     */
    const unsigned short CMD_ExchangeId_DGCX = 11;

    /**
     * @brief CMD_ExchangeId_TTLME
     */
    const unsigned short CMD_ExchangeId_TTLME = 12;

    /**
     * @brief CMD_ExchangeId_TTCME
     */
    const unsigned short CMD_ExchangeId_TTCME = 13;

    /**
     * @brief CMD_ExchangeId_CTP_CFFEX
     */
    const unsigned short CMD_ExchangeId_CTP_CFFEX = 14;

    /**
     * @brief CMD_ExchangeId_CTP_CZCE
     */
    const unsigned short CMD_ExchangeId_CTP_CZCE = 15;

    /**
     * @brief CMD_ExchangeId_CTP_DCE
     */
    const unsigned short CMD_ExchangeId_CTP_DCE = 16;

    /**
     * @brief CMD_ExchangeId_CTP_SHFE
     */
    const unsigned short CMD_ExchangeId_CTP_SHFE = 17;

    /**
     * @brief CMD_ExchangeId_SGXCUR
     */
    const unsigned short CMD_ExchangeId_SGXCUR = 18;

    /**
     * @brief CMD_ExchangeId_DGCXCD
     */
    const unsigned short CMD_ExchangeId_DGCXCD = 19;

    /**
     * @brief CMD_ExchangeId_MAX
     */
    const unsigned short CMD_ExchangeId_MAX = 20;

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
     * @brief CMD_SecurityType_MAX
     */
    const unsigned short CMD_SecurityType_MAX = 3;


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

    /**
     * @brief CMD_TransactionType_MAX
     */
    const unsigned short CMD_TransactionType_MAX = 3;



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



    /************************************************************************************************************************/
    /************************************************************************************************************************/

    const unsigned short CMD_OrderCategory_SINGLE = 0;
    const unsigned short CMD_OrderCategory_SPREAD = 1;
    const unsigned short CMD_OrderCategory_MULTILEG = 2;


    /************************************************************************************************************************/
    /************************************************************************************************************************/



    /**
     * @brief RSP_ErrorCode_SELF_TRADE Error Code For NSEFO
     * */ 
    const short RSP_ErrorCode_SELF_TRADE_FO = 17071;
    /**
     * @brief RSP_ErrorCode_SELF_TRADE Error Code For NSECM
     * */ 
    const short RSP_ErrorCode_SELF_TRADE_CM = 17080;



    /************************************************************************************************************************/
    /************************************************************************************************************************/

  }
}
#endif
