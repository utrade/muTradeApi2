#include <cstddef>
#include <baseCommands.h>
#include "sample.h"

typedef void *(*driverPtr) (void *);
extern "C"
{
  void getDriver(void * params)
  {
    printf("Driver Called\n");
    TestStrategy::TestContext::driver(params);
  }

  std::string getFrontEndDesign()
  {
    char params_txt[] = {
      0x5b, 0x53, 0x59, 0x4d, 0x42, 0x4f, 0x4c, 0x5d, 0x0a, 0x53, 0x59, 0x4d,
      0x42, 0x4f, 0x4c, 0x20, 0x4c, 0x45, 0x47, 0x31, 0x3d, 0x55, 0x49, 0x4e,
      0x54, 0x36, 0x34, 0x3a, 0x43, 0x3a, 0x31, 0x3a, 0x53, 0x79, 0x6d, 0x62,
      0x6f, 0x6c, 0x20, 0x4c, 0x65, 0x67, 0x20, 0x31, 0x0a, 0x4f, 0x72, 0x64,
      0x65, 0x72, 0x20, 0x4d, 0x6f, 0x64, 0x65, 0x20, 0x31, 0x3d, 0x55, 0x43,
      0x48, 0x41, 0x52, 0x3a, 0x30, 0x3a, 0x30, 0x0a, 0x0a, 0x5b, 0x53, 0x54,
      0x52, 0x41, 0x54, 0x45, 0x47, 0x59, 0x5f, 0x50, 0x41, 0x52, 0x41, 0x4d,
      0x53, 0x5d, 0x0a, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0x3d, 0x31,
      0x0a, 0x53, 0x45, 0x50, 0x41, 0x52, 0x41, 0x54, 0x4f, 0x52, 0x3d, 0x31,
      0x0a, 0x4f, 0x72, 0x64, 0x65, 0x72, 0x20, 0x4c, 0x6f, 0x74, 0x73, 0x28,
      0x42, 0x29, 0x3d, 0x55, 0x49, 0x4e, 0x54, 0x36, 0x34, 0x3a, 0x53, 0x50,
      0x49, 0x4e, 0x42, 0x4f, 0x58, 0x3a, 0x30, 0x3a, 0x39, 0x39, 0x39, 0x39,
      0x39, 0x39, 0x39, 0x3a, 0x31, 0x30, 0x3a, 0x31, 0x3a, 0x4f, 0x72, 0x64,
      0x65, 0x72, 0x20, 0x4c, 0x6f, 0x74, 0x73, 0x28, 0x42, 0x29, 0x3a, 0x31,
      0x3a, 0x30, 0x0a, 0x54, 0x6f, 0x74, 0x61, 0x6c, 0x20, 0x4c, 0x6f, 0x74,
      0x73, 0x28, 0x42, 0x29, 0x3d, 0x55, 0x49, 0x4e, 0x54, 0x36, 0x34, 0x3a,
      0x53, 0x50, 0x49, 0x4e, 0x42, 0x4f, 0x58, 0x3a, 0x30, 0x3a, 0x39, 0x39,
      0x39, 0x39, 0x39, 0x39, 0x39, 0x3a, 0x31, 0x30, 0x30, 0x3a, 0x31, 0x3a,
      0x54, 0x6f, 0x74, 0x61, 0x6c, 0x20, 0x4c, 0x6f, 0x74, 0x73, 0x28, 0x42,
      0x29, 0x3a, 0x31, 0x3a, 0x30, 0x0a, 0x4f, 0x72, 0x64, 0x65, 0x72, 0x20,
      0x4c, 0x6f, 0x74, 0x73, 0x28, 0x53, 0x29, 0x3d, 0x55, 0x49, 0x4e, 0x54,
      0x36, 0x34, 0x3a, 0x53, 0x50, 0x49, 0x4e, 0x42, 0x4f, 0x58, 0x3a, 0x30,
      0x3a, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x3a, 0x31, 0x30, 0x3a,
      0x31, 0x3a, 0x4f, 0x72, 0x64, 0x65, 0x72, 0x20, 0x4c, 0x6f, 0x74, 0x73,
      0x28, 0x53, 0x29, 0x3a, 0x31, 0x3a, 0x30, 0x0a, 0x54, 0x6f, 0x74, 0x61,
      0x6c, 0x20, 0x4c, 0x6f, 0x74, 0x73, 0x28, 0x53, 0x29, 0x3d, 0x55, 0x49,
      0x4e, 0x54, 0x36, 0x34, 0x3a, 0x53, 0x50, 0x49, 0x4e, 0x42, 0x4f, 0x58,
      0x3a, 0x30, 0x3a, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x3a, 0x31,
      0x30, 0x30, 0x3a, 0x31, 0x3a, 0x54, 0x6f, 0x74, 0x61, 0x6c, 0x20, 0x4c,
      0x6f, 0x74, 0x73, 0x28, 0x53, 0x29, 0x3a, 0x31, 0x3a, 0x30, 0x0a, 0x50,
      0x72, 0x69, 0x63, 0x65, 0x28, 0x42, 0x29, 0x3d, 0x46, 0x4c, 0x4f, 0x41,
      0x54, 0x3a, 0x44, 0x53, 0x50, 0x49, 0x4e, 0x42, 0x4f, 0x58, 0x3a, 0x30,
      0x2e, 0x30, 0x30, 0x3a, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x2e, 0x30,
      0x30, 0x3a, 0x32, 0x30, 0x30, 0x2e, 0x30, 0x30, 0x3a, 0x30, 0x2e, 0x30,
      0x35, 0x3a, 0x32, 0x3a, 0x50, 0x72, 0x69, 0x63, 0x65, 0x28, 0x42, 0x29,
      0x3a, 0x31, 0x3a, 0x30, 0x0a, 0x50, 0x72, 0x69, 0x63, 0x65, 0x28, 0x53,
      0x29, 0x3d, 0x46, 0x4c, 0x4f, 0x41, 0x54, 0x3a, 0x44, 0x53, 0x50, 0x49,
      0x4e, 0x42, 0x4f, 0x58, 0x3a, 0x30, 0x2e, 0x30, 0x30, 0x3a, 0x39, 0x39,
      0x39, 0x39, 0x39, 0x39, 0x2e, 0x30, 0x30, 0x3a, 0x33, 0x30, 0x30, 0x2e,
      0x30, 0x30, 0x3a, 0x30, 0x2e, 0x30, 0x35, 0x3a, 0x32, 0x3a, 0x50, 0x72,
      0x69, 0x63, 0x65, 0x28, 0x53, 0x29, 0x3a, 0x31, 0x3a, 0x30, 0x0a, 0x53,
      0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0x3d, 0x31, 0x0a, 0x53, 0x45, 0x50,
      0x41, 0x52, 0x41, 0x54, 0x4f, 0x52, 0x3d, 0x31, 0x0a, 0x0a, 0x5b, 0x4f,
      0x54, 0x48, 0x45, 0x52, 0x5d, 0x0a
    };
    unsigned int params_txt_len = 522;
    return std::string(params_txt,params_txt_len);
  }

  std::string getVersion()
  {
    return API2_VERSION_STRING;
  }
}
