
#ifndef PERFORMANCELOG_TIMER
#define PERFORMANCELOG_TIMER

#include <chrono>
#include <functional>
#include <thread>

#include "Session.h"


namespace performance_log {

    class Timer {
     public:
      Timer() = delete;
      Timer(Timer&) = delete;
      Timer& operator=(Timer&) = delete;
      Timer(Timer&&) = delete;
      Timer& operator=(Timer&&) = delete;
      ~Timer();
      
      Timer(Session& refSession, std::string name, std::string category);


      struct MeasurementData {
          const std::string category;
          const std::string name;
          const std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
          const std::thread::id tid = std::this_thread::get_id();
          std::chrono::duration<double, std::milli> duration;
      };

     private:
      MeasurementData data;

      const std::function<void(std::chrono::time_point<std::chrono::high_resolution_clock>)> finalAction; //a custom final action
      

    };
}

#endif
