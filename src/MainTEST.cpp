#include "Session.h"
#include "SessionTimer.h"
#include "formatters/ChromeTracingFormat.h"

#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace performance_log;


int main(int argc, char** argv) {
	Session session {"testSave.txt", 1s, std::make_unique<formatter::ChromeTracingFormat>()};

	SessionTimer timer0 {session, "#0 timer", "#0 category"};
	{
	SessionTimer timer1 {session, "#1 timer", "#1 category"};
	for (int i = 0; i < 10000; i++) {
			std::cout << std::rand();
		}
	}

	
	{
	SessionTimer timer2 {session, "#2 timer", "#2 category"};
	for (int i = 0; i < 5000; i++) {
			std::cout << std::rand();
		}
	}

	int a;
	std::cin >> a;

	{
	SessionTimer timer3 {session, "#3 timer", "#3 category"};
	for (int i = 0; i < 5000; i++) {
		std::cout << std::rand();
		}
	}

	return 0;
}