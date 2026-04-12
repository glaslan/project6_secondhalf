#pragma once

#include <string>

/// @brief 

class Deserializer {

	std::string datetime;
	float fuel;
	unsigned char flag;
	std::stringstream stream;

public:

	// Nothing to do in the serializer constructor so just use the default one
	void DeserializeBuffer(char* buffer);
	float GetFuel();
	int GetFlag();
	std::string GetDatetime();

};