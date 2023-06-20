#ifndef IV_GREEK_INTERFACE_H
#define IV_GREEK_INTERFACE_H

#include <apiDataTypes.h>
#include <apiConstants.h>
#include <cmdDefines.h>

namespace API2 {

  struct SymbolStaticData;

  namespace COMMON {

    class Instrument;

    /**
     * @brief The IvGreekValues class
     * @description : This structure will be use in calculating Greeks with the following inputs
     *
     *                -- INPUT values which are required to be set --
     * 1. InstrumentPtr - Instrument symbol for which the IV need to be calculated.
     *                  - And its should be Call or Put.
     * 2. SpotPrice - SpotPrice of underlying symbol in scrip precision
     *              - If scrip precision is 2 and actual price is 123.45 then
     * 3. InterestRate - Interest rate in percentage(%)
     *                 - i.e. for 25% value of 0.25 need to pass.
     * 4. IvValue - IV in percentage(%).
     * 5. UnderlyingSymbolId - For which the spot price need to be fetch.
     * 6. ExpiryDayType - Default value CMD_ExpiryDay_EXCLUDE in constructor
     *    - If CMD_ExpiryDay_INCLUDE passed then the Expiry day will be included i.e. 24 hours.
     *    - If CMD_ExpiryDay_HALF_INCLUDE passed then only Half Expiry day included i.e. 12 hours.
     *    - If CMD_ExpiryDay_INCLUDE_ON_EXPIRY passed then Expiry day included only if current date is also Expiry.
     *    - If CMD_ExpiryDay_EXCLUDE passed then Expiry day will not be included.
     * 7. ReferenceSpotPriceType - Default Value API2::CONSTANTS::ReferenceSpotPrice_LTP in constructor.
     * @note - Underlying price is getting fetch through API::COMMON::getSymbolSpotPrice which will add latency
     *       - If snapshot is disable then this method won't work as spot price can't be fetch.
     *
     *              -- OUTPUT will be fetch after this class passed through API2::COMMON::getGreekValues --
     * 1. Delta - Rate of change of Option price w.r.t to underlying asset
     * 2. Gamma - Rate of change of Delta
     * 3. Theta - Time decay
     * 4. Vega  - Sensitivity to volatility
     * 5. Rho   - Sensitivity to interest rates
     */
    class IvGreekValues {

      //Inputs required to calculate greek values
      CREATE_FIELD_PTR( API2::COMMON::Instrument, InstrumentPtr );
      CREATE_FIELD( API2::DATA_TYPES::PRICE, SpotPrice );
      CREATE_FIELD( API2::DATA_TYPES::INTEREST_RATE, InterestRate );
      CREATE_FIELD( API2::DATA_TYPES::IMPLIED_VOLATILITY, IvValue );
      CREATE_FIELD( API2::DATA_TYPES::SYMBOL_ID, UnderlyingSymbolId );
      CREATE_FIELD( API2::DATA_TYPES::EXPIRYDAY_TYPE, ExpiryDayType );
      CREATE_FIELD( API2::DATA_TYPES::REFERENCE_SPOT_PRICE_TYPE, ReferenceSpotPriceType );

      //Output
      CREATE_FIELD( API2::DATA_TYPES::GREEK, Delta );
      CREATE_FIELD( API2::DATA_TYPES::GREEK, Gamma );
      CREATE_FIELD( API2::DATA_TYPES::GREEK, Theta );
      CREATE_FIELD( API2::DATA_TYPES::GREEK, Vega );
      CREATE_FIELD( API2::DATA_TYPES::GREEK, Rho );

      public:
      IvGreekValues() = delete;
      IvGreekValues(
          API2::COMMON::Instrument* instrument,
          API2::DATA_TYPES::SYMBOL_ID underlyingSymbolId,
          API2::DATA_TYPES::PRICE spotPrice,
          API2::DATA_TYPES::INTEREST_RATE interestRate,
          API2::DATA_TYPES::IMPLIED_VOLATILITY ivValue,
          API2::DATA_TYPES::EXPIRYDAY_TYPE expiryDayType = API2::CONSTANTS::CMD_ExpiryDay_EXCLUDE,
          API2::DATA_TYPES::REFERENCE_SPOT_PRICE_TYPE referenceSpotPriceType = API2::CONSTANTS::ReferenceSpotPrice_LTP );
    };

    class IvGreekInterface {

      public:
        IvGreekInterface() = delete;

