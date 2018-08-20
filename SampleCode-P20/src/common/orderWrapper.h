#ifndef API2_COMMON_ORDER_WRAPPER
#define API2_COMMON_ORDER_WRAPPER

#include <sgContext.h>

/**
 * This file is provided to perform some common functions that are generally useful in algos.
 * User can change code as per their requirement and apply neccessary checks to minimize risk
 * and maximize performance of application.
 * These functions may not fullfill all the requirements. So, user should check the implementation and 
 * documentation before use.
 * 
 * Disclaimer: uTrade will not be responsible for any issue due to this code as implementation is also provided
 *
 */

namespace API2 {
  namespace CUSTOM_COMMON {

    class LegDetail :public SGContext::OrderLegData{
      public:
        SGContext *_context;
        API2::DATA_TYPES::OrderMode _mode;
        SIGNED_LONG _orderValidity;
        SIGNED_LONG _lastQuotedPrice;
        SIGNED_LONG _lastQuantity;
        SIGNED_LONG _lastFilledQuantity;
        SIGNED_LONG _orderType;
        SIGNED_LONG _productType;
        SIGNED_LONG _totalTradedQty;
        bool _isReset;
        API2::AccountDetail _account;

        LegDetail(
            SGContext *context,
            COMMON::Instrument *instrument,
            const DATA_TYPES::OrderMode &mode,
            const DATA_TYPES::OrderType &orderType,
            const DATA_TYPES::OrderValidity &validity,
            const DATA_TYPES::ProductType &productType,
            const API2::AccountDetail &account
            )
          :
            SGContext::OrderLegData(instrument),
            _context(context),
            _mode(mode),
            _orderValidity(validity),
            _lastQuotedPrice(0),
            _lastQuantity(0),
            _lastFilledQuantity(0),
            _orderType(orderType),
            _productType(productType),
            _totalTradedQty(0),
            _isReset(false),
            _account(account)
      {
        orderId = _context->createNewOrderId(instrument,_account,_mode);
        reset();
      }

        void reset();

        API2::DATA_TYPES::PRICE getOrderPrice(){return order->getPrice();}
        SIGNED_LONG getLastQuotedPrice(){ return _lastQuotedPrice;}
        SIGNED_LONG getLastQuantity(){ return _lastQuantity;}
        SIGNED_LONG getLastFilledQuantity(){ return _lastFilledQuantity;}
        API2::DATA_TYPES::PRICE getOrderQty(){return order->getQuantity();}
        void updateOrderWrapper(SIGNED_LONG qty,SIGNED_LONG price,SIGNED_LONG lastFilledQty);
        void resetOrderWrapper();
    };
    struct OrderWrapper{

      API2::DATA_TYPES::String _exchangeOrderId;
      SGContext *_context;
      bool _isReset;
      bool _isPendingNew;
      bool _isPendingReplace;
      bool _isPendingCancel;
      int _numLegs;
      bool _isSpread;
      DATA_TYPES::OrderPriority _orderPriority;
      COMMON::OrderId *_orderId;
      SingleOrder *_order;
      COMMON::Instrument *_instrument;
      std::vector<LegDetail> _orderLegData;

      OrderWrapper(API2::COMMON::Instrument *instrument,
          const API2::DATA_TYPES::OrderMode &mode,
          SGContext *context,
          const API2::AccountDetail &account,
          SIGNED_LONG orderValidity= CONSTANTS::CMD_OrderValidity_DAY,
          SIGNED_LONG productType = CONSTANTS::CMD_ProductType_INTRADAY,
          SIGNED_LONG orderType = CONSTANTS::CMD_OrderType_LIMIT,
          bool isSpread =false,
          DATA_TYPES::OrderPriority orderPriority = CONSTANTS::CMD_OrderPriority_MaxPriority
          )
        :
          _exchangeOrderId(""),
          _context(context),
          _isReset(true),
          _isPendingNew(false),
          _isPendingReplace(false),
          _isPendingCancel(false),
          _numLegs(1),
          _isSpread(isSpread),
          _orderPriority(orderPriority)
      {
        LegDetail leg(context,
            instrument,
            mode,
            orderType,
            orderValidity,
            productType,
            account
            );
        _order = leg.order;
        _orderId = leg.orderId;
        _instrument = leg.instrument;
        _orderLegData.push_back(leg);
      }


