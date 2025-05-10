#ifndef TIMER_H
#define TIMER_H

#include <chrono>

/**
 * @brief Class to measure execution time.
 */
class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;

public:
    void start();
    void stop();
    double getDurationMilliseconds() const;
};

#endif // TIMER_H
