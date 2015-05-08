#ifndef API2_JAVA_EXTERNAL_INTERFACE_H
#define API2_JAVA_EXTERNAL_INTERFACE_H

#define CUSTOM_STRATEGY_CLASS_NAME "sampleStgy"
/// Add path where Java sources will be placed
#define API_JAVA_CLASS_PATH "-Djava.class.path=/code/sarvpriye/trinity-env/hft-bin"
#define CUSTOM_STRATEGY_NAME "JavaTest1"


#include <iostream>
namespace API2 {

  namespace ADAPTER {

    void JNIDriver(void *params, const std::string &customStrategyName, const std::string &customStrategyClassName);

  }
}

#endif //API2_PYTHON_EXTERNAL_INTERFACE_H
