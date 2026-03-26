#include "Logger.h"

Logger::Logger(std::string path, std::string errorpath) {
	this->path = path;
	this->errorpath = errorpath;
}


bool Logger::WriteToFile(std::string datetime, float fuel){
	std::fstream logfile(Logger::path, std::ios::out);
	if (!logfile.is_open()) {
		std::cerr << "Failed to open the file!" << std::endl;
		return false;
	}

	logfile << datetime << " " << fuel << "\n";

	// Reset the file pointer to the beginning
	logfile.seekg(0);
	logfile.close();

	return true;
}


bool Logger::WriteError(std::string error) {
	std::fstream errorfile(Logger::errorpath, std::ios::out);
	if (!errorfile.is_open()) {
		std::cerr << "Failed to open the file!" << std::endl;
		return false;
	}

	errorfile << error << "\n";
	errorfile.seekg(0);
	errorfile.close();

	return true;
}