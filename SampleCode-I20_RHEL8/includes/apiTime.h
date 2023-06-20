#ifndef API2_TIME_H
#define API2_TIME_H
#include <sharedDefines.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <fstream>

#ifdef HFT_LATENCY_BENCHMARKING
#define HFT_Start_Timer_Define\
  struct timespec tStart, tStop; \
  API2::COMMON::getTime(&tStart);

#define HFT_Start_Timer\
  API2::COMMON::getTime(&tStart);

#define HFT_Record_Timer(histogram)\
  API2::COMMON::getTime(&tStop); \
  histogram.record(API2::COMMON::diff(tStart,tStop).tv_nsec);
//#define BENCHMARK_MARKET_DATA
#else
#define HFT_Start_Timer_Define
#define HFT_Start_Timer
#define HFT_Record_Timer(histogram)
#endif

namespace ut
{
  ///
  /// \brief spinlock_t
  ///
  typedef volatile int spinlock_t;
}

namespace API2 {

  namespace COMMON {

    void getTime(struct timespec* t);

    struct timespec diff(struct timespec start, struct timespec end);

    struct LatencyNumbers
    {
      /**
       * @brief _lock - used to synchronize the usage of _values and _outFile when used in multiple threads
       */
      ut::spinlock_t _lock;

      std::string _dataSetName;
      std::vector<UNSIGNED_LONG> _values;
      void record(UNSIGNED_LONG value);
      std::ofstream _outFile;
      UNSIGNED_LONG getMedian();
      double getMean();
      void dumpDataSet(std::string fileName="");
      explicit LatencyNumbers(const std::string &name);
      LatencyNumbers();
      void setName(const std::string &name);
    };

  }

}


#endif //API2_TIME_H
