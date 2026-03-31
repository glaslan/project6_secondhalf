#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Reader {
    std::string filename;
    std::ifstream file;

public:
    Reader(std::string filename);
    std::string ReadLine();
    bool IsOpen();
    ~Reader();

};