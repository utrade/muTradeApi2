#ifndef SHARED_DEFINES_H
#define SHARED_DEFINES_H
#include <stdint.h>
#include <map>
#define EXCHANGE_ORDERID_SIZE 50
#define TRADEID_SIZE 50
#define SYMBOL_SIZE 24
#define SERIES_SIZE 20
#define API_REQUEST_SIZE 200
#define MAX_BUF_SIZE 2048
#define STRATEGY_TYPE_SIZE 3
#define STRATEGY_TYPE_SQNNO_SIZE 20

#define API_COMPILATION 1

typedef uint8_t UNSIGNED_CHARACTER;
typedef uint16_t UNSIGNED_SHORT;
typedef uint32_t UNSIGNED_INTEGER;
typedef uint64_t UNSIGNED_LONG;
typedef int64_t SIGNED_LONG;
typedef int32_t SIGNED_INTEGER;
typedef std::map<UNSIGNED_LONG, UNSIGNED_LONG> MapULong;
typedef MapULong::const_iterator MapULongIter;



#define ACCOUNT_FIELD_SIZE 12
#define MARKET_DATA_DEPTH_MAX 11

#define stringify( name ) # name
#define varString(name) stringify(name)<<":"<<name

#define OMM_DUMP_LOGS 0
#define MKTDATA_EVENT 0
#define USE_EXCHANGE_ORDER_ID_FOR_REFERENCE 1

#endif
