from muTradePyBase import *
import sys
"""
summary::

on init event: create instrument to trade on
on market data: new order is placed if no other order is pending in the market
on partial fill: cancel the existing order
on filled: specify by assigning -1 to order id that new order can be placed on market data event
on confirmed: place a replace order
"""

class sample(CustomStrategy):
    def __init__(self, tokenId):
        CustomStrategy.__init__(self,tokenId)
        #orderId = -1 tells us that there is no order in the market
        self.orderId = -1


    def printOrderReply(self, reply):
        self.reqAddLogMessage("Order Reply: \nriskStatus: " + str(reply.riskStatus) + "\nOrderId: "+ str(reply.orderID) + "\nSendSuccess: " + str(reply.SendSuccess) )


    def onInitEvent(self):
        """!@brief first event of the strategy. Used here to create an instrument in which we want to trade on
        """
        try:
            #we save the instrument and instrument id as an instance variable of the class i.e. every strategy has it's own
            self.TradeInstrument = self.createInstrumentFromSymbolFormat("ESMNSE INFY", True, True, False)
            self.TradeInsrumentId = self.reqQryInstrumentId("ESMNSE INFY")
        except:
            #adding debug messages to log file
            self.reqAddLogMessage("error in creating instrument: " + sys.exc_info()[0])
            self.reqAddLogMessage("terminating strategy")
            #terminating strategy as the instrument was not created successfully or the instrument id was not recieved properly
            self.reqTerminateStrategy(False);
            return
        self.reqAddLogMessage("new instrument added : ESMNSE RELIANCE")

    def onCMDModifyStrategy(self):
        pass

    def onCMDTerminateStartegy(self):
        pass

    def onCMDTerminateSqOffStrategy(self):
        pass

    def onMarketDataEvent(self, InstrumentId):
        self.reqAddLogMessage("onMarketDataEvent")
        self.reqAddLogMessage("instrument id : " + str(InstrumentId))
        if(self.orderId != -1):
            return
        #as order id = -1 we place a new order
        #check the current buy price
        buyPrice = self.reqQryPrice(InstrumentId, pyApi.OrderMode.OrderMode_BUY, 1)
        self.reqAddLogMessage("buy price : " + str(buyPrice))
        #check the current buy qty
        buyQty = self.reqQryQty(InstrumentId, pyApi.OrderMode.OrderMode_BUY, 1)
        self.reqAddLogMessage("buy quantity : "+ str(buyQty))
        #creating an order with price order according to our logic
        order = pyApi.SingleOrder(self.TradeInstrument, 100, 0, buyPrice - 20, 0, pyApi.OrderMode.OrderMode_BUY, pyApi.OrderType.OrderType_LIMIT, pyApi.OrderValidity.OrderValidity_DAY)
        #placing a new order
        reply = self.reqPlaceNewOrder(order)
        self.orderId = reply.orderID
        if(reply.SendSuccess):
            self.reqAddLogMessage("success : buy order placed with risk status : "+ str(reply.riskStatus))
        else:
            self.reqTerminateStrategy(True)
            self.reqAddLogMessage("failure : order failed with risk status : "+ str(reply.riskStatus))


    def onOhlcTimeOutEvent(self):
        pass

    def onNewRejected(self, OrderId, ErrorCode):
        self.orderId = -1;

    def onReplaceRejected(self, OrderId, ErrorCode):
        pass

    def onCancelRejected(self, OrderId, ErrorCode):
        self.reqAddLogMessage("cancel rejected of orderId : " + str(OrderId));

    def onConfirmed(self, OrderId, exchangeOrderId):
        #on order confirmation we place a new replace order according to our logic
        buyPrice = self.reqQryPrice(self.TradeInsrumentId, pyApi.OrderMode.OrderMode_BUY, 1)
        self.reqAddLogMessage("buy price : "+ str(buyPrice))
        buyQty = self.reqQryQty(self.TradeInsrumentId, pyApi.OrderMode.OrderMode_BUY, 1)
        self.reqAddLogMessage("buy quantity : "+ str(buyQty))
        order = pyApi.SingleOrder(self.TradeInstrument, buyQty, 0, buyPrice - 20, 0, pyApi.OrderMode.OrderMode_BUY, pyApi.OrderType.OrderType_LIMIT, pyApi.OrderValidity.OrderValidity_DAY)
        #place replace order by specifying the order id of the current order and the new replace order
        reply = self.reqPlaceReplaceOrder(self.orderId, order)
        #orderId is still not -1 so no order will be placed on market data event
        self.orderId = reply.orderID
        if(reply.SendSuccess):
            self.reqAddLogMessage("success : buy order placed with risk status : "+ str(reply.riskStatus))
        else:
            self.reqTerminateStrategy(True)
            self.reqAddLogMessage("failure : order failed with risk status : "+ str(reply.riskStatus))


    def onReplaced(self, OrderId):
        pass

    def onCanceled(self, OrderId):
        self.reqAddLogMessage("Order Got Canceled: OrderId: "+ str(OrderId))
        self.orderId = -1;
        pass

    def onIOCCanceled(self, OrderId, CanceledQty):
        pass

    def onFilled(self, OrderId, LastFillPrice, LastFillQty):
        self.reqAddLogMessage("Order Got Filled: OrderId: "+ str(OrderId) + "\nLast Fill Qty: "+ str(LastFillQty) + "\nFille Price: "+ str(LastFillPrice))
        #changing orderId to -1 as our order is now completely and we are back with no pending orders in the market
        self.orderId = -1;
        pass

    def onPartialFill(self, OrderId, LastFillPrice, LastFillQty):
        orderReply = self.reqPlaceCancelOrder(OrderId)
        if(orderReply.SendSuccess):
            self.orderId = -1
        else:
            self.reqTerminateStrategy(True)

    def onMarketToLimit(self, OrderId):
        pass

    def onFrozen(self, OrderId):
        pass


    def onTimerEvent(self):
        pass

