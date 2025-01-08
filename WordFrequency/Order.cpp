/*
* Mandar Patil
* mpatil2
* Fall 24 - CSE 101
* Order.cpp
* Reads in input files and inserts each line as strings in a dictionary
*/
#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    if (!input.is_open()) {
        std::cerr << "Error: Unable to open input file \"" << argv[1] << "\"\n";
        return 1;
    }

    if (!output.is_open()) {
        std::cerr << "Error: Unable to open output file \"" << argv[2] << "\"\n";
        return 1;
    }

    Dictionary Dict;
    std::string line;
    int numLine = 1;

    while (std::getline(input, line)) {
        Dict.setValue(line, numLine++);
    }

    output << Dict.to_string();

    output << Dict.pre_string(); 

    input.close();
    output.close();

    return 0;
}
