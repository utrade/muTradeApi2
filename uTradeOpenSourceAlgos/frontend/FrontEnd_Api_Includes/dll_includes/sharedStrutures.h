#ifndef SHAREDSTRUTURES_H
#define SHAREDSTRUTURES_H
#include "sharedEnums.h"
#if IS_QT4_VERSION
#include <QtGui>
#else
#include <QtWidgets>
#endif
#ifndef MUTRADE_CLIENT
#include "../../api2/api_includes/apiConstants.h"
#include "../../api2/api_includes/apiDataTypes.h"
#include "../../api2/api_includes/sharedResponse.h"
#define ResponseCategory_ORDER_CONFIRMATION 2
#else
#include "../../api2/headers/apiConstants.h"
#endif
#define STRATEGY_TYPE_MAX 16
typedef struct SymbolPanelElements
{
    QComboBox *orderMode;
    QComboBox *market;
    QComboBox *source;
    QComboBox *instrument;
    QVBoxLayout *symbolLayout;
    QComboBox *expiry;
    QComboBox *optionType;
    QComboBox *strikePrice;
    QLineEdit *lotSize;
    QComboBox *series;
    QRadioButton *radioButtonClient;
    QRadioButton *radioButtonPro;
    QComboBox *clientProCombo;
    QLineEdit *pcCode;
    QComboBox *accountDetailCombo;

    SymbolPanelElements(QComboBox *ordMode,
                        QComboBox *src,
                        QComboBox *mkt,
                        QComboBox *inst,
                        QVBoxLayout *symbol,
                        QComboBox *groupName,
                        QComboBox *exp,
                        QComboBox *optType,
                        QComboBox *stkPrice,
                        QLineEdit *lot,
                        QRadioButton *radioBtnClient,
                        QRadioButton *radioBtnPro,
                        QLineEdit *pcode,
                        QComboBox *actDetailCombo)
        :orderMode(ordMode),
          market(mkt),
          source(src),
          instrument(inst),
          symbolLayout(symbol),
          expiry(exp),
          optionType(optType),
          strikePrice(stkPrice),
          lotSize(lot),
          series(groupName),
          radioButtonClient(radioBtnClient),
          radioButtonPro(radioBtnPro),
          clientProCombo(NULL),
          pcCode(pcode),
          accountDetailCombo(actDetailCombo)
    {

    }

    SymbolPanelElements(QComboBox *ordMode,
                        QComboBox *src,
                        QComboBox *mkt,
                        QComboBox *inst,
                        QVBoxLayout *symbol,
                        QComboBox *groupName,
                        QComboBox *exp,
                        QComboBox *optType,
                        QComboBox *stkPrice,
                        QLineEdit *lot,
                        QComboBox *clientProComboBox,
                        QLineEdit *pcode,
                        QComboBox *actDetailCombo)
        :orderMode(ordMode),
          market(mkt),
          source(src),
          instrument(inst),
          symbolLayout(symbol),
          expiry(exp),
          optionType(optType),
          strikePrice(stkPrice),
          lotSize(lot),
          series(groupName),
          radioButtonClient(NULL),
          radioButtonPro(NULL),
          clientProCombo(clientProComboBox),
          pcCode(pcode),
          accountDetailCombo(actDetailCombo)
    {

    }

}SymbolPanelElements;



class BaseSymbolIds
{
public:
    BaseSymbolIds()
    {
        symbolId = 0 ;
        lotSize  = 1 ;
        orderMode = API2::DllCMD::OrderMode_MAX;
        quantity = 0;
        strategyType=STRATEGY_TYPE_MAX;
    }

    BaseSymbolIds(qlonglong tempSymbolId,
              short tempOrderMode,
              qlonglong tempQuantity,
              short tempStrategyType)
        :symbolId(tempSymbolId),
          orderMode(tempOrderMode),
          quantity(tempQuantity),
          strategyType(tempStrategyType)
    {
    }
    virtual ~BaseSymbolIds() {}
    int lotSize;
    qlonglong symbolId;
    qlonglong underlyingSymbolID;
    short orderMode;
    qlonglong quantity;
    short strategyType;
    bool contains(qlonglong symId)
    {
        return symId == symbolId ? true : false;
    }
};



struct ColumnIndex
{
    int adminTokenIdIndex;
    int strategyIdIndex;
    int strategyLegIndex;
    int stateIndex;
    int strategyCommentIndex;
    int portFolioIdIndex;
    int portFolioNameIndex;
    int sidQtyLeg1Index;
    int sidQtyLeg2Index;
    int sidQtyLeg3Index;
    int sidQtyLeg4Index;
    int orderMode;
    int symbolIdLeg1;
    int strategyType;
    int futurePrice;
    int dmDeltaPercentage;
    int remQtyLeg1;
    int spreadType;


    ColumnIndex():adminTokenIdIndex(-1),
        strategyIdIndex(-1),stateIndex(-1),
        strategyCommentIndex(-1),portFolioIdIndex(-1),
        portFolioNameIndex(-1),orderMode(-1),symbolIdLeg1(-1),
        futurePrice(-1),dmDeltaPercentage(-1),spreadType(-1),strategyLegIndex(-1)

