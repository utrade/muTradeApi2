#ifndef SG_SYMBOL_DATA_DEFINESH
#define SG_SYMBOL_DATA_DEFINESH
#include <string>
#include <boost/unordered_map.hpp>
#include <map>
#include <sharedDefines.h>
#include <apiDataTypes.h>
#include <apiConstants.h>
namespace API2  {

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
    
    std::string tradingSessionId ; // Newfor MOEX FX

    long tradeValue;

    std::string tradeUnit;
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

    boost::unordered_map < long, std::map< double, double > > _mapMultiTickSize ;

    bool isCurrentFut;

    long currentMonthFutureSecId;

    long futureUnderLyingSecurityId;

    long indexSecurityId;

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
     * @brief scrip_group
     */
    std::string scrip_group;
    
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
     * @param yearMon2 : yearMon eg 201502 represents expiry month of far future(Spread Contract)
     * @param targetExchange : Exchange Id for the future
     * @return symbol id
     */
    static SIGNED_LONG getSymbolFuture(std::string symbolName,
        int yearMon,
        const API2::DATA_TYPES::ExchangeId targetExchange,
        int yearMon2 = 0);

    double getTickSizeForPrice( double price ) ;
    void insertTickSizeForPrice( double price, double tickSize ) ;

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
  int getStaticData(long symbolId, API2::SymbolStaticData& sd);
    
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