        /**
         * @brief getIVForOption
         * @param retIvValue - IV will be return by this reference variable in percentage(%)
         *                   - i.e. if IV is 256.99 then it will return 2.5699.
         * @param instrument - Instrument symbol for which the IV need to be calculated.
         *                   - And its should be Call or Put.
         * @param spotPrice - SpotPrice of underlying symbol in scrip precision
         *                  - If scrip precision is 2 and actual price is 123.45 then
         *                  - price in scrip precision 12345( i.e. 123.45 * 100 )
         * @param interestRate - Interest rate in percentage(%)
         *                     - i.e. for 25% value of 0.25 need to pass.
         * @param optionPrice - Option Price or exercise price in scrip precision.
         * @param dividend - Dividend in percentage(%) same as Interest rate.
         * @param expiryDayType - Default value CMD_ExpiryDay_EXCLUDE
         *    - If CMD_ExpiryDay_INCLUDE passed then the Expiry day will be included i.e. 24 hours.
         *    - If CMD_ExpiryDay_HALF_INCLUDE passed then only Half Expiry day included i.e. 12 hours.
         *    - If CMD_ExpiryDay_INCLUDE_ON_EXPIRY passed then Expiry day included only if current date is also Expiry.
         *    - If CMD_ExpiryDay_EXCLUDE passed then Expiry day will not be included.
         * @return bool - return true if successful otherwise returns false.
         */
        static bool getIVForOption(
            API2::DATA_TYPES::IMPLIED_VOLATILITY &retIvValue,
            API2::COMMON::Instrument* instrument,
            const API2::DATA_TYPES::PRICE spotPrice,
            const API2::DATA_TYPES::INTEREST_RATE interestRate,
            const API2::DATA_TYPES::PRICE optionPrice,
            const API2::DATA_TYPES::DIVIDEND dividend,
            const API2::DATA_TYPES::EXPIRYDAY_TYPE expiryDayType = API2::CONSTANTS::CMD_ExpiryDay_EXCLUDE );

        /**
         * @brief getIVForOption
         * @param retIvValue - IV will be return by this reference variable in percentage(%)
         *                   - i.e. if IV is 256.99 then it will return 2.5699.
         * @param instrument - Instrument symbol for which the IV need to be calculated.
         *                   - And its should be Call or Put.
         * @param underlyingSymbolId - For which the spot price need to be fetch.
         * @param interestRate - Interest rate in percentage(%)
         *                     - i.e. for 25% value of 0.25 need to pass.
         * @param dividend - Dividend in percentage(%) same as Interest rate.
         * @param optionPrice - Option Price or exercise price in scrip precision.
         * @param expiryDayType - Default value CMD_ExpiryDay_EXCLUDE
         *    - If CMD_ExpiryDay_INCLUDE passed then the Expiry day will be included i.e. 24 hours.
         *    - If CMD_ExpiryDay_HALF_INCLUDE passed then only Half Expiry day included i.e. 12 hours.
         *    - If CMD_ExpiryDay_INCLUDE_ON_EXPIRY passed then Expiry day included only if current date is also Expiry.
         *    - If CMD_ExpiryDay_EXCLUDE passed then Expiry day will not be included.
         * @param referenceSpotPriceType - Default Value API2::CONSTANTS::ReferenceSpotPrice_LTP.
         * @note - Underlying price is getting fetch through API::COMMON::getSymbolSpotPrice which will add latency
         *       - If snapshot is disable then this method won't work as spot price can't be fetch.
         * @return bool - return true if successful otherwise returns false.
         */
        static bool getIVForOption(
            API2::DATA_TYPES::IMPLIED_VOLATILITY &retIvValue,
            API2::COMMON::Instrument* instrument,
            const API2::DATA_TYPES::SYMBOL_ID underlyingSymbolId,
            const API2::DATA_TYPES::INTEREST_RATE interestRate,
            const API2::DATA_TYPES::DIVIDEND dividend,
            const API2::DATA_TYPES::PRICE optionPrice,
            const API2::DATA_TYPES::EXPIRYDAY_TYPE expiryDayType = API2::CONSTANTS::CMD_ExpiryDay_EXCLUDE,
            const API2::DATA_TYPES::REFERENCE_SPOT_PRICE_TYPE referenceSpotPriceType = API2::CONSTANTS::ReferenceSpotPrice_LTP );

