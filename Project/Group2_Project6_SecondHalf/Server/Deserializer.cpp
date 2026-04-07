
#include <sstream>
#include <iostream>

#include "Deserializer.h"
#include "constants.h"

void Deserializer::DeserializeBuffer(char* buffer) {

	char day[PKT_SIZE_DAY + 1];
	char month[PKT_SIZE_MONTH + 1];
	char year[PKT_SIZE_YEAR + 1];
	char hour[PKT_SIZE_HOUR + 1];
	char minute[PKT_SIZE_MINUTES + 1];
	char second[PKT_SIZE_SECONDS + 1];
	unsigned char meridian;
	float fuel;
	int flag;

	int offset = 0;

	memcpy(&flag, buffer + offset, PKT_SIZE_FLAG);
	offset += PKT_SIZE_FLAG;

	memcpy(&day, buffer + offset, PKT_SIZE_DAY);
	memset(&day + PKT_SIZE_DAY, '\0', sizeof(char));
	offset += PKT_SIZE_DAY;

	memcpy(&month, buffer + offset, PKT_SIZE_MONTH);
	memset(&month + PKT_SIZE_MONTH, '\0', sizeof(char));
	offset += PKT_SIZE_MONTH;

	memcpy(&year, buffer + offset, PKT_SIZE_YEAR);
	memset(&year + PKT_SIZE_YEAR, '\0', sizeof(char));
	offset += PKT_SIZE_YEAR;

	memcpy(&minute, buffer + offset, PKT_SIZE_MINUTES);
	memset(&minute + PKT_SIZE_MINUTES, '\0', sizeof(char));
	offset += PKT_SIZE_MINUTES;

	memcpy(&meridian, buffer + offset, PKT_SIZE_MERIDIAN);
	offset += PKT_SIZE_MERIDIAN;

	memcpy(&hour, buffer + offset, PKT_SIZE_HOUR);
	memset(&hour + PKT_SIZE_HOUR, '\0', sizeof(char));
	offset += PKT_SIZE_HOUR;

	memcpy(&second, buffer + offset, PKT_SIZE_SECONDS);
	memset(&second + PKT_SIZE_SECONDS, '\0', sizeof(char));
	offset += PKT_SIZE_SECONDS;

	memcpy(&fuel, buffer + offset, PKT_SIZE_FUEL);
	memset(&fuel + PKT_SIZE_FUEL, '\0', sizeof(char));
	offset += PKT_SIZE_FUEL;

	// concatenate values into final datetime string to be displayed nicely
	std::stringstream stream;

	stream << day << "/" << month << "/" << year << " ";
	if (meridian) {
		stream << "PM ";
	}
	else {
		stream << "AM ";
	}
	stream << hour << ":" << minute << ":" << second;
	std::cout << stream.str();

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