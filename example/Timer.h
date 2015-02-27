#ifndef TIMER__H
#define TIMER__H value
#endif
#include <chrono>

class Timer
{
public:
    Timer(){Update();};
    std::chrono::duration<double> Update(){
        auto t0=t;
        t=std::chrono::high_resolution_clock::now();
        return (t-t0);
    };

private:
    std::chrono::high_resolution_clock::time_point t;
};