    {

    }

};

//Spread upadation
struct SpreadDetails
{
    bool isUpdated;
    QString hitSpread;

    SpreadDetails()
        :isUpdated(true),
          hitSpread("")
    {

    }

    void updateSpread(SpreadDetails &detail)
    {
        if(hitSpread!=detail.hitSpread)
        {
            isUpdated = true;
            hitSpread==detail.hitSpread;
        }
    }

};

namespace API2
{
typedef struct SymbolDetail
{
    SymbolDetail():market(""), source(""), securityId(0), symbol("") , scripName(""),  groupName(""),
        instrType("C") , maturityDay(0), maturityYearMon(0),
        optType(""), optAttribute(""), strikePrice(0), symbolType(""),
        lotSize(1), tickSize(1), precision(2), multiplier(100), flag(false), symbolId(0),
        contractType(""), maturityDay2(0), maturityYearMon2(0), securityId1(0), securityId2(0), tradeValue(1.00),tradeUnit(""),upperCktLimit(0),lowerCktLimit(0),
        symbolBaseCurrency(""){}


    QString market;
    short exchangeId;
    QString source;
    short sourceId;
    qlonglong securityId;
    qlonglong symbolId;
    QString symbol;
    QString scripName;
    QString groupName;
    QString instrType;
    int maturityDay;
    int maturityYearMon;
    QString optType;
    QString optAttribute;
    qlonglong strikePrice;
    QString strikePriceStr;
    QString symbolType;
    int lotSize;
    int tickSize;
    int precision;
    double multiplier;
    bool flag;
    QString contractType;
    int maturityDay2;
    int maturityYearMon2;
    qlonglong securityId1;
    qlonglong securityId2;
    double tradeValue;
    QString tradeUnit;
    QString expiryStr;
    QString ISIN;
    QString symbolBaseCurrency;
    QString scripGroup;
    qlonglong lowerCktLimit;
    qlonglong upperCktLimit;

    bool operator<(const SymbolDetail & r) const
    {
        if(securityId < r.securityId)
            return true;
        else if(securityId > r.securityId)
            return false;
        else
        {
            return market < r.market;
        }
    }

    bool operator==(const SymbolDetail & r) const
    {
        return (securityId == r.securityId && market == r.market);
    }

}SymbolDetail;

typedef struct TradeWiseTrackerData
{
    TradeWiseTrackerData():orderSeqNumber(0), strategyId(0), twoLeg3LegStrategyType(-1),
        convRevStrategyType(-1), symbolId(0),maxPrecision(-1),  lotSize(1), orderQty(1), minSpread(0), time(0),
        minQty(1), isSquareOff(false), strikePrice(0),strikeDiff(0),execSpread(0),isSpreadInBps(false),
        dividend(0.00),orderModeBps(API2::DllCMD::OrderMode_MAX),strategyName(""),
        isSpreadAlreadyCalculated(false),
        tradingCost(0),
        execSprdExcludingCost(0)
    {
        portFolio.clear();
        orderModeList.clear();
        avgPriceList.clear();
        OrderQtyRatio.clear();
    }

    QString portFolio;
    QString strategyName;
    qlonglong orderSeqNumber;
    qlonglong strategyId;
    short twoLeg3LegStrategyType;
    short convRevStrategyType;
    qlonglong symbolId;
    QList<API2::DllCMD::OrderMode> orderModeList;
    int lotSize;
    int orderQty;
    qlonglong minSpread;
    QList<double> avgPriceList;
    qlonglong time;
    int minQty;
    QString OrderQtyRatio;
    bool isSquareOff;
    qlonglong strikePrice;
    qlonglong strikeDiff;
    qlonglong execSpread;
    qlonglong tradingCost;
    qlonglong execSprdExcludingCost;
    bool isSpreadInBps;
    double dividend;
    API2::DllCMD::OrderMode orderModeBps;
    short maxPrecision;
    bool isSpreadAlreadyCalculated;
    QString description;
}TradeWiseTrackerData;

struct apiOrderBookParams
{
   apiOrderBookParams(): cancelOrModify(0),orderPrice(0),orderId("") {}
   char cancelOrModify;
   qlonglong orderQty;
   qlonglong orderPrice;
   std::string orderId;
};
}

#ifndef MUTRADE_CLIENT
namespace RSP
{
class OrderConfirmation : public API2::OrderConfirmation
{
  public:
    OrderConfirmation(OrderConfirmation *other);

