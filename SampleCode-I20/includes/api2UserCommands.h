#ifndef api2_UserParams_h
#define api2_UserParams_h
#include <baseCommands.h>

#define API2_VERSION_STRING "3.5.4"

namespace API2 {


/**
 * @brief The API2_UserParamsError enum
 */
enum UserParamsError
{
    UserParamsError_OK,
    UserParamsError_KeyNotFound,
    UserParamsError_DataTypeMismatch
};

/**
 * @brief The API2_UserParams class
 */
class UserParams : public AbstractUserParams
{
    /**
     * @brief _userParams
     */
    std::map<std::string,BaseType *> _userParams;


#ifdef FRONTEND_COMPILATION
    std::map<std::string,int> _mapVectorStringVectorIndex;
#endif

    /**
     * @brief ApiIndex
     */
    CREATE_FIELD_DERIVED( int, ApiIndex);

#ifdef FRONTEND_COMPILATION
    void clone(const UserParams& other);
#endif

  public:

    /**
     * @brief API2_UserParams
     * @param frontendDesign
     * @param buf
     * @throw DuplicateKeyException
     */
    explicit UserParams(const std::string &frontendDesign,const char *buf = NULL);

#ifdef FRONTEND_COMPILATION
    UserParams(const UserParams &other);
    UserParams& operator=(const UserParams& other);
#endif

    /**
     * @brief serialize
     * @param buf
     * @param apiIndex
     * @param comCat
     * @return
     */
    int serialize(char *buf,int apiIndex,
        COMMAND_CATEGORY_TYPE comCat
        = CONSTANTS::CMD_CommandCategory_API2_STRATEGY);


    /**
     * @brief setValue
     * @param key
     * @param val
     * @return
     */
    template<class T>
    UserParamsError setValue(const std::string &key,const T &val)
    {
        std::map<std::string,BaseType *>::iterator it = _userParams.find(key);
        if(it == _userParams.end())
        {
            std::cout<<"Key not found : "<<key;

            return UserParamsError_KeyNotFound;
        }
        else
        {
            DerivedType<T> *value = dynamic_cast<DerivedType<T> *>(it->second);
            if(value == NULL)
            {
                std::cout<<"Data Type Mismatch for "
                        <<key<<" "
                       << typeid(val).name()
                       <<std::endl;
                //it->second->printType();
                return UserParamsError_DataTypeMismatch;
            }
            else
            {
                value->setValue(val);
                return UserParamsError_OK;
            }
        }
    }


    /**
     * @brief getValue
     * @param key
     * @param val
     * @return
     */
    template<class T>
    UserParamsError getValue(const std::string &key,T &val)
    {
        std::map<std::string,BaseType *>::iterator it = _userParams.find(key);
        if(it == _userParams.end())
        {
            return UserParamsError_KeyNotFound;
        }
        else
        {
            DerivedType<T> *value = dynamic_cast<DerivedType<T> *>(it->second);
            if(value == NULL)
            {
                std::cout<<"Data Type Mismatch for "<<key<<std::endl;
                return UserParamsError_DataTypeMismatch;
            }
            else
            {
                val = value->getValue();
                return UserParamsError_OK;
            }
        }
    }
    ~UserParams();
};
}
#endif 
