#include "Session.h"
#include "Timer.h"
#include "formatters/ChromeTracingFormat.h"

#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace performance_log;

Session performance_log::GlobalSession;


int main(int argc, char** argv) {
	Session session {"testSave.txt", 1s, std::make_unique<formatter::ChromeTracingFormat>()};

	Timer timer0 {session, "#0 timer", "#0 category"};
	{
	Timer timer1 {session, "#1 timer", "#1 category"};
	for (int i = 0; i < 10000; i++) {
			std::cout << std::rand();
		}
	}

	
	{
	Timer timer2 {session, "#2 timer", "#2 category"};
	for (int i = 0; i < 5000; i++) {
			std::cout << std::rand();
		}
	}

	int a;
	std::cin >> a;

	{
	Timer timer3 {session, "#3 timer", "#3 category"};
	for (int i = 0; i < 5000; i++) {
		std::cout << std::rand();
		}
	}



	ScopedTimer::time_point time;
	measure([]()
	{
			std::this_thread::sleep_for(std::chrono::seconds(3));
	}, time);

	return 0;
}