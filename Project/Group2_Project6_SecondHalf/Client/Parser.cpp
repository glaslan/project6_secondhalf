
#include "Parser.h"

/// @brief

// copied pasted from old assignment will be used in parser class
std::vector<std::string> Parser::split(std::string buffer, char delimiter) {

    std::vector<std::string> SubStrings = {};
    std::string line = "";

    for (int i = 0; i < buffer.length(); i++) {

        if (buffer.at(i) == delimiter) {
            SubStrings.push_back(line);
            line = "";
            continue;
        }

        line = line + buffer.at(i);
    }

    SubStrings.push_back(line);

    return SubStrings;
}