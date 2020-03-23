module;
#include <string>
#include <chrono>

export module performanceLog:measurementOutputFormat;
import :timer;

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
		 virtual void finalizeFormat(std::string& allMeasurements) const = 0; //format the string with all the measurements
		 virtual void finalizeFormat(std::string filename) const = 0; //format the file with all the measurements

	};
}
}