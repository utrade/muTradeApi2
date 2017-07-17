#ifndef SG_API2_SHARED_COMMANDS_H
#define SG_API2_SHARED_COMMANDS_H
#include <sharedDefines.h>
#include <boost/shared_ptr.hpp>
#define EXCHANGE_ID_BASE 10000000

#define GET_SYMBOL_ID(scripCode, exchangeId) ((exchangeId)*EXCHANGE_ID_BASE + scripCode)

#define GET_SCRIP_CODE(symbolId) (symbolId % EXCHANGE_ID_BASE)

#define GET_EXCHANGE_ID(symbolId) ((API2::DATA_TYPES::ExchangeId)(symbolId/EXCHANGE_ID_BASE))


namespace API2 
{
  struct AccountDetail
  {
    char _Account[ACCOUNT_FIELD_SIZE];
    SIGNED_LONG _TraderId;
    UNSIGNED_LONG _LocationId;
    UNSIGNED_CHARACTER _AccountType;

    void initialize();
    
    std::string dump() const;
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
    void setAccountId(const char *accountId);
    void setAccountType(char type);
    void setLocationId(UNSIGNED_LONG locationId);
    void setTraderId(SIGNED_LONG traderId);

    const char *getAccountId() const;
    const char getAccountType() const;
    SIGNED_LONG getTraderId() const;
    UNSIGNED_LONG getLocationId() const;
  };


  //typedef boost::shared_ptr<API2::AccountDetail> AccountDetailsPtr;
  //typedef API2::AccountDetail AccountDetail;


}



#endif
