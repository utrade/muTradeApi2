#ifndef DBStringConverter_h
#define DBStringConverter_h
#include <string>
#include <sharedDefines.h>
#include <sharedCommands.h>


namespace API2
{
  namespace DBConverter
  {
    std::string getDBString(const std::string &);
    std::string getDBString(const char *);
    std::string getDBString(const UNSIGNED_LONG );
    std::string getDBString(const SIGNED_LONG );
    std::string getDBString(const UNSIGNED_CHARACTER );
    std::string getDBString(const char );
    std::string getDBString(const UNSIGNED_INTEGER );
    std::string getDBString(const int );
    std::string getDBString(const UNSIGNED_SHORT );
    std::string getDBString(const short );
    std::string getDBString(const AccountDetail &);
    std::string getDBString(const StringList &);
  }
}
#endif
