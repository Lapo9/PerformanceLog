#include "Session.h"
//C++20 module PerformanceLog;

#include <fstream>


namespace performance_log {

	Session::Session(std::string outFileName, std::chrono::milliseconds saveRate, std::unique_ptr<formatter::MeasurementOutputFormat> formatter) :
		measurementFormat {std::move(formatter)}, outFileName {outFileName}, saveRate {saveRate}
	{
		//if the save rate is <= 0 then no thread is needed (@measurements will be saved at the end of the session)
		if (this->saveRate > 0ms) {
			waitAndSave = std::thread{[this]{
				while (!endSession) {
					std::unique_lock<std::mutex> cvLock {cvMutex};
					cv.wait_for(cvLock, this->saveRate, [this]{return endSession;}); //wait for @saveRate or if the session is going to be destroyed
					save();
				} 
			}};
		}
	}


	Session::~Session() noexcept {
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
		measurementFormat->finalizeFormat(outFileName); //format the file based on the formatter service chosen
	}
	

	void Session::save() {
		if (!measurements.empty()) {
			std::lock_guard<std::mutex> measurementsLock {measurementGuard};
			std::ofstream outFile {outFileName, std::ios::app | std::ios::out};
			outFile << measurements;
			measurements.clear();
		}
	}


	void Session::write(std::string measurement) {
		if (!measurement.empty()) {
			std::lock_guard<std::mutex> measurementsLock {measurementGuard};
			this->measurements += measurement;
		}
	}

}