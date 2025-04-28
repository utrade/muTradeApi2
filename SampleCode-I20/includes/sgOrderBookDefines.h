#ifndef ORDER_BOOK_DEFINES_H
#define ORDER_BOOK_DEFINES_H
#include <boost/unordered_map.hpp>
#include <apiDataTypes.h>

namespace CMD {

  /**
 *
 */
  class SingleOrder;
}
namespace API2   {

  /**
 * @brief The OrderBook struct
 */
  struct OrderBook
  {
    OrderBook() = default ;
    ~OrderBook() ;

    /// deleting to avoid shallow copy issues in future.
    OrderBook(const OrderBook& ) = delete ;
    OrderBook& operator=(const OrderBook& ) =delete ;
    OrderBook(OrderBook&& ) = delete ;
    OrderBook& operator=(OrderBook&& ) =delete ;

    /**
     * @brief insert
     * @param order
     */
    void insert(CMD::SingleOrder* order);

    /**
     * @brief insert
     * @param order
     */
    void insert(SingleOrder* order);


    /**
     * @brief getOrder
     * @param clOrderId
     * @return
     */
    CMD::SingleOrder* getOrder(DATA_TYPES::CLORDER_ID clOrderId);

    /**
     * @brief getOrderFromMasterOrderId : get SingleOrder with given MasterOrderId
     * @param masterClOrderId
     * @return
     */
    CMD::SingleOrder* getOrderFromMasterOrderId(DATA_TYPES::CLORDER_ID masterClOrderId);

    /**
     * @brief getApiOrder To get the API order by client order id
     * @param clOrderId
     * @return
     */
    SingleOrder* getApiOrder(DATA_TYPES::CLORDER_ID clOrderId);

    /**
     * @brief update To update the order book
     * @param confirmation
     * @param reconcileOldOrders
     * @param  clientId
     * @param isUnhedgeTrackerRequired
     * @param staticData
     * @return
     */
    int update(OrderConfirmation& confirmation,
               bool reconcileOldOrders = false,
               int clientId = 0, bool isUnhedgeTrackerRequired = true,
               SG::SymbolStaticData* staticData = nullptr );

    /**
     * @brief alignOrders
     * @param order
     */
    void alignOrders(CMD::SingleOrder * order);
    
    /**
     * @brief isCancelOrderPending checks if an cancel order is in pending state or not
     * param cancelOrderId
     * return true if order is in pending state else return false
     */
    bool isCancelOrderPending( const UNSIGNED_LONG cancelOrderId );

    // Client order Id to order mapping
    boost::unordered_map<DATA_TYPES::CLORDER_ID, CMD::SingleOrder*> _orderBook;

    /**
     * @brief _orderBook : MasterClientOrderId Vs ClientOrderId
     */
    std::unordered_map<DATA_TYPES::CLORDER_ID, DATA_TYPES::CLORDER_ID> _masterClOrderIdVsClOrderIdMap;

    /**
     * @brief updateClOrderIdOfMasterOrderId
     * @param masterOrderId
     * @param clOrderId
     */
    void updateClOrderIdOfMasterOrderId(DATA_TYPES::CLORDER_ID masterOrderId, DATA_TYPES::CLORDER_ID clOrderId);

    //boost::unordered_map<long, CMD::ThreeLegOrder*> _orderBookThreeLeg;
  };

}
#endif