    OrderConfirmation();
    OrderConfirmation(const char* buf);
    OrderConfirmation(
        API2::DATA_TYPES::CLORDER_ID &clientOrderId,
        API2::DATA_TYPES::SYMBOL_ID &symbolId,
        API2::DATA_TYPES::STRATEGY_ID &strategyId,
        API2::DATA_TYPES::CLIENT_ID &clientId,
        API2::DATA_TYPES::OrderStatus &orderStatus,
        API2::DATA_TYPES::OrderMode &orderMode,
        API2::DATA_TYPES::OrderType &orderType,
        API2::DATA_TYPES::QTY &orderQty,
        API2::DATA_TYPES::PRICE &orderPrice,
        API2::DATA_TYPES::CLORDER_ID &origClOrdId,
        const API2::DATA_TYPES::PRICE &stopPrice,
        const API2::DATA_TYPES::ProductType &productType,
        const API2::DATA_TYPES::PlatformType &platformType,
        const API2::ExchangeAdapterDetails &exchangeAdapterDetails);
    void initialize();

    UNSIGNED_LONG getConfirmationTimeSeconds() const { return _confirmationTimeSeconds; }
    UNSIGNED_LONG getConfirmationTimeMicroSeconds() const { return _confirmationTimeMicroSeconds; }
    UNSIGNED_CHARACTER getIsOffline() const {return _isOffline;}
    UNSIGNED_LONG getSequenceNumber() const {return _sequenceNumber;}
    const char* getTradeId() const {return getTradeIdCharPtr();}
    const char* getExchangeOrderId() const {return getExchangeOrderIdCharPtr();}
    UNSIGNED_INTEGER getReasonText() const {return _reasonText;}
    UNSIGNED_CHARACTER getUnknownOrder() const{return _unknownOrder;}

    void setConfirmationTimeSeconds(UNSIGNED_LONG seconds) ;
    void setConfirmationTimeMicroSeconds(UNSIGNED_LONG microSeconds) ;
    void setIsOffline(UNSIGNED_CHARACTER isOffline);
    void setSequenceNumber(UNSIGNED_LONG sequenceNumber);
    void setReasonText(UNSIGNED_INTEGER reasonText);
    void setUnknownOrder(UNSIGNED_CHARACTER unknownOrder);
    void dumpCSV(std::ofstream &csvFile);
    void dump() const;
    std::string getString() const;
    bool isVersionValid(){return true;}
#ifndef FRONTEND_COMPILATION
    void dumpCSVTrades(std::ofstream &csvFile,
        SG::SymbolStaticData &symbolData,
        bool notFound,
        int custFirm,
        const std::string& accountId,
        const std::string& settler,
        const std::string& branchId,
        const std::string& userId
        );

    void dumpCSVDetailed(std::ofstream &csvFile,
        SG::SymbolStaticData &symbolData,
        bool notFound,
        int custFirm,
        const std::string& accountId,
        const std::string& settler,
        const std::string& branchId,
        const std::string& userId
        );
#endif

    std::string convertEpochToString(time_t rawtime);
    std::string convertEpochToDate(time_t rawtime);
    std::string convertEpochToTime(time_t rawtime);
    int serialize(char* buf, short rc = ResponseCategory_ORDER_CONFIRMATION );
    std::string getMonthFromNumber(int number);

  private:
    void serializeAll(char* buf, int &bytes);
    void serializeConfirmAndReplace(char* buf, int &bytes);
    void serializeTrade(char* buf, int &bytes);
    void serializeTradeModify(char* buf, int &bytes);
    void serializeCancelAndCancelOfIoc(char* buf, int &bytes);
    void serializeRejected(char* buf, int &bytes);
    void serializeMktToLimitAndTriggered(char* buf, int &bytes);
    void serializeRelay(char* buf, int &bytes);

    void deSerializeAll(const char* buf, int &offset);
    void deSerializeConfirmAndReplace(const char* buf, int &offset);
    void deSerializeTrade(const char* buf, int &offset);
    void deSerializeTradeModify(const char* buf, int &offset);
    void deSerializeCancelAndCancelOfIoc(const char* buf, int &offset);
    void deSerializeRejected(const char* buf, int &offset);
    void deSerializeMktToLimitAndTriggered(const char* buf, int &offset);
    void deSerializeRelay(const char* buf, int &offset);


    UNSIGNED_LONG _confirmationTimeSeconds;
    UNSIGNED_LONG _confirmationTimeMicroSeconds;
    UNSIGNED_CHARACTER _isOffline;
    UNSIGNED_LONG _sequenceNumber;
    UNSIGNED_INTEGER _reasonText;
    UNSIGNED_CHARACTER _unknownOrder;

    CREATE_FIELD(UNSIGNED_CHARACTER,GiveupFlag);

#ifdef FRONTEND_COMPILATION
    CREATE_FIELD(UNSIGNED_LONG,TotalFillQuantity);
    //CREATE_FIELD(UNSIGNED_CHARACTER,OrderType);
#endif

#ifndef FRONTEND_COMPILATION
    CREATE_FIELD(SIGNED_LONG, Price1);
    CREATE_FIELD(SIGNED_LONG, Price2);
#endif

#ifdef FRONTEND_COMPILATION
#ifdef ENABLE_DMS
    public:
      OrderConfirmation(const UT::PROTO::Order& protoOrder) ;
#endif
#endif

};
}
#endif
#endif // SHAREDSTRUTURES_H
