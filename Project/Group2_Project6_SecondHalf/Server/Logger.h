#pragma once
#include <iostream>
#include <fstream>

/// @brief 
/// Creates log files and writes information or errors to them.

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