        /**
         * @brief getIVForOption
         * @param retIvValue - IV will be return by this reference variable in percentage(%)
         *                   - i.e. if IV is 256.99 then it will return 2.5699.
         * @param optionMode - Option mode Call or Put
         * @param spotPrice - SpotPrice of underlying symbol
         *                  - If scrip precision is 2 and actual price is 123.45 then
         *                  - price in scrip precision 12345( i.e. 123.45 * 100 )
         * @param strikePrice - Strike price of the symbol in scrip precision
         * @param interestRate - Interest rate in percentage(%)
         *                     - i.e. for 25% value of 0.25 need to pass.
         * @param optionPrice - Option Price or exercise price in scrip precision.
         * @param timeToExpire - Maturity time of a contract in years.
         *                     - For example mautrity of a contract is after 35 days then
         *                     - in years it will be 35/356 i.e. 0.09589.
         * @param dividend - Dividend in percentage(%) same as Interest rate.
         * @return bool - return true if successful otherwise returns false.
         */
        static bool getIVForOption(
            API2::DATA_TYPES::IMPLIED_VOLATILITY &retIvValue,
            API2::SymbolStaticData* staticData,
            const API2::DATA_TYPES::OptionMode optionMode,
            const API2::DATA_TYPES::PRICE spotPrice,
            const API2::DATA_TYPES::PRICE strikePrice,
            const API2::DATA_TYPES::INTEREST_RATE interestRate,
            const API2::DATA_TYPES::PRICE optionPrice,
            const API2::DATA_TYPES::TIME_TO_EXPIRE timeToExpire,
            const API2::DATA_TYPES::DIVIDEND dividend );

        /**
         * @brief getDeltaForOption
         * @param retDelta - Delta will be return by this reference variable in actual form (i.e between -1 to 1).
         * @param instrument - Instrument symbol for which the Delta need to be calculated.
         *                   - And its should be Call or Put.
         * @param spotPrice - SpotPrice of underlying symbol in scrip precision
         *                  - If scrip precision is 2 and actual price is 123.45 then
         *                  - price in scrip precision 12345( i.e. 123.45 * 100 )
         * @param interestRate - Interest rate in percentage(%)
         *                     - i.e. for 25% value of 0.25 need to pass.
         * @param impliedVolatility - IV in percentage(%).
         * @param dividend - Dividend in percentage(%) same as Interest rate.
         * @param expiryDayType - Default value CMD_ExpiryDay_EXCLUDE
         *    - If CMD_ExpiryDay_INCLUDE passed then the Expiry day will be included i.e. 24 hours.
         *    - If CMD_ExpiryDay_HALF_INCLUDE passed then only Half Expiry day included i.e. 12 hours.
         *    - If CMD_ExpiryDay_INCLUDE_ON_EXPIRY passed then Expiry day included only if current date is also Expiry.
         *    - If CMD_ExpiryDay_EXCLUDE passed then Expiry day will not be included.
         * @return bool - return true if successful otherwise returns false.
         */
        static bool getDeltaForOption(
            API2::DATA_TYPES::GREEK &retDelta,
            API2::COMMON::Instrument* instrument,
            const API2::DATA_TYPES::PRICE spotPrice,
            const API2::DATA_TYPES::INTEREST_RATE interestRate,
            const API2::DATA_TYPES::IMPLIED_VOLATILITY impliedVolatility,
            const API2::DATA_TYPES::DIVIDEND dividend,
            const API2::DATA_TYPES::EXPIRYDAY_TYPE expiryDayType = API2::CONSTANTS::CMD_ExpiryDay_EXCLUDE );

        /**
         * @brief getDeltaForOption
         * @param retDelta - Delta will be return by this reference variable in actual form (i.e between -1 to 1).
         * @param instrument - Instrument symbol for which the Delta need to be calculated.
         *                   - And its should be Call or Put.
         * @param interestRate - Interest rate in percentage(%)
         *                     - i.e. for 25% value of 0.25 need to pass.
         * @param underlyingSymbolId - For which the spot price need to be fetch.
         * @param impliedVolatility - IV in percentage(%).
         * @param dividend - Dividend in percentage(%) same as Interest rate.
         * @param expiryDayType - Default value CMD_ExpiryDay_EXCLUDE
         *    - If CMD_ExpiryDay_INCLUDE passed then the Expiry day will be included i.e. 24 hours.
         *    - If CMD_ExpiryDay_HALF_INCLUDE passed then only Half Expiry day included i.e. 12 hours.
         *    - If CMD_ExpiryDay_INCLUDE_ON_EXPIRY passed then Expiry day included only if current date is also Expiry.
         *    - If CMD_ExpiryDay_EXCLUDE passed then Expiry day will not be included.
         * @param referenceSpotPriceType - Default Value API2::CONSTANTS::ReferenceSpotPrice_LTP.
         * @note - Underlying price is getting fetch through API::COMMON::getSymbolSpotPrice which will add latency
         *       - If snapshot is disable then this method won't work as spot price can't be fetch.
         * @return bool - return true if successful otherwise returns false.
         */
        static bool getDeltaForOption(
            API2::DATA_TYPES::GREEK &retDelta,
            API2::COMMON::Instrument* instrument,
            const API2::DATA_TYPES::INTEREST_RATE interestRate,
            const API2::DATA_TYPES::SYMBOL_ID underlyingSymbolId,
            const API2::DATA_TYPES::IMPLIED_VOLATILITY impliedVolatility,
            const API2::DATA_TYPES::DIVIDEND dividend,
            const API2::DATA_TYPES::EXPIRYDAY_TYPE expiryDayType = API2::CONSTANTS::CMD_ExpiryDay_EXCLUDE,
            const API2::DATA_TYPES::REFERENCE_SPOT_PRICE_TYPE referenceSpotPriceType = API2::CONSTANTS::ReferenceSpotPrice_LTP );

