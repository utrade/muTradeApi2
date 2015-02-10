#include "orderWrapper.h"


namespace API2 {
  namespace COMMON {

    void OrderWrapper::reset()
    {
      _order = _context->createNewOrder(_instrument,0,0,_mode,_orderType);
      API2::AccountDetail account;
      _orderId = _context->createNewOrderId(_instrument,account,_mode);
      _isReset = true;
    }

    bool OrderWrapper::newOrder(DATA_TYPES::RiskStatus &risk, const DATA_TYPES::PRICE &price, const DATA_TYPES::QTY &qty)
    {
      _isReset = false;
      _isPendingNew = true;
      if(qty==0)
      {
        risk = API2::CONSTANTS::RSP_RiskStatus_WRONG_QUANTITY;
        return false;
      }
      if(_order)
      {
        _order->setPrice(price);
        _order->setQuantity(qty);

        if(_context->reqNewSingleOrder(risk,_instrument,_order,_orderId))
        {
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

    bool OrderWrapper::replaceOrder(DATA_TYPES::RiskStatus &risk, const DATA_TYPES::PRICE &price, const DATA_TYPES::QTY &qty)
    {
      if(!_orderId){
            DEBUG_MESSAGE(_context->reqQryDebugLog(), "OrderWrapper replace fail OrderId null");
          return false;
      }
      _isReset = false;
      _isPendingReplace = true;
       if(price == _instrument->getLastQuotedPrice(_mode))
           return false;
      API2::SingleOrder *order = _context->createNewOrder(_instrument,0,0,_mode);
      if(order)
      {
        API2::SingleOrder *origOrder = _context->reqQryOrder(_context->reqQryClientOrderId(_orderId));
        if(origOrder)
        {
          if(price !=0)
            order->setPrice(price);
          else
            order->setPrice(origOrder->getPrice());
          if(qty !=0)
            order->setQuantity(qty);
          else
            order->setQuantity(origOrder->getQuantity());

          if(_context->reqQryOrderStatus(_orderId) != API2::CONSTANTS::RSP_OrderStatus_PENDING){

            if(_context->reqReplaceOrder(risk,_instrument,order,_orderId)){
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
      _isReset = false;      _isPendingCancel = true;
      return _context->reqCancelOrder(risk,_orderId);
    }

    bool OrderWrapper::processConfirmation(OrderConfirmation &confirmation)
    {

      if(strcmp(confirmation.getExchangeOrderId().c_str(),_context->reqQryExchangeOrderId(_orderId).c_str()))
        return false;
      switch(confirmation.getOrderStatus())
      {
        case API2::CONSTANTS::RSP_OrderStatus_CONFIRMED:
          _isPendingNew = false;break;
        case API2::CONSTANTS::RSP_OrderStatus_REPLACED:
          _isPendingReplace = false;break;
        case API2::CONSTANTS::RSP_OrderStatus_CANCELED:
          _isPendingCancel = false;break;

      }
      return true;
    }

  }

}
