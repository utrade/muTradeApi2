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
        }
        SIGNED_LONG tickDeviation = price % symbolData.tickSize;
        if( tickDeviation )
        {
          //different handling for round up/down of price in spread contracts
          if(symbolData.contractType == API2::CONSTANTS::CMD_ContractType_SPREAD)
          {
            if( mode == API2::CONSTANTS::CMD_OrderMode_BUY)
            {
              if(price > 0)
              {
                price -= tickDeviation;
              }
              else
              {
                //different formula for round down of negative price
                price -= (symbolData.tickSize - tickDeviation);
              }
            }
            else
            {
              if(price > 0)
              {
                price += (symbolData.tickSize - tickDeviation);
              }
              else
              {
                //different formula for round up of negative price
                price += tickDeviation;
              }
            }
          }
          else // for all other contract types
          {
            if( mode == API2::CONSTANTS::CMD_OrderMode_BUY)
              price -= tickDeviation;
            else
              price += (symbolData.tickSize - tickDeviation);
          }
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

    /**
     * @brief getTimeToExpireInYears
     * @param data
     * @param expiryDayType
     *    - If CMD_ExpiryDay_INCLUDE passed then the Expiry day will be included i.e. 24 hours.
     *    - If CMD_ExpiryDay_HALF_INCLUDE passed then only Half Expiry day included i.e. 12 hours.
     *    - If CMD_ExpiryDay_INCLUDE_ON_EXPIRY passed then Expiry day included only if current date is also Expiry.
     *    - If CMD_ExpiryDay_EXCLUDE passed then Expiry day will not be included.
     * @return Return time of maturity of contract in years
     */
    static inline double getTimeToExpireInYears(
        const API2::SymbolStaticData *data,
        const API2::DATA_TYPES::EXPIRYDAY_TYPE expiryDayType )
    {
      if( nullptr == data ||
          data->securityType == API2::CONSTANTS::CMD_SecurityType_COMMON_STOCK )
      {
        return 0;
      }

      time_t gmTime = time(NULL);
      struct tm *currTime = localtime(&gmTime);

      struct std::tm currentDate = { 0, 0, 0, currTime->tm_mday, currTime->tm_mon, currTime->tm_year };

      int maturityYear = (data->maturityYearmon /100) - 1900;  // This is year-1900, so 112 = 2012
      int maturityMonth = data->maturityYearmon % 100 -1 ;  // Month required from 0 - 11
      int maturityDay = data->maturityDay;

      struct std::tm maturityDate = { 0, 0, 0, maturityDay, maturityMonth, maturityYear };

      std::time_t currentTime = std::mktime(&currentDate);
      std::time_t maturityTime = std::mktime(&maturityDate);

      if ( currentTime != -1 && maturityTime != -1 )
      {
        double day = 0;
        switch ( expiryDayType )
        {
          case API2::CONSTANTS::CMD_ExpiryDay_INCLUDE_ON_EXPIRY:
            if(currentTime != maturityTime)
            {
              day = 0;
              break;
            }
          case API2::CONSTANTS::CMD_ExpiryDay_INCLUDE:
            day = 24 * 60 * 60;
            break;
          case API2::CONSTANTS::CMD_ExpiryDay_HALF_INCLUDE:
            day = 12 * 60 * 60;
            break;
          default:
            day = 0;
            break;
        }
        return ( (std::difftime(maturityTime, currentTime) + day) / (365 * 24 * 60 * 60) );
      }

      return 0;
    }

    /**
     * @brief increasePrecision - Convert the price from scrip precision to Rupees.
     * @param price
     * @param staticData
     * @return
     */
    static inline double increasePrecision( const API2::DATA_TYPES::PRICE price, API2::SymbolStaticData* staticData  )
    {
      return ( double( price ) / pow( 10, staticData->scripPrecision ) );
    }

    /**
     * @brief decreasePrecision - Convert the price from Rupees to scrip precision.
     * @param price
     * @param staticData
     * @return
     */
    static inline API2::DATA_TYPES::PRICE decreasePrecision( const double price, API2::SymbolStaticData* staticData )
    {
      return ( price * pow( 10, staticData->scripPrecision ) );
    }

  };


}
#endif
