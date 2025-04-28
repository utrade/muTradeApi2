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
     * @brief CURRENCY_TYPE
     */
    typedef std::string CURRENCY_TYPE;
    /**
     * @typedef
     * @brief PRICE
     */
    typedef SIGNED_LONG PRICE;

    /**
     * @typedef
     * @brief PRICE_PROTECTIOM
     */
    typedef UNSIGNED_SHORT PRICE_PROTECTION;

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
     * @brief LAST_TRADE_TIME
     */
    typedef int64_t LAST_TRADE_TIME;

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
     * @brief STREAM_ID
     */
    typedef UNSIGNED_SHORT STREAM_ID;
    
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

    typedef std::string StrategyError;

    /**
     * @brief TerminationReasonType
     */
    typedef UNSIGNED_SHORT TerminationReasonType;

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
     * @brief SourceId
     */
    typedef UNSIGNED_SHORT SourceId;

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
     * @brief SelfTradeOrderFlag
     */
    typedef UNSIGNED_SHORT SelfTradeOrderFlag;

    /**
     * @typedef
     * @brief STPC
     */
    typedef uint8_t STPC;

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
     * @brief MarketSessionType
     */
    typedef UNSIGNED_SHORT MarketSessionType;

    /**
     * @typedef
     * @brief MarketType
     */
    typedef UNSIGNED_SHORT MarketType;

    /**
     * enum
     *
     * @brief AccountType - customer for normal clients trading, firm for direct broker trading
     */
    enum class AccountType : uint8_t
    {
      CUSTOMER,
      FIRM,
      SPLCLIENT,
      INST,
      MAX
    };

    /**
     * enum
     *
     * @brief ClientSegmentType - CM for cash segment, FO for future / option segment
     */
    enum class ClientSegmentType : uint8_t
    {
      CM,
      FO,
      ALL,
      MAX
    };

    /**
     * @typedef
     * @brief String
     */
    typedef std::string String;

    /**
     * @typedef
     * @brief OrderPriority
     */
    typedef UNSIGNED_SHORT OrderPriority;

    /**
      * @typedef
      * @brief GTC_GTD_Date
      */
    typedef UNSIGNED_LONG GTD_Date;

    /**
     * @typedef
     * @brief UCHAR
     */
    typedef UNSIGNED_CHARACTER UCHAR;

    /**
     * @typedef
     * @brief USHORT
     */
    typedef UNSIGNED_SHORT USHORT;

    /**
     * @typedef
     * @brief UINTEGER32
     */
    typedef UNSIGNED_INTEGER UINTEGER32;

    /**
     * @typedef
     * @brief UINTEGER64
     */
    typedef UNSIGNED_LONG UINTEGER64;

    /**
     * @typedef
     * @brief INTEGER32
     */
    typedef SIGNED_INTEGER INTEGER32;

    /**
     * @typedef
     * @brief INTEGER64
     */
    typedef SIGNED_LONG INTEGER64;

    /**
     * @typedef
     * @brief PlatformType
     */
    typedef UNSIGNED_SHORT PlatformType;

    /**
     * @typedef
     * @brief ConfirmationType
     */
    typedef UNSIGNED_SHORT ConfirmationType;

    /**
     * @typedef
     * @brief TradeReportId
     */
    typedef UNSIGNED_LONG TRADE_REPORT_ID;

    /**
     * @typedef
     * @brief TradeMatchId 
     */
    typedef std::string TRADE_MATCH_ID ;

    /**
     * @typedef
     * @brief TradeId 
     */
    typedef std::string TRADE_ID ;

    /**
     * @typedef
     * @brief PreviouslyReported flag
     */
    typedef bool PREVIOUSLY_REPORTED;

    /**
     * @typedef
     * @brief TradeDate
     */
    typedef UNSIGNED_LONG TRADE_DATE ;

    /**
     * @typedef
     * @brief TransactTime
     */
    typedef UNSIGNED_LONG TRANSACT_TIME ;

    /**
     * @typedef
     * @brief PartyId 
     */
    typedef std::string PARTY_ID ;

    /**
     * @typedef
     * @brief AllocId 
     */
    typedef std::string ALLOC_ID ;
    
    /**
     * @typedef
     * @brief CopyIndicator
     */
    typedef bool COPY_INDICATOR ;

    /**
     * @typedef
     * @brief TradeType 
     */
    typedef int TRD_TYPE ;
    
    /**
     * @typedef
     * @brief AggressorIndicator
     */
    typedef bool AGGRESSOR_INDICATOR ;

    /**
     * @typedef
     * @brief AllocationAccount
     */
    typedef std::string ALLOC_ACCOUNT ;

    /**
     * @typedef
     * @brief IndividualAllocId 
     */
    typedef std::string INDIVIDUAL_ALLOC_ID ;

    /**
     * @typedef
     * @brief AMT
     */
    typedef UNSIGNED_LONG AMT ;

    /**
     * @typedef
     * @brief TradeFeeType
     */
    typedef std::string TRADE_FEE_TYPE ;

    /**
     * @typedef
     * @brief Text
     */
    typedef std::string TEXT ;

    /**
     * @typedef
     * @brief OrderReference
     */
    typedef std::string ORDER_REFERENCE ;

    /**
     * @typedef
     * @brief DealNumber
     */
    typedef SIGNED_INTEGER DEAL_NUMBER ;

    /*
     * @typedef
     * @brief Delivery Unit
     * */
    typedef SIGNED_INTEGER DELIVERY_UNIT ;

    /*
     * @typedef
     * @brief Side Num
     * */
    typedef int SIDE_NUM ;
    
    /*
     * @typedef
     * @brief Account
     * */
    typedef std::string ACCOUNT ;

    /**
     * @typedef
     * @brief OrderCategory
     */
    typedef UNSIGNED_SHORT OrderCategory;

    /**
     * @brief HOLDING_TYPE
     */
    typedef UNSIGNED_CHARACTER HOLDING_TYPE;
  
    /**
     * @brief AlgoId
     */
    typedef SIGNED_LONG  AlgoId;

    /**
     * @brief AlgoCategory
     */
    typedef short  AlgoCategory;

    /**
     * @brief ScripGroup  - group containing symbols based on type of security(cash, future, option)
     *                      and type of derivative(stock, future, currency etc)
     */
    typedef short ScripGroup;

    /**
     * @brief MicroTimeStamp
     */
    typedef int64_t MicroTimeStamp;

    /**
     * @brief The TimerType enum
     */
    enum TimerType
    {
      TimerType_Preopen = 0,
      TimerType_PreOpenClose = 1,
      TimerType_Open = 2,
      TimerType_Close = 3,
      TimerType_PostClose = 4,
      TimerType_Max = 5
    };

    /**
     * @brief SECURITY_ID
     */
    typedef SIGNED_LONG SECURITY_ID;


    /**
     * @brief The BYPASS_NNFID enum
     * @description - If BYPASS_NNFID is enabled in strategyBlock and the strategy is running
     *              - interexchange then set 13th digit of location Id with '4' in case of NSE orders
     */
    enum BYPASS_NNFID
    {
      BYPASS_NNFID_DISABLED = 0,
      BYPASS_NNFID_ENABLED = 1,
      BYPASS_NNFID_SOR_ENABLED = 2,
      BYPASS_NNFID_MAX
    };

    /**
     * @brief AVG_PRICE
     */
    typedef double AVG_PRICE;

    /**
     * @brief RMS_POSITION_PRECISION
     */
    typedef double RMS_POSITION_PRECISION;

     /*
     * @brief NanoSecondTimeStamp
     */
    typedef SIGNED_LONG NanoSecondTimeStamp;

    /**
     * @brief TBT_ORDER_ID: Used to represent exchange order id's in nse Multicast tbt
     */
    typedef UNSIGNED_LONG TBT_ORDER_ID;

    /**
     * @brief Service: Service of a wave.
     */
    typedef UNSIGNED_SHORT Service;

    /**
     * @brief CARE_ORDER_ID
     */
    typedef UNSIGNED_LONG CARE_ORDER_ID;

    /**
     * @brief LINE_ID
     */
    typedef UNSIGNED_SHORT LINE_ID;

    /**
     * @brief WAVE_ID
     */
    typedef UNSIGNED_SHORT WAVE_ID;

    /**
     * @brief USER_ID_STR
     */
    typedef std::string USER_ID_STR;

    /**
     * @brief PERCENTAGE
     */
    typedef int64_t PERCENTAGE;

    /**
     * @brief CASH_UNIQUE_KEY
     */
    typedef std::string CASH_UNIQUE_KEY;

    /**
     * @brief GiveUpFlag
     */
    typedef UNSIGNED_CHARACTER GiveUpFlag;
    
    /**
     * @brief EXPIRYDAY_TYPE
     */
    typedef UNSIGNED_SHORT EXPIRYDAY_TYPE;

    /**
     * @brief REFERENCE_SPOT_PRICE_TYPE
     */
    typedef UNSIGNED_SHORT REFERENCE_SPOT_PRICE_TYPE;

    /**
     * @brief DIVIDEND
     */
    typedef double DIVIDEND;

    /**
     * @brief INTEREST_RATE
     */
    typedef double INTEREST_RATE;

    /**
     * @brief TIME_TO_EXPIRE
     */
    typedef double TIME_TO_EXPIRE;

    /**
     * @brief IMPLIED_VOLATILITY
     */
    typedef double IMPLIED_VOLATILITY;

    /**
     * @brief DELTA
     */
    typedef double GREEK;

    /**
     * @brief time in epoch
     */
    typedef UNSIGNED_INTEGER EPOCH_TIME;

    /**
     * @brief CUSTOM_TRADER_ID
     */
    typedef UNSIGNED_SHORT CUSTOM_TRADER_ID ;

    /**
     * @typedef
     * @brief LISTING_DATE
     */
    typedef UNSIGNED_INTEGER LISTING_DATE;
    
  }

  namespace TYPE_DEFS
  {
    /**
     * @typedef
     * @brief STRATEGY_ID
     */
    typedef UNSIGNED_INTEGER STRATEGY_ID;

    /**
     * @typedef
     * @brief CLIENT_ID
     */
    typedef UNSIGNED_INTEGER CLIENT_ID;
    
    /**
     * @typedef
     * @brief ERROR_CODE
     */
    typedef UNSIGNED_INTEGER ERROR_CODE;

    /**
     * @typedef
     * @brief OrderType
     */
    typedef UNSIGNED_CHARACTER OrderType;

    /**
     * @typedef
     * @brief OrderValidity
     */
    typedef UNSIGNED_CHARACTER OrderValidity;

    /**
     * @typedef
     * @brief PlatformType
     */
    typedef UNSIGNED_CHARACTER PlatformType;

    /**
     * @typedef
     * @brief ProductType
     */
    typedef UNSIGNED_CHARACTER ProductType;

    /**
      * @typedef
      * @brief GTC_GTD_Date
      */
    typedef UNSIGNED_INTEGER GTD_Date;

    /**
     * @typedef
     * @brief ConfirmationType
     */
    typedef UNSIGNED_CHARACTER ConfirmationType;

    /**
     * @brief AlgoCategory
     */
    typedef UNSIGNED_CHARACTER  AlgoCategory;

    /**
     * @brief AssetType
     */
    typedef UNSIGNED_SHORT AssetType;

  }
}
#endif
