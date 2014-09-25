#ifndef SG_DEBUGLOG_DEFINES_H
#define SG_DEBUGLOG_DEFINES_H
namespace API2
{

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
    void openDebugLogFile(int strategyId, int clientId, const char *);

    /**
     * @brief timeStamp
     */
    void timeStamp();

    /**
     * @brief message
     * @param debug_message
     */
    void message(const char* debug_message);

    /**
     * @brief flushLog
     */
    void flushLog();



    /**
     * @brief value_of
     * @param name
     * @param value
     */
    template<class T> void value_of(const std::string& name, const T& value)
    {
      timeStamp();
      log_file  << name << " = " << value << "\n";
    }

    /**
     * @brief printToLog
     * @param debug_message
     * @param debug_var
     */
    template<class T> void printToLog(const char* debug_message,const T& debug_var)
    {
      timeStamp();
      log_file  << debug_message << " " << debug_var << "\n";
    }

    /**
     * @brief printToLog2
     * @param debug_message
     * @param debug_var1
     * @param debug_var2
     */
    template<class T,class K>  void printToLog2(const char* debug_message,const T& debug_var1, const K& debug_var2)
    {
      timeStamp();
      log_file  << debug_message << " " << debug_var1 << " " <<debug_var2 << "\n";
      std::cout  << debug_message << " " << debug_var1 << " " <<debug_var2 << "\n";
    }


    /**
     * @brief printToLogArr
     * @param debug_message
     * @param debug_var
     * @param index
     */
    template<class T> void printToLogArr(const char* debug_message,const T debug_var[],int index)
    {
      timeStamp();
      log_file  << debug_message;
      for(int i=0; i < index; i++)
        log_file  << " " << debug_var[i].getPrice() << "," << debug_var[i].getQty() << ";";
      log_file << "\n";
    }

  };

#define DEBUG_METHOD(DEBUG_OBJECT) { DEBUG_OBJECT->message(__FUNCTION__); }
#define DEBUG_MESSAGE(DEBUG_OBJECT,debug_message) {  DEBUG_OBJECT->message(debug_message); }  
#define DEBUG_VALUE_OF(DEBUG_OBJECT,variable) { DEBUG_OBJECT->value_of(#variable, variable); }
#define DEBUG_VARSHOW(DEBUG_OBJECT,debug_message,var) { DEBUG_OBJECT->printToLog(debug_message,var); }
#define DEBUG_VARSHOW2(DEBUG_OBJECT,debug_message,var1, var2) { DEBUG_OBJECT->printToLog2(debug_message,var1, var2); }
#define DEBUG_ARRAYSHOW(DEBUG_OBJECT,debug_message,var,var2) { DEBUG_OBJECT->printToLogArr(debug_message,var,var2); }
#define DEBUG_FLUSH(DEBUG_OBJECT) { DEBUG_OBJECT->flushLog(); }
}
#endif
