#ifndef API2_REQUEST_RESPONSE_H
#define API2_REQUEST_RESPONSE_H
#include "sharedDefines.h"
#include <string>
#include "cmdDefines.h"
#include "sharedCommands.h"

namespace API2
{
class API2_Request
{
    char _request[API_REQUEST_SIZE];
public:
    void setRequest(const char *request);
    const char * getRequest() const;
    API2_Request();
    API2_Request(const char* buf, int &offset);
    int serialize(char *buf, COMMAND_CATEGORY_TYPE commandCat);
    void intialize();
    void dump();
};

class API2_Response
{
    int _apiIndex; //negative means api not loaded
    char _request[API_REQUEST_SIZE];
    int _frontendDesignSize;
    std::string _frontendDesign;
    //comma seperated
    CREATE_FIELD(std::string, CustomTableHeader);
    
public:

    void setRequest(const char *request);
    const char * getRequest() const;

    void setApiIndex(int apiIndex);
    int getApiIndex() const;

    void setFrontendDesignSize(int frontendDesignSize);
    int getFrontendDesignSize() const ;

    void setFrontendDesign(const std::string &frontendDesign);
    std::string getFrontendDesign() const ;

    API2_Response();
    API2_Response(const char* buf, int &offset);
    int serialize(char *buf);
    int serialize(char *buf, COMMAND_CATEGORY_TYPE cat);
    void intialize();
    void dump();

};
class API2_CustomResponse
{
    CREATE_FIELD(UNSIGNED_INTEGER, ApiIndex);
    CREATE_FIELD(UNSIGNED_INTEGER, RowId);
    CREATE_FIELD(UNSIGNED_INTEGER, StrategyId);
    CREATE_FIELD(UNSIGNED_INTEGER, AdminTokenId);
    //comma seperated , order same as CustomTableHeader in API2_Response
    CREATE_FIELD(std::string, CustomData);
    CREATE_FIELD(StringList, UiDataPair);
public:
    void dump();
    API2_CustomResponse();
    API2_CustomResponse(const char* buf, int &offset);
    int serialize(char *buf);
    int serialize(char *buf, COMMAND_CATEGORY_TYPE cat);
};


}
#endif
