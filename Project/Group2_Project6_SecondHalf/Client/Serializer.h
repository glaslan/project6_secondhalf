#pragma once

#include <winsock.h> 

#include "../Server/constants.h"

class Serializer {

	char* buffer;

public:

	Serializer();
	void Serialize(std::string datetime, float fuel);
	void SerializeEndPacket();
	void SerializeFlag(unsigned char flag);
	void SerializeDatetime(std::string datetime);
	void SerializeFuel(float fuel);
	char* GetBuffer();
	~Serializer();

};