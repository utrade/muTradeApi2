#ifndef ORDER_BOOK_DEFINES_H
#define ORDER_BOOK_DEFINES_H
#include <boost/unordered_map.hpp>
namespace CMD {

  /**
 *
 */
  class SingleOrder;
  class SpreadOrder;
}
namespace API2   {

  /**
 * @brief The OrderBook struct
 */
  struct OrderBook
  {
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

    void insert(CMD::SpreadOrder* order);

    /**
     * @brief getOrder
     * @param clOrderId
     * @return
     */
    CMD::SingleOrder* getOrder(long clOrderId);

    /**
     * @brief getSpreadOrder
     * @param clOrderId
     * @return
     */
    CMD::SpreadOrder* getSpreadOrder(long clOrderId);

    /**
     * @brief getApiOrder
     * @param clOrderId
     * @return
     */
    SingleOrder* getApiOrder(long clOrderId);

    /**
     * @brief update
     * @param confirmation
     * @param reconcileOldOrders
     * @return
     */
    int update(OrderConfirmation& confirmation, bool reconcileOldOrders = false);

    /**
     * @brief alignOrders
     * @param order
     */
    void alignOrders(CMD::SingleOrder * order);
    // Client order Id to order mapping
    boost::unordered_map<long, CMD::SingleOrder*> _orderBook;
    boost::unordered_map<long, CMD::SpreadOrder*> _spreadOrderBook;
    //boost::unordered_map<long, CMD::ThreeLegOrder*> _orderBookThreeLeg;

    // ExchangeOrderId to TradeId mapping -- used in reconcilation to find duplicate fills
    std::multimap<std::string, std::string> _exchangeOrderIdToTradeId;
  };

}
#endif
