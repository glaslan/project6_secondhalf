
#include <sstream>
#include <iostream>

#include "Deserializer.h"
#include "constants.h"

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
	std::stringstream stream;

	stream << day << "/" << month << "/" << year << " ";
	if (meridian == '1') {
		stream << "PM ";
	}
	else {
		stream << "AM ";
	}
	stream << hour << ":" << minute << ":" << second;
	std::cout << stream.str() << std::endl;
	std::cout << fuel;

	// set values
	this->datetime = stream.str();
	this->fuel = fuel;
}

float Deserializer::GetFuel() {
	return this->fuel;
}

int Deserializer::GetFlag() {
	return this->flag;
}

std::string Deserializer::GetDatetime() {
	return this->datetime;
}