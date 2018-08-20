#include "orderWrapper.h"

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
  namespace COMMON {

    void OrderWrapper::updateOrderWrapper(SIGNED_LONG qty,SIGNED_LONG price,SIGNED_LONG lastFilledQty)
    {
      _lastQuotedPrice = price;
      _lastQuantity = qty;
      _lastFilledQuantity += lastFilledQty;
    }

    void OrderWrapper::resetOrderWrapper()
    {
      _lastQuotedPrice = 0;
      _lastQuantity = 0;
      _lastFilledQuantity = 0;
    }

    void OrderWrapper::reset()
    {
      //      DEBUG_VARSHOW(_context->reqQryDebugLog(),"PCC: Order Wrapper ", _accountDetail.getPrimaryClientCode());
      _order = _context->createNewOrder(_instrument,0,0,_mode,_orderType,_orderValidity);
      _orderId = _context->createNewOrderId(_instrument,_accountDetail,_mode);
      _order->setAccountDetails(_accountDetail);
      _isReset = true;
    }

    bool OrderWrapper::newOrder(DATA_TYPES::RiskStatus &risk, const DATA_TYPES::PRICE &price, 
        const DATA_TYPES::QTY &qty, DATA_TYPES::PRICE stopPrice)
    {
      _isReset = false;
      if(qty==0)
      {
        risk = API2::CONSTANTS::RSP_RiskStatus_WRONG_QUANTITY;
        return false;
      }
      if(_order)
      {
        _order->setPrice(price);
        _order->setStopPrice(stopPrice);
        _order->setQuantity(qty);
        _order->setSelfTradeCancelFlag( _selfTradeOrderFlag );

        if( _orderType == API2::CONSTANTS::CMD_OrderType_STOP)
        {
          _order->setPrice(0);
          _order->setStopPrice( price );
        }

        //        DEBUG_MESSAGE(_context->reqQryDebugLog(), _context->getStrOrderId(_orderId).c_str());
        if(_context->reqNewSingleOrder(risk,_instrument,_order,_orderId,_isSpread))
        {
          _isPendingNew = true;
          return true;
        }
      }
      else
      {
        DEBUG_MESSAGE(_context->reqQryDebugLog(), "Order Wrapper Not Set. Terminating strategy");
        _context->reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
        _context->reqTerminateStrategy();
        return false;
      }
      return false;

    }

    bool OrderWrapper::addOrderDetails(DATA_TYPES::RiskStatus &risk, const DATA_TYPES::PRICE &price, 
        const DATA_TYPES::QTY &qty, DATA_TYPES::PRICE stopPrice)
    {
      reset();
      _isReset = false;
      if(qty==0)
      {
        risk = API2::CONSTANTS::RSP_RiskStatus_WRONG_QUANTITY;
        return false;
      }
      if(_order)
      {
        _order->setPrice(price);
        _order->setStopPrice(stopPrice);
        _order->setQuantity(qty);
        _order->setSelfTradeCancelFlag( _selfTradeOrderFlag );
      }
      else
      {
        DEBUG_MESSAGE(_context->reqQryDebugLog(), "Order Wrapper Not Set. Terminating strategy");
        _context->reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
        _context->reqTerminateStrategy();
        return false;
      }
      return true;
    }

    bool OrderWrapper::placeNewOrder( DATA_TYPES::RiskStatus &risk )
    {
      //addOrderDetails should be used to add price and quantity before call to this func.

      if(_context->reqNewSingleOrder(risk,_instrument,_order,_orderId,_isSpread))
      {
        _isPendingNew = true;
        return true;
      }
      return false;
    }

    bool OrderWrapper::replaceOrder(DATA_TYPES::RiskStatus &risk, const DATA_TYPES::PRICE &price, 
        const DATA_TYPES::QTY &qty, DATA_TYPES::PRICE stopPrice)
    {
      if(!_orderId){
        DEBUG_MESSAGE(_context->reqQryDebugLog(), "OrderWrapper replace fail OrderId null");
        return false;
      }
      _isReset = false;
      API2::SingleOrder *order = _context->createNewOrder(_instrument,0,0,_mode,_orderType,_orderValidity);
      if(order)
      {
        API2::SingleOrder *origOrder = _context->reqQryOrder(_context->reqQryClientOrderId(_orderId));
        if(origOrder)
        {
          order->setPrice(price);

          if(qty !=0)
            order->setQuantity(qty);
          else
            order->setQuantity(origOrder->getQuantity());

          order->setSelfTradeCancelFlag( _selfTradeOrderFlag );

          if(_context->reqQryOrderStatus(_orderId) != API2::CONSTANTS::RSP_OrderStatus_PENDING){

            _replaceOrder = order;
            if(_context->reqReplaceOrder(risk,_instrument,order,_orderId,_isSpread))
            {
              _isPendingReplace = true;
              return true;
            }
            else
            {

              DEBUG_MESSAGE(_context->reqQryDebugLog(), "_context->reqReplaceOrder fail");
              DEBUG_VARSHOW(_context->reqQryDebugLog(), "Replace Order Rejected. Reason:", risk);
              return false;
            }
          }
          else{
            DEBUG_MESSAGE(_context->reqQryDebugLog(),"Current state of Original Order is Pending");
            return false;
          }
        }
        DEBUG_MESSAGE(_context->reqQryDebugLog(),"Original Order NULL");
        return false;
      }
      else
      {
        DEBUG_MESSAGE(_context->reqQryDebugLog(), "Order Wrapper Not Set. Terminating strategy");
        _context->reqAddStrategyComment(API2::CONSTANTS::RSP_StrategyComment_STRATEGY_ERROR_STATE);
        _context->reqTerminateStrategy();
        return false;
      }
      return false;

    }

    bool OrderWrapper::cancelOrder(DATA_TYPES::RiskStatus &risk)
    {
      _isReset = false;  

      if( _context->reqCancelOrder(risk,_orderId) )
      {
        _isPendingCancel = true;
        return true;
      }
      return false;
    }

    bool OrderWrapper::processConfirmation(OrderConfirmation &confirmation)
    {
      switch(confirmation.getOrderStatus())
      {
        case API2::CONSTANTS::RSP_OrderStatus_CONFIRMED:
          updateOrderWrapper(confirmation.getOrderQuantity(),confirmation.getOrderPrice(),0);
          _isPendingNew = false;
          break;
        case API2::CONSTANTS::RSP_OrderStatus_NEW_REJECTED:
          _isPendingNew = false;
          return true;

        case API2::CONSTANTS::RSP_OrderStatus_REPLACED:
          {
            _order = _replaceOrder;
            updateOrderWrapper(confirmation.getOrderQuantity(),confirmation.getOrderPrice(),0);
          }
        case API2::CONSTANTS::RSP_OrderStatus_REPLACE_REJECTED:
          _isPendingReplace = false;break;

        case API2::CONSTANTS::RSP_OrderStatus_CANCELED:
        case API2::CONSTANTS::RSP_OrderStatus_CANCELED_OF_IOC:
          resetOrderWrapper();
        case API2::CONSTANTS::RSP_OrderStatus_CANCEL_REJECTED:
          _isPendingCancel = false;break;

        case API2::CONSTANTS::RSP_OrderStatus_FILLED:
          if(confirmation.getLastFillQuantity() + getLastFilledQuantity() != _lastQuantity)//PartiallyFILLed
          {
            updateOrderWrapper(getLastQuantity(),_lastQuotedPrice,confirmation.getLastFillQuantity());
            break;
          }
          resetOrderWrapper();
          break;

        case API2::CONSTANTS::RSP_OrderStatus_RMS_REJECT:
          _isPendingNew = false;
          _isPendingReplace = false;
          break;

      }

      if(confirmation.getOrderStatus() == API2::CONSTANTS::RSP_OrderStatus_CONFIRMED)
        _exchangeOrderId = _context->reqQryExchangeOrderId(_orderId);

      if(strcmp(confirmation.getExchangeOrderId().c_str(),_exchangeOrderId.c_str()))
      {
        DEBUG_MESSAGE(_context->reqQryDebugLog(),"Mismatch in order id");
        return false;
      }
      return true;
    }

    long OrderWrapper::getClOrderId()
    {
      if( _order )
        return _order->getClOrdId();
      return 0;
    }

  }
}