        /**
         * @brief getDeltaForOption
         * @param retDelta - Delta will be return by this reference variable in actual form (i.e between -1 to 1).
         * @param optionMode - Option mode Call or Put
         * @param spotPrice - SpotPrice of underlying symbol in scrip precision
         *                  - If scrip precision is 2 and actual price is 123.45 then
         *                  - price in scrip precision 12345( i.e. 123.45 * 100 )
         * @param strikePrice - Strike price of the symbol in scrip precision
         * @param interestRate - Interest rate in percentage(%)
         *                     - i.e. for 25% value of 0.25 need to pass.
         * @param optionPrice - Option Price or exercise price in scrip precision.
         * @param timeToExpire - Maturity time of a contract in years.
         *                     - For example mautrity of a contract is after 35 days then
         *                     - in years it will be 35/356 i.e. 0.09589.
         * @param dividend - Dividend in percentage(%) same as Interest rate.
         * @return bool - return true if successful otherwise returns false.
         */
        static bool getDeltaForOption(
            API2::DATA_TYPES::GREEK &retDelta,
            API2::SymbolStaticData* staticData,
            const API2::DATA_TYPES::OptionMode optionMode,
            const API2::DATA_TYPES::PRICE spotPrice,
            const API2::DATA_TYPES::PRICE strikePrice,
            const API2::DATA_TYPES::INTEREST_RATE interestRate,
            const API2::DATA_TYPES::PRICE optionPrice,
            const API2::DATA_TYPES::TIME_TO_EXPIRE timeToExpire,
            const API2::DATA_TYPES::DIVIDEND dividend );

        /**
         * @brief getOptionPrice
         * @param retOptionPrice - OptionPrice will be return by this reference variable in scrip precision.
         *                       - There may be precision loss of 1 paisa so round off to tick size.
         * @param instrument - Instrument symbol for which the OptionPrice need to be calculated.
         *                   - And its should be Call or Put.
         * @param spotPrice - SpotPrice of underlying symbol in scrip precision
         *                  - If scrip precision is 2 and actual price is 123.45 then
         *                  - price in scrip precision 12345( i.e. 123.45 * 100 )
         * @param interestRate - Interest rate in percentage(%)
         *                     - i.e. for 25% value of 0.25 need to pass.
         * @param impliedVolatility - IV in percentage(%).
         * @param dividend - Dividend in percentage(%) same as Interest rate.
         * @param expiryDayType - Default value CMD_ExpiryDay_EXCLUDE
         *    - If CMD_ExpiryDay_INCLUDE passed then the Expiry day will be included i.e. 24 hours.
         *    - If CMD_ExpiryDay_HALF_INCLUDE passed then only Half Expiry day included i.e. 12 hours.
         *    - If CMD_ExpiryDay_INCLUDE_ON_EXPIRY passed then Expiry day included only if current date is also Expiry.
         *    - If CMD_ExpiryDay_EXCLUDE passed then Expiry day will not be included.
         * @return bool - return true if successful otherwise returns false.
         */
        static bool getOptionPrice(
            API2::DATA_TYPES::PRICE &retOptionPrice,
            API2::COMMON::Instrument* instrument,
            const API2::DATA_TYPES::PRICE spotPrice,
            const API2::DATA_TYPES::INTEREST_RATE interestRate,
            const API2::DATA_TYPES::IMPLIED_VOLATILITY impliedVolatility,
            const API2::DATA_TYPES::DIVIDEND dividend,
            const API2::DATA_TYPES::EXPIRYDAY_TYPE expiryDayType = API2::CONSTANTS::CMD_ExpiryDay_EXCLUDE );

