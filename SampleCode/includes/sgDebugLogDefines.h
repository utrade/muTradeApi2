#ifndef SG_DEBUGLOG_DEFINES_H
#define SG_DEBUGLOG_DEFINES_H
namespace API2
{

  class AbstractSingle
  {
    struct timeval _time;
    public:
    AbstractSingle();

    virtual std::string getString();
  };

  template<class T>
    class VariablePair : public AbstractSingle
  {
    //char  * _name;
    const std::string  _name;
    const T _value;
    public:
    VariablePair(const char *name,const T&value):
      _name(name),
      _value(value)
    {
      //  int _strlen = strlen(name);
      //  _name = new char[_strlen];
      //  memcpy(_name,name,_strlen);
    }

    std::string getString()
    {
      std::ostringstream oss;
      oss<<AbstractSingle::getString()<<_name<<":"<<_value;
      return oss.str();
    }
  };


  template<class T>
    class ArrayPair : public AbstractSingle
  {
    //char  * _name;
    const std::string  _name;
    T * _value;
    const int _length;

    public:
    ArrayPair(const char *name,const T *value,const int length):
      _name(name),_length(length)
    {
      _value = NULL;
      if(length <=0)
        return;
      int size = sizeof(T);
      _value = new T[size];
      memcpy(_value,value,size * _length);
    }
    ~ArrayPair()
    {
      delete [] _value;
    }
    std::string getString()
    {
      std::ostringstream oss;
      oss<<AbstractSingle::getString()<<_name<<":";
      for(int i = 0;i<_length;i++)
      {
        oss<<_value[i];
      }
      return oss.str();
    }
  };

  class Logs_Single : public  AbstractSingle
  {

    const API2::OrderConfirmation& _confirmation;
    public:
    Logs_Single(const API2::OrderConfirmation& conf); 
    std::string getString();
  };

  class StringSingle : public AbstractSingle
  {
    //char  * _name;
    const std::string  _name;
    public:
    StringSingle(const char *name);

    std::string getString();
  };

  class DebugLog ;
  class Logs
  {
    bool _printDepth;
    bool _flushLogs;
    bool _active;
    bool _printOnExit;
    DebugLog *_file;
    std::queue<AbstractSingle *> logs;
    void print();
    public:
    Logs();

    void releaseResources();
    void forcePrintLogs();

    void intialize(const bool &printDepth,
        const bool &flushLogs,
        const bool &printOnExit ,
        API2::DebugLog *file);

    void push(const API2::OrderConfirmation &confirmation);

    template<class T>
      void push(const char *name,const T &value)
      {
        VariablePair<T> * obj = new VariablePair<T>(name,value);
        logs.push(obj);
      }

    void push(const char *name);

    template<class T>
      void push(const char *name,const T *value,const int &size)
      {
        ArrayPair<T> *obj = new ArrayPair<T>(name,value,size);
        logs.push(obj);
      }

    void push(const char * name,const char * value);

    void printLogs();

  };
  /**
   * @brief The DebugLog class
   */
  class DebugLog
  {
    /* TO USE THIS CREATE INSTANCE AS _debugLog ALWAYS */

    /**
     * @brief log_file
     */
    std::ofstream log_file;

    /**
     * @brief ttime
     */
    struct timeval ttime;
    Logs _bufferedLogs;
    bool _useBufferedLogs;
    bool _silientMode ;
    public:

    /**
     * @brief DebugLog
     */
    DebugLog();

    ~DebugLog();

    /**
     * @brief DebugLog
     * @param strategyId
     */
    DebugLog(int strategyId, int);

    /**
     * @brief openDebugLogFile
     * @param strategyId
     * @param clientId
     */
    void openDebugLogFile(int strategyId, int clientId, const char *,
        const bool &silientMode = false,
        const bool &useBufferedLogs = false,
        const bool &printDepthOnConfirmation = false,
        const bool &flushLogs = false,
        const bool &printOnExit = false);

    /**
     * @brief timeStamp
     */
    void timeStamp();

    /**
     * @brief message
     * @param debug_message
     */
    void message(const char* debug_message);

    void messageSkipBuffLogs(const char* debug_message);

    void flushLogBuffLogs();

    void flushLog();

    /**
     * @brief value_of
     * @param name
     * @param value
     */
    template<class T> void value_of(const std::string& name, const T& value)
    {
      if(_silientMode)
        return;
      if(_useBufferedLogs == false)
      { 
      timeStamp();
      log_file  << name << " = " << value << "\n";
    }
      else
      {
        _bufferedLogs.push(name,value);
      }
    }

    /**
     * @brief printToLog
     * @param debug_message
     * @param debug_var
     */
    template<class T> void printToLog(const char* debug_message,const T& debug_var)
    {
      if(_silientMode)
        return;
      if(_useBufferedLogs == false)
      {
      timeStamp();
      log_file  << debug_message << " " << debug_var << "\n";
        //flushLog();
      }
      else
      {
        _bufferedLogs.push(debug_message,debug_var); 
      }
    }

    /**
     * @brief printToLog2
     * @param debug_message
     * @param debug_var1
     * @param debug_var2
     */
    template<class T,class K>  void printToLog2(const char* debug_message,const T& debug_var1, const K& debug_var2)
    {
      if(_silientMode)
        return;
      if(_useBufferedLogs == false)
      {
      timeStamp();
      log_file  << debug_message << " " << debug_var1 << " " <<debug_var2 << "\n";
      }
      else
      {
        T arr[2];
        arr[0] = debug_var1;
        arr[1] = debug_var2;
        _bufferedLogs.push(debug_message,arr,2);
      }
    }


    /**
     * @brief printToLogArr
     * @param debug_message
     * @param debug_var
     * @param index
     */
    template<class T> void printToLogArr(const char* debug_message,const T debug_var[],int index)
    {
      if(_silientMode)
        return;
      if(_useBufferedLogs == false)
      {
      timeStamp();
      log_file  << debug_message;
      for(int i=0; i < index; i++)
          log_file  << " " << debug_var[i];
      log_file << "\n";
    }
      else
      {
        _bufferedLogs.push(debug_message,debug_var,index);
      }
    }
    void printBufferedLogs();

    void saveConfirmation(const API2::OrderConfirmation &confirmation);

    void printBLogs();

  };
}


#define DEBUG_METHOD(DEBUG_OBJECT) { DEBUG_OBJECT->message(__FUNCTION__); }
#define DEBUG_MESSAGE(DEBUG_OBJECT,debug_message) {  DEBUG_OBJECT->message(debug_message); }  
#define DEBUG_VALUE_OF(DEBUG_OBJECT,variable) { DEBUG_OBJECT->value_of(#variable, variable); }
#define DEBUG_VARSHOW(DEBUG_OBJECT,debug_message,var) { DEBUG_OBJECT->printToLog(debug_message,var); }
#define DEBUG_VARSHOW2(DEBUG_OBJECT,debug_message,var1, var2) { DEBUG_OBJECT->printToLog2(debug_message,var1, var2); }
#define DEBUG_ARRAYSHOW(DEBUG_OBJECT,debug_message,var,var2) { DEBUG_OBJECT->printToLogArr(debug_message,var,var2); }
#define DEBUG_FLUSH(DEBUG_OBJECT) { DEBUG_OBJECT->flushLog(); }
#endif
