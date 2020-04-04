
#ifndef PERFORMANCELOG_TIMEROUTPUTFORMAT
#define PERFORMANCELOG_TIMEROUTPUTFORMAT

#include <string>
#include <chrono>
#include <fstream>

#include "..\Timer.h"

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

		 virtual std::string formatInput(Timer::MeasurementData measurementData) const = 0; //format the single measure
		 virtual void finalizeFormat(std::string filename) const = 0; //format the file with all the measurements

	};
}
}

#endif
