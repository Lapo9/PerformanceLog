#include <sstream>
#include "ChromeTracingFormat.h"
#include "..\Timer.h"
#include "MeasurementOutputFormat.h"

namespace performance_log {
namespace formatter {

	std::string ChromeTracingFormat::formatInput(Timer::MeasurementData md) const {
		//use a stringstream to convert from thread::id to string
		std::stringstream ssTid;
		ssTid << md.tid;

		return "\n\t\t{ \"name\":\""	+ md.name + 
				"\", \"cat\": \""		+ md.category + 
				"\", \"ph\": \""		+ "X"	+ //for now the category is always a complete event
				"\", \"ts\": "			+ std::to_string(md.start.time_since_epoch().count()) +
				", \"dur\": "			+ std::to_string(md.duration.count()) +
				", \"pid\": "			+ std::to_string(md.pid) +
				", \"tid\": \""			+ ssTid.str() + "\"},";
	}


	void ChromeTracingFormat::finalizeFormat(std::string fn) const {
		//TODO I should use a dedicated class to read and write a file
		//read the entire content of the file
		std::ifstream f {fn};
		std::string s((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

		s.insert(0, "{\n\t\"traceEvents\": ["); //insert at the beginning of the string
		s.pop_back(); //removes the last ',' in the string
		s.append("\n\t]\n}"); //append to the string

		//save on the same file
		std::ofstream outFile {fn, std::ios::out};
		outFile << s;

		//TODO there is more data which could be added:
		//https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/preview#heading=h.q8di1j2nawlp
	}

}
}