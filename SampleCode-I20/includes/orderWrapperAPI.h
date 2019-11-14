#pragma once

#include <sgContext.h>
#include <sharedCommands.h>

namespace API2 {
  namespace COMMON {

    struct OrderWrapperAPI{

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

      /**
       * @brief _isPendingNew: This parameter set to true on new order request and set to false on confirm/new reject recieved.
       *                                    This parameter is also used to check the state of Multileg IOC order,
       *                                    In multileg IOC order, this parameter is true until cancel or filll is recieved.
       * @brief _isPendingReplace : This parameter set to true on replace request and set to false on replaced/replace rejected recieved
       * @brief _isPendingCancel :  This parameter set to true on cancel request and set to false on canceled/cance rejected is recieved
       * _isPendingNew, _isPendingReplace & _isPendingCancel are used seprately for every exchange request,
       * These can be replaced by single variable _isPending.
       */
      bool _isPendingNew;
      bool _isPendingReplace;
      bool _isPendingCancel;
      bool _isSpread;
      SIGNED_LONG _price;
      SIGNED_LONG _lastQuantity;
      SIGNED_LONG _lastQuotedPrice;
      SIGNED_LONG _lastFilledQuantity;
      API2::DATA_TYPES::SelfTradeOrderFlag _selfTradeOrderFlag;
      API2::DATA_TYPES::MarketSessionType _marketSessionType;
      const API2::ExchangeAdapterDetails* _exchangeAdapterDetails;

      OrderWrapperAPI(API2::COMMON::Instrument *instrument,
          const API2::DATA_TYPES::OrderMode &mode,
          SGContext *context,
          const API2::AccountDetail &account,
          const API2::DATA_TYPES::OrderType &type = API2::CONSTANTS::CMD_OrderType_LIMIT,
          const API2::DATA_TYPES::OrderValidity &validity = API2::CONSTANTS::CMD_OrderValidity_DAY,
          bool isSpread =false,
          const API2::DATA_TYPES::SelfTradeOrderFlag &selfTradeOrderFlag = API2::CONSTANTS::CMD_SelfTradeOrderFlag_CANCEL_PASSIVE,
          const API2::DATA_TYPES::MarketSessionType marketSessionType = API2::CONSTANTS::CMD_QUEUED_SESSION_NORMAL,
          const API2::ExchangeAdapterDetails* const exchangeAdapterDetails = nullptr)
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
          _selfTradeOrderFlag( selfTradeOrderFlag ),
          _marketSessionType(marketSessionType),
          _exchangeAdapterDetails(exchangeAdapterDetails)
      {
        reset();
      }
      void setPrimaryClientCode(const std::string &pcc)
      {
        _accountDetail.setPrimaryClientCode(pcc.c_str());
        _accountDetail.setAccountType(0);
      }
      OrderWrapperAPI()
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
          _selfTradeOrderFlag(API2::CONSTANTS::CMD_SelfTradeOrderFlag_CANCEL_PASSIVE),
          _marketSessionType(API2::CONSTANTS::CMD_QUEUED_SESSION_NORMAL),
          _exchangeAdapterDetails(nullptr)
      {}
      void reset();

      SIGNED_LONG getLastQuantity() { return _lastQuantity; }
      SIGNED_LONG getLastQuotedPrice() { return _lastQuotedPrice; }
      SIGNED_LONG getLastFilledQuantity() { return _lastFilledQuantity; }
      API2::DATA_TYPES::PRICE getLastPrice(){return _order->getPrice();}
      API2::DATA_TYPES::PRICE getLastQty(){return _order->getQuantity();}
      API2::DATA_TYPES::String getExchangeOrderId(){ return _exchangeOrderId;} 
      API2::DATA_TYPES::OrderMode getOrderMode() { return _order->getOrderMode(); }
      bool newOrder(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price, const API2::DATA_TYPES::QTY &qty, API2::DATA_TYPES::PRICE stopPrice = 0 );
      bool addOrderDetails(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price, const API2::DATA_TYPES::QTY &qty, API2::DATA_TYPES::PRICE stopPrice = 0 );
      bool placeNewOrder( API2::DATA_TYPES::RiskStatus &risk );

      /**
       * @brief replaceOrder:  To send a replace Order
       * @param risk
       * @param price
       * @param qty
       * @param stopPrice
       * @return  true if order is replaced sucessfully
       *         else false(Also it return false if order type is IOC because there is no sense to cancel/replace IOC order)
       * Note: If modification of IOC order is requested, then false is returned without any processing.
       *       As there is no meaning to modify IOC order.
       */
      bool replaceOrder(API2::DATA_TYPES::RiskStatus &risk, const API2::DATA_TYPES::PRICE &price=0, const API2::DATA_TYPES::QTY &qty=0, API2::DATA_TYPES::PRICE stopPrice = 0);

      /**
       * @brief cancelOrder to cancel order
       * @param risk
       * @return true if order is cancelled sucessfully
       *              else false (Also it return false if order type is IOC because there is no sense to cancel/replace IOC order)
       * Note: If cancellation of IOC order is requested, then false is returned without any processing.
       *       As there is no meaning to cancel IOC order.
       */
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
      bool isOrderOpen()
      {//return true if any order qty is still placed in xchng.
        return ( isOrderPending() || getLastQuantity() );
      }

      long getClOrderId();

      /**
       * @brief setMarketSessionType - Setter for marketSessionType
       * @param marketSessionType
       */
      void setMarketSessionType( API2::DATA_TYPES::MarketSessionType marketSessionType )
      {
        _marketSessionType = marketSessionType;
      }
    };

  }
}


