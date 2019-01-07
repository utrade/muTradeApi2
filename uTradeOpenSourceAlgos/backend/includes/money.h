#ifndef API2_CURRENCY_H
#define API2_CURRENCY_H
//#include <shared/commands.h>
//#include "baseCommands.h"
#include <sharedDefines.h>
#include <apiDataTypes.h>
#define STRINGIFY(x) #x
#define CurrencyPrecision 100000000
#define CurrencyMinorPrecision 100
namespace API2
{
  namespace Currency {
    typedef SIGNED_LONG PriceType;

    /**
     * @brief The CurrencyType enum
     */
    enum CurrencyType{
      USD,
      EUR,
      INR,
      GBP,
      CNY,
      AUD,
      BRL,
      JPY,
      RUB,
      LKR,
      ERROR
    };

    /**
     * @brief PairCurrency
     */
    typedef std::pair<CurrencyType, CurrencyType> PairCurrency;

    class MoneyImpl;
    class MultiCurrencyBase;

    /**
     * @brief The Money class
     */
    class Money{
      friend class MultiCurrencyBase;
    public:

      Money(){}
      ~Money();

      /**
       * @brief Moneyint
       * @param buf
       * @param offset
       */
      Money(const char *buf, int &offset);

      /**
       * @brief serialize
       * @param buf
       * @param bytes
       */
      void serialize(char *buf, int &bytes) const;

      /**
       * @brief operator +
       * @param other
       * @return
       */
      Money operator+(const Money &other);

      /**
       * @brief operator -
       * @param other
       * @return
       */
      Money operator-(const Money &other);

      /**
       * @brief operator *
       * @param other
       * @return
       */
      Money operator*(const Money &other);

      /**
       * @brief operator ==
       * @param other
       * @return
       */
      bool operator ==(const Money &other);

      bool operator ==(const CurrencyType &otherType);


      /**
       * @brief operator +=
       * @param other
       */
      void operator +=(const Money &other);


      /**
       * @brief operator -=
       * @param other
       */
      void operator -=(const Money &other);

      /**
       * @brief operator -=
       * @param other
       */
      void operator *=(const Money &other);


      /**
       * @brief getValue
       * @param changedPrcsn
       * @return
       */
      double getValue() const;

      /**
       * @brief getValueLong
       * @return
       */
      PriceType getValueLong() const;

      /**
       * @brief getPriceLong
       * @return
       */
      PriceType getPriceLong() const;

      /**
       * @brief getRoundOff
       * @param precision
       * @param tick
       * @param floor, true to round off for SELL PRICE, and false for BUY PRICE
       * @return
       */
      PriceType getRoundOff(int precision, int tick, bool floor);

      /**
       * @brief getTypeString
       * @return
       */
      std::string getTypeString() const;

      /**
       * @brief getType
       * @return
       */
      CurrencyType getType() const;

      /**
       * @brief getPrecision
       * @return
       */
      static SIGNED_LONG getPrecision();

      /**
       * @brief dump
       */
      void dump();

      /**
       * @brief getStr
       * @param ss
       */
      void getStr(std::ostringstream &ss);


      /**
       * @brief setValue
       * @param val
       */
      void setValue(PriceType val);

      /**
       * @brief to
       * @param type
       * @param precision
       * @return
       */
      Money to(CurrencyType type) const;

      /**
       * @brief from
       * @param type
       * @param price
       * @param precision
       * @return
       */
      static Money from(CurrencyType type, PriceType price=0);


    private:

      /**
       * @brief _impl
       */
      MoneyImpl *_impl;

      /**
       * @brief Money
       * @param currency
       * @param value
       * @param precision
       */
      Money(CurrencyType currency, PriceType value);
    };
  }
}

#endif // API2_CURRENCY_H
