#ifndef SG_API2_SHARED_COMMANDS_H
#define SG_API2_SHARED_COMMANDS_H

#include <sharedDefines.h>
#include <cmdDefines.h>
#include <apiConstants.h>
#include <apiDataTypes.h>
#include <sstream>

#ifndef FRONTEND_COMPILATION

#include <boost/shared_ptr.hpp>
#include <cstring>

#else

#include <qvariant.h>
#include <iostream>

#endif


#ifndef FRONTEND_COMPILATION

#define GET_SYMBOL_ID_NEW(scripCode, exchangeId, sourceId) ::API2::getSymbolId(sourceId, exchangeId, scripCode)

#define GET_EXCHANGE_ID_NEW(symbolId) ((API2::DATA_TYPES::ExchangeId)(::API2::getExchangeId(symbolId)))

#define GET_SYMBOL_ID(scripCode, exchangeId) ::API2::getSymbolId(API2::CONSTANTS::CMD_SourceId_DEFAULT, exchangeId, scripCode)

#define GET_EXCHANGE_SYMBOL_ID(symbolId) symbolId

#define GET_SCRIP_CODE(symbolId) ::API2::getScripCode(symbolId)

#define GET_EXCHANGE_ID(symbolId) ((API2::DATA_TYPES::ExchangeId)(::API2::getExchangeId(symbolId)))

#define IS_CTP_EXCHANGE(symbolId) \
  (::API2::getSourceId(symbolId) == API2::CONSTANTS::CMD_SourceId_CTP)

#define GET_EXCHANGE_ID_API(symbolId) ((API2::DATA_TYPES::ExchangeId)(::API2::getExchangeId(symbolId)))

#define IS_CTP_EXCHANGE_ID(exchangeId) \
  ((exchangeId == API2::CONSTANTS::CMD_ExchangeId_CFFEX) || \
   (exchangeId == API2::CONSTANTS::CMD_ExchangeId_CZCE) || \
   (exchangeId == API2::CONSTANTS::CMD_ExchangeId_DCE) || \
   (exchangeId == API2::CONSTANTS::CMD_ExchangeId_SHFE))

#else

#define GET_SYMBOL_ID_NEW(scripCode, exchangeId, sourceId) ::SG::getSymbolId(sourceId, exchangeId, scripCode)

#define GET_EXCHANGE_ID_NEW(symbolId) ((CMD::ExchangeId)(::SG::getExchangeId(symbolId)))

#define GET_SYMBOL_ID(scripCode, exchangeId) ::SG::getSymbolId(CMD::SourceId_DEFAULT, exchangeId, scripCode)

#define GET_EXCHANGE_SYMBOL_ID(symbolId) symbolId

#define GET_SCRIP_CODE(symbolId) ::SG::getScripCode(symbolId)

#if API_COMPILATION == 0

#define GET_EXCHANGE_ID(symbolId) ((CMD::ExchangeId)(::SG::getExchangeId(symbolId)))

#define GET_SOURCE_ID(symbolId) ((CMD::SourceId)(::SG::getSourceId(symbolId)))

#define IS_CTP_EXCHANGE(symbolId) \
  (::SG::getSourceId(symbolId) == CMD::SourceId_CTP)

#define IS_CTP_EXCHANGE_ID(exchangeId) \
  ((exchangeId == CMD::ExchangeId_CFFEX) || \
   (exchangeId == CMD::ExchangeId_CZCE) || \
   (exchangeId == CMD::ExchangeId_DCE) || \
   (exchangeId == CMD::ExchangeId_SHFE))

#else

#define GET_EXCHANGE_ID(symbolId) ((API2::DATA_TYPES::ExchangeId)(::SG::getExchangeId(symbolId)))

#define IS_CTP_EXCHANGE(symbolId) \
  (::SG::getSourceId(symbolId) == API2::CONSTANTS::CMD_SourceId_CTP)

#define IS_CTP_EXCHANGE_ID(exchangeId) \
  ((exchangeId == API2::CONSTANTS::CMD_ExchangeId_CFFEX) || \
   (exchangeId == API2::CONSTANTS::CMD_ExchangeId_CZCE) || \
   (exchangeId == API2::CONSTANTS::CMD_ExchangeId_DCE) || \
   (exchangeId == API2::CONSTANTS::CMD_ExchangeId_SHFE))

#endif

const short CommandCategory_STRATEGY_COMMAND = 4;

