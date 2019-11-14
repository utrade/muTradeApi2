#ifndef SHARED_UTILITIES_H
#define SHARED_UTILITIES_H
#include <sharedDefines.h> 
#include <sharedCommands.h>
#include <sgSymbolDataDefines.h>
#include <api2Exceptions.h>
namespace API2
{

  /**
   * @brief The SharedUtilities class
   */
  class SharedUtilities
  {
  public:

    /**
         * @brief roundPriceToTick
         * @param price
         * @param mode
         * @param symbolData
         */
    template<class A,class B>
      static void roundPriceToTick(A &price ,
          API2::DATA_TYPES::OrderMode mode,
          const B &symbolData)
      {
        if(symbolData.tickSize == 0)
        {
          throw UnknownTypeException();
          return;
        }
        SIGNED_LONG tickDeviation = price % symbolData.tickSize;
        if( tickDeviation )
        {
          if( mode == API2::CONSTANTS::CMD_OrderMode_BUY)
            price -= tickDeviation;
          else
            price += (symbolData.tickSize - tickDeviation);
        }
      }

    static inline time_t getCurrentTimeToMidNightTimeDiffInSeconds()
    {
      time_t rawTime = time(NULL);
      struct tm timeInfo;
      localtime_r(&rawTime, &timeInfo);
      timeInfo.tm_hour = 0;
      timeInfo.tm_min  = 0;
      timeInfo.tm_sec  = 0;
      return difftime(rawTime,mktime(&timeInfo));
    }

    static inline int64_t convertLocalDayTimeToUTC(const time_t localDayTime)
    {
      time_t rawTime = time(NULL);  //  UTC time
      struct tm timeInfo;
      localtime_r(&rawTime, &timeInfo); //  get local time from UTC time
      //  reset the hour, min and second to 0
      timeInfo.tm_hour = 0;
      timeInfo.tm_min  = 0;
      timeInfo.tm_sec  = 0;
      //  return UTC time of day start + localDayTime
      //  this is the UTC
      return mktime(&timeInfo) + localDayTime;
    }

    static inline std::string getFormattedTime( const time_t& dateTime,
        const std::string& format,
        const uint32_t& timezone)
    {
      char buffer[100];
      std::tm *convertedTime;

      const time_t dateTimeTMAdjusted = dateTime + timezone;
      convertedTime = gmtime( &dateTimeTMAdjusted );

      strftime(buffer,100, format.c_str(), convertedTime);
      return buffer;
    }
  };


}
#endif
