#ifndef BASECOMMANDS_H
#define BASECOMMANDS_H
#include <vector>
//#include "defines.h"
//#include "response.h"
#include <iostream>
#include "cmdDefines.h"
#include <map>
#include <serializeCommands.h>
#include <stdio.h>
#include <typeinfo>
#include <sstream>

#ifndef FRONTEND_COMPILATION
#include <DBConverter.h>
#if API_COMPILATION == 0
#include <soci.h>
#endif
#endif
#include "strategyWave.h"

namespace CMD{

  /**
   * @brief The BaseStrategyParamCommmand class
   *
   *The class is inherited to all the Strategy Parameters Commands
   *All the common parameters of strategies should be a member of
   *this class.
   */
  class BaseStrategyParamCommmand
  {

    /**
     * @brief PortfolioId: uHedge portfolio id
     */
    CREATE_FIELD(UNSIGNED_INTEGER, PortfolioId);
    
    /**
     * @brief ParentStrategyId: id of api strategy from which any inHouse strategy invoked(invoking API)
     */
    CREATE_FIELD(UNSIGNED_INTEGER, ParentStrategyId);

    // DTA Work
    // /**
    //  * @brief FixClOrderId: It is set when API strategy is run throgh FIX.     
    //  */
    // CREATE_FIELD( UNSIGNED_LONG, FixClOrderId );

    CREATE_FIELD(ST::StrategyWave, StrategyWave);

    public:
    BaseStrategyParamCommmand();

    ~BaseStrategyParamCommmand();

    /**
     * @brief initialize initialize the members of the class.
     */
    void initialize();

    /**
     * @brief serializeMembers - serialize the members of this class without command category
     * @param buff
     * @return
     */
    void serializeMembers(char * buff, int &bytes);

    /**
     * @brief deSerializeMembers - deSerialize the members of this class
     * @param buff
     * @return
     */
    void deSerializeMembers(const char * buff, int &offset);

    /**
     * @brief getString
     * @return
     */
    std::string getString()
    {
      std::stringstream ss;
      ss << "\n PortfolioId() : " << getPortfolioId();
      ss << "\n ParentStrategyId : " << getParentStrategyId();
      // DTA Work
      // ss << "\n FixClOrderId : " << getFixClOrderId() << std::endl;
      ss << "\n Dump of wave details: " <<getRefStrategyWave().getString() << std::endl;
      return ss.str();
    }

  };


}//namespace CMD

namespace API2{

  using namespace Serialization;
  /**
   * @brief The BaseType class
   */
  class BaseType
  {
    CREATE_FIELD_STR_PTR(std::string, String);
    public:


    virtual ~BaseType(){}

    /**
     * @brief serializeFun
     * @param buf
     * @param bytes
     */
    virtual void serializeFun(char *buf, int &bytes) const =0;

    /**
     * @brief deSerializeFun
     * @param buf
     * @param offset
     */
    virtual void deSerializeFun(const char *buf, int &offset)=0;

    /**
     * @brief dump
     */
    virtual void dump() const =0;

    /**
     * @brief getKeyValueString
     */
    virtual std::string getKeyValueString() const =0;
    virtual std::string getDBValueString() const =0;

#if API_COMPILATION == 0
#ifndef FRONTEND_COMPILATION
    virtual void setSociData(const soci::row &r,size_t index) = 0;
#endif
#endif


    /**
     * @brief printType
     */
    virtual void printType() const = 0;



    /**
     * @brief BaseType
     * @param stringType
     */
    BaseType(const std::string &stringType, bool useName =true)
    {
      if(useName)
        setString(new std::string(stringType));
    }
    //    BaseType(const BaseType &other)
    //    {
    //      _String = new std::string(other.getString());
    //    }

    /**
     * @brief BaseType
     */
    BaseType()
    {
    }
  };


  /**
   * @brief The DerivedType class
   */
  template <class T>
    class DerivedType :public BaseType
  {
    CREATE_FIELD( T, Value);
    CREATE_FIELD( UNSIGNED_INTEGER, Count );


    public:

    /**
     * @brief DerivedType
     * @param type
     */
    explicit DerivedType(const std::string &type):
      BaseType(type),
      _Value(T()),
      _Count(0)
    {
    }

    /**
     * @brief DerivedType
     */
    DerivedType(){}

