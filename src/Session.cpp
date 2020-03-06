#include "Session.h"
//C++20 module PerformanceLog;

#include <string>
#include <chrono>
#include <fstream>

namespace PerformanceLog {

	Session::~Session()
	{
		saveMeasurements();
		//TODO deve terminare il thread (o forse si termina da solo se lo facciamo membro e va out of scope)
	}
	

	Session::Session(std::string outFileName, std::chrono::duration<float> saveRate) : 
	outFileName {outFileName}, saveRate{saveRate}
	{
		if (saveRate > 0s) {
			//TODO deve creare un thread dove tiene conto del tempo che passa per salvare
		}

	};


	void Session::saveMeasurements() {
		std::ofstream outFile {outFileName};
		outFile << measurements;
	}

}