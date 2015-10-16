#ifndef MYAPI_CONTEXT_H
#define MYAPI_CONTEXT_H
#include <sgContext.h>
#include <api2UserCommands.h>
#include <api2Exceptions.h>
#include <apiConstants.h>
#include <apiDataTypes.h>
#include <sharedSingleOrder.h>
#include <list>
#include <unordered_map>
#include "../common/orderWrapper.h"
#define TESTING
#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
   __typeof__ (b) _b = (b); \
   _a > _b ? _a : _b; })

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
   __typeof__ (b) _b = (b); \
   _a < _b ? _a : _b; })

#define PUT_FACTOR -1
#define CALL_FACTOR 1

namespace API2
{
  namespace MultiTest
  {

    /**
     * @brief The FrontEndParameters struct
     */
    struct FrontEndParameters
    {
      SIGNED_LONG _numLegs;
      SIGNED_LONG _symbolIdLeg1;
      SIGNED_LONG _symbolIdLeg2;
      SIGNED_LONG _symbolIdLeg3;
      char _side1;
      char _side2;
      char _side3;
      SIGNED_LONG _qty1;
      SIGNED_LONG _qty2;
      SIGNED_LONG _qty3;
      SIGNED_LONG _price1;
      SIGNED_LONG _price2;
      SIGNED_LONG _price3;
      bool _isSpread;
      bool _isSingle;
      bool _isMultiLeg;
      FrontEndParameters()
        :
          _numLegs(0),
          _symbolIdLeg1(0),
          _symbolIdLeg2(0),
          _symbolIdLeg3(0),
          _side1(0),
          _side2(0),
          _side3(0),
          _qty1(0),
          _qty2(0),
          _qty3(0),
          _isSpread(false),
          _isSingle(false),
          _isMultiLeg(false)
      {
      }
      void dump(std::stringstream &ss, const char *str= ""){
        ss <<
          str <<"==============================\nSymbol ID ====="
          <<_symbolIdLeg1
          << "\n qty====="
          <<_qty1
          << "\n"
          "==============================\n"
          <<"==============================\nSymbol ID 2====="
          <<_symbolIdLeg2
          << "\n qty====="
          <<_qty2
          << "\n"
          "==============================\n"
          <<"==============================\nSymbol ID 3====="
          <<_symbolIdLeg3
          << "\n qty====="
          <<_qty3
          << "\n"
          "==============================\n"
          ;
      }
      std::string dump()
      {
        std::stringstream ss;
        dump(ss);
        return ss.str();

      }
    };

    /**
     * @brief The Context class
     */
    class Context: public API2::SGContext
    {
      API2::COMMON::Instrument *_Instrument1, *_Instrument2, *_Instrument3;
      FrontEndParameters _userParams;
      API2::COMMON::OrderWrapper _orderWrapper;

      public:

      /**
       * @brief Context
       * @param params
       */
      Context(API2::StrategyParameters *params);


      void registerMoreSymbol();

      /**
       * @brief onModifyStrategy
       */
      void onCMDModifyStrategy(API2::AbstractUserParams*);

      /**
       * @brief onDerivedMarketDataEvent
       * @param symbolId
       */
      void onMarketDataEvent(UNSIGNED_LONG symbolId);

      /**
       * @brief processOrderConfirmation
       * @param confirmation
       */
      void onProcessOrderConfirmation(OrderConfirmation &confirmation);


      /**
       * @brief onConfirmed
       * @param confirmation
       * @param orderId
       */
      void onConfirmed(OrderConfirmation &confirmation, COMMON::OrderId *orderId);

      /**
       * @brief onReplaced
       * @param confirmation
       * @param orderId
       */
      void onReplaced(OrderConfirmation &confirmation, COMMON::OrderId *orderId);

      /**
       * @brief onFilled
       * @param confirmation
       * @param orderId
       */
      void onFilled(OrderConfirmation &confirmation, COMMON::OrderId *orderId);

      /**
       * @brief onPartialFill
       * @param confirmation
       * @param orderId
       */
      void onPartialFill(OrderConfirmation &confirmation, COMMON::OrderId *orderId);

      /**
       * @brief onIOCCanceled
       * @param confirmation
       * @param orderId
       */
      void onIOCCanceled(OrderConfirmation &Confirmation, COMMON::OrderId *orderId);

      /**
       * @brief onCanceled
       * @param confirmation
       * @param orderId
       */
      void onCanceled(OrderConfirmation &confirmation, COMMON::OrderId *orderId);

      /**
       * @brief setInternalParameters
       * @brief params
       */
      bool setInternalParameters(API2::UserParams *params);


      /**
       * @brief onTimerEvent
       */
      void onTimerEvent();

      /**
       * @brief getPrice
       */
      API2::DATA_TYPES::PRICE getPrice();


      private:

      /**
       * @brief setParams
       */
      bool setParams();
    };

    /**
     * @brief TestDriver
     */
    void TestDriver(void *params);
  } //namespace MultiTest
} //namespace API2
#endif