    /**
     * @brief printType
     */
    void printType() const override
    {
      std::cout<<"\n typename "<<typeid(_Value).name()<<std::endl;
    }

    /**
     * @brief serializeFun
     * @param buf
     * @param bytes
     */
    void serializeFun(char *buf, int &bytes) const override
    {
      serialize(_Value, buf, bytes);
    }

    /**
     * @brief deSerializeFun
     * @param buf
     * @param offset
     */
    void deSerializeFun(const char *buf, int &offset) override
    {
      deSerialize(_Value, buf, offset);
    }

    /**
     * @brief serialize
     * @param mapULong
     * @param buf
     * @param bytes
     */
    void serialize(
        const MapULong &mapULong,
        char *buf,
        int &bytes) const
    {
      for(MapULongIter i= mapULong.begin(); i!= mapULong.end(); ++i)
      {
        Serialization::serialize(i->first,buf,bytes);
        Serialization::serialize(i->second,buf,bytes);
        //SERIALIZE_64(tmpLong, i->first, buf, bytes);
        //SERIALIZE_64(tmpLong, (i->second), buf, bytes);
      }
    }

    /**
     * @brief deSerialize
     * @param val
     * @param buf
     * @param offset
     */
    void deSerialize(MapULong &val, const char *buf, int &offset)
    {
      for(unsigned int i=0; i <getCount();i++)
      {
        UNSIGNED_LONG key;
        UNSIGNED_LONG value;
        Serialization::deSerialize(key,buf,offset);
        Serialization::deSerialize(value,buf,offset);
        //DESERIALIZE_64(tmp1, tmp2, t.setTmpKey(tmp2), buf, offset);
        //DESERIALIZE_64(tmp1, tmp2, t.setTmpVal(tmp2), buf, offset);
        val[key] = value;
      }
    }
    /**
     * @brief serialize
     * @param value
     * @param buf
     * @param bytes
     */
    template<class M>
      void serialize(const M &value,
          char *buf,int &bytes) const
      {
        Serialization::serialize(value,buf,bytes);
      }
    template<class M>

      /**
       * @brief deSerialize
       * @param val
       * @param buf
       * @param offset
       */
      void deSerialize(M &val, const char *buf, int &offset)
      {
        Serialization::deSerialize(val,buf,offset);
      }

    /**
     * @brief dump
     */
    void dump() const override
    {
      std::cout<<getKeyValueStringImpl(getValue());
    }
    /**
     * @brief getKeyValueString
     */
    std::string getKeyValueString() const override
    {
      return getKeyValueStringImpl(getValue());
    }

    std::string getDBValueString() const override
    {
#ifndef FRONTEND_COMPILATION
      return API2::DBConverter::getDBString(_Value);
#endif
      return "";
    }

#if API_COMPILATION == 0
#ifndef FRONTEND_COMPILATION
    void setSociData(const soci::row &r,size_t index) override
    {
      return API2::DBConverter::setSociData(r,index,_Value);
    }
#endif
#endif

    /**
     * @brief getKeyValueStringImpl
     * @param val
     */
    template<class M>
      std::string getKeyValueStringImpl(const M &val) const
      {
        std::ostringstream out;
        out << std::endl << getString() <<"--->"<< val;
        return out.str();
      }

    std::string getKeyValueStringImpl(const API2::AccountDetail &val) const
    {
      std::ostringstream out;
      out << std::endl << getString() <<"--->"<< val.dump();
      return out.str();
    }

    /**
     * @brief getKeyValueStringImpl
     * @param val
     */
    std::string getKeyValueStringImpl(const char &val) const
    {
      std::ostringstream out;
      out << std::endl << getString() <<"--->"<< (short)val;
      return out.str();
    }

    /**
     * @brief getKeyValueStringImpl
     * @param val
     */
    std::string getKeyValueStringImpl(const UNSIGNED_CHARACTER &val) const
    {
      std::ostringstream out;
      out << std::endl << getString() <<"--->"<< (short)val;
      return out.str();
    }

    /**
     * @brief getKeyValueStringImpl
     * @param val
     */
    std::string getKeyValueStringImpl(const MapULong &val) const
    {
      std::ostringstream out;
      out <<"========" << std::endl << getString() << "========";
      for(MapULongIter iter = _Value.begin(); iter != _Value.end(); ++iter)
      {
        out << std::endl << iter->first <<"--->"<< iter->second;
      }
      return out.str();
    }

  };


