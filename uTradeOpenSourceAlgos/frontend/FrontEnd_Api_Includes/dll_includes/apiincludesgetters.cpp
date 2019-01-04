#include "../../api2/api_includes/sharedResponse.h"

namespace API2 {

AccountDetail::AccountDetail()
{
  initialize();
}

void AccountDetail::initialize(){
  strcpy(_primaryClientCode, "");
  _TraderId =0;
  _LocationId =0;
  _AccountType = 4;
}

DATA_TYPES::CLORDER_ID OrderConfirmation::getClOrderId()
const { return _clOrderId; }

std::string OrderConfirmation::getExchangeOrderId()
const { return std::string(_exchangeOrderId); }

DATA_TYPES::SYMBOL_ID OrderConfirmation::getSymbolId()
const { return _symbolId; }

DATA_TYPES::QTY  OrderConfirmation::getLastFillQuantity()
const { return _lastFillQuantity; }

DATA_TYPES::PRICE  OrderConfirmation::getLastFillPrice()
const { return _lastFillPrice; }

DATA_TYPES::PRICE  OrderConfirmation::getOrigLastFillPrice()
const { return _origLastFillPrice; }

DATA_TYPES::EXCHANGE_TIME  OrderConfirmation::getExchangeEntryTime()
const { return _exchangeEntryTime; }

DATA_TYPES::String OrderConfirmation::getStrategyTypeSqnNo()
const { return std::string ( _strategyTypeSqnNo ); }

DATA_TYPES::EXCHANGE_TIME  OrderConfirmation::getExchangeModifyTime()
const { return _exchangeModifyTime; }

DATA_TYPES::STRATEGY_ID  OrderConfirmation::getStrategyId()
const { return _strategyId; }

DATA_TYPES::CLIENT_ID  OrderConfirmation::getClientId()
const { return _clientId; }

DATA_TYPES::PRICE  OrderConfirmation::getLimitPrice()
const { return _limitPrice; }

DATA_TYPES::PRICE  OrderConfirmation::getOrigLimitPrice()
const { return _origLimitPrice; }

DATA_TYPES::OrderStatus OrderConfirmation::getOrderStatus()
const { return _orderStatus; }

DATA_TYPES::OrderMode OrderConfirmation::getOrderMode()
const { return _orderMode; }

DATA_TYPES::QTY  OrderConfirmation::getOrderQuantity()
const { return _orderQuantity; }

DATA_TYPES::PRICE  OrderConfirmation::getOrderPrice()
const { return _orderPrice; }

DATA_TYPES::PRICE  OrderConfirmation::getOrigOrderPrice()
const { return _origOrderPrice; }

DATA_TYPES::QTY OrderConfirmation::getIOCCanceledQuantity()
const { return _iocCanceledQuantity; }

DATA_TYPES::CLORDER_ID OrderConfirmation::getOriginalClOrderId()
const { return _originalClOrderId; }

DATA_TYPES::String OrderConfirmation::getTradeId()
const {return std::string(_tradeId);}

const char *OrderConfirmation::getTradeIdCharPtr() const
{
    return _tradeId;
}

const char *OrderConfirmation::getExchangeOrderIdCharPtr()const
{
    return _exchangeOrderId;
}

DATA_TYPES::ERROR_CODE OrderConfirmation::getErrorCode()
const {return _errorCode;}

DATA_TYPES::TRADER_ID OrderConfirmation::getTraderId()
const {return _traderId;}

DATA_TYPES::ENUM OrderConfirmation::getOrderCategory()
const {return _orderCategory;}

DATA_TYPES::PRICE OrderConfirmation::getLastFillPrice1()
const {return _lastFillPrice1;}

DATA_TYPES::PRICE OrderConfirmation::getLastFillPrice2()
const {return _lastFillPrice2;}

API2::DATA_TYPES::OrderValidity OrderConfirmation::getOrderValidity()
const {return _orderValidity;}

DATA_TYPES::GTD_Date OrderConfirmation::getGTDDate()
const {return _gtdDate;}

DATA_TYPES::ENUM OrderConfirmation::getBookType()
const {return _bookType;}

char OrderConfirmation::getOpenCloseFlag()
const {return _openCloseFlag;}

DATA_TYPES::PRICE OrderConfirmation::getStopPrice()
const {return _stopPrice;}

DATA_TYPES::OrderType OrderConfirmation::getOrderType()
const {return _orderType;}

DATA_TYPES::ProductType OrderConfirmation::getProductType()
const {return _productType;}

DATA_TYPES::PlatformType OrderConfirmation::getPlatformType()
const {return _platformType;}

DATA_TYPES::CLORDER_ID OrderConfirmation::getQuoteId()
const {return _quoteId;}

API2::DATA_TYPES::ConfirmationType OrderConfirmation::getConfirmationType()
const {return _confirmationType;}

std::string OrderConfirmation::getFixClOrderId()
const { return std::string(_fixClOrderId); }

char* OrderConfirmation::getFixClOrderIdCharPtr()
{
    return _fixClOrderId;
}


DATA_TYPES::STRATEGY_ID OrderConfirmation::getChildStrategyId() const
{
    return _childStrategyId;
}

DATA_TYPES::STRATEGY_ID OrderConfirmation::getParentStrategyId() const
{
    return _parentStrategyId;
}

}
