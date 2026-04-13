#pragma once

#include <iostream>
#include <fstream>
#include <string>

/// @brief Class that reads lines from a specified file. It provides functionality to check if the file is open and to read lines sequentially until the end of the file is reached.

class Reader {
    std::string filename;
    std::ifstream file;

public:
    Reader(std::string filename);
    std::string ReadLine();
    bool IsOpen();
    ~Reader();

};