  typedef std::vector<BaseType *> BaseTypeVector;
  typedef std::vector<const BaseType *> ConstBaseTypeVector;

  /**
   * @brief The AbstractUserParams class
   */
  class AbstractUserParams : public CMD::BaseStrategyParamCommmand
  {

    /**
     * @brief StrategyVersion
     */
    CREATE_FIELD_DERIVED( UNSIGNED_LONG, StrategyVersion);

    /**
     * @brief TransactionType
     */
    CREATE_FIELD_DERIVED( UNSIGNED_CHARACTER, TransactionType);

    /**
     * @brief ClientId
     */
    CREATE_FIELD_DERIVED( UNSIGNED_INTEGER, ClientId);

    /**
     * @brief StrategyId
     */
    CREATE_FIELD_DERIVED( UNSIGNED_INTEGER, StrategyId);

    /**
     * @brief AdminTokenId
     */
    CREATE_FIELD_DERIVED( UNSIGNED_LONG, AdminTokenId);

    /**
     * @brief SequenceNumber
     */
    CREATE_FIELD_DERIVED( UNSIGNED_LONG, SequenceNumber);

    /**
     * @brief _Members
     */
    BaseTypeVector _Members;

    CREATE_FIELD(bool, DataOnlyFlag);

    public:
    /**
     * @brief AbstractUserParams
     */
    AbstractUserParams(bool dataOnlyFlag=false)
      :
        _DataOnlyFlag(dataOnlyFlag)
    {
      AbstractUserParams::initialize();
    }

    /**
     * @brief ~AbstractUserParams
     */
    virtual ~AbstractUserParams(){}

    /**
     * @brief initialize
     */
    virtual void initialize()
    { 
      _Members.clear();
      SET_DERIVED_TYPE_API2( StrategyVersion, 0);
      SET_DERIVED_TYPE_API2( TransactionType, 0);
      SET_DERIVED_TYPE_API2( ClientId, 0);
      SET_DERIVED_TYPE_API2( StrategyId, 0);
      SET_DERIVED_TYPE_API2( AdminTokenId, 0);
      SET_DERIVED_TYPE_API2( SequenceNumber, 0);
    }

    int serializeBase(char *buf, bool isResponse, COMMAND_CATEGORY_TYPE cat, COMMAND_CATEGORY_TYPE comCat)
    {
      int bytes = 0;

      if (isResponse)
      {
        Serialization::serializeCommand(cat, buf, bytes);
      }
      else
      {
        Serialization::serializeCommand(comCat, buf, bytes);
      }

      Serialization::serialize(getStrategyVersion(),buf,bytes);
      Serialization::serialize(getTransactionType(),buf,bytes);
      Serialization::serialize(getClientId(),buf,bytes);
      Serialization::serialize(getStrategyId(),buf,bytes);
      Serialization::serialize(getAdminTokenId(),buf,bytes);
      Serialization::serialize(getSequenceNumber(),buf,bytes);
      CMD::BaseStrategyParamCommmand::serializeMembers(buf, bytes);

      /**
       *Put size as the first field after deducting 2 bytes reserved for size
       */
      Serialization::serializePacketLength(bytes, buf);

      return bytes;
    }

    /**
     * @brief serialize
     * @param buf
     * @param isResponse
     * @param cat
     * @param comCat
     * @return
     */
    int serialize(char *buf, bool isResponse, COMMAND_CATEGORY_TYPE cat, COMMAND_CATEGORY_TYPE comCat)
    {
      int bytes = 0;

      if (isResponse)
      {
        Serialization::serializeCommand(cat, buf, bytes);
      }
      else
      {
        Serialization::serializeCommand(comCat, buf, bytes);
      }

      for( int i=0; i<(int)_Members.size(); i++)
      {
        //printf("Serializing :%s \n",_Members[i]->getString().c_str());
        _Members[i]->serializeFun(buf,bytes);
      }

      CMD::BaseStrategyParamCommmand::serializeMembers(buf, bytes);

      /**
       *Put size as the first field after deducting 2 bytes reserved for size
       */
      Serialization::serializePacketLength(bytes, buf);

      return bytes;
    }

