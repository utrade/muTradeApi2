#pragma once

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

#include <sgContext.h>
namespace API2 {
  namespace COMMON {

    struct OrderWrapper{

      API2::COMMON::Instrument *_instrument;
      API2::DATA_TYPES::OrderMode _mode;
      API2::DATA_TYPES::OrderType _orderType;
      API2::DATA_TYPES::OrderValidity _orderValidity;
      API2::SingleOrder *_order;
      API2::SingleOrder *_replaceOrder;
      API2::COMMON::OrderId *_orderId;
      API2::DATA_TYPES::String _exchangeOrderId;
      SGContext *_context;
      AccountDetail _accountDetail;
      bool _isReset;
      bool _isPendingNew;
      bool _isPendingReplace;
      bool _isPendingCancel;
      bool _isSpread;
      SIGNED_LONG _price;
      SIGNED_LONG _lastQuantity;
      SIGNED_LONG _lastQuotedPrice;
      SIGNED_LONG _lastFilledQuantity;
      API2::DATA_TYPES::SelfTradeOrderFlag _selfTradeOrderFlag;
      OrderWrapper(API2::COMMON::Instrument *instrument,
          const API2::DATA_TYPES::OrderMode &mode,
          SGContext *context,
          const API2::AccountDetail &account,
          const API2::DATA_TYPES::OrderType &type = API2::CONSTANTS::CMD_OrderType_LIMIT,
          const API2::DATA_TYPES::OrderValidity &validity = API2::CONSTANTS::CMD_OrderValidity_DAY,
          bool isSpread =false,
          const API2::DATA_TYPES::SelfTradeOrderFlag &selfTradeOrderFlag = API2::CONSTANTS::CMD_SelfTradeOrderFlag_CANCEL_PASSIVE  
          )
        :
          _instrument(instrument),
          _mode(mode),
          _orderType(type),
          _orderValidity(validity),
          _order(NULL),
          _replaceOrder(NULL),
          _orderId(NULL),
          _exchangeOrderId(""),
          _context(context),
          _accountDetail(account),
          _isReset(false),
          _isPendingNew(false),
          _isPendingReplace(false),
          _isPendingCancel(false),
          _isSpread(isSpread),
          _selfTradeOrderFlag( selfTradeOrderFlag ),
          _price(0),
          _lastQuantity(0),
          _lastQuotedPrice(0),
          _lastFilledQuantity(0)
      {
        reset();
      }
      void setPrimaryClientCode(const std::string &pcc)
      {
        _accountDetail.setPrimaryClientCode(pcc.c_str());
        _accountDetail.setAccountType(0);
      }
      OrderWrapper()
        :
          _instrument(NULL),
          _mode(API2::CONSTANTS::CMD_OrderMode_MAX),
          _order(NULL),
          _orderId(NULL),
          _context(NULL),
          _isReset(false),
          _isSpread(false),
          _isPendingNew(false),
          _isPendingReplace(false),
          _isPendingCancel(false),
          _price(0),
          _lastQuantity(0),
          _lastQuotedPrice(0),
          _lastFilledQuantity(0),
          _selfTradeOrderFlag(API2::CONSTANTS::CMD_SelfTradeOrderFlag_CANCEL_PASSIVE)
      {}
      void reset();

      SIGNED_LONG getLastQuantity() { return _lastQuantity; }
      SIGNED_LONG getLastQuotedPrice() { return _lastQuotedPrice; }
      SIGNED_LONG getLastFilledQuantity() { return _lastFilledQuantity; }
      API2::DATA_TYPES::PRICE getLastPrice(){return _order->getPrice();}
      API2::DATA_TYPES::PRICE getLastQty(){return _order->getQuantity();}
      API2::DATA_TYPES::String getExchangeOrderId(){ return _exchangeOrderId;}


      bool newOrder(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price, const API2::DATA_TYPES::QTY &qty );

      bool replaceOrder(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price=0, const API2::DATA_TYPES::QTY &qty=0);

      bool cancelOrder(API2::DATA_TYPES::RiskStatus &risk);
      void updateOrderWrapper(SIGNED_LONG qty,SIGNED_LONG price,SIGNED_LONG lastFilledQty);
      void resetOrderWrapper();
      void setSelfTradeFlag( API2::DATA_TYPES::SelfTradeOrderFlag &selfTradeOrderFlag );
      bool processConfirmation(API2::OrderConfirmation &confirmation);
      bool isOrderReplaceable()
      {
        return !_isReset && (!_isPendingCancel && !_isPendingNew && !_isPendingReplace);
      }
      inline bool isOrderPending()
      {
        return _isPendingReplace || _isPendingNew || _isPendingCancel;
      }
    };

  }
}


