
#include <sstream>
#include <iostream>

#include "Deserializer.h"
#include "constants.h"

/// @brief Moves information from a buffer to the private members of the deserializer
/// @param buffer 

void Deserializer::DeserializeBuffer(char* buffer) {

	int offset = 0;

	memcpy(&this->flag, buffer + offset, PKT_SIZE_FLAG);
	offset += PKT_SIZE_FLAG;

	std::string day(buffer + offset, PKT_SIZE_DAY);
	offset += PKT_SIZE_DAY;

	std::string month(buffer + offset, PKT_SIZE_MONTH);
	offset += PKT_SIZE_MONTH;

	std::string year(buffer + offset, PKT_SIZE_YEAR);
	offset += PKT_SIZE_YEAR;

	std::string minute(buffer + offset, PKT_SIZE_MINUTES);
	offset += PKT_SIZE_MINUTES;

	unsigned char meridian;
	memcpy(&meridian, buffer + offset, PKT_SIZE_MERIDIAN);
	offset += PKT_SIZE_MERIDIAN;

	std::string hour(buffer + offset, PKT_SIZE_HOUR);
	offset += PKT_SIZE_HOUR;

	std::string second(buffer + offset, PKT_SIZE_SECONDS);
	offset += PKT_SIZE_SECONDS;

	float fuel;
	memcpy(&fuel, buffer + offset, PKT_SIZE_FUEL);
	offset += PKT_SIZE_FUEL;

	// concatenate values into final datetime string to be displayed nicely

	this.stream << day << "/" << month << "/" << year << " ";
	if (meridian == '1') {
		this.stream << "PM ";
	}
	else {
		this.stream << "AM ";
	}
	this.stream << hour << ":" << minute << ":" << second;
	std::cout << this.stream.str() << std::endl;
	std::cout << fuel;

	// set values
	this->datetime = this.stream.str();
	this->fuel = fuel;
	this.stream.clear();
}

/// @brief Returns the value of the private member, fuel
/// @return fuel

float Deserializer::GetFuel() {
	return this->fuel;
}

/// @brief 
/// @return 

int Deserializer::GetFlag() {
	return this->flag;
}

/// @brief 
/// @return 

std::string Deserializer::GetDatetime() {
	return this->datetime;
}