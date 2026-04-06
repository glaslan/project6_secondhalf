#pragma once

#include <winsock.h> 

#include "../Server/packet.h"
#include "../Server/constants.h"

class Serializer {

	Packet packet;
	char* buffer;

public:

	Serializer();
	void Serialize(std::string datetime, float fuel);
	void SerializeEndPacket();
	void SerializeFlag(int flag);
	void SerializeDatetime(std::string datetime);
	void SerializeFuel(float fuel);
	bool Send(SOCKET connection);
	~Serializer();

};