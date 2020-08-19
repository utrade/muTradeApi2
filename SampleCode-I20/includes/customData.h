#ifndef CUSTOM_DATA_H
#define CUSTOM_DATA_H

namespace API2
{
  /**
   * @description Base class of the custom data which is passed while
   * generating callBack on all API strategy of a specific dealer, with the
   * help of function
   * "sendCustomDataToStrategiesDealerWise(dealerId,CustomDataPtr)".
   * User can write his own customData class which should be inherited by this
   * class and then pass it in the function call of
   * sendCustomDataToStrategiesDealerWise
   *
   * Example :
   * call sendCustomDataToStrategiesDealerWise(dealerId ,CustomDataSharedPtr ptr); from API
   * This calls to virtual method receiveCustomData
   * API's receiveCustomData(customDataSharedPtr ptr) is called
   * cast ptr into derived class ptr and perform the required functionality
   *
   * Note : Pass std::shared_ptr of Class CustomData
   */ 
  class CustomData
  {
      public:
         CustomData()
         {}
 
  };

}

#endif
