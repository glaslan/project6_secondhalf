#include "FuelUsageCalculator.h"

/// @brief Constructor that initializes the fuel usage calculator with an initial fuel level.
/// 
/// 
/// 
/// @param initial_fuel 

UsageCalculator::UsageCalculator(float initial_fuel) {
    previous_fuel = initial_fuel;
    current_fuel = initial_fuel;
    total_consumed = 0.0;
    time_intervals = 0;
	recent_difference = 0.0;
	has_first_reading = false;
}

/// @brief Processes new fuel level data, updating the total consumed fuel and time intervals accordingly.
/// 
/// 
/// 
/// @param new_level 

void UsageCalculator::process_fuel_data(float new_level) {

    if (!has_first_reading) {
		has_first_reading = true;
		recent_difference = 0.0;
		previous_fuel = new_level;
		current_fuel = new_level;
		return;
    }

	current_fuel = new_level;
    recent_difference = previous_fuel - current_fuel;

    if (recent_difference > 0) {
		total_consumed += recent_difference;
		time_intervals++;
    }

	previous_fuel = current_fuel;
}

/// @brief Returns the most recent difference in fuel level, which represents the fuel consumed since the last reading.
/// 
/// 
/// 
/// @return 

float UsageCalculator::getRecentDifference() const {
    return recent_difference;
}

/// @brief Calculates and returns the average fuel consumption based on the total consumed fuel and the number of time intervals recorded.
/// 
/// 
/// 
/// @return 

float UsageCalculator::getAverageConsumption() const {
    if (time_intervals == 0) {
        return 0.0;
    }
    return total_consumed / time_intervals;
}
