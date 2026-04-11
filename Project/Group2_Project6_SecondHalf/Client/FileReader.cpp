#include "FileReader.h"

/// @brief Constructor that accepts a filename to read from.
/// 
/// 
/// 
/// @param filename 

Reader::Reader(std::string filename) {
    this->filename = filename;
    this->file.open(filename);
}

/// @brief Reads a single line from the file specified in the constructor
/// 
/// 
/// 
/// @return line from file

std::string Reader::ReadLine() {
    std::string line;
    std::getline(this->file, line);
    return line;
}

/// @brief Checks to see if the file is open or at EOF
/// 
/// 
/// 
/// @return true if file is open and not EOF

bool Reader::IsOpen() {
    return this->file.is_open() && !this->file.eof();
}

/// @brief Deconstructor that closes the opened file

Reader::~Reader() {
    if (this->file.is_open()) {
        this->file.close();
    }
}