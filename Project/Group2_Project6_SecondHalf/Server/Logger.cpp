#include "Logger.h"

/// @brief Constructor that creates and/or opens a log file and an error log file at the provided paths.
/// @param path 
/// @param errorpath 

Logger::Logger(std::string path, std::string errorpath) {
	logfilePtr.open(path.c_str(), std::ios::out | std::ios::app);
	// errorfilePtr.open(errorpath.c_str(), std::ios::out | std::ios::app);

	if (!logfilePtr.is_open())
		std::cerr << "Error opening Log file\n";
	// we are not using the error file so might as well not open an extra file
	//if (!errorfilePtr.is_open())
	//	std::cerr << "Error opening Error file\n";
}

/// @brief Deconstructor that closes the two files

Logger::~Logger() {
	logfilePtr.close();
	// errorfilePtr.close();
}

/// @brief Writes a line to the log file.
/// @param line 
/// @return bool

bool Logger::WriteToFile(std::string line){
	if (!logfilePtr.is_open()) {
		std::cerr << "Log file not open" << std::endl;
		return false;
	}

	logfilePtr << line << "\n";

	return true;
}

/// @brief Writes a line to the error file.
/// @param error 
/// @return bool

bool Logger::WriteError(std::string error) {
	if (!errorfilePtr.is_open()) {
		std::cerr << "Error file not open" << std::endl;
		return false;
	}

	errorfilePtr << error << "\n";

	return true;
}