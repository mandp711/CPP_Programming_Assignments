/*
* Mandar Patil
* mpatil2
* Fall 24 - CSE 101
* Arithmetic.cpp
* Contains the main function for the BigInteger ADT
*/
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return (EXIT_FAILURE);
    }

    ifstream in(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    ofstream out(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    string strA, strB;
    getline(in, strA);
    in.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(in, strB);

    BigInteger A(strA), B(strB);
    const BigInteger s3("3"), s2("2"), s9("9"), s16("16");

    // print out requested quantities
    
    // A
    out << (A) << endl << endl;
    
    // B
    out << (B) << endl << endl;
    
    // A + B
    out << (A + B) << endl << endl;
    
    // A - B
    out << (A - B) << endl << endl;
    
    // A - A
    out << (A - A) << endl << endl;
    
    // 3A - 2B
    out << ((s3 * A) - (s2 * B)) << endl << endl;
    
    // AB
    out << (A * B) << endl << endl;    
    
    // A^2
    out << (A * A) << endl << endl;
    
    // B^2
    out << (B * B) << endl << endl;
    
    // 9A^4 + 16B^5
    out << ((s9 * (A * A * A * A)) + (s16 * (B * B * B * B * B))) << endl << endl;


    // Close files
    in.close();
    out.close();

    return(0);
}
