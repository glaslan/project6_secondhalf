#pragma once
#include <iostream>
#include <fstream>

class Logger
{
	std::string path;
	std::string errorpath;

	Logger(std::string path, std::string errorpath);

	bool WriteToFile(std::string datetime, float fuel);
	bool WriteError(std::string error);
};
