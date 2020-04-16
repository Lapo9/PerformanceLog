#ifndef PERFORMANCELOG_BASICTIMER
#define PERFORMANCELOG_BASICTIMER

#include <chrono>
#include <functional>

namespace performance_log {

	/**
	 * @class BasicTimer 
	 * @brief A simple scoped timer. 
	 * @details It sets a time point upon creation, and get the time elapsed upon destruction. A user defined final action is performed upon destruction.
	**/
	class BasicTimer {
		public:
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;
		using Duration = std::chrono::duration<float>;
	
		//TODO perfect forwarding?

		/**
		 * @brief Constructs a new timer and record the current timestamp
		 * @param final_action The action to be performed upon destruction. The parameter holds the duration recorded by the timer.
		**/
		BasicTimer(std::function<void(const Duration&)> final_action) : final_action{final_action} {};
		BasicTimer(BasicTimer&) = delete;
		BasicTimer& operator=(BasicTimer&) = delete;
		BasicTimer(BasicTimer&&) = delete;
		BasicTimer& operator=(BasicTimer&&) = delete;
		/**
		 * @brief Get the duration recorded by the timer and perform the user defined final action. Destructs the timer.
		**/
		~BasicTimer() {
			final_action(getCurrent());
		}
		
		/**
		 * @brief Returns the current duration of the timer.
		 * @return The current duration of the timer (the time elapsed from its construction).
		**/
		Duration getCurrent() {
			return Clock::now() - start;
		}

		/**
		 * @brief Get the timestamp of the creation of the timer.
		 * @return The timestamp of the creation of the timer (such timestamp is used to calculate the duration of the timer).
		**/
		TimePoint getStart() {
			return start;
		}
	
	
		private:
		TimePoint start = Clock::now();
		std::function<void(const Duration&)> final_action;
		
	};
}

#endif
