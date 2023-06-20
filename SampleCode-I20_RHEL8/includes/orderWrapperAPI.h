#pragma once

#include <sgContext.h>
#include <sharedCommands.h>

namespace API2 {
  namespace COMMON {

    /**
     * @brief The LegDetailAPI class : User to store data for each leg in case of multileg orders.
     */
    class LegDetailAPI :public SGContext::OrderLegData{

      SGContext *context = nullptr;
      CREATE_FIELD (DATA_TYPES::OrderMode, Mode);
      CREATE_FIELD (DATA_TYPES::OrderValidity, OrderValidity);
      CREATE_FIELD (DATA_TYPES::OrderType, OrderType);
      CREATE_FIELD (DATA_TYPES::PRICE, OutstandingOrderPrice);
      CREATE_FIELD (DATA_TYPES::QTY, OutstandingOrderQuantity);
      CREATE_FIELD (DATA_TYPES::QTY, LastFilledQuantity);
      CREATE_FIELD (DATA_TYPES::ProductType, ProductType);
      CREATE_FIELD (DATA_TYPES::AMT, TotalFilledAmount);
      CREATE_FIELD (AccountDetail, Account);
      CREATE_FIELD (bool, IsReset);

      public:
      /**
       * @brief LegDetailAPI
       * @param context
       * @param instrument
       * @param mode
       * @param orderType
       * @param validity
       * @param productType
       * @param account
       * @param clientId
       */
      LegDetailAPI(
          SGContext *context,
          Instrument *instrument,
          const DATA_TYPES::OrderMode &mode,
          const DATA_TYPES::OrderType &orderType,
          const DATA_TYPES::OrderValidity &validity,
          const DATA_TYPES::ProductType &productType,
          const AccountDetail &account,
          const DATA_TYPES::CLIENT_ID &clientId =0);

      /**
       * @brief reset : To initialize and create orders.
       * @param clientId
       */
      void reset(const DATA_TYPES::CLIENT_ID &clientId = 0);

      /**
       * @brief updateLegDetail : To update leg data.
       * @param qty
       * @param price
       * @param lastFilledQty
       * @param lastFilledPrice
       */
      void updateLegDetail(
          const DATA_TYPES::QTY &qty,
          const DATA_TYPES::PRICE &price,
          const DATA_TYPES::QTY &lastFilledQty,
          const DATA_TYPES::PRICE &lastFilledPrice = 0);

      /**
       * @brief resetLegDetail : To reset leg data.
       */
      void resetLegDetail();
    };

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
      API2::DATA_TYPES::PRICE _price;
      API2::DATA_TYPES::QTY _lastQuantity;
      API2::DATA_TYPES::PRICE _lastQuotedPrice;
      API2::DATA_TYPES::QTY _lastFilledQuantity;
      API2::DATA_TYPES::SelfTradeOrderFlag _selfTradeOrderFlag;
      API2::DATA_TYPES::MarketSessionType _marketSessionType;
      const API2::ExchangeAdapterDetails* _exchangeAdapterDetails;

      /**
       * @brief _timeStart : Start time of placing order
       */
      timespec _timeStart;
      /**
       * @brief _timeEnd : End time of placing order
       */
      timespec _timeEnd;
      /**
       * @brief _timeFavourable : Time when the strategy is ready to place order
       */
      timespec _timeFavourable;
      /**
       * @brief _timeTurnAround : Time at which strategy is getting confirmation of placed order
       */
      timespec _timeTurnAround;

      /**
       * @brief _printLatency : configuration of whether to print latency logs
       */
      CREATE_FIELD ( bool, PrintLatency);

      /*-------Parameters For multilegIOC-------
       * Note: For multileg orders, leg details must be accessed from_orderLegData
       */
      CREATE_FIELD ( int, NumOfLegs);
      CREATE_FIELD ( int, NumOfConfirmation);
      std::vector<LegDetailAPI> _orderLegData;
      std::map<SIGNED_LONG, API2::DATA_TYPES::String> _mapSymbolIdExchangeOrderId;

      /**
       * @brief _customTraderId: This parameter is used to give custom trader id value by user
       * Used in case of NSE for multiqueuing task.
       */
      API2::DATA_TYPES::CUSTOM_TRADER_ID _customTraderId;

