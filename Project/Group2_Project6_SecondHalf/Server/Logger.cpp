#include "Logger.h"

Logger::Logger(std::string path, std::string errorpath) {

	std::ifstream logpath(path); 
	if (!logpath.good())
		std::ofstream(path).close(); // This creates the file b/c of course it does...

	std::ifstream errpath(errorpath);
	if (!errpath.good())
		std::ofstream(errorpath).close();

	logfilePtr.open(path.c_str(), std::ios::out | std::ios::app);
	errorfilePtr.open(errorpath.c_str(), std::ios::out | std::ios::app);

	if (!logfilePtr.is_open())
		std::cerr << "Error opening Log file\n";
	if (!errorfilePtr.is_open())
		std::cerr << "Error opening Error file\n";
}

Logger::~Logger() {
	logfilePtr.close();
	errorfilePtr.close();
}


bool Logger::WriteToFile(std::string line){
	if (!logfilePtr.is_open()) {
		std::cerr << "Failed to open the file!" << std::endl;
		return false;
	}

	logfilePtr << line << "\n";

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