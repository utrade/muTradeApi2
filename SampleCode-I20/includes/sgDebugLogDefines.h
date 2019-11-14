#ifndef SG_DEBUGLOG_DEFINES_H
#define SG_DEBUGLOG_DEFINES_H
#include <fstream>
#include <sharedResponse.h>
#include <queue>

namespace API2
{

  class AbstractSingle
  {
    struct timeval _time;
    public:
    AbstractSingle();

    virtual std::string getString();
    virtual ~AbstractSingle(){}
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

  template<class T,class V>
    class VariablePair2 : public AbstractSingle
  {
    //char  * _name;
    const std::string  _name;
    const T _value1;
    const V _value2;
    public:
    VariablePair2(const char *name,
        const T&value1,
        const V &value2):
      _name(name),
      _value1(value1),
      _value2(value2)
    {
    }

    std::string getString()
    {
      std::ostringstream oss;
      oss<<AbstractSingle::getString()<<_name<<":"<<_value1
        <<":"<<_value2;
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
      _value = new T[_length];
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

 struct ConfirmationPrintData
  {
    CREATE_FIELD( DATA_TYPES::CLORDER_ID, ClOrderId );  
    CREATE_FIELD( DATA_TYPES::SYMBOL_ID, SymbolId ); 
    CREATE_FIELD( DATA_TYPES::QTY, LastFillQuantity ); 
    CREATE_FIELD( DATA_TYPES::PRICE, LastFillPrice ); 
    CREATE_FIELD( DATA_TYPES::OrderStatus, OrderStatus ); 
    CREATE_FIELD( DATA_TYPES::OrderMode, OrderMode ); 
    CREATE_FIELD( DATA_TYPES::QTY, OrderQuantity ); 
    CREATE_FIELD( DATA_TYPES::PRICE, OrderPrice ); 
    CREATE_FIELD( DATA_TYPES::QTY, IOCCanceledQuantity );
    public:
    ConfirmationPrintData(const API2::OrderConfirmation& conf );
  };

  class Logs_Single : public  AbstractSingle
  {
    const ConfirmationPrintData _confirmationPrint;
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

    /**
     * @brief _logs -   queue to store log objects
     * @note            this is used when single thread is being used to push logs and pop them and dump in ofstream
     */
    std::queue<AbstractSingle *> _logs;

    /////////////   Locked logs ////////////

    //  The below structures are used when logging is done in multiple threads
    //  single thread will add to logs
    //  and multiple threads may pop the logs and dump in ofstream
    //  _logVector1, _logVector2 : one of these will be used for pushing the logs and the other will be dumped

    /**
     * @brief _useLocksWhilePoppingLogsAndFileDumping   -   access logs in multiple threads or not
     */
    bool _useLocksWhilePoppingLogsAndFileDumping;

    /**
     * @brief _spinLockForFileLogging   -   spin lock on _file logging
     */
    volatile int _spinLockForFileLogging;

    /**
     * @brief _spinLock -   lock over the log vectors
     */
    volatile int _spinLock;

    /**
     * @brief _logVector1   -   vector to store logs
     */
    std::vector<AbstractSingle *> _logVector1;
    /**
     * @brief _logVector2   -   vector to store logs
     */
    std::vector<AbstractSingle *> _logVector2;

    /**
     * @brief _logVector    -   reference to vector on which next log will be pushed and from which logs need to be popped and dumped
     */
    std::vector<AbstractSingle *> *_logVector;

    //////////////  Locked logs end ////////////

    void print();
    public:
    Logs();

    void releaseResources();
    void forcePrintLogs();

    /**
     * @brief intialize     -   initialize the object
     * @param printDepth    -   unused for now
     * @param flushLogs     -   if logs need to be flushed in print
     * @param printOnExit   -   if false, logs will be dumped to ofstream in printLogs
     * @param file          -   debug log file handle
     * @param useLocksWhilePoppingLogsAndFileDumping    -   use multiple threads when accessing logs
     */
    void intialize(
        const bool &printDepth,
        const bool &flushLogs,
        const bool &printOnExit ,
        API2::DebugLog *file,
        const bool useLocksWhilePoppingLogsAndFileDumping = false);

    void push(const API2::OrderConfirmation &confirmation);

    /**
     * @brief takeLock  -   take lock on _logVector
     */
    void takeLock();

    /**
     * @brief releaseLock   -   release lock on _logVector
     */
    void releaseLock();

    /**
     * @brief pushToLogs  -   push to logs vector or queue depending on configuration
     * @param value
     */
    template<class T>
      void pushToLogs(const T &value)
      {
        if(_useLocksWhilePoppingLogsAndFileDumping)
        {
          takeLock();
          _logVector->push_back(value);
          releaseLock();
        }
        else
        {
          _logs.push(value);
        }
      }

    template<class T>
      void push(const char *name,const T &value)
      {
        VariablePair<T> * obj = new VariablePair<T>(name,value);

        pushToLogs(obj);
      }

    void push(const char *name);

    template<class T>
      void push(const char *name,const T *value,const int &size)
      {
        ArrayPair<T> *obj = new ArrayPair<T>(name,value,size);

        pushToLogs(obj);
      }

    template<class T,class V>
      void push(const char *name,const T &value1,const V &value2)
      {
        VariablePair2<T,V> * obj = new VariablePair2<T,V>(name,value1,value2);

        pushToLogs(obj);
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
    bool _silentMode ;
    public:

    /**
     * @brief DebugLog
     */
    DebugLog();

    /**
     * @brief DebugLog
     * @param fileName
     * @param silientMode
     * @param useBufferedLogs
     * @param printDepthOnConfirmation
     * @param flushLogs
     * @param printLogsOnExit
     */
    DebugLog(
        const std::string &fileName,
        const bool &silientMode = false,
        const bool &useBufferedLogs = false,
        const bool &printDepthOnConfirmation = false,
        const bool &flushLogs = false,
        const bool &printLogsOnExit = false);

    ~DebugLog();

    /**
     * @brief DebugLog
     * @param strategyId
     */
    DebugLog(int strategyId, int);

    /**
     * @brief openDebugLogFile  -   open debug log file
     * @param strategyId        -   strategy id : used to create file name
     * @param clientId          -   dealer id : used to create file name
     * @param silientMode       -   configurable logging on / off
     * @param useBufferedLogs   -   use internal queuing instead of direct writing to ofstream
     * @param printDepthOnConfirmation  -   print depth with confirmation log dumping
     * @param flushLogs -   if logs need to be flushed by buffered logs
     * @param printOnExit
     * @param useLocksWhilePoppingLogsAndFileDumping    -   use locking and multiple threads for log dumping
     */
    void openDebugLogFile(
        int strategyId,
        int clientId,
        const char *,
        const bool &silientMode = false,
        const bool &useBufferedLogs = false,
        const bool &printDepthOnConfirmation = false,
        const bool &flushLogs = false,
        const bool &printOnExit = false,
        const bool useLocksWhilePoppingLogsAndFileDumping = false);

    /**
     * @brief openDebugLogFile  -   open debug log file
     * @param filename          -   file name
     * @param silientMode       -   configurable logging on / off
     * @param useBufferedLogs   -   use internal queuing instead of direct writing to ofstream
     * @param printDepthOnConfirmation  -   print depth with confirmation log dumping
     * @param flushLogs -   if logs need to be flushed by buffered logs
     * @param printOnExit
     * @param useLocksWhilePoppingLogsAndFileDumping    -   use locking and multiple threads for log dumping
     */
    void openDebugLogFile(
        std::ostringstream &filename,
        const bool &silentMode = false,
        const bool &useBufferedLogs = false,
        const bool &printDepthOnConfirmation = false,
        const bool &flushLogs = false,
        const bool &printOnExit = false,
        const bool useLocksWhilePoppingLogsAndFileDumping = false);

    /**
     * @brief timeStamp
     */
    void timeStamp();

    /**
     * @brief message
     * @param debug_message
     */
    void message(const char* debug_message);

    void message(const std::string &debugMessage);

    void messageSkipBuffLogs(const char* debug_message);

    void flushLogBuffLogs();

    void flushLog(bool printNextLine = true);

    /**
     * @brief value_of
     * @param name
     * @param value
     */
    template<class T> void value_of(const std::string& name, const T& value)
    {
      if(_silentMode)
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
      if(_silentMode)
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
    template<class T> void printToLog2(const char* debug_message,const char* debug_var1, const T& debug_var2)
    {
      if(_silentMode)
        return;
      if(_useBufferedLogs == false)
      {
        timeStamp();
        log_file  << debug_message << " " << debug_var1 << " " <<debug_var2 << "\n";
      }
      else
      {
        _bufferedLogs.push(debug_message,std::string(debug_var1),debug_var2); 
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
      if(_silentMode)
        return;
      if(_useBufferedLogs == false)
      {
      timeStamp();
      log_file  << debug_message << " " << debug_var1 << " " <<debug_var2 << "\n";
      }
      else
      {
        _bufferedLogs.push(debug_message,debug_var1,debug_var2); 
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
      if(_silentMode)
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
#define DEBUG_METHOD_DETAILED(DEBUG_OBJECT) { DEBUG_OBJECT->message(__PRETTY_FUNCTION__); }
#define DEBUG_MESSAGE(DEBUG_OBJECT,debug_message) {  DEBUG_OBJECT->message(debug_message); }  
#define DEBUG_VALUE_OF(DEBUG_OBJECT,variable) { DEBUG_OBJECT->value_of(#variable, variable); }
#define DEBUG_VARSHOW(DEBUG_OBJECT,debug_message,var) { DEBUG_OBJECT->printToLog(debug_message,var); }
#define COND_DEBUG_VARSHOW(isShow, dbgLog, msg, data)\
if( isShow )\
  DEBUG_VARSHOW(dbgLog, msg, data);
#define DEBUG_VARSHOW2(DEBUG_OBJECT,debug_message,var1, var2) { DEBUG_OBJECT->printToLog2(debug_message,var1, var2); }
#define DEBUG_ARRAYSHOW(DEBUG_OBJECT,debug_message,var,var2) { DEBUG_OBJECT->printToLogArr(debug_message,var,var2); }
#define DEBUG_FLUSH(DEBUG_OBJECT) { DEBUG_OBJECT->flushLog(); }
#endif
