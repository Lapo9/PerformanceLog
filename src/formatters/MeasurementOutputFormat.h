
#ifndef PERFORMANCELOG_TIMEROUTPUTFORMAT
#define PERFORMANCELOG_TIMEROUTPUTFORMAT

#include <string>
#include <chrono>
#include <fstream>

namespace performance_log{
namespace formatter{

class MeasurementOutputFormat {
	
	public:
	 MeasurementOutputFormat() = default;
	 MeasurementOutputFormat(MeasurementOutputFormat&) = delete;
	 MeasurementOutputFormat& operator=(MeasurementOutputFormat&) = delete;
	 MeasurementOutputFormat(MeasurementOutputFormat&&) = delete;
	 MeasurementOutputFormat& operator=(MeasurementOutputFormat&&) = delete;
	 virtual ~MeasurementOutputFormat() = default;

	 virtual std::string formatInput(std::string category/*, std::string name, std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::milliseconds duration, int tid*/) const = 0; //format the single measure
	 virtual void finalizeFormat(std::string& allMeasurements) const = 0; //format the string with all the measurements
	 virtual void finalizeFormat(std::string filename) const = 0; //format the file with all the measurements

};
}
}

#endif