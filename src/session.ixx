module;
#include <string>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <fstream>
#include <iostream>

export module performanceLog:session;

//UNSUPPORTED
//import std.core; non funziona importare std.core
//import std.threading; non funziona importare std.threading
using namespace std::chrono_literals;

export namespace performance_log {

    class Session {

     public:
     //TODO va fatto l'overload perchè sta prendendo troppi argomenti
      Session(const std::string outFileName/*UNSUPPORTED = "Measurements", const std::chrono::milliseconds saveRate = 10ms, std::unique_ptr<formatter::MeasurementOutputFormat> formatter = std::make_unique<formatter::ChromeTracingFormat>()*/) :
          /*measurementFormat {std::move(formatter)},*/ outFileName {outFileName}, saveRate {saveRate}
          {
          std::cout << "\n\nSession construction...\n\n"; //DEBUG test da rimuovere
          //if the save rate is <= 0 then no thread is needed (@measurements will be saved at the end of the session)
          if (this->saveRate > 0ms) {
              waitAndSave = std::thread {[this] {
                  while (!endSession) {
                      std::unique_lock<std::mutex> cvLock {cvMutex};
                      cv.wait_for(cvLock, this->saveRate, [this] {return endSession; }); //wait for @saveRate or if the session is going to be destroyed
                      save();
                  }
              }};
              }
          }

      Session() = default; //DEBUG va tolto, il problema è che nel costruttore sopra non posso mettere il valore di default all'argomento saveRate (https://developercommunity.visualstudio.com/content/problem/959598/fatal-error-c1001-with-chrono-literals-and-modules.html)
      Session(Session&) = delete;
      Session& operator=(Session&) = delete;
      Session(Session&&) = delete;
      Session& operator=(Session&&) = delete;

      ~Session() noexcept {
              {
              std::lock_guard<std::mutex> cvLock {cvMutex};
              endSession = true; //signal that the session is going to end soon
              }
              cv.notify_one(); //tells the @waitAndSave thread (if present) to join as soon as possible
              try {
                  waitAndSave.join(); //if the thread exists (aka @saveRate > 0), wait for it
                  }
              catch (const std::system_error& e) {
                  if (e.code() != std::errc::invalid_argument) {
                      std::terminate(); //if the exception was not due to the non existance of the thread (aka @saveRate > 0), terminate the program
                      }
                  }

              save(); //save all (if the thread existed (aka @saveRate > 0) @measurements should be empty)
              //DEBUG measurementFormat->finalizeFormat(outFileName); //format the file based on the formatter service chosen
          }

      void write(std::string measurement) {
          if (!measurement.empty()) {
              std::lock_guard<std::mutex> measurementsLock {measurementGuard};
              this->measurements += measurement;
              }
          }

    //DEBUG  std::unique_ptr<formatter::MeasurementOutputFormat> measurementFormat; //the format of the measurements in this session

     private:
      //TODO use a in/out thread safe object to save the string to a file 
      //writes measurements to the output file
      void save() {
          if (!measurements.empty()) {
              std::lock_guard<std::mutex> measurementsLock {measurementGuard};
              std::ofstream outFile {outFileName, std::ios::app | std::ios::out};
              outFile << measurements;
              measurements.clear();
              }
       }
      
      std::string measurements;  //contains the measurements while the program is running
      std::mutex measurementGuard;
      const std::string outFileName = "Measurements";
      const std::chrono::milliseconds saveRate; //UNSUPPORTED = 10ms; //how often @measurements are saved to file
    
      std::thread waitAndSave; //the thread responsible to save measurements at the specified @saveRate
      std::condition_variable cv; //https://en.cppreference.com/w/cpp/thread/condition_variable
      bool endSession = false; //signals if the session is going to be destroyed
      std::mutex cvMutex;

    };
    
}
