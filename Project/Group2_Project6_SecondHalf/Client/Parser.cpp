
#include "Parser.h"

/// @brief Takes a string and seperates it into smaller strings that are seperated by
/// a delimiting character
/// @param buffer the string to split into subsets
/// @param delimiter the character to split the string by
/// @return std::vector<string> the list of subsets of string split by the delimiter character

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