#ifndef API2_CMD_DEFINES_H
#define API2_CMD_DEFINES_H


#define CREATE_FIELD_DECLARATION( TYPE, NAME ) \
  public : TYPE get##NAME() const ; \
  public : TYPE &getRef##NAME() ; \
  public : void set##NAME(const TYPE &value ) ; \
  private : TYPE _##NAME

#define CREATE_FIELD_DEFINATION( TYPE, NAME ,CLASS) \
  TYPE ##CLASS::get##NAME() const ; \
  TYPE &  ##CLASS::getRef##NAME() ; \
  void ##CLASS::set##NAME(const TYPE &value )

#define CREATE_FIELD( TYPE, NAME ) \
  public : TYPE get##NAME() const {  return _##NAME ; } \
  public : TYPE &getRef##NAME() {  return _##NAME ; } \
  public : void set##NAME(const TYPE &value ) { _##NAME = value ; } \
  private : TYPE _##NAME



#define CONVERT_TO_STRING(x) #x

#define CREATE_FIELD_DERIVED( TYPE, NAME ) \
  public : TYPE get##NAME() const {  return _##NAME.getValue() ; } \
  public : TYPE &getRef##NAME() {  return _##NAME.getRefValue() ; } \
  public : void set##NAME(const TYPE &value ) { _##NAME.setValue(value); } \
  private : DerivedType<TYPE> _##NAME

#define CREATE_FIELD_DERIVED( TYPE, NAME ) \
  public : TYPE get##NAME() const {  return _##NAME.getValue() ; } \
  public : TYPE &getRef##NAME() {  return _##NAME.getRefValue() ; } \
  public : void set##NAME(const TYPE &value ) { _##NAME.setValue(value); } \
  private : DerivedType<TYPE> _##NAME

#define CREATE_FIELD_PTR( TYPE, NAME ) \
  public : TYPE* get##NAME() {  return _##NAME ; } \
  public : TYPE* &getRef##NAME() {  return _##NAME ; } \
  public : void set##NAME(TYPE *value ) { _##NAME = value ; } \
  private : TYPE *_##NAME

#define CREATE_CONSTRUCTORS( Cls, Command, Response, VERSION) \
  public:     static const UNSIGNED_LONG STRATEGY_VERSION = VERSION; \
  public:     Cls(const char *buf) {    deSerialize(buf);} \
  public:     Cls(){initialize();} \
  public: int serialize(char* buf, bool isResponse = false){ \
  return AbstractUserParams::serialize(buf, \
  isResponse, (UNSIGNED_CHARACTER)Response, \
  (UNSIGNED_CHARACTER)Command);}

#define DECLARE_CONSTRUCTORS( Cls, VERSION) \
  public:     static const UNSIGNED_LONG BACK_END_STRATEGY_VERSION = VERSION; \
  public:     Cls(const char *buf); \
  public:     Cls();\
  public: int serialize(char* buf, bool isResponse = false); \
  public: void initialize();\
  public: bool isVersionValid(){return BACK_END_STRATEGY_VERSION == getStrategyVersion(); } \
  public: UNSIGNED_LONG getBackendStrategyVersion() const { return BACK_END_STRATEGY_VERSION;}

#define DEFINE_CONSTRUCTORS( Cls, Cmd, Response) \
  Cls::Cls(const char *buf){ initialize();deSerialize(buf);}\
  Cls::Cls(){initialize();} \
  int Cls::serialize(char* buf, bool isResponse){ \
  return AbstractUserParams::serialize(buf, \
  isResponse, (UNSIGNED_CHARACTER)Response, \
  (UNSIGNED_CHARACTER)Cmd);}




#define INIT_DERIVED_TYPE( NAME, VALUE ) \
  _##NAME(CONVERT_TO_STRING(NAME))

#define SET_DERIVED_TYPE( NAME, VALUE) \
  _##NAME.setString(CONVERT_TO_STRING(NAME)); \
    set##NAME(VALUE); \
  addType(&_##NAME)

#define DEBUG_METHOD(DEBUG_OBJECT) { DEBUG_OBJECT->message(__FUNCTION__); }
#define DEBUG_MESSAGE(DEBUG_OBJECT,debug_message) {  DEBUG_OBJECT->message(debug_message); }
#define DEBUG_VALUE_OF(DEBUG_OBJECT,variable) { DEBUG_OBJECT->value_of(#variable, variable); }
#define DEBUG_VARSHOW(DEBUG_OBJECT,debug_message,var) { DEBUG_OBJECT->printToLog(debug_message,var); }
#define DEBUG_VARSHOW2(DEBUG_OBJECT,debug_message,var1, var2) { DEBUG_OBJECT->printToLog2(debug_message,var1, var2); }
#define DEBUG_ARRAYSHOW(DEBUG_OBJECT,debug_message,var,var2) { DEBUG_OBJECT->printToLogArr(debug_message,var,var2); }
#define DEBUG_FLUSH(DEBUG_OBJECT) { DEBUG_OBJECT->flushLog(); }


#endif // API2_CMD_DEFINES_H
