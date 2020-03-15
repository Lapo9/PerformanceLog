#include "Session.h"
#include "Timer.h"
#include "formatters/ChromeTracingFormat.h"

#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace performance_log;

int main(int argc, char** argv) {
	Session session {"testSave.txt", 10s, std::make_unique<formatter::ChromeTracingFormat>()};

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
}