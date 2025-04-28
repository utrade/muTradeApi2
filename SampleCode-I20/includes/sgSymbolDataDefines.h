#ifndef SG_SYMBOL_DATA_DEFINESH
#define SG_SYMBOL_DATA_DEFINESH
#include <string>
#include <boost/unordered_map.hpp>
#include <map>
#include <sharedDefines.h>
#include <apiDataTypes.h>
#include <apiConstants.h>
namespace API2  {

  typedef std::map< long, long > MultiTickMap ;

  /**
 * @brief The API_SymbolStaticData struct
 */
  struct SymbolStaticData
  {

    /**
     * @brief marketId
     */
    std::string marketId;//To be removed

    /**
     * @brief securityId
     */
    long        securityId;

    /**
     * @brief symbol
     */
    std::string symbol;

    /**
     * @brief baseCurrency
     */
    DATA_TYPES::CURRENCY_TYPE baseCurrency;

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
     * Mandatorily zero in case other than Option
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
     *
     * FOR SGX ITCH-OUCH SPREAD Contracts :
     *  We are storing information about whether to buy or sell the leg
     * while buying or selling the spread contracts in suspended field of
     * scrip master for first leg.
     * Possible values :
     *  B -> Same
     *  C -> Opposite.
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
     * @brief assetCode : asset Code from exchange
     * eg:- BSEFO = ACCL , AXIS  scrip_master = ACC , AXISBANK
     */
    std::string assetCode;

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
    long long lowerBandPrice;

    /**
     * @brief upperBandPrice
     */
    long long upperBandPrice;

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
     * @brief underlyingMarketCode
     */
    int underlyingMarketCode;

    /**
     * @brief instrumentModifier
     */
    int instrumentModifier;

    /**
     * @brief seriesIdentity
     */
    std::string seriesIdentity;

    /**
     * @brief instrumentGroup
     */
    int instrumentGroup;

    /**
     * @brief sourceId
     */
    std::string  sourceId; //To be removed later

    /**
     * @brief source
     */
    short source;
    
    /**
     * @brief exchangeId
     */
    short exchangeId;
    short underlyingExchangeId;
    
    /**
     * @brief scripMasterKey
     */
    std::string  scripMasterKey;
    
    /**
     * @brief underlyingSecId
     */
    //long        underlyingSecId;
    
    /**
     * @brief segment
     */
    char segment;

    std::string brokerSecurityId;

    std::string exchangeSecurityId;

    std::string brokerSymbol;
    
    std::string tradingSessionId; // Newfor MOEX FX

    double tradeValue;

    std::string tradeUnit;
    
    bool isCurrentFut;

    long currentMonthFutureSecId;

    long futureUnderLyingSecurityId;

    long indexSecurityId;

    /**
     * @brief partitionId
     */
    int partitionId;

    /**
     * @brief applyLot
     */
    int applyLot;
    
    /**
     * @brief spreadMaturityYearmon
     */
    unsigned int spreadMaturityYearmon;

    /**
     * @brief spreadMaturityDay
     */
    int spreadMaturityDay;

    /**
     * @brief price with respect to tick size is insertedin this map
     */
    MultiTickMap _mapMultiTickSize ;

    /**
     * @brief priceUnit
     */
    std::string priceUnit;

    /**
     * @brief quantityUnit
     */
    std::string quantityUnit;
    
    /**
     * @brief deliveryUnit
     */
    std::string deliveryUnit;

    /**
     * @brief index name for indices symbol
     */
    std::string indexName;

    /**
     * @brief scripGroup  - group containing symbols based on type of security(cash, future, option)
     *                      and type of derivative(stock, future, currency etc)
     *                      it's derived from security type and instrument type
     */
    API2::DATA_TYPES::ScripGroup scripGroup = API2::CONSTANTS::ScripGroup_MAX;

    /**
     * @brief upperStrikePriceStaticData - Pointer of the staticData of strikePrice adjacent to the staticData of current strike price.
     * Its strike price is greater than the strike price of current staticData
     * Null for other symbols other than options.
     */
    SymbolStaticData* upperStrikePriceStaticData;

    /**
     * @brief lowerStrikePriceStaticData - Pointer of the staticData of strikePrice adjacent to the staticData of current strike price.
     * Its strike price is lesser than the strike price of current staticData
     * Null for other symbols other than options.
     */
    SymbolStaticData* lowerStrikePriceStaticData;

