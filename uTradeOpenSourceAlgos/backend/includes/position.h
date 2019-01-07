#ifndef POSITION_H
#define POSITION_H
#include<cmdDefines.h>
namespace INVOKING
{
  class Position
  {
    public:
      Position();

      Position( SIGNED_LONG tradedQty, double avgTradedPrice );

    /* @brief getTradedQty gets the total traded qty corresponding to the order mode and symbol id
     * @return 
     */
    SIGNED_LONG getTradedQty() const;

    /* @brief getAvgTradedPrice gets the average traded price corresponding to the order mode and symbol id
     * @return 
     */
    double getAvgTradedPrice() const;
  };
}
#endif
