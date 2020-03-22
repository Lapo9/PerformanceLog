#include <sstream>
export module ubascn;
#include "ChromeTracingFormat.h"
#include "..\Timer.h"

namespace performance_log {
namespace formatter {

//TODO implementare veramente i metodi, ora sono solo per far compilare
	std::string ChromeTracingFormat::formatInput(Timer::MeasurementData md) const {
		//use a stringstream to convert from thread::id to string
		std::stringstream ssTid;
		ssTid << md.tid;

		return "\n\t\t{ \"name\":\""	+ md.name + 
				"\", \"cat\":\""	+ md.category + 
				"\", \"ph\":\""		+ "X\""	+ //for now the category is always a complete event
				"\", \"ts\":\""		+ std::to_string(md.start.time_since_epoch().count()) +
				"\", \"dur\":\""	+ std::to_string(md.duration.count()) +
				"\", \"tid\":\""	+ ssTid.str() + "\"}";
	}


	void ChromeTracingFormat::finalizeFormat(std::string& s) const {
		s.insert(0, "{\n\t\"trace events\": [");
		s.append("\n\t]\n}");
		//TODO ci sono altri dati che potrebbero essere aggiunti: 
		//https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/preview#heading=h.q8di1j2nawlp
	}


	void ChromeTracingFormat::finalizeFormat(std::string s) const {
		//TODO
	}

}
}