    /**
     * @brief underlyingFutureStaticData - Pointer of the staticData of underlying Future
     * It is the Future of same month as that of option
     * Null for other symbols other than options.
     */
    SymbolStaticData* underlyingFutureStaticData;

    /**
     * @brief lastTradePrice - ltp of the symbol
     * Initial value is zero.
     */
    long lastTradePrice;
    
    /**
     * @brief asmGsmSurveillanceIndicator : Stages 0 - 6 for GSM & Stages 10 - 16 for Short Term Securities
     * and Long Term Securities of ASM
     */
    UNSIGNED_CHARACTER asmGsmSurveillanceIndicator;

    /**
     * @brief tradeForTrade
     */
    bool tradeForTrade;

    /**
     * @brief isNormalMarket - whether trading is allowed in normal market for this symbol
     */
    bool isNormalMarket;

    /**
     * @brief cashUniqueKey - made after multiple filters on exchange contract files to
     * identify cash contracts on NSE and BSE.
     */
    API2::DATA_TYPES::CASH_UNIQUE_KEY cashUniqueKey;

    /**
     * Fields contractStartDate , contractEndDate , tendorStartDate and
     * tendorEndDate added for MCX
     */

    /**
     * @brief contractStartDate - First trading date of the product
     */
    API2::DATA_TYPES::EPOCH_TIME  contractStartDate;
    
    /**
     * @brief - Last trading date of the product
     */
    API2::DATA_TYPES::EPOCH_TIME contractEndDate;
    
    /**
     * @brief - First Date from which delivery intention shall be accepted for
     * the product 
     */
    API2::DATA_TYPES::EPOCH_TIME tendorStartDate;
    
    /**
     * @brief - Last date upto which delivery intention shall be accepted for
     * the product
     */
    API2::DATA_TYPES::EPOCH_TIME tendorEndDate;

    /**
     * @brief marketType
     */
    API2::DATA_TYPES::MarketType marketType;

    /**
     * @brief symbolNameId
     */
    int32_t symbolNameId;

    /**
     * AssetType
     */
    API2::TYPE_DEFS::AssetType assetType;

    /**
     * wrappedExchange : This will be used in case of interopts, it will
     * be common among symbols present in multiple exchanges.
     * In other cases it will be same as exchange id field.
     */
    API2::DATA_TYPES::ExchangeId wrappedExchange;

    /**
     * uniqueId : This will be used in case of interopts, it will be symbol
     * id of the preferred exchange and will be common among symbols present
     * in multiple exchanges.
     * In other cases it will be same as symbol id field.
     */
    API2::DATA_TYPES::SYMBOL_ID uniqueId;

    /**
     * preferredExchangeStaticData : This will be used in case of interopts, it
     * will be static data ptr of the preferred exchange.
     * In other cases it will point to this pointer.
     */
    SymbolStaticData* preferredExchangeStaticData;

    /**
     * @brief companyName - stores company name of a scrip
     */
    std::string companyName;

    /**
     * @brief listingDate
     */
    API2::DATA_TYPES::LISTING_DATE listingDate;

    /**
     * @brief isListedToday : This will be used to check that listing date is equal to current date
     */
    bool isListedToday;

    /**
     * @brief streamId
     */
    API2::DATA_TYPES::STREAM_ID streamId;

    /**
     * @brief API_SymbolStaticData
     */
    SymbolStaticData();

    /**
     * @brief dump
     */
    void dump() const;
    
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
     * @param groupName -> returned symbolId will be acc. to the groupName
     * associated with it
     * @return symbol id
     */
    static SIGNED_LONG getUnderlyingSymbolId(API2::SymbolStaticData *staticData,
        const API2::DATA_TYPES::ExchangeId targetExchange,
        const std::string &groupName = "EQ");
     
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
    static SIGNED_LONG getATMOption(
        const std::string &symbolName,
        SIGNED_LONG lastTradePrice,
        const API2::DATA_TYPES::OptionMode optionMode,
        char upDown,
        int yearMon,
        const API2::DATA_TYPES::ExchangeId targetExchange);

