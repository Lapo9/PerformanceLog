
#ifndef PERFORMANCELOG_SESSION
#define PERFORMANCELOG_SESSION

#include <iostream>
#include <string>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <mutex>
#include "MeasurementData.h"
#include "formatters\MeasurementOutputFormat.h"
#include "formatters\ChromeTracingFormat.h"


namespace performance_log {



using namespace std::chrono_literals;


/**
 * @class Session 
 * @brief The class receives inputs of type MeasurementData and stores them as a string, formatted as specified by the user provided MeasurementFormatter. 
 * @details The user can specify a frequency at which to save the measurements stored in the string to the specified file. When the session is destroyed, the output file undergoes a final formatting, specified by the MeasurementFormatter.
 **/
class Session {

 public:
 //TODO needs overload (it is taking too many args)

 /**
  * @brief Constructs a Session with the specified output file, save frequency and formatter.
  * @param outFileName The path to the file where to write measurements. If the file doesn't exists it is created. If the file is not empty, it will be wiped.
  * @param saveRate The frequency at which the session saves the output string to the output file. If the frequency is less than or equal to 0, the output string is savet to the output file only when the session is destroyed. A too small value can decrease performances.
  * @param formatter A MeasurementFormatter object which specifies how to convert the MeasurementData to a string. It is also responsible for the last formatting of the when the session is destroyed.
 **/
  Session(const std::string outFileName = "Measurements", const std::chrono::milliseconds saveRate = 0ms,std::unique_ptr<formatter::MeasurementFormatter>formatter=std::make_unique<formatter::ChromeTracingFormat>()) : measurementFormat{ std::move(formatter) }, outFileName{ outFileName }, saveRate{ saveRate }
  {
      //if the save rate is <= 0 then no thread is needed (@measurements will be saved at the end of the session)
      if (this->saveRate > 0ms) {
          waitAndSave = std::thread{ [this] {
              while (!endSession) {
                  std::unique_lock<std::mutex> cvLock {cvMutex};
                  cv.wait_for(cvLock, this->saveRate, [this] {return endSession; }); //wait for @saveRate or if the session is going to be destroyed
                  save();
                  std::cout << "\nSaved\n"; //DEBUG
              }
          } };
      }
  }

  Session(Session&) = delete;
  Session& operator=(Session&) = delete;
  Session(Session&&) = delete;
  Session& operator=(Session&&) = delete;

  /**
   * @brief Destructs the session and saves the string containing the measurements to the output file.
   * @details After saving the string to the output file, such file is formatted by the finalizeFormat method of the specified MeasurementFormatter.
  **/
  ~Session() noexcept {
          {
              std::lock_guard<std::mutex> cvLock{ cvMutex };
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
          measurementFormat->finalizeFormat(outFileName); //format the file based on the formatter service chosen
      }

  void write(performance_log::MeasurementData measurement) {
          std::string stringMeasurement{ measurementFormat->formatInput(measurement) };
          std::lock_guard<std::mutex> measurementsLock{ measurementGuard };
          measurements += stringMeasurement;
      }

 private:
  std::unique_ptr<formatter::MeasurementFormatter> measurementFormat; //the format of the measurements in this session

  //TODO use a in/out thread safe object to save the string to a file
  //writes measurements to the output file
  void save() {
          if (!measurements.empty()) {
              std::lock_guard<std::mutex> measurementsLock{ measurementGuard };
              std::ofstream outFile{ outFileName, std::ios::app | std::ios::out };
              outFile << measurements;
              measurements.clear();
          }
      }
  
  std::string measurements;  //contains the measurements while the program is running
  std::mutex measurementGuard;
  const std::string outFileName;
  const std::chrono::milliseconds saveRate {0ms}; //how often @measurements are saved to file
  
  std::thread waitAndSave; //the thread responsible to save measurements at the specified @saveRate
  std::condition_variable cv; //https://en.cppreference.com/w/cpp/thread/condition_variable
  bool endSession = false; //signals if the session is going to be destroyed
  std::mutex cvMutex;

};

}


#endif
