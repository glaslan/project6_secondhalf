#include "Logger.h"

Logger::Logger(std::string path, std::string errorpath) {
	logfilePtr.open(path.c_str(), std::ios::out | std::ios::app);
	errorfilePtr.open(errorpath.c_str(), std::ios::out | std::ios::app);

	if (!logfilePtr.is_open())
		std::cout << "Error opening Log file\n";
	if (!errorfilePtr.is_open())
		std::cout << "Error opening Error file\n";
}

Logger::~Logger() {
	logfilePtr.close();
	errorfilePtr.close();
}


bool Logger::WriteToFile(std::string datetime, float fuel){
	if (!logfilePtr.is_open()) {
		std::cerr << "Failed to open the file!" << std::endl;
		return false;
	}

	logfilePtr << datetime << " " << fuel << "\n";

	return true;
}


bool Logger::WriteError(std::string error) {
	if (!errorfilePtr.is_open()) {
		std::cerr << "Failed to open the file!" << std::endl;
		return false;
	}

	errorfilePtr << error << "\n";

	return true;
}