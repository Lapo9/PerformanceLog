#ifndef __ScopedTimer_H__
#define __ScopedTimer_H__

#include <functional>
#include <chrono>

class ScopedTimer {
    public:

        using clock = std::chrono::high_resolution_clock;
        using time_point = std::chrono::time_point<clock>; 

        template<typename ElapsedFnT>
        ScopedTimer(ElapsedFnT&& elapsed)
            :elapsed_(std::forward<ElapsedFnT>(elapsed)), start_(clock::now())
        {
        }
        ~ScopedTimer()
        {
            elapsed_(Duration());
        }

        ScopedTimer(ScopedTimer&) = delete;
        ScopedTimer& operator=(ScopedTimer&) = delete;
        ScopedTimer(ScopedTimer&&) = delete;
        ScopedTimer& operator=(ScopedTimer&&) = delete;
    
    public:
    
        time_point Duration() const
        {
            return clock::now() - start_;
        }

        private:
            time_point start_;
            std::function<void(const time_point&)> elapsed_;
    };

    template<typename FunctionT>
    void measure(FunctionT&& fn, ScopedTimer::time_point& duration)
    {
        ScopedTimer([&duration](const ScopedTimer::time_point &elapsed) {
            duration=elapsed;
        });
        fn();
    }

#endif 