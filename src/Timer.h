
#ifndef PERFORMANCELOG_TIMER
#define PERFORMANCELOG_TIMER

#include <chrono>
#include <functional>
#include <thread>
#include <string>


namespace performance_log {

    class Session;

    class Timer {
     public:
      Timer() = delete;
      Timer(Timer&) = delete;
      Timer& operator=(Timer&) = delete;
      Timer(Timer&&) = delete;
      Timer& operator=(Timer&&) = delete;
      ~Timer();
      
      Timer(Session& refSession, std::string name, std::string category);


      //ihe structure of data needed by a Timer
      struct MeasurementData {
          const std::string category; //informal category of the measurement
          const std::string name; //informal name of the measurement
          const std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now(); //beginning timestamp
          const int pid = 14; //TODO get the real process id
          const std::thread::id tid = std::this_thread::get_id(); //id of the current thread
          std::chrono::duration<double, std::milli> duration; //duration of the timer
      };

     private:
      MeasurementData data;

      const std::function<void(std::chrono::time_point<std::chrono::high_resolution_clock>)> finalAction; //a custom final action
      

    };
}

#endif
