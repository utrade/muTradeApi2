#ifndef SHARED_COMMANDS_H
#define SHARED_COMMANDS_H
#include <sharedDefines.h>
#define EXCHANGE_ID_BASE 10000000

#define GET_SYMBOL_ID(scripCode, exchangeId) ((exchangeId)*EXCHANGE_ID_BASE + scripCode)

#define GET_SCRIP_CODE(symbolId) (symbolId % EXCHANGE_ID_BASE)

#define GET_EXCHANGE_ID(symbolId) ((CMD::ExchangeId)(symbolId/EXCHANGE_ID_BASE))

#endif
