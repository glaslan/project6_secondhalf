#pragma once
#include <iostream>
#include <fstream>

class Logger
{
private:
	std::ofstream logfilePtr;
	std::ofstream errorfilePtr;

public:
	Logger(std::string path, std::string errorpath);
	~Logger();
	bool WriteToFile(std::string data);
	bool WriteError(std::string error);
};