        /**
         * @brief getOptionPrice
         * @param retOptionPrice - OptionPrice will be return by this reference variable in scrip precision.
         *                       - There may be precision loss of 1 paisa so round off to tick size.
         * @param instrument - Instrument symbol for which the OptionPrice need to be calculated.
         *                   - And its should be Call or Put.
         * @param interestRate - Interest rate in percentage(%)
         *                     - i.e. for 25% value of 0.25 need to pass.
         * @param underlyingSymbolId - For which the spot price need to be fetch.
         * @param impliedVolatility - IV in percentage(%).
         * @param dividend - Dividend in percentage(%) same as Interest rate.
         * @param expiryDayType - Default value CMD_ExpiryDay_EXCLUDE
         *    - If CMD_ExpiryDay_INCLUDE passed then the Expiry day will be included i.e. 24 hours.
         *    - If CMD_ExpiryDay_HALF_INCLUDE passed then only Half Expiry day included i.e. 12 hours.
         *    - If CMD_ExpiryDay_INCLUDE_ON_EXPIRY passed then Expiry day included only if current date is also Expiry.
         *    - If CMD_ExpiryDay_EXCLUDE passed then Expiry day will not be included.
         * @param referenceSpotPriceType - Default Value API2::CONSTANTS::ReferenceSpotPrice_LTP.
         * @note - Underlying price is getting fetch through API::COMMON::getSymbolSpotPrice which will add latency
         *       - If snapshot is disable then this method won't work as spot price can't be fetch.
         * @return bool - return true if successful otherwise returns false.
         */
        static bool getOptionPrice(
            API2::DATA_TYPES::PRICE &retOptionPrice,
            API2::COMMON::Instrument* instrument,
            const API2::DATA_TYPES::INTEREST_RATE interestRate,
            const API2::DATA_TYPES::SYMBOL_ID underlyingSymbolId,
            const API2::DATA_TYPES::IMPLIED_VOLATILITY impliedVolatility,
            const API2::DATA_TYPES::DIVIDEND dividend,
            const API2::DATA_TYPES::EXPIRYDAY_TYPE expiryDayType = API2::CONSTANTS::CMD_ExpiryDay_EXCLUDE,
            const API2::DATA_TYPES::REFERENCE_SPOT_PRICE_TYPE referenceSpotPriceType = API2::CONSTANTS::ReferenceSpotPrice_LTP );

        /**
         * @brief getOptionPrice
         * @param retOptionPrice - OptionPrice will be return by this reference variable in scrip precision.
         *                       - There may be precision loss of 1 paisa so round off to tick size.
         * @param optionMode - Option mode Call or Put
         * @param spotPrice - SpotPrice of underlying symbol in scrip precision
         *                  - If scrip precision is 2 and actual price is 123.45 then
         *                  - price in scrip precision 12345( i.e. 123.45 * 100 )
         * @param strikePrice - Strike price of the symbol in scrip precision
         * @param interestRate - Interest rate in percentage(%)
         *                     - i.e. for 25% value of 0.25 need to pass.
         * @param impliedVolatility - IV in percentage(%).
         * @param timeToExpire - Maturity time of a contract in years.
         *                     - For example mautrity of a contract is after 35 days then
         *                     - in years it will be 35/356 i.e. 0.09589.
         * @param dividend - Dividend in percentage(%) same as Interest rate.
         * @return bool - return true if successful otherwise returns false.
         * @return
         */
        static bool getOptionPrice(
            API2::DATA_TYPES::PRICE &retOptionPrice,
            API2::SymbolStaticData* staticData,
            const API2::DATA_TYPES::OptionMode optionMode,
            const API2::DATA_TYPES::PRICE spotPrice,
            const API2::DATA_TYPES::PRICE strikePrice,
            const API2::DATA_TYPES::INTEREST_RATE interestRate,
            const API2::DATA_TYPES::IMPLIED_VOLATILITY impliedVolatility,
            const API2::DATA_TYPES::TIME_TO_EXPIRE timeToExpire,
            const API2::DATA_TYPES::DIVIDEND dividend );

        /**
         * @brief getGreekValues
         * @param greekValues
         * @description - If underling symbol is set in IvGreekValues structure
         *              - it will calculate spotprice w.r.t ReferenceSpotPriceType otherwise
         *              - it will use the spotprice will is already set in the structure.
         * @return
         */
        static bool getGreekValues(
            API2::COMMON::IvGreekValues &greekValues );

    };

  }

}

#endif // IV_GREEK_INTERFACE_H
