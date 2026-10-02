// UsageMonitor.h
// TCS302 Unit 2: circular queue (fixed-size rolling usage history)
// TCS307 Unit 1: loops, functions, overloaded readUsage()
#ifndef USAGEMONITOR_H
#define USAGEMONITOR_H

#include "CircularQueue.h"
#include "Utils.h"
#include <vector>
#include <cstdlib>

class UsageMonitor {
private:
    CircularQueue<double> history;   // rolling window of usage % readings

public:
    explicit UsageMonitor(int windowSize = 10) : history(windowSize) {}

    // Overloaded readUsage() #1 -- simulate a reading from a "sensor"
    void readUsage() {
        double simulated = 40.0 + (std::rand() % 6000) / 100.0;   // 40% - 100%
        history.enqueue(clampValue(simulated, 0.0, 100.0));
    }

    // Overloaded readUsage() #2 -- accept an externally supplied reading (real sensor source)
    void readUsage(double externalReadingPercent) {
        history.enqueue(clampValue(externalReadingPercent, 0.0, 100.0));
    }

    double averageUsage() const {
        return averageValue(history.toVector());
    }

    std::vector<double> recentReadings() const { return history.toVector(); }
};

#endif
