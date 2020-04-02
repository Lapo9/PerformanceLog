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
