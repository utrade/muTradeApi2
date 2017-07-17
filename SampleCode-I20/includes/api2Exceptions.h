#ifndef api2_Exceptions_h
#define api2_Exceptions_h
#include <exception>
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
}

#endif
