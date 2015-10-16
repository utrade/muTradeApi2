#ifndef SG_SYMBOL_DATA_DEFINESH
#define SG_SYMBOL_DATA_DEFINESH
#include <string>
#include <sharedDefines.h>
#include <apiDataTypes.h>
namespace API2  {

  /**
   * @brief The API_SymbolStaticData struct
   */
  struct SymbolStaticData
  {

    /**
     * @brief marketId
     */
    std::string marketId;//new

    /**
     * @brief securityId
     */
    long        securityId;

    /**
     * @brief symbol
     */
    std::string symbol;

    /**
     * @brief instrumentName
     */
    std::string instrumentName;
    /**
     * @brief securityType
     */
    char securityType;

    /**
     * @brief scripName
     */
    std::string scripName;

    /**
     * @brief groupName
     */
    std::string groupName;

    /**
     * @brief maturityYearmon
     */
    unsigned int         maturityYearmon;//new

    /**
     * @brief maturityDay
     */
    int         maturityDay;//new

    /**
     * @brief optionMode
     */
    char optionMode;

    /**
     * @brief optionAttribute
     */
    char optionAttribute;

    /**
     * @brief timeElapsedBse
     */
    long        timeElapsedBse;//un

    /**
     * @brief timeElapsedNse
     */
    long        timeElapsedNse;//un

    /**
     * @brief instrumentType
     */
    char instrumentType;

    /**
     * @brief strikePrice
     */
    long        strikePrice;

    /**
     * @brief noDelivery
     */
    char        noDelivery;

    /**
     * @brief marketLot
     */
    int         marketLot;

    /**
     * @brief tickSize
     */
    int         tickSize;

    /**
     * @brief suspended
     */
    char        suspended;

    /**
     * @brief avmFlag
     */
    char        avmFlag;

    /**
     * @brief avmBuyMargin
     */
    long        avmBuyMargin;

    /**
     * @brief avmSellMargin
     */
    long        avmSellMargin;

    /**
     * @brief spanMargin
     */
    long        spanMargin;

    /**
     * @brief exposureMargin
     */
    long        exposureMargin;

    /**
     * @brief settlementType
     */
    char        settlementType;

    /**
     * @brief isinNumber
     */
    std::string isinNumber;

    /**
     * @brief haircut
     */
    long        haircut;

    /**
     * @brief bcastFlag
     */
    long        bcastFlag;

    /**
     * @brief mktPicBcastFlag
     */
    std::string mktPicBcastFlag;

    /**
     * @brief productCode
     */
    std::string productCode;

    /**
     * @brief underlyingId
     */
    long        underlyingId;   // SymbolId

    /**
     * @brief is_auction_eligible
     */
    int         is_auction_eligible;//new

    /**
     * @brief hi_52_wk
     */
    int         hi_52_wk;//new

    /**
     * @brief lo_52_wk
     */
    int         lo_52_wk;//new

    /**
     * @brief lowerBandPrice
     */
    long        lowerBandPrice;

    /**
     * @brief upperBandPrice
     */
    long        upperBandPrice;

    /**
     * @brief freezeQuantity
     */
    long        freezeQuantity;

    /**
     * @brief closePrice
     */
    long        closePrice;

    /**
     * @brief symbolId
     */
    long        symbolId;

    /**
     * @brief scripPrecision
     */
    int         scripPrecision;

    /**
     * @brief symbolAlias
     */
    std::string symbolAlias;

    /**
     * @brief contractType
     */
    char contractType;

    /**
     * @brief maturityYearmon2
     */
    unsigned int maturityYearmon2;

    /**
     * @brief maturityDay2
     */
    int maturityDay2;

    /**
     * @brief securityId1
     */
    long long  securityId1;

    /**
     * @brief securityId2
     */
    long long securityId2;

    long        lowTradeExecutionRange;
    long        highTradeExecutionRange;

    /**
     * @brief timeElapsedNseSymbol2
     */
    long timeElapsedNseSymbol2;


    /**
     * @brief API_SymbolStaticData
     */
    SymbolStaticData();

    /**
     * @brief dump
     */
    void dump();

    /**
     * @brief getUnderlyingSymbolId function returns future symbol id for index Options
     * returns stock symbol id for stock options
     * @param staticData -> symbol static data of option
     * @return symbol id
     */
    static SIGNED_LONG getUnderlyingSymbolId(API2::SymbolStaticData *staticData);

    /**
     * @brief getUnderlyingSymbolId function returns future symbol id for index Options
     * returns stock symbol id for stock options 
     * @param staticData -> symbol static data of option
     * @param targetExchange -> returned symbol id will according to target exchange
     * @return symbol id
     */
    static SIGNED_LONG getUnderlyingSymbolId(API2::SymbolStaticData *staticData,
        const API2::DATA_TYPES::ExchangeId targetExchange);

    /**
     * @brief getATMOption returns ATM option symbolId for the given inputs
     * @param symbolName : symbolName for the option/future
     * @param lastTradePrice : last trade price for underlying
     * @param optionMode : CALL|PUT value for the option
     * @param upDown : Up/Down Price should be greater/lower than strikePrice | 0 -> Up and 1 -> Down
     * @param yearMon : yearMon eg 201502 represents expiry month of option
     * @param targetExchange : Exchange Id for the option
     * @return symbol id
     */
    static SIGNED_LONG getATMOption(std::string symbolName,
        SIGNED_LONG lastTradePrice,
        const API2::DATA_TYPES::OptionMode optionMode,
        char upDown,
        int yearMon,
        const API2::DATA_TYPES::ExchangeId targetExchange);


    /**
     * @brief getATMOption returns ATM option symbolId for the given inputs
     * @param symbolName : symbolName for the option/future
     * @param lastTradePrice : last trade price for underlying
     * @param optionMode : CALL|PUT value for the option
     * @param yearMon : yearMon eg 201502 represents expiry month of option
     * @param targetExchange : Exchange Id for the option
     * @return symbol id
     */
    static SIGNED_LONG getATMOption(std::string symbolName,
        SIGNED_LONG lastTradePrice,
        const API2::DATA_TYPES::OptionMode optionMode,
        int yearMon,
        const API2::DATA_TYPES::ExchangeId targetExchange);

    /**
     * @brief getSymbolFuture returns future according to given inpus
     * @param symbolName : symbolName for the option/future
     * @param yearMon : yearMon eg 201502 represents expiry month of future
     * @param targetExchange : Exchange Id for the future
     * @return symbol id
     */
    static SIGNED_LONG getSymbolFuture(std::string symbolName,
        int yearMon,
        const API2::DATA_TYPES::ExchangeId targetExchange);


  };
}
#endif
