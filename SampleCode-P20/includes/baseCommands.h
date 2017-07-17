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
namespace API2{

  using namespace Serialization;
  /**
   * @brief The BaseType class
   */
  class BaseType
  {
    CREATE_FIELD(std::string, String);
    public:


    virtual ~BaseType(){}

    /**
     * @brief serializeFun
     * @param buf
     * @param bytes
     */
    virtual void serializeFun(char *buf, int &bytes)=0;

    /**
     * @brief deSerializeFun
     * @param buf
     * @param offset
     */
    virtual void deSerializeFun(const char *buf, int &offset)=0;

    /**
     * @brief dump
     */
    virtual void dump()=0;

    /**
     * @brief getKeyValueString
     */
    virtual std::string getKeyValueString()=0;


    /**
     * @brief printType
     */
    virtual void printType() = 0;

    /**
     * @brief BaseType
     * @param stringType
     */
    BaseType(const std::string &stringType)
    {
      setString(stringType);
    }

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
    DerivedType(const std::string &type):
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
    void printType()
    {
      std::cout<<"\n typename "<<typeid(_Value).name()<<std::endl;
    }

    /**
     * @brief serializeFun
     * @param buf
     * @param bytes
     */
    void serializeFun(char *buf, int &bytes)
    {
      serialize(_Value, buf, bytes);
    }

    /**
     * @brief deSerializeFun
     * @param buf
     * @param offset
     */
    void deSerializeFun(const char *buf, int &offset)
    {
      printf("calling deSerialize in main \n");
      deSerialize(_Value, buf, offset);
    }
#if 1

    /**
     * @brief serialize
     * @param mapULong
     * @param buf
     * @param bytes
     */
    void serialize(
        const MapULong &mapULong,
        char *buf,
        int &bytes)
    {
      UNSIGNED_LONG tmpLong = 0;
      for(MapULongIter i= mapULong.begin(); i!= mapULong.end(); i++)
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
      UNSIGNED_LONG tmp1,tmp2= 0;
      for(int i=0; i<getCount();i++)
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
          char *buf,int &bytes)
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
#endif

    /**
     * @brief dump
     */
    void dump()
    {
      std::cout<<getKeyValueStringImpl(getValue());
    }
    /**
     * @brief getKeyValueString
     */
    std::string getKeyValueString()
    {
      return getKeyValueStringImpl(getValue());
    }

    /**
     * @brief getKeyValueStringImpl
     * @param val
     */
    template<class M>
      std::string getKeyValueStringImpl(const M &val)
      {
        std::ostringstream out;
        out << std::endl << getString() <<"--->"<< val;
        return out.str();
      }
    std::string getKeyValueStringImpl(const API2::AccountDetail &val)
    {
      std::ostringstream out;
      out << std::endl << getString() <<"--->"<< val.dump();
      return out.str();
    }

    /**
     * @brief getKeyValueStringImpl
     * @param val
     */
    std::string getKeyValueStringImpl(const char &val)
    {
      std::ostringstream out;
      out << std::endl << getString() <<"--->"<< (short)val;
      return out.str();
    }

    /**
     * @brief getKeyValueStringImpl
     * @param val
     */
    std::string getKeyValueStringImpl(const UNSIGNED_CHARACTER &val)
    {
      std::ostringstream out;
      out << std::endl << getString() <<"--->"<< (short)val;
      return out.str();
    }

    /**
     * @brief getKeyValueStringImpl
     * @param val
     */
    std::string getKeyValueStringImpl(const MapULong &val)
    {
      std::ostringstream out;
      out <<"========" << std::endl << getString() << "========";
      for(MapULongIter iter = _Value.begin(); iter != _Value.end(); iter ++)
      {
        out << std::endl << iter->first <<"--->"<< iter->second;
      }
      return out.str();
    }

  };


  typedef std::vector<BaseType *> BaseTypeVector;

  /**
   * @brief The AbstractUserParams class
   */
  class AbstractUserParams
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

    public:
    /**
     * @brief AbstractUserParams
     */
    AbstractUserParams()
    {
      initialize();
    }

    /**
     * @brief initialize
     */
    virtual void initialize()
    { 
      _Members.clear();
      SET_DERIVED_TYPE( StrategyVersion, 0);
      SET_DERIVED_TYPE( TransactionType, 0);
      SET_DERIVED_TYPE( ClientId, 0);
      SET_DERIVED_TYPE( StrategyId, 0);
      SET_DERIVED_TYPE( AdminTokenId, 0);
      SET_DERIVED_TYPE( SequenceNumber, 0);
    }

