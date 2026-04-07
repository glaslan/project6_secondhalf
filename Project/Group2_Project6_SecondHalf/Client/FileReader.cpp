#include "FileReader.h"

Reader::Reader(std::string filename) {
    this->filename = filename;
    this->file.open(filename);
}

std::string Reader::ReadLine() {
    std::string line;
    std::getline(this->file, line);
    return line;
}

bool Reader::IsOpen() {
    return this->file.is_open() && !this->file.eof();
}

Reader::~Reader() {
    if (this->file.is_open()) {
        this->file.close();
    }
}