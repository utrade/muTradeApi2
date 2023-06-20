#ifndef API2_PYTHON_EXTERNAL_INTERFACE_H
#define API2_PYTHON_EXTERNAL_INTERFACE_H
#define PYTHON_STRATEGY_CLASS_NAME "sample"
#define PYTHON_STRATEGY_FILE_NAME "pyTest1"
#include <iostream>
namespace API2 {

namespace ADAPTER {

namespace PY {

void PyDriver(void *params, const std::string &strategyName, const std::string &pyStrategyFileName, const std::string &pyStrategyClassName);

}
}
}

#endif //API2_PYTHON_EXTERNAL_INTERFACE_H