    /**
     * @brief serializeApi
     * @param buf
     * @param isResponse
     * @param cat
     * @param comCat
     * @param apiIndex
     * @return
     */
    int serializeApi(char *buf,
        bool isResponse,
        COMMAND_CATEGORY_TYPE cat,
        COMMAND_CATEGORY_TYPE comCat,
        int apiIndex)
    {
      int bytes = 0;

      if (isResponse)
      {
        Serialization::serializeCommand(cat, buf, bytes);
      }
      else
      {
        Serialization::serializeCommand(comCat, buf, bytes);
      }

      Serialization::serialize(apiIndex,buf,bytes);
      for( int i=0; i<(int)_Members.size(); i++)
      {
        //printf("Serializing :%s \n",_Members[i]->getString().c_str());
        _Members[i]->serializeFun(buf,bytes);
      }

      CMD::BaseStrategyParamCommmand::serializeMembers(buf, bytes);

      /**
       *Put size as the first field after deducting 2 bytes reserved for size
       */
      Serialization::serializePacketLength(bytes, buf);

      return bytes;
    }

    /**
     * @brief deSerialize
     * @param buf
     */
    int deSerialize(const char* buf)
    {
      //      initialize();
      int offset =0;

      for( int i=0; i<(int)_Members.size(); i++)
      {
        //printf("Deserializing :%s  \n",_Members[i]->getString().c_str());
        _Members[i]->deSerializeFun(buf,offset);
      }

      CMD::BaseStrategyParamCommmand::deSerializeMembers(buf, offset);

      return offset;
    }

    /**
     * @brief addType
     * @param type
     */
    void addType(BaseType *type)
    {
      _Members.push_back(type);
    }

    /**
     * @brief dump
     */
    void dump()
    {
      std::cout << std::endl<< "SG_DUMP. Total Params:" <<_Members.size()<<std::endl;
      std::cout << std::endl<< "===============================" <<std::endl;

      for( int i=0; i<(int)_Members.size(); i++)
      {
        _Members[i]->dump();
      }
      std::cout<< CMD::BaseStrategyParamCommmand::getString()<<std::endl;
      std::cout << std::endl;
    }

    std::string getString()
    {
      std::ostringstream out;
      out << std::endl<< "SG_DUMP. Total Params:" <<_Members.size()<<std::endl;
      out << std::endl<< "===============================" <<std::endl;

      for( int i=0; i<(int)_Members.size(); i++)
      {
        out<<_Members[i]->getKeyValueString();
      }
      return out.str();
    }
    void writeToFileAll(FILE *fp)
    {
      char strategyCommandBuffer[MAX_BUF_SIZE] = {0};
      int strategyBytes = serialize((char *)strategyCommandBuffer,false,0,0);
      fwrite((void*)strategyCommandBuffer,strategyBytes, 1, fp);
      fflush(fp);
    }
    void writeToFileBase(FILE *fp)
    {
      char strategyCommandBuffer[MAX_BUF_SIZE] = {0};
      int strategyBytes = serializeBase((char *)strategyCommandBuffer,false,0,0);
      fwrite((void*)strategyCommandBuffer,strategyBytes, 1, fp);
      fflush(fp);
    }

    virtual void writeToFile(FILE *fp)
    {
      writeToFileBase(fp);
    }

    int getSerializeSize()
    {
      char strategyCommandBuffer[MAX_BUF_SIZE] = {0};
      int strategyBytes = serialize(strategyCommandBuffer,false,0,0);
      return strategyBytes;
    }
    void deSerializeMemorySize(const char *buff)
    {
      COMMAND_CATEGORY_TYPE tmp1;
      PACKET_LENGTH_TYPE tmp2;
      int offset = 0;

      Serialization::deSerializeCommand(tmp1, buff, offset);
      Serialization::deSerializePacketLength(tmp2,buff,offset);
      deSerialize(buff + offset);
    }

    /**
     * @brief serializeMembers - serialize only members of class not response category
     * @param buf
     * @param bytes
     * @return
     */
    int serializeMembers(char * buf, int bytes)
    {
      for( int i=0; i<(int)_Members.size(); i++)
      {
        _Members[i]->serializeFun(buf,bytes);
      }

      CMD::BaseStrategyParamCommmand::serializeMembers(buf, bytes);

      return bytes;

    }
  };





}
#endif // BASECOMMANDS_H
