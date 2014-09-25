#ifndef SERIALIZE_COMMANDS_H
#define SERIALIZE_COMMANDS_H
#include <sharedDefines.h>
#include <sharedSingleOrder.h>
#include <string>
//extern "C"
namespace API2 {
  namespace Serialization {

    /**
 * @brief serialize will serialize the long value and append to buf and auto-increment bytes with size of data serialized
 * @param val to be serialized
 * @param buf char array pointer
 * @param bytes start index of char, auto adjusted according to size of val after serialization
 */

    void serialize(const UNSIGNED_LONG &val, char *buf, int &bytes);

    /**
 * @brief serialize will serialize the long value and append to buf and auto-increment bytes with size of data serialized
 * @param val to be serialized
 * @param buf char array pointer
 * @param bytes start index of char, auto adjusted according to size of val after serialization
 */

    void serialize(const UNSIGNED_CHARACTER &val, char *buf, int &bytes);

    /**
 * @brief serialize will serialize the long value and append to buf and auto-increment bytes with size of data serialized
 * @param val to be serialized
 * @param buf char array pointer
 * @param bytes start index of char, auto adjusted according to size of val after serialization
 */

    void serialize(const char &val, char *buf, int &bytes);

    /**
 * @brief serialize will serialize the long value and append to buf and auto-increment bytes with size of data serialized
 * @param val to be serialized
 * @param buf char array pointer
 * @param bytes start index of char, auto adjusted according to size of val after serialization
 */

    void serialize(const UNSIGNED_INTEGER &val, char *buf, int &bytes);

    /**
 * @brief serialize will serialize the long value and append to buf and auto-increment bytes with size of data serialized
 * @param val to be serialized
 * @param buf char array pointer
 * @param bytes start index of char, auto adjusted according to size of val after serialization
 */

    void serialize(const int &val, char *buf, int &bytes);


    /**
 * @brief serialize will serialize the long value and append to buf and auto-increment bytes with size of data serialized
 * @param val to be serialized
 * @param buf char array pointer
 * @param bytes start index of char, auto adjusted according to size of val after serialization
 */

    void serialize(const UNSIGNED_SHORT &val, char *buf, int &bytes);

    /**
 * @brief serialize will serialize the long value and append to buf and auto-increment bytes with size of data serialized
 * @param val to be serialized
 * @param buf char array pointer
 * @param bytes start index of char, auto adjusted according to size of val after serialization
 */
    void serialize(const short &val, char *buf, int &bytes);

    /**
 * @brief serialize will serialize the long value and append to buf and auto-increment bytes with size of data serialized
 * @param val to be serialized
 * @param buf char array pointer
 * @param bytes start index of char, auto adjusted according to size of val after serialization
 */
    void serialize(const SIGNED_LONG &val, char *buf, int &bytes);

    /**
 * @brief serialize will serialize the long value and append to buf and auto-increment bytes with size of data serialized
 * @param val to be serialized
 * @param buf char array pointer
 * @param bytes start index of char, auto adjusted according to size of val after serialization
 */
    void serialize(const std::string &val, char *buf, int &bytes);



    /**
 * @brief serializeAccountDetails
 * @param accountDetails, to be serialized
 * @param buf
 * @param bytes
 */
    void serialize(const AccountDetail &accountDetails, char* buf, int &bytes);


    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param val to be deserialized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(UNSIGNED_LONG &val, const char *buf, int &offset);

    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param val to be deserialized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(UNSIGNED_CHARACTER &val, const char *buf, int &offset);

    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param val to be deserialized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(char &val, const char *buf, int &offset);

    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param val to be deserialized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(UNSIGNED_INTEGER &val, const char *buf, int &offset);

    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param val to be deserialized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(int &val, const char *buf, int &offset);

    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param val to be deserialized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(UNSIGNED_SHORT &val, const char *buf, int &offset);

    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param val to be deserialized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(short &val, const char *buf, int &offset);

    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param val to be deserialized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(SIGNED_LONG &val, const char *buf, int &offset);

    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param val to be deserialized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(std::string &val, const char *buf, int &offset);

    /**
 * @brief deSerialize overloaded function, deserializes to val from buf, and adjusts offset to bytes read for deserialization.
 * @param accountDetails to be deseralized
 * @param buf char array pointer
 * @param offset start index of char, auto adjusted according to size of val after deserialization
 */
    void deSerialize(AccountDetail &accountDetails, const char *buf, int &offset);


    /**
 * @brief deserializeAccountDetails
 * @param accountDetails
 * @param buf
 * @param offset
 */
    void deserializeAccountDetails(AccountDetail &accountDetails, const char* buf, int &offset);

    /**
 * @brief serializeAccountDetails
 * @param accountDetails
 * @param buf
 * @param bytes
 */
    void serializeAccountDetails(AccountDetail &accountDetails, char* buf, int &bytes);

  }
}
#endif