    public:
      /**
       * @brief OrderWrapperAPI : constructor
       * @param instrument
       * @param mode : order mode for placing order
       * @param context : SGContext pointer
       * @param account : Account detail
       * @param type : Order Type for placing order, By default LIMIT
       * @param validity : Order Validity
       * @param isSpread : Set this parameter to true. if this is spread order
       * @param selfTradeOrderFlag : STPC flag
       * @param marketSessionType : market session type
       * @param exchangeAdapterDetails : echange adapter datail
       * @param latencyPrint : this parameter is used to enable Latency logs. i.e Time to send , time to react, TAT, TotalTime
       * @param customTraderId : this parameter is used to set custom trader id , default value which is 0.
       */
      OrderWrapperAPI(API2::COMMON::Instrument *instrument,
          const API2::DATA_TYPES::OrderMode &mode,
          SGContext *context,
          const API2::AccountDetail &account,
          const API2::DATA_TYPES::OrderType &type = API2::CONSTANTS::CMD_OrderType_LIMIT,
          const API2::DATA_TYPES::OrderValidity &validity = API2::CONSTANTS::CMD_OrderValidity_DAY,
          bool isSpread =false,
          const API2::DATA_TYPES::SelfTradeOrderFlag &selfTradeOrderFlag = API2::CONSTANTS::CMD_SelfTradeOrderFlag_CANCEL_PASSIVE,
          const API2::DATA_TYPES::MarketSessionType marketSessionType = API2::CONSTANTS::CMD_QUEUED_SESSION_NORMAL,
          const API2::ExchangeAdapterDetails* const exchangeAdapterDetails = nullptr,
          bool latencyPrint = false,
          API2::DATA_TYPES::CUSTOM_TRADER_ID customTraderId = 0 )
        :
          _instrument(instrument),
          _mode(mode),
          _orderType(type),
          _orderValidity(validity),
          _order(nullptr),
          _replaceOrder(nullptr),
          _orderId(nullptr),
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
          _exchangeAdapterDetails(exchangeAdapterDetails),
          _PrintLatency(latencyPrint),
          _NumOfLegs(0),
          _NumOfConfirmation(0),
          _customTraderId(customTraderId)
      {
        _timeFavourable.tv_nsec = 0;
        _timeFavourable.tv_sec = 0;
        reset();

      }
      void setPrimaryClientCode(const std::string &pcc)
      {
        _accountDetail.setPrimaryClientCode(pcc.c_str());
        _accountDetail.setAccountType(0);
      }
      OrderWrapperAPI()
        :
          _instrument(nullptr),
          _mode(API2::CONSTANTS::CMD_OrderMode_MAX),
          _order(nullptr),
          _replaceOrder(nullptr),
          _orderId(nullptr),
          _context(nullptr),
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
          _exchangeAdapterDetails(nullptr),
          _PrintLatency(false),
          _NumOfLegs(0),
          _NumOfConfirmation(0),
          _customTraderId(0)
      {
        _timeFavourable.tv_nsec = 0;
        _timeFavourable.tv_sec = 0;
      }

      /**
       * @brief OrderWrapperAPI : Multileg order wrapper constructor.
       *                          Must be call with atleast two instruments.
       * @param context
       * @param instrumentLeg1
       * @param modeLeg1
       * @param account1
       * @param instrumentLeg2
       * @param modeLeg2
       * @param account2
       * @param instrumentLeg3
       * @param modeLeg3
       * @param account3
       * @param printLatency
       * @param selfTradeFlag
       */
      OrderWrapperAPI(SGContext *context,
          API2::COMMON::Instrument *instrumentLeg1,
          const API2::DATA_TYPES::OrderMode &modeLeg1,
          const API2::AccountDetail &account1,
          API2::COMMON::Instrument *instrumentLeg2,
          const API2::DATA_TYPES::OrderMode &modeLeg2,
          const API2::AccountDetail &account2,
          API2::COMMON::Instrument *instrumentLeg3=nullptr,
          const API2::DATA_TYPES::OrderMode &modeLeg3 =CONSTANTS::CMD_OrderMode_MAX,
          API2::AccountDetail account3=AccountDetail(),
          const bool printLatency = false,
          const API2::DATA_TYPES::SelfTradeOrderFlag selfTradeFlag =
          API2::CONSTANTS::CMD_SelfTradeOrderFlag_CANCEL_PASSIVE);

      void reset();

      API2::DATA_TYPES::QTY getLastQuantity() { return _lastQuantity; }
      API2::DATA_TYPES::PRICE getLastQuotedPrice() { return _lastQuotedPrice; }
      API2::DATA_TYPES::QTY getLastFilledQuantity() { return _lastFilledQuantity; }
      API2::DATA_TYPES::PRICE getLastPrice(){return _order->getPrice();}
      API2::DATA_TYPES::PRICE getLastQty(){return _order->getQuantity();}
      API2::DATA_TYPES::String getExchangeOrderId(){ return _exchangeOrderId;} 
      API2::DATA_TYPES::OrderMode getOrderMode() { return _order->getOrderMode(); }