      OrderWrapper(
          SIGNED_LONG orderType,
          SGContext *context,
          API2::COMMON::Instrument *instrumentLeg1,
          const API2::DATA_TYPES::OrderMode &modeLeg1,
          API2::COMMON::Instrument *instrumentLeg2,
          const API2::DATA_TYPES::OrderMode &modeLeg2,
          const API2::AccountDetail &account,
          API2::COMMON::Instrument *instrumentLeg3=0,
          const API2::DATA_TYPES::OrderMode &modeLeg3 =CONSTANTS::CMD_OrderMode_MAX
          ):
        _exchangeOrderId(""),
        _context(context),
        _isReset(true),
        _isPendingNew(false),
        _isPendingReplace(false),
        _isPendingCancel(false),
        _numLegs(0),
        _isSpread(false),
        _orderPriority(CONSTANTS::CMD_OrderPriority_MaxPriority)
      {
        LegDetail leg1(context,
            instrumentLeg1,
            modeLeg1,
            orderType,
            CONSTANTS::CMD_OrderValidity_IOC,
            CONSTANTS::CMD_ProductType_INTRADAY,
            account
            );
        _orderLegData.push_back(
            leg1
            );
        _numLegs++;

        _order = leg1.order;
        _orderId = leg1.orderId;
        _instrument = leg1.instrument;

        _numLegs++;
        _orderLegData.push_back(
            LegDetail(context,
              instrumentLeg2,
              modeLeg2,
              orderType,
              CONSTANTS::CMD_OrderValidity_IOC,
              CONSTANTS::CMD_ProductType_INTRADAY,
              account
              ));
        if(instrumentLeg3){
          _numLegs++;
          _orderLegData.push_back(
              LegDetail(context,
                instrumentLeg3,
                modeLeg3,
                orderType,
                CONSTANTS::CMD_OrderValidity_IOC,
                CONSTANTS::CMD_ProductType_INTRADAY,
                account
                ));
        }
      }

      OrderWrapper()
        :
          _context(NULL),
          _isReset(false),
          _isPendingNew(false),
          _isPendingReplace(false),
          _isPendingCancel(false),
          _numLegs(1),
          _isSpread(false),
          _orderPriority(CONSTANTS::CMD_OrderPriority_MaxPriority)
      {
        reset();
      }


      void reset();

      LegDetail *getLegOrder(const DATA_TYPES::SYMBOL_ID &symbolId)
      {
        for( std::vector<LegDetail>::iterator iter = _orderLegData.begin(); iter!=_orderLegData.end();iter++)
        {
          LegDetail &leg= *iter;
          if(leg.order->getSymbolId() == symbolId)
            return &leg;
        }
        return 0;
      }
      COMMON::OrderId *getLeg1OrderId(){
        if(_orderLegData.size()>=1)
          return _orderLegData[0].orderId;
        return 0;
      }
      COMMON::OrderId *getLeg2OrderId(){
        if(_orderLegData.size()>=2)
          return _orderLegData[1].orderId;
        return 0;
      }
      COMMON::OrderId *getLeg3OrderId(){
        if(_orderLegData.size()>=3)
          return _orderLegData[2].orderId;
        return 0;
      }


      //    void createSingleOrder();
      API2::DATA_TYPES::PRICE getOrderPrice(){
        if(_orderLegData.size()>0)
          return _orderLegData[0].getOrderPrice();
        return 0;
      }
      SIGNED_LONG getLastQuotedPrice(){
        if(_orderLegData.size()>0)
          return _orderLegData[0].getLastQuotedPrice();
        return 0;
      }
      SIGNED_LONG getLastQuantity(){
        if(_orderLegData.size()>0)
          return _orderLegData[0].getLastQuantity();
        return 0;
      }
      SIGNED_LONG getLastFilledQuantity(){
        if(_orderLegData.size()>0)
          return _orderLegData[0].getLastFilledQuantity();
        return 0;
      }
      API2::DATA_TYPES::PRICE getOrderQty(){

        if(_orderLegData.size()>0)
          return _orderLegData[0].getOrderQty();
        return 0;
      }
      API2::DATA_TYPES::String getExchangeOrderId(){ return _exchangeOrderId;}

      void setOrderPriority(DATA_TYPES::OrderPriority orderPriority){ _orderPriority = orderPriority;}  

      bool newOrder(API2::DATA_TYPES::RiskStatus &risk,
          const API2::DATA_TYPES::PRICE &priceLeg1,
          const API2::DATA_TYPES::QTY &qtyLeg1,
          const API2::DATA_TYPES::PRICE &priceLeg2 =0,
          const API2::DATA_TYPES::QTY &qtyLeg2 =0,
          const API2::DATA_TYPES::PRICE &priceLeg3 =0,
          const API2::DATA_TYPES::QTY &qtyLeg3 =0
          );
      bool replaceOrder(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price=0, const API2::DATA_TYPES::QTY &qty=0);
      bool cancelOrder(API2::DATA_TYPES::RiskStatus &risk);
      bool processConfirmation(API2::OrderConfirmation &confirmation);
      inline bool isOrderReplacable()
      {
        if(_orderLegData.size()>1)
          return false;

        return !_isPendingNew && !_isPendingReplace && !_isPendingCancel;
      }
      inline bool isOrderPending()
      {
        return _isPendingNew || _isPendingReplace || _isPendingCancel;
      }
    };

  }
}


#endif //API2_COMMON_ORDER_WRAPPER
