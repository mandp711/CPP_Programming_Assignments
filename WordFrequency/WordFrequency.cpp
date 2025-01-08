/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
WordFrequency.cpp 
Reads in input files, removes all whitespace, punctuation, and special character
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return EXIT_FAILURE;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file " << argv[1] << "\n";
        return EXIT_FAILURE;
    }

    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    Dictionary dict;
    std::string line;
    std::string delimiters = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    while (getline(inputFile, line)) {
        size_t start = 0, end;
        while (start < line.size()) {
            start = line.find_first_not_of(delimiters, start);
            if (start == std::string::npos) break; // checks if start is too large of a value

            end = line.find_first_of(delimiters, start);

            std::string key = line.substr(start, end - start);

            for (char& ch : key) {
                ch = std::tolower(ch);
            }

            if (!key.empty()) {
                if (dict.contains(key)) {
                    dict.setValue(key, dict.getValue(key) + 1);
                } else {
                    dict.setValue(key, 1);
                }
            }

            start = end;
        }
    }

    outputFile << dict.to_string();

    inputFile.close();
    outputFile.close();
    return EXIT_SUCCESS;
}