      bool newOrder(API2::DATA_TYPES::RiskStatus &risk, 
          const API2::DATA_TYPES::PRICE &price, 
          const API2::DATA_TYPES::QTY &qty, 
          API2::DATA_TYPES::PRICE stopPrice = 0 );

      bool addOrderDetails(API2::DATA_TYPES::RiskStatus &risk, 
          const API2::DATA_TYPES::PRICE &price, 
          const API2::DATA_TYPES::QTY &qty, 
          API2::DATA_TYPES::PRICE stopPrice = 0 );

      bool placeNewOrder( API2::DATA_TYPES::RiskStatus &risk );
      API2::DATA_TYPES::CUSTOM_TRADER_ID getCustomTraderId()const;

      /**
       * @brief replaceOrder:  To send a replace Order
       * @param risk
       * @param price
       * @param qty
       * @param stopPrice
       * @param modifiedBy
       * @return  true if order is replaced sucessfully
       *         else false(Also it return false if order type is IOC because there is no sense to cancel/replace IOC order)
       * Note: If modification of IOC order is requested, then false is returned without any processing.
       *       As there is no meaning to modify IOC order.
       */
      bool replaceOrder(API2::DATA_TYPES::RiskStatus &risk,
          const API2::DATA_TYPES::PRICE &price=0,
          const API2::DATA_TYPES::QTY &qty=0,
          API2::DATA_TYPES::PRICE stopPrice = 0,
          const SIGNED_LONG modifiedBy = API2::CONSTANTS::Default_Modified_By_Id);

      /**
       * @brief cancelOrder to cancel order
       * @param risk
       * @param modifiedBy
       * @return true if order is cancelled sucessfully
       *              else false (Also it return false if order type is IOC because there is no sense to cancel/replace IOC order)
       * Note: If cancellation of IOC order is requested, then false is returned without any processing.
       *       As there is no meaning to cancel IOC order.
       */
      bool cancelOrder(API2::DATA_TYPES::RiskStatus &risk, const SIGNED_LONG modifiedBy = API2::CONSTANTS::Default_Modified_By_Id);
      void updateOrderWrapper(SIGNED_LONG qty,SIGNED_LONG price,SIGNED_LONG lastFilledQty);
      void resetOrderWrapper();
      void setSelfTradeFlag( API2::DATA_TYPES::SelfTradeOrderFlag &selfTradeOrderFlag );
      void setCustomTraderId( API2::DATA_TYPES::CUSTOM_TRADER_ID id );
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

      /**
       * @brief setStartTimer : For starting the timer when the strategy is ready for placing order.
       *                        Call this method to print Time to react and total time if latency print is on
       */
      void setStartTimer();

      /**
       * @brief printLatencyLogs : To print the latency logs
       */
      void printLatencyLogs();
      
      /**
       * @brief timeDiff : return the time diffrence between time1 and time2
       **/
      int64_t timeDiff(const timespec &time1, const timespec &time2);

      /**
       * @brief getLegOrder : Returns leg detail of the specied symbol id.
       *                      Must be used in case of multileg orders.
       * @param symbolId
       * @return
       */
      LegDetailAPI* getLegOrder(const DATA_TYPES::SYMBOL_ID &symbolId);

      /**
       * @brief getLeg1OrderId : Returns first leg orderId
       *                         Must be used in case of multileg orders.
       * @return
       */
      COMMON::OrderId* getLeg1OrderId();

      /**
       * @brief getLeg1OrderId : Returns second leg orderId
       *                         Must be used in case of multileg orders.
       * @return
       */
      COMMON::OrderId* getLeg2OrderId();

      /**
       * @brief getLeg1OrderId : Returns third leg orderId
       *                         Must be used in case of multileg orders.
       * @return
       */
      COMMON::OrderId* getLeg3OrderId();

      /**
       * @brief newOrder : Places new multileg orders.
       * @param risk : Risk status in casee of failure.
       * @param priceLeg1 : First leg price
       * @param qtyLeg1 : First leg qty
       * @param priceLeg2 : Second leg price
       * @param qtyLeg2 : Second leg qty
       * @param priceLeg3 : Third leg price
       * @param qtyLeg3 : Third leg qty
       * @return
       */
      bool newOrder(API2::DATA_TYPES::RiskStatus &risk,
          const API2::DATA_TYPES::PRICE &priceLeg1,
          const API2::DATA_TYPES::QTY &qtyLeg1,
          const API2::DATA_TYPES::PRICE &priceLeg2,
          const API2::DATA_TYPES::QTY &qtyLeg2,
          const API2::DATA_TYPES::PRICE &priceLeg3 = 0,
          const API2::DATA_TYPES::QTY &qtyLeg3 = 0);
    };

  }
}


