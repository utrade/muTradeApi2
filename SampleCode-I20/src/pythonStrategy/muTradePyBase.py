import pyApi
import sys
from pyApi import SingleOrder, AccountDetail, MarketDataWrapper, OrderReply

class CustomStrategy:
    def __init__(self, tokenId):
        self.tokenId = tokenId
        self.f = open('testLogs.txt','w')

    def onInitEvent(self):
        pass

    def onCMDModifyStrategy(self):
        pass

    def onCMDTerminateStartegy(self):
        pass

    def onCMDTerminateSqOffStrategy(self):
        pass

    def onDefaultEvent(self):
        print "something ode"
        #pass

    def onMarketDataEvent(self, InstrumentId):
        pass

    def onOhlcTimeOutEvent(self):
        pass

    def onNewRejected(self, OrderId, ErrorCode):
        pass

    def onReplaceRejected(self, OrderId, ErrorCode):
        pass

    def onCancelRejected(self, OrderId, ErrorCode):
        pass

    #orderId, exchangeOrderId
    def onConfirmed(self, OrderId, exchangeOrderId):
        pass

    #orderId, exchangeOrderId
    def onReplaced(self, OrderId):
        pass

    def onCanceled(self, OrderId):
        pass

    def onIOCCanceled(self, OrderId, CanceledQty):
        pass

    def onFilled(self, OrderId, LastFillPrice, LastFillQty):
        pass

    def onPartialFill(self, OrderId, LastFillPrice, LastFillQty):
        pass

    def onMarketToLimit(self, OrderId):
        pass

    def onFrozen(self, OrderId):
        pass

    def onTimerEvent(self):
        pass

    def createInstrument(self, InstrumentId, RegisterMktData, UseSnapshot, UseOHCL):
        Instrument = pyApi.createInstrument(InstrumentId, RegisterMktData, UseSnapshot, UseOHCL, self.tokenId);
        return Instrument

    def createInstrumentFromSymbolFormat(self, InstrumentId, RegisterMktData, UseSnapshot, UseOHCL):
        Instrument = pyApi.createInstrumentFromSymbolFormat(InstrumentId, RegisterMktData, UseSnapshot, UseOHCL, self.tokenId)
        return Instrument

    def reqPlaceNewOrder(self, singleOrder):
        orderReply = pyApi.reqPlaceNewOrder(singleOrder, self.tokenId)
        return orderReply

    def reqPlaceReplaceNewOrder(self, orderId, singleOrder):
        orderReply = reqPlaceReplaceNewOrder(orderId, singleOrder, self.tokenId)
        return orderReply

    def reqPlaceCancelOrder(self, orderId):
        orderReply = pyApi.reqPlaceCancelOrder(orderId, self.tokenId)
        return orderReply

    def reqStartAlgo(self, MarketDataEventRequired):
        pyApi.reqStartAlgo(MarketDataEventRequired, self.tokenId)
        return

    def reqUpdateMarketData(self, InstrumentId):
        pyApi.reqUpdateMarketData(InstrumentId, self.tokenId)
        return

    def reqRegisterTimerEvent(self, timeInterval):
        pyApi.reqRegisterTimerEvent(timeInterval, self.tokenId)
        return

    def reqTerminateStrategy(self, cancelOrders):
        pyApi.reqTerminateStrategy(cancelOrders, self.tokenId)
        return

    def reqTerminateSqOffStrategy(self):
        pyApi.reqTerminateSqOffStrategy(self.tokenId)
        return

    def reqQryPrice(self, InstrumentId, side, position):
        price = pyApi.reqQryPrice(InstrumentId, side, position, self.tokenId)
        return price

    def reqQryQty(self, InstrumentId, side, position):
        quantity = pyApi.reqQryQty(InstrumentId, side, position, self.tokenId)
        return quantity

    def reqQryLastTradePrice(self, InstrumentId):
        tradeprice = pyApi.reqQryLastTradePrice(InstrumentId, self.tokenId)
        return tradeprice

    def reqQryLastTradeQty(self, InstrumentId):
        tradequantity = pyApi.reqQryLastTradeQty(InstrumentId, self.tokenId)
        return tradequantity

    def reqQryOpenPrice(self, InstrumentId):
        openprice = pyApi.reqQryOpenPrice(InstrumentId, self.tokenId)
        return openprice

    def reqQryHighPrice(self, InstrumentId):
        highprice = pyApi.reqQryHighPrice(InstrumentId, self.tokenId)
        return highprice

    def reqQryLowPrice(self, InstrumentId):
        lowprice = pyApi.reqQryLowPrice(InstrumentId, self.tokenId)
        return lowprice

    def reqQryClosePrice(self, InstrumentId):
        closeprice = pyApi.reqQryClosePrice(InstrumentId, self.tokenId)
        return closeprice

    def reqQryVolume(self, InstrumentId):
        volume = pyApi.reqQryVolume(InstrumentId, self.tokenId)
        return volume

    def reqQryQuoteLastUpdateTime(self, InstrumentId):
        quotelastupdatetime = pyApi.reqQryQuoteLastUpdateTime(InstrumentId, self.tokenId)
        return quotelastupdatetime

    def reqQryInstrumentId(self, Instrument):
        instrumentid = pyApi.reqQryInstrumentId(Instrument, self.tokenId)
        return instrumentid

    def reqQryLastQuotedPrice(self, Instrument, mode):
        lastquotedprice = pyApi.reqQryLastQuotedPrice(Instrument, mode, self.tokenId)
        return lastquotedprice

    def reqQryOpenQty(self, Instrument):
        openquantity = pyApi.reqQryOpenQty(Instrument, self.tokenId)
        return openquantity

    def reqQryTradedQty(self, Instrument, mode):
        tradedquantity = pyApi.reqQryTradedQty(Instrument, mode, self.tokenId)
        return tradedquantity

    def reqQryOpenSide(self, Instrument):
        openside = pyApi.reqQryOpenSide(Instrument, self.tokenId)
        return openside

    def reqQryBookedPnl(self, Instrument):
        bookenpnl = pyApi.reqQryBookedPnl(Instrument, self.tokenId)
        return bookedpnl

    def reqQryMtmPnl(self, Instrument):
        mtmpnl = pyApi.reqQryMtmPnl(Instrument, self.tokenId)
        return mtmpnl

    def reqQryAvgPrice(self, Instrument, mode):
        averageprice = pyApi.reqQryAvgPrice(Instrument, mode, self.tokenId)
        return averageprice

    def reqQryPendingQty(self, Instrument, mode):
        pendingquantity = pyApi.reqQryPendingQty(Instrument, mode, self.tokenId)
        return pendingquantity

    def reqQryClientId(self, tokenId):
        clientid = pyApi.reqQryClientId(self.tokenId)
        return clientid

    def reqQryNetBookedPL(self):
        netbookedpnl = pyApi.reqQryNetBookedPL(self.tokenId)
        return netbookedpnl

    def reqQryNetMarkToMarkPL(self ):
        netmarktomarkpl = pyApi.reqQryNetMarkToMarkPL(self.tokenId)
        return netmarktomarkpl

    def reqQrySymbolId(self, InstrumentFormat):
        symbolid = pyApi.reqQrySymbolId(InstrumentFormat, self.tokenId)
        return symbolid

    def reqQryInstrumentList(self, Instrument):
        instrumentlist = pyApi.reqQryInstrumentList(Instrument, self.tokenId)
        return instrumentlist

    def reqQryAllInstruments(self):
        allinstruments = pyApi.reqQryAllInstruments(self.tokenId)
        return allinstruments

    def reqQryExchangeOrderId(self, orderId):
        exchangeorderid = pyApi.reqQryExchangeOrderId(orderId, self.tokenId)
        return exchangeorderid

    def reqAddLogMessage(self, message):
        self.f.write("[LOG_MESSAGE], "+message+ "\n")
        pyApi.reqAddLogMessage(message, self.tokenId)
        return

    def reqFlushLogMessage(self):
        pyApi.reqFlushLogMessage(self.tokenId)
        return

    def reqQryStrategyID(self):
        strategyid = pyApi.reqQryStrategyID(self.tokenId)
        return strategyid

    def reqQryOrderPendingQty(self, orderId):
        orderpendingquantity = pyApi.reqQryOrderPendingQty(orderId, self.tokenId)
        return orderpendingquantity

    def reqQryInstrumentPendingQty(self, Instrument, side):
        instrumentpendingquantity = pyApi.reqQryInstrumentPendingQty(Instrument, side, self.tokenId)
        return instrumentpendingquantity

    def reqQryClientOrderID(self, orderId):
        clientorderid = pyApi.reqQryClientOrderID(orderId, self.tokenId)
        return clientorderid

    def reqQryOrderStatus(self, orderId):
        orderstatus = pyApi.reqQryOrderStatus(orderId, self.tokenId)
        return orderstatus

    def reqQryExchangeOrderID(self, orderId, tokenId):
        exchangeorderid = pyApi.reqQryExchangeOrderID(orderId, self.tokenId)
        return exchangeorderid

    def getMarketDataEventRequired(self):
        return self.MarketDataEventRequired;

    def getOHLCDataEventRequired(self):
        return self.OHLCDataEventRequired;

