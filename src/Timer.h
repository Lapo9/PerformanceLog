
#ifndef PERFORMANCELOG_TIMER
#define PERFORMANCELOG_TIMER

#include <chrono>
#include <vector>
#include <functional>

#include "Session.h"

namespace PerformanceLog {

    class Timer {
     public:
      Timer() = delete;
      Timer(Timer&) = delete;
      Timer& operator=(Timer&) = delete;
      Timer(Timer&&) = delete;
      Timer& operator=(Timer&&) = delete;
      ~Timer();
      
      Timer(Session& refSession);

     private:
      const std::chrono::time_point<std::chrono::high_resolution_clock> start; //the starting time
      const std::function<void(std::chrono::time_point<std::chrono::high_resolution_clock>)> finalAction; //a custom final action
      
      const std::string name;

    };
}

#endif
