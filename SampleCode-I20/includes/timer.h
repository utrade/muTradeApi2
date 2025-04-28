#ifndef API2_TIMER_H
#define API2_TIMER_H

#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW CLOCK_MONOTONIC
#endif

#include <ctime>
#include <sys/time.h>

namespace API2 
{
  namespace TIMER
  {
    class Timer
    {
      public:

        Timer();

        ~Timer() { }

        void setTimer(unsigned int setTimeInSeconds, bool usePreviousCalculatedTime = false);

        void setTimerMilliSeconds(unsigned int setTimeInMilliSeconds, bool usePreviousCalculatedTime = false);

        void setTimerMicroSeconds(unsigned int setTimeInMicroSeconds, bool usePreviousCalculatedTime = false);

        unsigned int timeSinceSet(unsigned int interval);

        bool isTimerExpired() const;

        bool isOneLessEndTime();

        void clearTimer();

        signed long static getMicroSecondDiff(const struct timeval &endTime,const struct timeval &startTime);

        bool isTimerSet() { return _isSet; }

        timespec diff(timespec start, timespec end) const;

      private:

        timespec      _endTime;
        timespec      _oneLessEndTime;
        bool          _isSet;
    };
  }
}

#endif  //  API2_TIMER_H
