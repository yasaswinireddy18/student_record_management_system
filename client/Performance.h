#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <chrono>
#include <cstddef>

struct PerfStats {
    std::size_t recordsProcessed = 0;
    double loadMs = 0;
    double sortMs = 0;
    double transmitMs = 0;
    double saveMs = 0;
};

class Timer {
public:
    Timer() { reset(); }
    void reset() { start = std::chrono::high_resolution_clock::now(); }
    double elapsedMs() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - start).count();
    }
private:
    std::chrono::high_resolution_clock::time_point start;
};

#endif 
