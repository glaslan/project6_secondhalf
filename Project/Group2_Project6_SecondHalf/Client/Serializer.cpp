
#include <vector>
#include <string>
#include <winsock2.h>

#include "Serializer.h"
#include "Parser.h"

Serializer::Serializer() {
	// create buffer and cleer memory
	this->buffer = (char*)malloc(BUFFER_SIZE);
	memset(this->buffer, 0, BUFFER_SIZE);
}

void Serializer::Serialize(std::string datetime, float fuel) {

	memset(this->buffer, 0, BUFFER_SIZE);

	this->SerializeFlag(FLAG_CONTINUE);
	this->SerializeDatetime(datetime);
	this->SerializeFuel(fuel);
}

void Serializer::SerializeEndPacket() {
	memset(this->buffer, 0, BUFFER_SIZE);
	this->SerializeFlag(FLAG_END);
}

void Serializer::SerializeDatetime(std::string datetime) {

	// parse datetime
	Parser parser;

	// split into dd/mm/yyyy and hh:mm:ss
	std::vector<std::string> vals = parser.split(datetime, ' ');
	
	std::vector<std::string> dayMonthYear = parser.split(vals.at(0), '_');
	std::vector<std::string> hourMinuteSecond = parser.split(vals.at(1), ':');

	std::cout << dayMonthYear.at(0) << ":" << dayMonthYear.at(1) << ":" << dayMonthYear.at(2) << std::endl;
	std::cout << hourMinuteSecond.at(0) << ":" << hourMinuteSecond.at(1) << ":" << hourMinuteSecond.at(2) << std::endl;

	std::string day = (dayMonthYear.at(0));
	if (day.length() == 1) {
		day = "0" + day;
	}
	std::string month = (dayMonthYear.at(1));
	if (month.length() == 1) {
		month = "0" + month;
	}
	std::string year = (dayMonthYear.at(2));

	std::string hour = (hourMinuteSecond.at(0));
	if (hour.length() == 1) {
		hour = "0" + hour;
	}
	std::string minute = (hourMinuteSecond.at(1));
	if (minute.length() == 1) {
		minute = "0" + minute;
	}
	std::string second = (hourMinuteSecond.at(2));
	if (second.length() == 1) {
		second = "0" + second;
	}

	char meridian = '0';

	if (std::stoi(hour) > 11 && std::stoi(hour) <24) {
		meridian = '1';
	}
	if (std::stoi(hour) > 12) {
		hour = std::to_string(std::stoi(hour) - 12);
	}
		

	int offset = PKT_SIZE_FLAG;
	
	memcpy(this->buffer + offset, day.c_str(), PKT_SIZE_DAY);
	offset += PKT_SIZE_DAY;

	memcpy(this->buffer + offset, month.c_str(), PKT_SIZE_MONTH);
	offset += PKT_SIZE_MONTH;

	memcpy(this->buffer + offset, year.c_str(), PKT_SIZE_YEAR);
	offset += PKT_SIZE_YEAR;

	memcpy(this->buffer + offset, minute.c_str(), PKT_SIZE_MINUTES);
	offset += PKT_SIZE_MINUTES;

	memset(this->buffer + offset, meridian, PKT_SIZE_MERIDIAN);
	offset += PKT_SIZE_MERIDIAN;

	memcpy(this->buffer + offset, hour.c_str(), PKT_SIZE_HOUR);
	offset += PKT_SIZE_HOUR;

	memcpy(this->buffer + offset, second.c_str(), PKT_SIZE_SECONDS);
	offset += PKT_SIZE_SECONDS;

	memset(this->buffer + offset, '\0', sizeof(char));

	std::cout << this->buffer;

}

void Serializer::SerializeFuel(float fuel) {
	memset(this->buffer + PKT_OFFSET_TO_FUEL, fuel, PKT_SIZE_FUEL);
}

void Serializer::SerializeFlag(int flag) {
	memset(this->buffer, flag, PKT_SIZE_FLAG);
}

char* Serializer::GetBuffer() {
	return this->buffer;
}

Serializer::~Serializer() {
	memset(this->buffer, 0, BUFFER_SIZE);
	free(this->buffer);
}