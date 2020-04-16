
#ifndef PERFORMANCELOG_CHROMETRACINGFORMAT
#define PERFORMANCELOG_CHROMETRACINGFORMAT

#include <chrono>
#include <string>
#include <sstream>
#include "MeasurementOutputFormat.h"
#include "..\MeasurementData.h"

namespace performance_log{
namespace formatter{

/**
 * @class ChromeTracingFormat 
 * @brief The class provides the methods to write a file readable by chorome://tracing.
**/
class ChromeTracingFormat : public MeasurementFormatter {

	public:
	 ChromeTracingFormat() = default;
	 ChromeTracingFormat(ChromeTracingFormat&) = delete;
	 ChromeTracingFormat& operator=(ChromeTracingFormat&) = delete;
	 ChromeTracingFormat(ChromeTracingFormat&&) = delete;
	 ChromeTracingFormat& operator=(ChromeTracingFormat&&) = delete;
	 ~ChromeTracingFormat() = default;
	 
	 /**
	  * @brief Formats the data in input to make it an item readable by chrome://tracing
	  * @param[in] measurementData The measurement to be formatted
	 **/
	 std::string formatInput(const performance_log::MeasurementData& measurementData) const override {
		 //use a stringstream to convert from thread::id to string
		 std::stringstream ssTid;
		 ssTid << measurementData.tid;

		 return "\n\t\t{ \"name\":\""		+ measurementData.name +
			 "\", \"cat\": \""				+ measurementData.category +
			 "\", \"ph\": \""				+ "X" + //for now the category is always a complete event
			 "\", \"ts\": "					+ std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(measurementData.start.time_since_epoch()).count()) +
			 ", \"dur\": "					+ std::to_string(measurementData.duration.count()) +
			 ", \"pid\": "					+ std::to_string(measurementData.pid) +
			 ", \"tid\": \"" + ssTid.str()	+ "\"},";
	 }

	 /**
	  * @brief Adds the last formatting needed by the file written using formatInput method.
	  * @details The file is guaranteed be formatted correctly, and will be readable by chrome://tracing, if and only if it was written using only the formatInput method.
	  * @param The path to the file to be formatted.
	 **/
	 void finalizeFormat(std::string filename) const override {
		 //TODO I should use a dedicated class to read and write a file
		 //read the entire content of the file
		 std::ifstream f{ filename };
		 std::string s((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

		 s.insert(0, "{\n\t\"traceEvents\": ["); //insert at the beginning of the string
		 s.pop_back(); //removes the last ',' in the string
		 s.append("\n\t],\n\n\t\"displayTimeUnit\": \"ms\"\n}"); //append to the string

		 //save on the same file
		 std::ofstream outFile{ filename, std::ios::out };
		 outFile << s;

		 //TODO there is more data which could be added:
		 //https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/preview#heading=h.q8di1j2nawlp //format the file with all the measurements
	 }
};

}
}
#endif
