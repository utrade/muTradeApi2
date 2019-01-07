#ifndef API_POSITION_STRUCT_H
#define API_POSITION_STRUCT_H
#include <apiDataTypes.h>
#include <cmdDefines.h>
#include <boost/unordered_map.hpp>

namespace API2
{
  class PositionStruct
  {
    CREATE_FIELD( DATA_TYPES::QTY, TotalBuyQuantity );
    CREATE_FIELD( DATA_TYPES::QTY, TotalSellQuantity );
    CREATE_FIELD( DATA_TYPES::VOLUME, TotalBuyValue );
    CREATE_FIELD( DATA_TYPES::VOLUME, TotalSellValue );

    public:

    PositionStruct():
      _TotalBuyQuantity( 0 ),
      _TotalSellQuantity( 0 ),
      _TotalBuyValue( 0 ),
      _TotalSellValue( 0 )
    {
    }

    PositionStruct(
        DATA_TYPES::QTY totalBuyQuantity,
        DATA_TYPES::QTY totalSellQuantity,
        DATA_TYPES::VOLUME totalBuyValue,
        DATA_TYPES::VOLUME totalSellValue
        )
      :
        _TotalBuyQuantity( totalBuyQuantity ),
        _TotalSellQuantity( totalSellQuantity ),
        _TotalBuyValue( totalBuyValue ),
        _TotalSellValue( totalSellValue )
    {
    }

  };

  typedef boost::unordered_map< SIGNED_LONG, PositionStruct > SymbolIdAndPositionStructHash;
  typedef boost::unordered_map< SIGNED_INTEGER, SymbolIdAndPositionStructHash > 
    DealerIdVsSymbolIdAndPositionStructHash;

}// END OF NAMESPACE API2
#endif

