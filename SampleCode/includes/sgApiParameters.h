#ifndef SG_API_PARAMETERS_H
#define SG_API_PARAMETERS_H
namespace API2
{
  /**
 * @brief The StrategyParameters class provides the Basic Strategy Parameters, StrategyId and ClientId.\n
 * Stratgy Parameters are provided by StrategyParameters::getInfo()
 */
  class StrategyParameters
  {
  public:
    /**
       * @brief getInfo, Provides the Strategy Parameters
       * @return
       */
    void* getInfo();

    /**
       * @brief getClientId
       * @return
       */
    int getClientId() ;
    /**
       * @brief getId
       * @return
       */
    int getId();

    StrategyParameters():
      _clientId(-1),
      _info(0),
      _id(-1)
    {}
  protected:
    /**
       * @brief _clientId
       */
    int _clientId;

    /**
       * @brief _info
       */
    void* _info;
    /**
       * @brief _id
       */
    int _id;



  };
}
#endif
