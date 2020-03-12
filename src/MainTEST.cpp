#include "Session.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace PerformanceLog;

int main(int argc, char** argv) {
	Session session {"testSave.txt", 1s};
	int i;
	while(std::cin >> i)
	return 0;
}