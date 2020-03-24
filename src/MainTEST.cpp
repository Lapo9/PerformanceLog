//#include "Session.h"
//#include "Timer.h"
//#include "formatters/ChromeTracingFormat.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <random>
//
//using namespace performance_log;

#include <iostream>
#include <chrono>
#include <memory>
import performanceLog;

using namespace std::chrono_literals;

int main(int argc, char** argv) {
	performance_log::Session test{"test", std::make_unique<performance_log::formatter::ChromeTracingFormat>()}; //non funziona error C1001
	performance_log::Timer myTimer{8};
	std::cout << "\n\nciao\n\n";
	int i;
	std::cin >> i;
	return 0;
}
/*	Session session {"testSave.txt", 10s, std::make_unique<formatter::ChromeTracingFormat>()};

	{
	Timer timer {session};
	for (int i = 0; i < 10000; i++) {
			std::cout << std::rand();
		}
	}

	int a;
	std::cin >> a;
	
	{
	Timer timer1 {session};
	for (int i = 0; i < 10; i++) {
			std::cout << std::rand();
		}
	}

	std::cin >> a;

	{
	Timer timer2 {session};
	for (int i = 0; i < 10; i++) {
		std::cout << std::rand();
		}
	}

	return 0;
}*/