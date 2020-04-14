#ifndef __SessionTimer_H__
#define __SessionTimer_H__

#include "ScopedTimer.h"
#include "Session.h"

class SessionTimer {

public:
    SessionTimer(performance_log::Session& s, const std::string &name)
        :timer_([&s](const ScopedTimer::time_point& dur)
            {
                s.write(dur, name);
            })
        {

        }
private:
        ScopedTimer timer_;
};


#endif