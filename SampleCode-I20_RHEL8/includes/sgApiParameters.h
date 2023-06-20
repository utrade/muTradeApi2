#ifndef SG_API_PARAMETERS_H
#define SG_API_PARAMETERS_H

namespace SG
{
  class AccessParameters;
}

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
    int getClientId() const;
    /**
       * @brief getId
       * @return
       */
    int getId();

    /**
     * @brief getInfo, Provides the Strategy Parameters
     * @return
     */
    void* getBaseInfo();

    /**
     * @brief StrategyParameters
     */
    StrategyParameters();

    /**
     * @brief ~StrategyParameters
     */
    virtual ~StrategyParameters();

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

    /**
     * @brief _baseInfo
     */
    void* _baseInfo;

    /**
     * @brief _accessParameters - access allowed in strategy
     */
    SG::AccessParameters *_accessParameters = nullptr;
  };
}
#endif