    /**
     * @brief getOption returns ATM option symbolId for the given inputs
     * @param symbolName : symbolName for the option/future
     * @param lastTradePrice : last trade price for underlying
     * @param optionMode : CALL|PUT value for the option
     * @param upDown : Up/Down Price should be greater/lower than strikePrice | 0 -> Up and 1 -> Down
     * @param yearMon : yearMon eg 201502 represents expiry month of option
     * @param day : day 25 represents date of the expiry
     * @param targetExchange : Exchange Id for the option
     * @param Source : Source or broker id. default value is DEFAULT
     * @return symbol id
     */


    static SIGNED_LONG getOption(
        const std::string &symbolName,
        const SIGNED_LONG lastTradePrice,
        const API2::DATA_TYPES::OptionMode optionMode,
        const char upDown,
        const int yearMon,
        const int day,
        const API2::DATA_TYPES::ExchangeId targetExchange,
        const API2::DATA_TYPES::SourceId source = API2::CONSTANTS::CMD_SourceId_DEFAULT);


    /**
     * @brief getATMOption returns ATM option symbolId for the given inputs
     * @param symbolName : symbolName for the option/future
     * @param lastTradePrice : last trade price for underlying
     * @param optionMode : CALL|PUT value for the option
     * @param yearMon : yearMon eg 201502 represents expiry month of option
     * @param targetExchange : Exchange Id for the option
     * @return symbol id
     */
    static SIGNED_LONG getATMOption(
        const std::string &symbolName,
        SIGNED_LONG lastTradePrice,
        const API2::DATA_TYPES::OptionMode optionMode,
        int yearMon,
        const API2::DATA_TYPES::ExchangeId targetExchange);
    
    /**
     * @brief getSymbolFuture returns future according to given inpus
     * @param symbolName : symbolName for the option/future
     * @param yearMon : yearMon eg 201502 represents expiry month of future
     * @param yearMon2 : yearMon eg 201502 represents expiry month of far future(Spread Contract)
     * @param targetExchange : Exchange Id for the future
     * @return symbol id
     */
    static SIGNED_LONG getSymbolFuture(const std::string &symbolName,
        int yearMon,
        const API2::DATA_TYPES::ExchangeId targetExchange,
        int yearMon2 = 0);

    bool tickComparer( const MultiTickMap::value_type &a,
        const MultiTickMap::value_type &b) ;
    long getTickSizeForPrice( long price ) const;
    void insertTickSizeForPrice( long price, long tickSize ) ;

  };
    /**
     * @brief getExchangeId returns exchangeId according to given inpus
     * @param symbolId : symbolId for getting exchangeId
     * @return exchange id
     */
  short getExchangeId( const long& symbolId );
    /**
     * @brief getSymbolId returns symbolId according to given inpus
     * @param sourceId : sourceId of symbol
     * @param exchangeId : exchangeId of symbol
     * @param securityId : securityId of symbol
     * @return symbolId
     */
  int64_t getSymbolId( const short& sourceId, const short& exchangeId, const int64_t& securityId);
    /**
     * @brief getSourceId returns sourceId according to given inpus
     * @param symbolId : symbolId for getting sourceId
     * @return source id
     * */
  short getSourceId(const long& symbolId);
    /**
     * @brief getSourceId returns sourceId according to given inpus
     * @param source : source for the sourceId
     * @return source id
     * */
  long getSourceId(const std::string& source);
    /**
     * @brief getScripCode returns scripCode according to given inpus
     * @param symbolId : symbolId for the scripCode
     * @return scrip code
     * */
  int64_t getScripCode(const long& symbolId);

    /**
     * @brief getStaticData is for gettng scrip detail of a symbol
     * @param symbolId : symbolId for the scripCode
     * @param SymbolStaticData : static data object by reference
     * @return 0 on sucess and -1 when unsuccessful
     * */
  int getStaticData(SIGNED_LONG symbolId, API2::SymbolStaticData& sd);
    
    /**
     * @brief getStaticData is for gettng scrip detail of a symbol
     * @param symbolkay : symbolkey for the contract
     * @param SymbolStaticData : static data object by reference
     * @return 0 on sucess and -1 when unsuccessful
     * */
  int getStaticData(const std::string& symbolKey, API2::SymbolStaticData& sd);
  
  double getTickSizeForPrice( double price ) ;
  void insertTickSizeForPrice( double price, double tickSize ) ;
}
#endif