#endif


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
    
    AccountDetail(const AccountDetail &other) : 
      _TraderId(other._TraderId),
      _LocationId(other._LocationId),
      _AccountType(other._AccountType)
    {
      strncpy(_primaryClientCode,other._primaryClientCode,PRIMARY_CLIENT_CODE_SIZE);
    }
    
    AccountDetail& operator =(const AccountDetail &other)
    {
      strncpy(_primaryClientCode,other._primaryClientCode,PRIMARY_CLIENT_CODE_SIZE);
      _TraderId = other._TraderId;
      _LocationId = other._LocationId;
      _AccountType = other._AccountType;
      return *this;
    }

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
    std::string getString();
    void setValuesFromString(const std::string& str);
  };

  //typedef boost::shared_ptr<API2::AccountDetail> AccountDetailsPtr;
  //typedef API2::AccountDetail AccountDetail;

  // STRATEGY_COMMAND
  class StrategyCommand
  {
    public:
      StrategyCommand();

      explicit StrategyCommand(const char* buf);

      int serialize(char* buf);

      void setCommandCategory(COMMAND_CATEGORY_TYPE cm);

      COMMAND_CATEGORY_TYPE getCommandCategory();

      UNSIGNED_INTEGER getStrategyId() const;

      void setStrategyId(UNSIGNED_INTEGER strategyId);

      void dump();
    private:
      COMMAND_CATEGORY_TYPE _commandCategory;
      UNSIGNED_INTEGER _strategyId;
  };

  class ExchangeAdapterDetails
  {
    /**
     * @brief _TraderId - sent to exchange for every order
     */
    CREATE_FIELD(SIGNED_INTEGER,TraderId);
    /**
     * @brief _LocationId - sent to exchange for every order
     */
    CREATE_FIELD(SIGNED_LONG,LocationId);
    /**
     * @brief _AccountType -  whether it's a normal client or 
     *                        a pro / institutional client ( broker )
     */
    CREATE_ENUM_CLASS_FIELD(API2::DATA_TYPES::AccountType,AccountType);
    /**
     * @brief _PrimaryClientCode - client code sent to exchange for client identification
     */
    CREATE_FIELD_CHAR(PrimaryClientCode,PRIMARY_CLIENT_CODE_SIZE);
    /**
     * @brief _OldPrimaryClientCode - old client code, used in case of trade modification
     */
    CREATE_FIELD_CHAR(OldPrimaryClientCode,PRIMARY_CLIENT_CODE_SIZE);
    /**
     * _ExchangeId - exchange id of the exchange in which order is being placed
     */
    CREATE_FIELD(API2::DATA_TYPES::ExchangeId,ExchangeId);
    /**
     * @brief _SegmentType - segment under which order is placed
     */
    CREATE_ENUM_CLASS_FIELD(API2::DATA_TYPES::ClientSegmentType,SegmentType);
    /**
     * @brief _ExchangeClientCode - parent client code( UCC ) for the client,
     *                              sent to exchange
     */
    CREATE_FIELD_CHAR(ExchangeClientCode,EXCHANGE_CLIENT_CODE_SIZE);
    /**
     * @brief _ParticipantCode - sent to exchange for every order
     */
    CREATE_FIELD_CHAR(ParticipantCode,PARTICIPANT_CODE_SIZE);
    /**
     * @brief _OldExchangeClientCode - old parent code( UCC ), used in trade modification
     */
    CREATE_FIELD_CHAR(OldExchangeClientCode,EXCHANGE_CLIENT_CODE_SIZE);

    /**
     * @brief PAN - Exchange Client Code PAN detail
     */
    CREATE_FIELD_CHAR(PAN,PAN_SIZE);

    public:

    /**
     * @brief ExchangeAdapterDetails - default constructor
     */
    ExchangeAdapterDetails();

    /**
     * @brief ~ExchangeAdapterDetails - destructor
     */
    virtual ~ExchangeAdapterDetails();

    /**
     * @brief getString     - get the string containing data members
     *
     * @return std::string  - the string containing data members
     */
    std::string getString() const;

    /**
     * @brief getStringCSV - get the string containing data members seperated by commas
     *
     * @return std::string - the string containing data members seperated by commas
     */
    std::string getStringCSV() const;

    /**
     * @brief ExchangeAdapterDetails  - copy constructor
     *
     * @param other                   - object which is to be copied into *this
     */
    ExchangeAdapterDetails(const ExchangeAdapterDetails &other);

    /**
     * @brief operator= - performs same function as copy constructor with the difference
     *                    that it returns * this
     *
     * @param other     - object which is to be copied into *this
     */
    ExchangeAdapterDetails& operator =(const ExchangeAdapterDetails &other);
  };
}

#endif
