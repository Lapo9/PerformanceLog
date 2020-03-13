#include "Timer.h"
#include "Session.h"

namespace PerformanceLog {

	//TODO questa versione del costruttore � di debug, bisogna scriverlo bene
	Timer::Timer(Session& refSession) : 
		start {std::chrono::high_resolution_clock::now()},
		finalAction {[this, &refSession](std::chrono::time_point<std::chrono::high_resolution_clock> end) {
						std::chrono::duration<double> elapsedTime = end-start;
						refSession.write("\n" + std::to_string(elapsedTime.count()));
					}}
		{
			
		}

		Timer::~Timer() {
			finalAction(std::chrono::high_resolution_clock::now());
		}


}