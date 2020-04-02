module;
#include <chrono>
#include <functional>
#include <thread>
#include <iostream>

export module performanceLog:timer;

export namespace performance_log {
    
    class Session; //forward declaration

    class Timer {
    public:
        Timer() = delete;
        Timer(Timer&) = delete;
        Timer& operator=(Timer&) = delete;
        Timer(Timer&&) = delete;
        Timer& operator=(Timer&&) = delete;
        ~Timer() {
            finalAction(std::chrono::high_resolution_clock::now());
        }

        Timer(Session& refSession, std::string name, std::string category);
 //       //DEBUG costruttore senza riferimenti a Session
 //       Timer(int x) :
 //           finalAction {[] (std::chrono::time_point<std::chrono::high_resolution_clock>){
 //               std::cout << "\nTimer dtor\n";
 //           }}
 //       {
 //           std::cout << "\nTimer ctor\n";
 //       }

        struct MeasurementData {
            const std::string category;
            const std::string name;
            const std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
            //UNSUPPORTED const std::thread::id tid = std::this_thread::get_id();
            std::chrono::duration<double, std::milli> duration;
        };

    private:
        MeasurementData data;

        const std::function<void(std::chrono::time_point<std::chrono::high_resolution_clock>)> finalAction; //a custom final action

        };
    }
