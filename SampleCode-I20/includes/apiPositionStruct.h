#ifndef API_POSITION_STRUCT_H
#define API_POSITION_STRUCT_H
#include <apiDataTypes.h>
#include <cmdDefines.h>
#include <sstream>
#include <boost/unordered_map.hpp>

namespace API2
{
  class PositionStruct
  {
    /*
     * --------------------------------------------------
     * | TotalBuyQuantity   | These four fields contains|
     * | TotalSellQuantity  | DAY + OLD position        |
     * | TotalBuyValue      | i.e. Intraday + Previous  |
     * | TotalSellValue     | day position              |
     * --------------------------------------------------
     *
     * --------------------------------------------------
     * | OldBuyQuantity   | These four fields contains  |
     * | OldSellQuantity  | OLD position.               |
     * | OldBuyValue      | i.e. Previous day position. |
     * | OldSellValue     |                             |
     * --------------------------------------------------
     *
     * Previous day position can also be the cumulative of past day positions
     * For e.g.
     * - Take today day as N
     *   N will be Day position or Intraday position
     * - And ( N - 1 ) day will be old position which can also be
     *   the cumulative of ( N - 1 ) + ( N - 2 ) + ..... + ( N - X ).
     */
    CREATE_FIELD( DATA_TYPES::QTY, TotalBuyQuantity );
    CREATE_FIELD( DATA_TYPES::QTY, TotalSellQuantity );
    CREATE_FIELD( DATA_TYPES::VOLUME, TotalBuyValue );
    CREATE_FIELD( DATA_TYPES::VOLUME, TotalSellValue );
    CREATE_FIELD( DATA_TYPES::QTY, OldBuyQuantity );
    CREATE_FIELD( DATA_TYPES::QTY, OldSellQuantity );
    CREATE_FIELD( DATA_TYPES::VOLUME, OldBuyValue );
    CREATE_FIELD( DATA_TYPES::VOLUME, OldSellValue );

    public:

    PositionStruct():
      _TotalBuyQuantity( 0 ),
      _TotalSellQuantity( 0 ),
      _TotalBuyValue( 0 ),
      _TotalSellValue( 0 ),
      _OldBuyQuantity( 0 ),
      _OldSellQuantity( 0 ),
      _OldBuyValue( 0 ),
      _OldSellValue( 0 )
    {
    }

    PositionStruct(
        DATA_TYPES::QTY totalBuyQuantity,
        DATA_TYPES::QTY totalSellQuantity,
        DATA_TYPES::VOLUME totalBuyValue,
        DATA_TYPES::VOLUME totalSellValue,
        DATA_TYPES::QTY oldBuyQuantity,
        DATA_TYPES::QTY oldSellQuantity,
        DATA_TYPES::VOLUME oldBuyValue,
        DATA_TYPES::VOLUME oldSellValue
        )
      :
        _TotalBuyQuantity( totalBuyQuantity ),
        _TotalSellQuantity( totalSellQuantity ),
        _TotalBuyValue( totalBuyValue ),
        _TotalSellValue( totalSellValue ),
        _OldBuyQuantity( oldBuyQuantity ),
        _OldSellQuantity( oldSellQuantity ),
        _OldBuyValue( oldBuyValue ),
        _OldSellValue( oldSellValue )
    {
    }

    std::string getPositionString()
    {
      std::ostringstream positionDump;

      positionDump << "\n _______________PositionStruct_________________"
        << "\n TotalBuyQuantity  : " << _TotalBuyQuantity
        << "\n TotalSellQuantity : " << _TotalSellQuantity
        << "\n TotalBuyValue     : " << _TotalBuyValue
        << "\n TotalSellValue    : " << _TotalSellValue
        << "\n OldBuyQuantity    : " << _OldBuyQuantity
        << "\n OldSellQuantity   : " << _OldSellQuantity
        << "\n OldBuyValue       : " << _OldBuyValue
        << "\n OldSellValue      : " << _OldSellValue << "\n";

      return positionDump.str();
    }

  };

  typedef boost::unordered_map< SIGNED_LONG, PositionStruct > SymbolIdAndPositionStructHash;
  typedef boost::unordered_map< SIGNED_INTEGER, SymbolIdAndPositionStructHash > 
    DealerIdVsSymbolIdAndPositionStructHash;

}// END OF NAMESPACE API2
#endif

