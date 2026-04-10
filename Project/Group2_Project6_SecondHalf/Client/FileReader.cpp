#include "FileReader.h"

/// @brief 
/// 
/// 
/// 
/// @param filename 

Reader::Reader(std::string filename) {
    this->filename = filename;
    this->file.open(filename);
}

/// @brief 
/// 
/// 
/// 
/// @return 

std::string Reader::ReadLine() {
    std::string line;
    std::getline(this->file, line);
    return line;
}

/// @brief 
/// 
/// 
/// 
/// @return 

bool Reader::IsOpen() {
    return this->file.is_open() && !this->file.eof();
}

/// @brief 

Reader::~Reader() {
    if (this->file.is_open()) {
        this->file.close();
    }
}