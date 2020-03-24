module;
#include <string>
#include <chrono>

export module performanceLog:chromeTracingFormat;
import :timer;
import :measurementOutputFormat;

export namespace performance_log{
namespace formatter{

	class ChromeTracingFormat : public MeasurementOutputFormat {

		public:
		 ChromeTracingFormat() = default;
		 ChromeTracingFormat(ChromeTracingFormat&) = delete;
		 ChromeTracingFormat& operator=(ChromeTracingFormat&) = delete;
		 ChromeTracingFormat(ChromeTracingFormat&&) = delete;
		 ChromeTracingFormat& operator=(ChromeTracingFormat&&) = delete;
		 ~ChromeTracingFormat() = default;


		 //formats the single measure
		 std::string formatInput(Timer::MeasurementData md) const override {
			 //use a stringstream to convert from thread::id to string
			 //UNSUPPORTED
			 //std::stringstream ssTid;
			 //ssTid << md.tid;

			 return "\n\t\t{ \"name\":\"" + md.name +
					"\", \"cat\":\"" + md.category +
					"\", \"ph\":\"" + "X\"" + //for now the category is always a complete event
					"\", \"ts\":\"" + std::to_string(md.start.time_since_epoch().count()) +
					"\", \"dur\":\"" + std::to_string(md.duration.count()) +
					/*"\", \"tid\":\"" + ssTid.str() +*/"\"}"; //UNSUPPORTED
		 }


		 //formats the string with all the measurements
		 void finalizeFormat(std::string& s) const override {
			 s.insert(0, "{\n\t\"trace events\": [");
			 s.append("\n\t]\n}");
			 //TODO ci sono altri dati che potrebbero essere aggiunti: https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/preview#heading=h.q8di1j2nawlp
		 }


		 //formats the file with all the measurements
		 void finalizeFormat(std::string filename) const override {
			 //TODO
		 }

	};

}
}