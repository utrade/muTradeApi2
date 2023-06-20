#ifndef api2_Exceptions_h
#define api2_Exceptions_h

#include <exception>
#include <apiDataTypes.h>
#include <string>

namespace API2 {
  /**
   * @brief The UnknownTypeException struct
   */
  struct UnknownTypeException : public std::exception {

    /**
     * @brief what
     * @return
     */
    const char* what() const throw ();
  };

  /**
   * @brief The DuplicateKeyException struct
   */
  struct DuplicateKeyException : public std::exception {

    /**
     * @brief what
     * @return
     */
    const char* what() const throw ();
  };

  /**
   * @brief The MarketDataSubscriptionFailedException struct
   */
  struct MarketDataSubscriptionFailedException : public std::exception {
    /**
     * @brief what
     * @return
     */
    const char* what() const throw ();
  };

  /**
   * @brief The InstrumentNotFoundException struct
   */
  struct InstrumentNotFoundException : public std::exception {
    /**
     * @brief what
     * @return
     */
    const char* what() const throw ();
  };

  /**
   * @brief If security type is not valid
   * @return
   */
  struct InvalidInstrumentException : public std::exception {

    const char* what() const throw ();
  };

  /**
   * @brief The writeToDatabaseFailed struct
   */
  struct writeToDatabaseFailedException : public std::exception {
    /**
     * @brief what
     * @return
     */
    const char* what() const throw() ;
  };

  /**
   * @brief The LicenseNotAvailableException struct - exception if strategy couldn't be run
   *          due to license unavailability
   */
  struct LicenseNotAvailableException : public std::exception
  {
    /**
     * @brief errorText - error text generated in construction will be saved here
     */
    std::string errorText;

    /**
     * @brief LicenseNotAvailableException
     * @param dealerId  - dealer id for which strategy run
     * @param exchangeId  - exchange id for which license not available
     */
    LicenseNotAvailableException(
        API2::DATA_TYPES::CLIENT_ID dealerId,
        API2::DATA_TYPES::ExchangeId exchangeId);

    /**
     * @brief what  - returns exception error text
     * @return
     */
    const char* what() const throw ();
  };
}

#endif
