
#ifndef PERFORMANCELOG_CHROMETRACINGFORMAT
#define PERFORMANCELOG_CHROMETRACINGFORMAT

#include "MeasurementOutputFormat.h"
#include "../Timer.h"

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
	 
	 std::string formatInput(Timer::MeasurementData measurementData) const override; //format the single measure
	 void finalizeFormat(std::string& allMeasurements) const override; //format the string with all the measurements
	 void finalizeFormat(std::string filename) const override; //format the file with all the measurements

};

}
}
#endif
