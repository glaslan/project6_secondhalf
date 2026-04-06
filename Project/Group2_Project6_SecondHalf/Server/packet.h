#pragma once
#include <memory>
#include <iostream>
#include <fstream>

#include "constants.h"

class Packet
{
public:

	struct BODY {

		// Byte 1
		unsigned char day : PKT_SIZE_DAY;
		unsigned char month : PKT_SIZE_MONTH;
		unsigned char year : PKT_SIZE_YEAR;
		unsigned char minutes : PKT_SIZE_MINUTES;
		unsigned char meridian : PKT_SIZE_MERIDIAN;

		// Byte 2 -> 2.5
		unsigned char hour : PKT_SIZE_HOUR;
		unsigned char seconds : PKT_SIZE_SECONDS;

		// Byte 2.5 -> 3.5
		unsigned char fuelData : PKT_SIZE_FUEL;

	} Body;


	Packet()
	{
		// Get the header information
		memset(&this->Body, 0, sizeof(this->Body));
	}

};