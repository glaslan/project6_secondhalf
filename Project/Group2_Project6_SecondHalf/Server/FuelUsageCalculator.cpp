#include "FuelUsageCalculator.h"

UsageCalculator::UsageCalculator(float initial_fuel) {
    previous_fuel = initial_fuel;
    current_fuel = initial_fuel;
    total_consumed = 0.0;
    time_intervals = 0;
}

void UsageCalculator::process_fuel_data(float new_level) {

    time_intervals++;

    float difference = previous_fuel - new_level;

    if (difference < 0) {
        total_consumed += difference;
    }

    current_fuel = new_level;
    previous_fuel = new_level;
}

float UsageCalculator::getRecentDifference() const {
    return previous_fuel - current_fuel;
}

float UsageCalculator::getAverageConsumption() const {
    if (time_intervals == 0) {
        return 0.0;
    }
    return total_consumed / time_intervals;
}
