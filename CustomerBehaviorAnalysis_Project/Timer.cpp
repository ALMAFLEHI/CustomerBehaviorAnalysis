#include "Timer.h"

void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    end_time = std::chrono::high_resolution_clock::now();
}

double Timer::getDurationMilliseconds() const {
    return std::chrono::duration<double, std::milli>(end_time - start_time).count();
}
