#ifndef PERFORMANCELOG_SESSION
#define PERFORMANCELOG_SESSION

#include <string>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <mutex>


namespace PerformanceLog {
    using namespace std::chrono_literals;

    class Session {

     public:
      Session(std::string outFileName = "Measurements", std::chrono::milliseconds saveRate = 0ms);
      Session(Session&) = delete;
      Session& operator=(Session&) = delete;
      Session(Session&&) = delete;
      Session& operator=(Session&&) = delete;
      ~Session() noexcept;

      void write(std::string& measurement);


     private:
      //TODO use a in/out thread safe object to save the string to a file
      void save(); //writes measurements to the output file

      std::string measurements;  //contains the measurements while the program is running
      std::mutex measurementGuard;
      std::string outFileName = "Measurements";
      std::chrono::milliseconds saveRate {0ms}; //how often @measurements are saved to file
      
      std::thread waitAndSave; //the thread responsible to save measurements at the specified @saveRate
      std::condition_variable cv; //https://en.cppreference.com/w/cpp/thread/condition_variable
      bool endSession = false; //signals if the session is going to be destroyed
      std::mutex cvMutex;

    };

}


#endif
