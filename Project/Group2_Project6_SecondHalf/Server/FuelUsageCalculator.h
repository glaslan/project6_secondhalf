#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

/// @brief Class that calculates fuel usage based on fuel level readings over time. 
/// It keeps track of the previous and current fuel levels, total fuel consumed, and the number of time intervals for calculating average consumption.

class UsageCalculator {
private:
    float previous_fuel;
    float current_fuel;
    float total_consumed;
    float recent_difference;
    int time_intervals;
    bool has_first_reading;

public:
    UsageCalculator(float initial_fuel);
    void process_fuel_data(float new_level);
    float getAverageConsumption() const;
    float getRecentDifference() const;
	UsageCalculator() : previous_fuel(0.0), current_fuel(0.0), total_consumed(0.0), recent_difference(0.0), time_intervals(0), has_first_reading(false) {}
};