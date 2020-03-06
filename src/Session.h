#ifndef PERFORMANCELOG_SESSION
#define PERFORMANCELOG_SESSION

#include <string>
#include <chrono>


namespace PerformanceLog {
    using namespace std::chrono_literals;

    class Session {

     public:
      Session() = default;
      Session(Session&) = delete;
      Session& operator=(Session&) = delete;
      Session(Session&&) = delete;
      Session& operator=(Session&&) = delete;
      ~Session();

      Session(std::string outFileName = "Measurements", std::chrono::duration<float> saveRate = 0s);


     private:
     void saveMeasurements(); // writes measurements to the output file

      std::string measurements;  // contains the measurements while the program is running
      std::string outFileName = "Measurements";
      std::chrono::duration<float> saveRate {0s}; // how often measurements are saved to file
    };

}


#endif