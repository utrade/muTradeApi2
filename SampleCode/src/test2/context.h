#ifndef MYAPI_CONTEXT_H
#define MYAPI_CONTEXT_H
#include <sgContext.h>
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <apiConstants.h>
#include <apiDataTypes.h>
#include <sharedSingleOrder.h>
#include <list>
#include <unordered_map>
#include "../common/orderWrapper.h"

#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

#define PUT_FACTOR -1
#define CALL_FACTOR 1

namespace API2
{
namespace Test2 {

enum EventType{

    UpSide =0,
    DownSide,
    NoEvent
};

/**
 * @brief The FrontEndParameters struct
 */
struct FrontEndParameters
{
    enum PriceType{
            BestBid =1,
            BestAsk,
            LTP
        };
    SIGNED_LONG _symbolId;
    char _side;
    char _priceType;
    SIGNED_LONG _qty;
    FrontEndParameters()
        :
          _symbolId(0),
          _priceType(LTP),
          _qty(0)
    {}
    void dump(std::stringstream &ss, const char *str= ""){
        ss <<
              str <<"==============================\nSymbol ID ====="
           <<_symbolId
          << "\n_priceType====="
          <<(char)_priceType
         << "\n qty====="
         <<_qty
        << "\n"
           "==============================\n"
           ;
    }
    std::string dump()
    {
        std::stringstream ss;
        dump(ss);
        return ss.str();

    }
};


class Context;

/**
 * @brief The Context class
 */
class Context: public API2::SGContext
{
    API2::COMMON::Instrument *_Instrument;
    FrontEndParameters _userParams;
    API2::COMMON::OrderWrapper _orderWrapper;

public:

    /**
     * @brief Context
     * @param params
     */
    Context(API2::StrategyParameters *params);

    /**
     * @brief onModifyStrategy
     */
    void onCMDModifyStrategy(API2::AbstractUserParams*);

    /**
     * @brief onDerivedMarketDataEvent
     * @param symbolId
     */
    void onMarketDataEvent(UNSIGNED_LONG symbolId);

    /**
     * @brief processOrderConfirmation
     * @param confirmation
     */
    void onProcessOrderConfirmation(OrderConfirmation &confirmation);


    void onConfirmed(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
    void onReplaced(OrderConfirmation &confirmation, COMMON::OrderId *orderId);

    void onFilled(OrderConfirmation &confirmation, COMMON::OrderId *orderId);

    bool setInternalParameters(API2::UserParams *params);

    bool setTestParameters();

    API2::DATA_TYPES::PRICE getPrice();


};
void TestDriver(void *params);
}
}
#endif
