#pragma once

#include <string>

class Deserializer {

	std::string datetime;
	float fuel;
	unsigned char flag;

public:

	// Nothing to do in the serializer constructor so just use the default one
	void DeserializeBuffer(char* buffer);
	float GetFuel();
	int GetFlag();
	std::string GetDatetime();

};