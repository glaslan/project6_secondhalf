#pragma once

#include <vector>
#include <iostream>

class Parser {

// Use default constructor no member variables so we dont need a defined one
public:
	// I do not think we are going to need the other functions for the parser should just be this one function 
	std::vector<std::string> split(std::string buffer, char delimiter);

};