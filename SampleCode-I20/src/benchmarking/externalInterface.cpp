#include <cstddef>
#include <baseCommands.h>
#include "sample.h"
extern "C"
{
void getDriver(void * params)
{
    printf("Calling API 2.0 Benchmarking \n");
    API2::BENCHMARK::BenchmarkingDriver(params);
}
std::string getFrontEndDesign()
{
    char params_txt[] = {
    };
    unsigned int params_txt_len = 0;

    return std::string(params_txt,params_txt_len);
}

}
