#ifndef STRATEGY_WAVE_H
#define STRATEGY_WAVE_H

#include <cmdDefines.h>
#include <apiDataTypes.h>
#include <apiConstants.h>
#include <cstring>

namespace ST
{

  /*
   * brief StrategyWave: Consists details regarding strategy ran from a care order
   */
  class StrategyWave
  {

    CREATE_FIELD( UNSIGNED_LONG, CareOrderId );
    CREATE_FIELD( UNSIGNED_SHORT, LineId );
    CREATE_FIELD( UNSIGNED_SHORT, WaveId );
    CREATE_FIELD( API2::DATA_TYPES::TransactionType, TransactionType );
    CREATE_FIELD( API2::DATA_TYPES::Service, Service );
    CREATE_FIELD_CHAR( AlgoName, ALGO_NAME_SIZE );
    CREATE_FIELD( API2::DATA_TYPES::PRICE, LimitPrice );
    CREATE_FIELD( API2::DATA_TYPES::QTY, TotalQty );
    CREATE_FIELD( API2::DATA_TYPES::STRATEGY_ID, StrategyId );
    CREATE_FIELD( API2::DATA_TYPES::CLORDER_ID, ClOrderId );
    CREATE_FIELD( bool, IsTransactionSuccessful );

    public:

    StrategyWave():
      _CareOrderId(0),
      _LineId(0),
      _WaveId(0),
      _TransactionType( API2::CONSTANTS::CMD_TransactionType_MAX ),
      _Service( API2::CONSTANTS::Srvce_MAX ),
      _LimitPrice(0),
      _TotalQty(0),
      _StrategyId(0),
      _ClOrderId(0),
      _IsTransactionSuccessful(true)
    {
      setAlgoName("");
    }

    StrategyWave(const StrategyWave& other);

    StrategyWave( const char* buf, int &offset );

    std::string getString() const
    {
      std::ostringstream oss;
      oss << "\n ____________Wave Details _____________\n";
      oss << "\n CareOrderId: " << getCareOrderId();
      oss << "\n LineId: " << getLineId();
      oss << "\n WaveId: " << getWaveId();
      oss << "\n TransactionType: " << getTransactionType();
      oss << "\n Service: " << getService();
      oss << "\n LimitPrice: " << getLimitPrice();
      oss << "\n TotalQty: " << getTotalQty();
      oss << "\n StrategyId: " << getStrategyId();
      oss << "\n ClOrderId: " << getClOrderId();
      oss << "\n IsTransactionSuccessful: " << getIsTransactionSuccessful();
      oss << "\n AlgoName: " << getAlgoName();
      return oss.str();
    }

    void serializeStrategyWave(char *buf, int& bytes);

    void deserializeStrategyWave( const char* buf, int &offset );

  }; // StrategyWave

} //namespace ST

#endif //STRATEGY_WAVE_H
