
#ifndef PERFORMANCELOG_CHROMETRACINGFORMAT
#define PERFORMANCELOG_CHROMETRACINGFORMAT

#include "MeasurementOutputFormat.h"

namespace performance_log{
namespace formatter{

class ChromeTracingFormat : public MeasurementOutputFormat {

	public:
	 ChromeTracingFormat() = default;
	 ChromeTracingFormat(ChromeTracingFormat&) = delete;
	 ChromeTracingFormat& operator=(ChromeTracingFormat&) = delete;
	 ChromeTracingFormat(ChromeTracingFormat&&) = delete;
	 ChromeTracingFormat& operator=(ChromeTracingFormat&&) = delete;
	 ~ChromeTracingFormat() = default;

	 std::string formatInput(std::string category/*, std::string name, std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::milliseconds duration, int tid*/) const override; //format the single measure
	 void finalizeFormat(std::string& allMeasurements) const override; //format the string with all the measurements
	 void finalizeFormat(std::string filename) const override; //format the file with all the measurements

};

}
}
#endif
