#pragma once

/**
 * @brief This class is provided to perform some common functions that are generally useful in 
 * algos. It helps to manage state of an order.
 * api algo writer need to take care initialization steps and pass on
 * exchange confirmation/responses to this class's method.
 * User can modify/enhance/optimise this class as per their requirement and 
 * apply neccessary checks to minimize risk and maximize performance of application.
 * These functions may not fullfill all the requirements. So, user should check the implementation and 
 * documentation before use.
 
 * Algo can also be written without this but we are providing this clss alongwith 
 * implementation detail to save order state management task so that user will be
 * able to focus on algo logic
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
          _price(0),
          _lastQuantity(0),
          _lastQuotedPrice(0),
          _lastFilledQuantity(0),
          _selfTradeOrderFlag( selfTradeOrderFlag )
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
          _isReset(false),
          _isPendingNew(false),
          _isPendingReplace(false),
          _isPendingCancel(false),
          _isSpread(false),
          _price(0),
          _lastQuantity(0),
          _lastQuotedPrice(0),
          _lastFilledQuantity(0),
          _selfTradeOrderFlag(API2::CONSTANTS::CMD_SelfTradeOrderFlag_CANCEL_PASSIVE)
      {}

      /**
       * @brief reset, reset state of existing order. This should be called before sending every new order
       * @return
       */
      void reset();

      /**
       * @brief setPrimaryClientCode, To set account detail of an order
       * @return
       */
      void setPrimaryClientCode(const std::string &pcc)
      {
        _accountDetail.setPrimaryClientCode(pcc.c_str());
        _accountDetail.setAccountType(0);
      }

      /**
       * @brief getLastQuantity, To get order quantity of last placed order
       * @return
       */
      SIGNED_LONG getLastQuantity() { return _lastQuantity; }
      
      /**
       * @brief getLastQuotedPrice, To get order price of last placed order
       * @return
       */
      SIGNED_LONG getLastQuotedPrice() { return _lastQuotedPrice; }
      
      /**
       * @brief getLastFilledQuantity, To get traded quantity of last trade (filled or partial filled)
       * @return
       */
      SIGNED_LONG getLastFilledQuantity() { return _lastFilledQuantity; }

      API2::DATA_TYPES::PRICE getLastPrice(){return _order->getPrice();}

      API2::DATA_TYPES::PRICE getLastQty(){return _order->getQuantity();}
      
      /**
       * @brief getExchangeOrderId, To get Exchange order Id of placed order
       * @return
       */
      API2::DATA_TYPES::String getExchangeOrderId(){ return _exchangeOrderId;}

      /**
       * @brief getOrderMode : To get order mode of order placed.
       * @return
       */
      API2::DATA_TYPES::OrderMode getOrderMode() { return _order->getOrderMode(); }

      /**
       * @brief newOrder, To place new order in the market
       * @param risk, rms error code if fail due to rms failure
       * @param price, price of an order being placed
       * @param qty, quantity of an order being placed
       * @param stopPrice : To set stop price for stop limit order's.
       * @return true if success otherwise false
       */
      bool newOrder(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price, 
          const API2::DATA_TYPES::QTY &qty ,API2::DATA_TYPES::PRICE stopPrice = 0);

      /**
       * @brief replaceOrder, To replace/modify existing order
       * @param risk, rms error code if fail due to rms failure
       * @param price, price of an order being placed
       * @param qty, quantity of an order being placed
       * @param stopPrice : To set stop price for stop limit order's.
       * @return true if success otherwise false
       */
      bool replaceOrder(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price=0, 
          const API2::DATA_TYPES::QTY &qty=0,API2::DATA_TYPES::PRICE stopPrice = 0);

      /**
       * @brief cancelOrder, To cancel existing order
       * @param risk, rms error code if fail (exchange disconnected or order already filled)
       * @return true if success otherwise false
       */
      bool cancelOrder(API2::DATA_TYPES::RiskStatus &risk);

      /**
       * @brief updateOrderWrapper
       * @param qty
       * @param price
       * @param lastFilledQty
       */
      void updateOrderWrapper(SIGNED_LONG qty,SIGNED_LONG price,SIGNED_LONG lastFilledQty);

      /**
       * @brief addOrderDetails
       * @param risk
       * @param price
       * @param qty
       * @param stopPrice
       * @return
       */
      bool addOrderDetails(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price,
          const API2::DATA_TYPES::QTY &qty, API2::DATA_TYPES::PRICE stopPrice = 0);

      /**
       * @brief placeNewOrder
       * @param risk
       * @return
       */
      bool placeNewOrder( API2::DATA_TYPES::RiskStatus &risk );

      /**
       * @brief resetOrderWrapper
       */
      void resetOrderWrapper();
      
      /**
       * @brief setSelfTradeFlag, To configure active/passive order cancel in case of self trade
       * @return
       */
      void setSelfTradeFlag( API2::DATA_TYPES::SelfTradeOrderFlag &selfTradeOrderFlag );
      
      /**
       * @brief processConfirmation, User need to pass all confirmations to this methods to effectively maintain state of an order
       * @return true in case of success, false if wrong confirmation passed or neccessary detail is missing
       */
      bool processConfirmation(API2::OrderConfirmation &confirmation);

      /**
       * @brief isOrderReplaceable, flag to check if order can be replaced or not. No need to check everytime. 
       * replaceOrder is taking care of it.
       * @return
       */
      bool isOrderReplaceable()
      {
        return !_isReset && (!_isPendingCancel && !_isPendingNew && !_isPendingReplace);
      }
      
      /**
       * @brief isOrderPending, flag to check if response for the request (new/modify/cancel) has come or not
       * @return
       */
      inline bool isOrderPending()
      {
        return _isPendingReplace || _isPendingNew || _isPendingCancel;
      }

      /**
       * @brief isOrderOpen
       * @return true if any order qty is still placed in xchng.
       */
      bool isOrderOpen()
      {
        return ( isOrderPending() || getLastQuantity() );
      }

      /**
       * @brief getClOrderId
       * @return
       */
      long getClOrderId();
    };

  }
}


