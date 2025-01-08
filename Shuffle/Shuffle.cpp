/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
Shuffle.cpp
Main Program that performs shuffle operation 
*/
#include <iostream>
#include <iomanip>
#include "List.h"

using namespace std;

// Function to perform a perfect shuffle on a List
void shuffle(List& D) {
    int n = D.length();
    List firstHalf, secondHalf;

    // Split the list into two halves
    D.moveFront();
    for (int i = 0; i < n / 2; ++i) {
        firstHalf.insertBefore(D.moveNext());
    }
    for (int i = n / 2; i < n; ++i) {
        secondHalf.insertBefore(D.moveNext());
    }

    // Interleave the two halves back into the original list
    D.clear();
    firstHalf.moveFront();
    secondHalf.moveFront();
    for (int i = 0; i < n/2; i++) {
        D.insertBefore(secondHalf.moveNext());
        D.insertBefore(firstHalf.moveNext());
    }
    if(n % 2 != 0){
        D.insertBefore(secondHalf.moveNext()); 
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <maximum deck size>" << std::endl;
        return EXIT_FAILURE;
    }

    // Read the maximum deck size from the command line argument
    int maxDeckSize = atoi(argv[1]);

    cout << "deck size shuffle count" << endl;
    cout << "------------------------------" << endl;
    for (int j = 1; j <= maxDeckSize; j++) {
        List D;
        // Initialize the deck
        for (int i = 0; i < j; i++) {
            D.insertBefore(i);
        }

        int count = 0;
        List deck = D;

        do {
            shuffle(D);
            count++;
        } while (!D.equals(deck));

        cout << setw(8) << left << j << setw(12) << right << count << endl;
    }

    return 0;
}


