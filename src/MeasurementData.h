#ifndef PERFORMANCELOG_MEASUREMENTDATA
#define PERFORMANCELOG_MEASUREMENTDATA

#include <string>
#include <thread>
#include <chrono>

namespace performance_log {
	//TODO where should I put this?

	/**
	 * @class MeasurementData 
	 * @brief A set of data stored for each item in a Session.
	**/
	struct MeasurementData {
		const std::string category; ///< Informal category of the measurement.
		const std::string name; ///< Informal name of the measurement.
		std::chrono::time_point<std::chrono::high_resolution_clock> start; ///< Beginning timestamp.
		const int pid = 14; //TODO probably not here
		const std::thread::id tid = std::this_thread::get_id(); ///< ID of the current thread.
		std::chrono::duration<float, std::nano> duration; ///< Duration of the measurement.
	};
}

#endif
