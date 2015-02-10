#ifndef API2_COMMON_ORDER_WRAPPER
#define API2_COMMON_ORDER_WRAPPER

#include <sgContext.h>

namespace API2 {
  namespace COMMON {


  struct OrderWrapper{

    API2::COMMON::Instrument *_instrument;
    API2::DATA_TYPES::OrderMode _mode;
    API2::DATA_TYPES::OrderType _orderType;
    API2::SingleOrder *_order;
    API2::COMMON::OrderId *_orderId;
    SGContext *_context;
    bool _isReset;
    bool _isPendingNew;
    bool _isPendingReplace;
    bool _isPendingCancel;
    OrderWrapper(API2::COMMON::Instrument *instrument,const API2::DATA_TYPES::OrderMode &mode,const API2::DATA_TYPES::OrderType &type, SGContext *context)
      :
        _instrument(instrument),
        _mode(mode),
        _orderType(type),
        _order(NULL),
        _orderId(NULL),
        _context(context),
        _isReset(false),
        _isPendingNew(false),
        _isPendingReplace(false),
        _isPendingCancel(false)
    {
      reset();
    }
    OrderWrapper()
      :
        _instrument(NULL),
        _mode(API2::CONSTANTS::CMD_OrderMode_MAX),
        _order(NULL),
        _orderId(NULL),
        _context(NULL),
        _isReset(false)
    {}
    void reset();

    API2::DATA_TYPES::PRICE getLastPrice(){return _order->getPrice();}
    API2::DATA_TYPES::PRICE getLastQty(){return _order->getQuantity();}
    bool newOrder(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price, const API2::DATA_TYPES::QTY &qty);
    bool replaceOrder(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price=0, const API2::DATA_TYPES::QTY &qty=0);
    bool cancelOrder(API2::DATA_TYPES::RiskStatus &risk);
    bool processConfirmation(API2::OrderConfirmation &confirmation);
  };

  }
}


#endif //API2_COMMON_ORDER_WRAPPER
