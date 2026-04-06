#include <iostream>
#include <fstream>

class UsageCalculator {
private:
    float previous_fuel;
    float current_fuel;
    float total_consumed;
    int time_intervals;

public:
    UsageCalculator(float initial_fuel);
    void process_fuel_data(float new_level);
    float getAverageConsumption() const;
    float getRecentDifference() const;
};