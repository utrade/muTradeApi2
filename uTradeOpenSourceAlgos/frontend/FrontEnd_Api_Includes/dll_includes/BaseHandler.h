#ifndef BASEHANDLER_H
#define BASEHANDLER_H
#include "baseStrategyWrapper.h"

class BaseStrategyWrapper;
class CommonMethodsWrapper;
class BaseHandler
{
    explicit BaseHandler()
    {

    }
    CommonMethodsWrapper *_commonWrapperPtr;

public:
    static BaseHandler& getInstance()
    {
       static BaseHandler instance;
       return instance;
    }

    void setCommonMethodWrapperPtr(CommonMethodsWrapper *commonPtr)
    {
        _commonWrapperPtr = commonPtr;
    }
    CommonMethodsWrapper *getCommonMethodWrapperPtr()
    {
      return _commonWrapperPtr;
    }
};



#endif // BASEHANDLER_H
