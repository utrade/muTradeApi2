#include "sample.h"

namespace API2
{
  namespace BENCHMARK
  {

    SampleStrategy::SampleStrategy(API2::StrategyParameters *params)
      :
        SGContext(params, "BenchmarkingSample")
    {
#ifdef BENCHMARK_MARKET_DATA
      _instrument = createNewInstrument("NSE RELIANCE",true);
#else
      _instrument = createNewInstrument("ESMNSE RELIANCE",true);
#endif

      _LNCreateOrder.setName("CreateBuyOrder");
      _LNResetOrder.setName("ResetBuyOrder");

      _LNNewOrder.setName("PlaceNewOrder");
      _LNNewOrderReject.setName("PlaceNewOrderReject");
      _LNReplaceOrder.setName("PlaceReplaceOrder");
      _LNReplaceOrderReject.setName("PlaceReplaceOrderReject");
      _LNCancelOrder.setName("PlaceCancelOrder");
      _LNCancelOrderReject.setName("PlaceCancelOrderReject");

      HFT_Start_Timer_Define;
      _orderWrapper  = new COMMON::OrderWrapper(_instrument,API2::CONSTANTS::CMD_OrderMode_BUY,API2::CONSTANTS::CMD_OrderType_LIMIT, this);
      HFT_Record_Timer(_LNCreateOrder);
    }

#ifndef BENCHMARK_MARKET_DATA
    void SampleStrategy::onMarketDataEvent(UNSIGNED_LONG symbolId)
    {
      API2::DATA_TYPES::PRICE price = reqQryMarketData(symbolId)->getBidPrice(1);
      API2::DATA_TYPES::QTY qty = _instrument->getStaticData()->marketLot*100;
      if(_orderWrapper->getLastQuotedPrice() == price)
        return;

#ifdef BENCHMARK_NEW_ORDERS
      HFT_Start_Timer_Define
      _orderWrapper->reset();
      HFT_Record_Timer(_LNResetOrder);
      sendNewOrder(price,qty);
      return;
#endif

      if(_orderWrapper->_isReset)
        {
          sendNewOrder(price,qty);
        }

      API2::DATA_TYPES::OrderStatus status = reqQryOrderStatus(_orderWrapper->_orderId);

      //      DEBUG_VARSHOW(reqQryDebugLog(), "Order Status:", status);
      switch(status)
        {
        case API2::CONSTANTS::RSP_OrderStatus_FILLED:
        case API2::CONSTANTS::RSP_OrderStatus_FROZEN:
        case API2::CONSTANTS::RSP_OrderStatus_CANCELED:
          sendNewOrder(price,qty);
          break;
        case API2::CONSTANTS::RSP_OrderStatus_REPLACED:
          sendCancelOrder();break;
        case API2::CONSTANTS::RSP_OrderStatus_CONFIRMED:
        case API2::CONSTANTS::RSP_OrderStatus_PARTIALLY_FILLED:
        case API2::CONSTANTS::RSP_OrderStatus_REPLACE_REJECTED:
        case API2::CONSTANTS::RSP_OrderStatus_CANCEL_REJECTED:
          sendReplaceOrder(price);break;

        }
    }
#endif
#ifndef BENCHMARK_NEW_ORDERS
    void SampleStrategy::onConfirmed(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
//      DEBUG_METHOD(reqQryDebugLog());
    }

    void SampleStrategy::onReplaced(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
//      DEBUG_METHOD(reqQryDebugLog());
    }

    void SampleStrategy::onReplaceRejected(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
//      DEBUG_METHOD(reqQryDebugLog());
    }

    void SampleStrategy::onCancelRejected(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
//      DEBUG_METHOD(reqQryDebugLog());
    }

    void SampleStrategy::onPartialFill(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
//      DEBUG_METHOD(reqQryDebugLog());
    }
    void SampleStrategy::onNewReject(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
      //      DEBUG_METHOD(reqQryDebugLog());
      reqTerminateStrategy(false);
    }

    void SampleStrategy::onCanceled(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
      //      DEBUG_METHOD(reqQryDebugLog());
      HFT_Start_Timer_Define
          _orderWrapper->reset();
      HFT_Record_Timer(_LNResetOrder);
    }


    void SampleStrategy::onFilled(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
      //      DEBUG_METHOD(reqQryDebugLog());
      HFT_Start_Timer_Define
          _orderWrapper->reset();
      HFT_Record_Timer(_LNResetOrder);
    }

    void SampleStrategy::onFrozen(OrderConfirmation &confirmation, COMMON::OrderId *orderId)
    {
      //      DEBUG_METHOD(reqQryDebugLog());
      HFT_Start_Timer_Define
          _orderWrapper->reset();
      HFT_Record_Timer(_LNResetOrder);
    }
#endif


    void BenchmarkingDriver(void *params)
    {
      API2::StrategyParameters *param = (API2::StrategyParameters*)params;
//      SampleStrategy s(param);
      boost::shared_ptr<SampleStrategy> context(new SampleStrategy(param));
      context->reqStartAlgo(true,false);
      API2::SGContext::registerStrategy(context);
    }

    void SampleStrategy::sendNewOrder(DATA_TYPES::PRICE price, DATA_TYPES::QTY qty)
    {
      API2::DATA_TYPES::RiskStatus risk;
      HFT_Start_Timer_Define;
      if(_orderWrapper->newOrder(risk,price,qty))
        {
          HFT_Record_Timer(_LNNewOrder);
        }
      else
        {
          HFT_Record_Timer(_LNNewOrderReject);
          DEBUG_VARSHOW(reqQryDebugLog(), "New Order Rejected Internally, Exiting Strategy. Reject Reason:", risk);
          //          _LNNewOrderReject.dumpDataSet();
          HFT_Start_Timer
              _orderWrapper->reset();
          HFT_Record_Timer(_LNResetOrder);
          //          reqTerminateStrategy(false);
        }

    }

    void SampleStrategy::sendReplaceOrder(DATA_TYPES::PRICE price, DATA_TYPES::QTY qty)
    {
//      DEBUG_METHOD(reqQryDebugLog());
      HFT_Start_Timer_Define;
      API2::DATA_TYPES::RiskStatus risk;
      if(_orderWrapper->replaceOrder(risk,price,qty))
        {
          HFT_Record_Timer(_LNReplaceOrder);
        }
      else
        {
          HFT_Record_Timer(_LNReplaceOrderReject);
          DEBUG_VARSHOW(reqQryDebugLog(), "Replace Order Rejected Internally, Exiting Strategy. Reject Reason:", risk);
//          reqTerminateStrategy(false);
        }
    }

    void SampleStrategy::sendCancelOrder()
    {
      HFT_Start_Timer_Define;
      API2::DATA_TYPES::RiskStatus risk;
      if(_orderWrapper->cancelOrder(risk)){
          HFT_Record_Timer(_LNCancelOrder);
        }
      else{
          HFT_Record_Timer(_LNCancelOrderReject);
        }
    }

  }
}
