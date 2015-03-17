#ifndef API2_BENCHMARK_CONTEXT
#define API2_BENCHMARK_CONTEXT
#include <sgContext.h>
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <apiConstants.h>
#include <apiDataTypes.h>
#include <sharedSingleOrder.h>
#include <list>
#include <unordered_map>
#include "../common/orderWrapper.h"
#include <apiTime.h>

namespace API2
{
  namespace BENCHMARK
  {
    class SampleStrategy :public SGContext
     {

       API2::COMMON::OrderWrapper *_orderWrapper;
       API2::COMMON::Instrument *_instrument;
       API2::COMMON::LatencyNumbers _LNNewOrder, _LNReplaceOrder, _LNCancelOrder ;
       API2::COMMON::LatencyNumbers _LNNewOrderReject, _LNReplaceOrderReject, _LNCancelOrderReject ;
       API2::COMMON::LatencyNumbers _LNCreateOrder, _LNResetOrder;

       void sendNewOrder(API2::DATA_TYPES::PRICE price, API2::DATA_TYPES::QTY qty);
       void sendReplaceOrder(API2::DATA_TYPES::PRICE price=0, API2::DATA_TYPES::QTY qty=0);
       void sendCancelOrder();

     public:
       SampleStrategy(API2::StrategyParameters *params);
#ifndef BENCHMARK_MARKET_DATA
       void onMarketDataEvent(UNSIGNED_LONG symbolId);
#endif
#ifndef BENCHMARK_NEW_ORDERS
       void onConfirmed(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
       void onReplaced(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
       void onReplaceRejected(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
       void onCancelRejected(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
       void onPartialFill(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
       void onNewReject(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
       void onCanceled(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
       void onFilled(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
       void onFrozen(OrderConfirmation &confirmation, COMMON::OrderId *orderId);
#endif

       void onCMDModifyStrategy(AbstractUserParams *newParams){}


     };


     void BenchmarkingDriver(void *params);
  }
}

#endif //API2_BENCHMARK_CONTEXT