    int serializeBase(char *buf, bool isResponse, UNSIGNED_CHARACTER cat, UNSIGNED_CHARACTER comCat)
    {
      int bytes = 0;

      bytes = sizeof(UNSIGNED_SHORT);  // Leave 2 bytes for packet size
      if (isResponse)
      {
        Serialization::serialize(cat,buf,bytes);
      }
      else
      {
        Serialization::serialize(comCat,buf,bytes);
      }
      Serialization::serialize(getStrategyVersion(),buf,bytes);
      Serialization::serialize(getTransactionType(),buf,bytes);
      Serialization::serialize(getClientId(),buf,bytes);
      Serialization::serialize(getStrategyId(),buf,bytes);
      Serialization::serialize(getAdminTokenId(),buf,bytes);
      Serialization::serialize(getSequenceNumber(),buf,bytes);
      
      int dummyBytes = 0;
      /**
       *Put size as the first field after deducting 2 bytes reserved for size
       */
      Serialization::serialize((UNSIGNED_SHORT)(bytes-sizeof(UNSIGNED_SHORT)),buf,dummyBytes);

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
    int serialize(char *buf, bool isResponse, UNSIGNED_CHARACTER cat, UNSIGNED_CHARACTER comCat)
    {
      int bytes = 0;

      bytes = sizeof(UNSIGNED_SHORT);  // Leave 2 bytes for packet size
      if (isResponse)
      {
        Serialization::serialize(cat,buf,bytes);
      }
      else
      {
        Serialization::serialize(comCat,buf,bytes);
      }

      for( int i=0; i<(int)_Members.size(); i++)
      {
        //printf("Serializing :%s \n",_Members[i]->getString().c_str());
        _Members[i]->serializeFun(buf,bytes);
      }

      int dummyBytes = 0;
      /**
       *Put size as the first field after deducting 2 bytes reserved for size
       */
      Serialization::serialize((UNSIGNED_SHORT)(bytes-sizeof(UNSIGNED_SHORT)),buf,dummyBytes);

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
        UNSIGNED_CHARACTER cat,
        UNSIGNED_CHARACTER comCat,
        int apiIndex)
    {
      int bytes = 0;

      bytes = sizeof(UNSIGNED_SHORT);  // Leave 2 bytes for packet size
      if (isResponse)
      {
        Serialization::serialize(cat,buf,bytes);
      }
      else
      {
        Serialization::serialize(comCat,buf,bytes);
      }

      Serialization::serialize(apiIndex,buf,bytes);
      for( int i=0; i<(int)_Members.size(); i++)
      {
        //printf("Serializing :%s \n",_Members[i]->getString().c_str());
        _Members[i]->serializeFun(buf,bytes);
      }

      int dummyBytes = 0;
      /**
       *Put size as the first field after deducting 2 bytes reserved for size
       */
      Serialization::serialize((UNSIGNED_SHORT)(bytes-sizeof(UNSIGNED_SHORT)),buf,dummyBytes);

      return bytes;
    }

    /**
     * @brief deSerialize
     * @param buf
     */
    void deSerialize(const char* buf)
    {
//      initialize();
      int offset =0;

      for( int i=0; i<(int)_Members.size(); i++)
      {
        //printf("Deserializing :%s  \n",_Members[i]->getString().c_str());
        _Members[i]->deSerializeFun(buf,offset);
      }
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
      char strategyCommandBuffer[MAX_BUF_SIZE];
      int strategyBytes = serialize((char *)strategyCommandBuffer,false,0,0);
      fwrite((void*)strategyCommandBuffer,strategyBytes, 1, fp);
      fflush(fp);
    }
    void writeToFileBase(FILE *fp)
    {
      char strategyCommandBuffer[MAX_BUF_SIZE];
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
      char strategyCommandBuffer[MAX_BUF_SIZE];
      int strategyBytes = serialize(strategyCommandBuffer,false,0,0);
      return strategyBytes;
    }
    void deSerializeMemorySize(const char *buff)
    {
      UNSIGNED_SHORT tmp1;
      UNSIGNED_CHARACTER tmp2;
      int offset = 0;
      Serialization::deSerialize(tmp1, buff, offset);
      Serialization::deSerialize(tmp2,buff,offset);
      deSerialize(buff + offset);
    }
  };





}
#endif // BASECOMMANDS_H
