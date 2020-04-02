module;
#include <iostream>
#include <chrono>

module performanceLog;

using namespace performance_log;

Timer::Timer(Session& refSession, std::string name, std::string category) :
	data {name, category},
	finalAction {[this, &refSession](std::chrono::time_point<std::chrono::high_resolution_clock> end) {
					data.duration = end - data.start;
					std::string out = refSession.measurementFormat->formatInput(data);
					refSession.write(out);
					std::cout << "\n" << this.name << " dtor\n";
				}}
	{
		std::cout << "\n" << name << " ctor\n";
	}