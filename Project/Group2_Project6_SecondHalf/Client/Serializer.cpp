
#include <vector>
#include <string>
#include <winsock2.h>

#include "Serializer.h"
#include "Parser.h"

/// @brief constructor for serializer, alocates memory for buffer

Serializer::Serializer() {
	// create buffer and cleer memory
	this->buffer = (char*)malloc(BUFFER_SIZE);
	memset(this->buffer, 0, BUFFER_SIZE);
}

/// @brief adds continue flag, datetime and fuel into buffer to be sent
/// @param datetime datetime to put into buffer
/// @param fuel fuel to put into buffer

void Serializer::Serialize(std::string datetime, float fuel) {

	memset(this->buffer, 0, BUFFER_SIZE);

	this->SerializeFlag(FLAG_CONTINUE);
	this->SerializeDatetime(datetime);
	this->SerializeFuel(fuel);
}

/// @brief clears buffer and sets flag to EndPacket to be sent

void Serializer::SerializeEndPacket() {
	memset(this->buffer, 0, BUFFER_SIZE);
	this->SerializeFlag(FLAG_END);
}

/// @brief adds datetime into buffer
/// @param datetime datetime to put into buffer

void Serializer::SerializeDatetime(std::string datetime) {

	// parse datetime
	Parser parser;

	if (datetime.at(0) == ' ') {
		datetime = datetime.substr(1, datetime.length()-1);
	}

	// split into dd/mm/yyyy and hh:mm:ss
	std::vector<std::string> vals = parser.split(datetime, ' ');

	std::vector<std::string> dayMonthYear = parser.split(vals.at(0), '_');
	std::vector<std::string> hourMinuteSecond = parser.split(vals.at(1), ':');

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
	if (hour.length() == 1) {
		hour = "0" + hour;
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

}

/// @brief puts fuel into buffer
/// @param fuel fuel to put into buffer

void Serializer::SerializeFuel(float fuel) {
	memcpy(this->buffer + PKT_OFFSET_TO_FUEL, &fuel, PKT_SIZE_FUEL);
}

/// @brief puts flag into buffer
/// @param flag flag to put into buffer

void Serializer::SerializeFlag(unsigned char flag) {
	memcpy(this->buffer, &flag, PKT_SIZE_FLAG);
}

/// @brief gets the pointer to the buffer to be used to send 
/// @return char* buffer

char* Serializer::GetBuffer() {
	return this->buffer;
}

/// @brief deallocates buffer 

Serializer::~Serializer() {
	memset(this->buffer, 0, BUFFER_SIZE);
	free(this->buffer);
}