#ifndef user_Params_Reader_h 
#define user_Params_Reader_h

#define staticStringConstant(name) \
  static const std::string _##name = # name
#include <string>
#include <baseCommands.h>
#include <vector>
namespace API2 {
  namespace COMMON {

    /**
     * @brief The SerializedDataType enum
     */
    enum SerializedDataType {
      SerializedDataType_character,
      SerializedDataType_int16,
      SerializedDataType_int32,
      SerializedDataType_int64,
      SerializedDataType_string
    };

    namespace StringDataTypes {

      staticStringConstant(UINT64);
      staticStringConstant(INT64);
      staticStringConstant(FLOAT);
      staticStringConstant(TIMER);
      staticStringConstant(BOOL);
      staticStringConstant(COMBO);
      staticStringConstant(UCHAR);
      staticStringConstant(RADIO);
      staticStringConstant(STRING);

    }


    typedef
      /**
       * @brief The KeyValue struct
       */
      struct KeyValue {

        /**
         * @brief KeyValue
         * @param label
         * @param key
         * @param value
         * @param type
         */
        KeyValue(std::string label,
            std::string key,
            std::string value,
            SerializedDataType type) :
          _label(label),
          _key(key),
          _value(value),
          _type(type)
        {
        }

        /**
         * @brief _label
         */
        std::string _label;

        /**
         * @brief _key
         */
        std::string _key;

        /**
         * @brief _value
         */
        std::string _value;

        /**
         * @brief _type
         */
        SerializedDataType _type;
      } KeyValue;

    /**
     * @brief The UserParamsReader class
     */
    class UserParamsReader {
      public:
        /**
         * @brief symbol
         * @return
         */
        static std::string symbol();

        /**
         * @brief params
         * @return
         */
        static std::string params();

        /**
         * @brief other
         * @return
         */
        static std::string other();

        /**
         * @brief seperator
         * @return
         */
        static std::string seperator();

        /**
         * @brief stretch
         * @return
         */
        static std::string stretch();
        /**
         * @brief isComment
         * @param line
         * @return
         */
        static bool isComment(std::string &line);

        /**
         * @brief isLabel
         * @param line
         * @return
         */
        static bool isLabel(std::string &line);

        /**
         * @brief isSpace
         * @param line
         * @return
         */
        static bool isSpace(std::string &line);

        /**
         * @brief isSymbol
         * @param line
         * @return
         */
        static bool isSymbol(std::string &line);

        /**
         * @brief isParams
         * @param line
         * @return
         */
        static bool isParams(std::string &line);

        /**
         * @brief isOther
         * @param line
         * @return
         */
        static bool isOther(std::string &line);

        /**
         * @brief getBaseTypeVector
         * @param frontendDesign
         * @return
         */
        static BaseTypeVector getBaseTypeVector(const std::string &frontendDesign);

        /**
         * @brief getBaseTypeVector
         * @param vectorGuiTemplate
         * @return
         */
        static BaseTypeVector getBaseTypeVector(const std::vector<KeyValue> &vectorGuiTemplate);

        /**
         * @brief getVectorGuiTemplate
         * @param frontendDesign
         * @return
         */
        static std::vector<KeyValue>

          /**
           * @brief getVectorGuiTemplate
           * @param frontendDesign
           */
          getVectorGuiTemplate(const std::string &frontendDesign);

        /**
         * @brief compareBeg
         * @param s1
         * @param s2
         * @return
         */
        static int compareBeg(const std::string &s1, const std::string &s2);

        /**
         * @brief setSerializedDataType
         * @param vectorGuiTemplate
         * @throw UnknownTypeException
         */
        static void setSerializedDataType(std::vector<KeyValue> &vectorGuiTemplate);

    };
  }
}
#endif
