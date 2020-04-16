
#ifndef PERFORMANCELOG_TIMEROUTPUTFORMAT
#define PERFORMANCELOG_TIMEROUTPUTFORMAT

#include <string>
#include <chrono>
#include <fstream>

#include "..\MeasurementData.h"

namespace performance_log{
namespace formatter{

/**
 * @class MeasurementFormatter 
 * @brief A pure abstract class that defines the interface of a formatter.
**/
class MeasurementFormatter {

	public:
	 MeasurementFormatter() = default;
	 MeasurementFormatter(MeasurementFormatter&) = delete;
	 MeasurementFormatter& operator=(MeasurementFormatter&) = delete;
	 MeasurementFormatter(MeasurementFormatter&&) = delete;
	 MeasurementFormatter& operator=(MeasurementFormatter&&) = delete;
	 virtual ~MeasurementFormatter() = default;

	 virtual std::string formatInput(const performance_log::MeasurementData& measurementData) const = 0; //format the single measure
	 virtual void finalizeFormat(std::string filename) const = 0; //format the file with all the measurements

};

}
}

#endif
