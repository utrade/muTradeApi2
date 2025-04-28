#pragma once

#include <boost/unordered_map.hpp>
#include <sgContext.h>
#include <apiConstants.h>
#include <apiDataTypes.h>
#include <orderWrapperAPI.h>

namespace API2
{
  namespace COMMON
  {
    class OrderWrapperManager
    {
      public:
      OrderWrapperManager(SGContext* context): _context(context){}

      /**
      * @brief Create a new MultiLegOrderWrapper and return a shared_ptr to it.
      * @param instrumentLeg1 The first instrument leg.
      * @param modeLeg1 The order mode for the first leg.
      * @param account1 The account detail for the first leg.
      * @param instrumentLeg2 The second instrument leg.
      * @param modeLeg2 The order mode for the second leg.
      * @param account2 The account detail for the second leg.
      * @param instrumentLeg3 The third instrument leg.
      * @param modeLeg3 The order mode for the third leg.
      * @param account3 The account detail for the third leg.
      * @return A shared pointer to the created MultiLegOrderWrapper.
      */
      std::shared_ptr<API2::COMMON::OrderWrapperAPI> createOrderWrapper(API2::COMMON::Instrument *instrumentLeg1,
      const API2::DATA_TYPES::OrderMode &modeLeg1,
      const API2::AccountDetail &account1,
      API2::COMMON::Instrument *instrumentLeg2,
      const API2::DATA_TYPES::OrderMode &modeLeg2,
      const API2::AccountDetail &account2,
      API2::COMMON::Instrument *instrumentLeg3=nullptr,
      const API2::DATA_TYPES::OrderMode &modeLeg3 =CONSTANTS::CMD_OrderMode_MAX,
      API2::AccountDetail account3=AccountDetail());

      /**
      * @brief Handle order confirmation and update the order status.
      * @param confirmation The order confirmation received.
      * @param orderId The order ID associated with the confirmation.
      * to be called from strategy only when fill, cancel or newReject is received on one of the legs
      * handles logic to remove the wrapper if 1) confirmation is recceived on all 3 legs
      * 2) orderStatus of confirmation is either cancel, fill, newReject or rmsReject
      */
      void handleConfirmation(const API2::DATA_TYPES::OrderStatus &orderStatus, OrderId *id);

      bool processOrderConfirmation(OrderConfirmation &confirmation, OrderId *id);

      std::shared_ptr<API2::COMMON::OrderWrapperAPI> getOrderWrapper(OrderId *id);

      /**
      * @brief Expose the order map for external access.
      * @return A reference to the order map.
      */
      const std::unordered_map<API2::COMMON::OrderId*, std::shared_ptr<OrderWrapperAPI>>& getOrderMap() const;

      ~OrderWrapperManager();

      private:
            
      SGContext* _context;
      std::unordered_map<OrderId *, std::shared_ptr<OrderWrapperAPI>> _orderMap;
      std::unordered_map<std::shared_ptr<OrderWrapperAPI>, std::set<OrderId *>> _confirmationTracker;

      /**
      * @brief Remove an OrderWrapper based on OrderId.
      * @param orderId The order ID to remove.
      */
      void removeOrderWrapper(const std::shared_ptr<API2::COMMON::OrderWrapperAPI> &wrapper);
    };
  }
}