#include "Timer.h"
#include "Session.h"

namespace performance_log {

	//TODO questa versione del costruttore è di debug, bisogna scriverlo bene
	Timer::Timer(Session& refSession, std::string name, std::string category) : 
		data {category, name},
		finalAction {[this, &refSession](std::chrono::time_point<std::chrono::high_resolution_clock> end) {
						data.duration = end - data.start;
						std::string out = refSession.measurementFormat->formatInput(data);
						refSession.write(out);
					}}
		{
			
		}
		
		Timer::~Timer() {
			finalAction(std::chrono::high_resolution_clock::now());
		}


}