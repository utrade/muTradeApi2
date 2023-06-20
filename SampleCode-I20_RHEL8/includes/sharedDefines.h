#ifndef SHARED_DEFINES_H
#define SHARED_DEFINES_H
#include <stdint.h>
#include <map>
#include <string>
#include <set>
#include <list>
#include <string.h>
#include <unordered_map>
#define EXCHANGE_ORDERID_SIZE 50
#define CONF_EXCHANGE_ORDERID_SIZE 50
#define TRADEID_SIZE 25
#define SYMBOL_SIZE 24
#define SERIES_SIZE 20
#define API_REQUEST_SIZE 200
#define MAX_BUF_SIZE 8192
#define STRATEGY_TYPE_SIZE 3
#define STRATEGY_TYPE_SQNNO_SIZE 9
#define PRIMARY_CLIENT_CODE_SIZE 20
#define EXCHANGE_CLIENT_CODE_SIZE 20
#define PARTICIPANT_CODE_SIZE 13
#define ERROR_TEXT_SIZE 350
#define FIX_ORDERID_SIZE 20
#define PAN_SIZE 11
#define BUF_SIZE_60 60
#define API_COMPILATION 1
#define ALGO_NAME_SIZE 30

#ifdef FRONTEND_COMPILATION
#define MULTIPLIER_ONE 1
#define MULTIPLIER_TWO 100
#define MULTIPLIER_FOUR 10000
#define MULTIPLIER_SIX 1000000

#define PRECISION_ZERO 0
#define PRECISION_TWO 2
#define PRECISION_FOUR 4
#define PRECISION_SIX 6
#define BUFFSIZE 1024
#endif 

typedef uint8_t UNSIGNED_CHARACTER;
typedef uint16_t UNSIGNED_SHORT;
typedef uint32_t UNSIGNED_INTEGER;
typedef uint32_t COMMAND_CATEGORY_TYPE;
typedef uint32_t PACKET_LENGTH_TYPE;

#ifdef FRONTEND_COMPILATION
#if _WIN32
typedef uint64_t UNSIGNED_LONG;
typedef int64_t SIGNED_LONG;
#elif __linux__
typedef unsigned long long UNSIGNED_LONG;
typedef long long SIGNED_LONG;
#endif
#else
typedef uint64_t UNSIGNED_LONG;
typedef int64_t SIGNED_LONG;
#endif

typedef int32_t SIGNED_INTEGER;
typedef std::map<UNSIGNED_LONG, UNSIGNED_LONG> MapULong;
typedef std::set<std::string> StringSet;
typedef std::list<std::string> StringList;
typedef MapULong::const_iterator MapULongIter;

#define BUF_SIZE_60 60
#define GENERATED_CLORDID_SIZE 40
#define ACCOUNT_FIELD_SIZE 12
#define MARKET_DATA_DEPTH_MAX 11

#define stringify( name ) # name
#define STRINGIFY(x) #x
#define varString(name) stringify(name)<<":"<<name

#define OMM_DUMP_LOGS 0
#define MKTDATA_EVENT 0
#define USE_EXCHANGE_ORDER_ID_FOR_REFERENCE 1

#ifdef FRONTEND_COMPILATION
/**
 *usede to copy data from a string to other string
 **/
inline void  safeStringCpyDll(char *dest,const char*source,size_t srcSize)
{
  strncpy(dest,source,srcSize);
}
#endif 

#endif
