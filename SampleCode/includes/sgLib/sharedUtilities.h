#ifndef SHARED_UTILITIES_H
#define SHARED_UTILITIES_H
#include <sharedDefines.h> 
#include <sharedCommands.h>
#include <sgSymbolDataDefines.h>
namespace API2
{

/**
   * @brief The SharedUtilities class
   */
class SharedUtilities
{
public:

    /**
         * @brief roundPriceToTick
         * @param price
         * @param mode
         * @param symbolData
         */
    template<class A,class B>
    static void roundPriceToTick(A &price ,
                                 CMD::OrderMode mode,
                                 const B &symbolData)
    {
        UNSIGNED_LONG tickDeviation = price % symbolData.tickSize;
        if( tickDeviation )
        {
            if( mode == CMD::OrderMode_BUY)
                price -= tickDeviation;
            else
                price += (symbolData.tickSize - tickDeviation);
        }

    }
};


}
#endif
