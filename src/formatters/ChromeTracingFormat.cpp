
#include "ChromeTracingFormat.h"

namespace performance_log {
namespace formatter {

//TODO implementare veramente i metodi, ora sono solo per far compilare
	std::string ChromeTracingFormat::formatInput(std::string category) const {return "h";}
	void ChromeTracingFormat::finalizeFormat(std::string& s) const {}
	void ChromeTracingFormat::finalizeFormat(std::string s) const {}

}
}