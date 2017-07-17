#ifndef SG_API2_SHARED_COMMANDS_H
#define SG_API2_SHARED_COMMANDS_H
#include <sharedDefines.h>
#include <boost/shared_ptr.hpp>

#define GET_SYMBOL_ID_NEW(scripCode, exchangeId, sourceId) ::API2::getSymbolId(sourceId, exchangeId, scripCode)

#define GET_EXCHANGE_ID_NEW(symbolId) ((API2::DATA_TYPES::ExchangeId)(::API2::getExchangeId(symbolId)))

#define GET_SYMBOL_ID(scripCode, exchangeId) ::API2::getSymbolId(CMD::SourceId_DEFAULT, exchangeId, scripCode)

//#define GET_EXCHANGE_SYMBOL_ID(symbolId) (((int64_t)symbolId) % SOURCE_ID_BASE)
#define GET_EXCHANGE_SYMBOL_ID(symbolId) symbolId

#define GET_SCRIP_CODE(symbolId) ::API2::getScripCode(symbolId)

#define GET_EXCHANGE_ID(symbolId) ((API2::DATA_TYPES::ExchangeId)(::API2::getExchangeId(symbolId)))

namespace API2 
{
  struct AccountDetail
  {
    char _primaryClientCode[PRIMARY_CLIENT_CODE_SIZE];
    SIGNED_LONG _TraderId;
    UNSIGNED_LONG _LocationId;
    UNSIGNED_CHARACTER _AccountType;

    void initialize();
    
    std::string dump() const;
    std::string getString() const;

    AccountDetail();

    AccountDetail(const char *account,
        char accountType,
        const UNSIGNED_LONG &locationId,
        const SIGNED_LONG &traderId
        );

    void initialize(const char *account,
        char accountType,
        const UNSIGNED_LONG &locationId,
        const SIGNED_LONG &traderId
        );
    void setPrimaryClientCode(const char *);
    void setAccountType(char type);
    void setLocationId(UNSIGNED_LONG locationId);
    void setTraderId(SIGNED_LONG traderId);

    const char *getPrimaryClientCode() const;
    const char getAccountType() const;
    SIGNED_LONG getTraderId() const;
    UNSIGNED_LONG getLocationId() const;
  };


  //typedef boost::shared_ptr<API2::AccountDetail> AccountDetailsPtr;
  //typedef API2::AccountDetail AccountDetail;

  // STRATEGY_COMMAND
  class StrategyCommand
  {
    public:
      StrategyCommand();

      StrategyCommand(const char* buf);

      int serialize(char* buf);

      void setCommandCategory(UNSIGNED_CHARACTER cm);

      UNSIGNED_CHARACTER getCommandCategory();

      UNSIGNED_INTEGER getStrategyId();

      void setStrategyId(UNSIGNED_INTEGER strategyId);

      void dump();
      //std::string getString();
    private:
      UNSIGNED_CHARACTER _commandCategory;
      UNSIGNED_INTEGER _strategyId;
  };
}

#endif
