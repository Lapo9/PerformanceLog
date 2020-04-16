#ifndef PERFORMANCELOG_SESSIONTIMER
#define PERFORMANCELOG_SESSIONTIMER

#include <string>
#include "Session.h"
#include "MeasurementData.h"
#include "BasicTimer.h"


namespace performance_log {	
	
	/**
	 * @class SessionTimer 
	 * @brief A timer that upon destruction sends the recorded duration (along with other data) to the specified Session.
	**/
	class SessionTimer {	
		
	    public:
		/**
		 * @brief Constructs a BasicTimer with the name and category provided. The timer will report his data to the specified Session.
		 * @param session The Session the timer will send data to.
		 * @param name The informal name associated with the timer.
		 * @param category The informal category of the timer.
		**/
		SessionTimer(performance_log::Session& session, std::string name, std::string category) :
		data{category, name},
		timer{ [this, &session](BasicTimer::Duration elapsed) {
							data.duration = elapsed;
							data.start = timer.getStart();
							session.write(data);}} {}
	
		SessionTimer(SessionTimer&) = delete;
		SessionTimer& operator=(SessionTimer&) = delete;
		SessionTimer(SessionTimer&&) = delete;
		SessionTimer& operator=(SessionTimer&&) = delete;
		~SessionTimer() = default;
		

		private:
		MeasurementData data;
		BasicTimer timer;
	};

}

#endif
