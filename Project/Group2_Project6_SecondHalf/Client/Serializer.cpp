
#include <vector>
#include <string>

#include "Serializer.h"
#include "Parser.h"

Serializer::Serializer() {
	// create buffer and cleer memory
	this->buffer = (char*)malloc(BUFFER_SIZE);
	memset(this->buffer, 0, BUFFER_SIZE);
}

void Serializer::Serialize(std::string datetime, float fuel) {

	memset(this->buffer, 0, BUFFER_SIZE);

	this->SerializeDatetime(datetime);
	this->SerializeFuel(fuel);
}

void Serializer::SerializeDatetime(std::string datetime) {

	// parse datetime
	Parser parser;

	// split into dd/mm/yyyy and hh:mm:ss
	std::vector<std::string> vals = parser.split(datetime, ' ');
	
	std::vector<std::string> dayMonthYear = parser.split(vals.at(0), '_');
	std::vector<std::string> hourMinuteSecond = parser.split(vals.at(1), ':');

	unsigned char day = std::stoi(dayMonthYear.at(0));
	unsigned char month = std::stoi(dayMonthYear.at(1));
	unsigned char year = std::stoi(dayMonthYear.at(2));

	unsigned char hour = std::stoi(hourMinuteSecond.at(0));
	unsigned char minute = std::stoi(hourMinuteSecond.at(1));
	unsigned char second = std::stoi(hourMinuteSecond.at(2));

	unsigned char meridian = 0;

	if (hour > 11 && hour<24) {
		meridian = 1;
	}
	if (hour > 12) {
		hour -= 12;
	}
		

	int offset = 0;
	
	memset(this->buffer, day, PKT_SIZE_DAY);
	offset += PKT_SIZE_DAY;

	memset(this->buffer + offset, month, PKT_SIZE_MONTH);
	offset += PKT_SIZE_MONTH;

	memset(this->buffer + offset, year, PKT_SIZE_YEAR);
	offset += PKT_SIZE_YEAR;

	memset(this->buffer + offset, minute, PKT_SIZE_MINUTES);
	offset += PKT_SIZE_MINUTES;

	memset(this->buffer + offset, meridian, PKT_SIZE_MERIDIAN);
	offset += PKT_SIZE_MERIDIAN;

	memset(this->buffer + offset, hour, PKT_SIZE_HOUR);
	offset += PKT_SIZE_HOUR;

	memset(this->buffer + offset, second, PKT_SIZE_SECONDS);
	offset += PKT_SIZE_SECONDS;

	memset(this->buffer + offset, 0, PKT_SIZE_PADDING);
	offset += PKT_SIZE_PADDING;

}

void Serializer::SerializeFuel(float fuel) {
	memset(this->buffer + PKT_OFFSET_TO_FUEL, fuel, PKT_SIZE_FUEL);
}

bool Serializer::Send(SOCKET connection) {
	send(connection, this->buffer, sizeof(char*) * BUFFER_SIZE, 0);
}

Serializer::~Serializer() {
	memset(this->buffer, 0, BUFFER_SIZE);
	free(this->buffer);
}