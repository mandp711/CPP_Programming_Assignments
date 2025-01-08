/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
ListTest.cpp
Test file for testing function of List.cpp
*/
#include <iostream>
#include "List.h" // Assuming List.h defines the List class
#include <stdexcept>

int main() {
    try {
        // Initialize lists by inserting elements one by one
        List A;
        for (int value : {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) {
            A.insertAfter(value);
        }

        List B;
        for (int value : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) {
            B.insertAfter(value);
        }

        List C = B; // Assuming copy constructor
        List D = A; // Assuming copy constructor

        A.moveFront();
        B.moveFront();
        C.moveBack();
        D.moveBack();

        // Print initial states
        std::cout << "A = " << A << "\nA.position() = " << A.position() << "\n";
        std::cout << "B = " << B << "\nB.position() = " << B.position() << "\n";
        std::cout << "C = " << C << "\nC.position() = " << C.position() << "\n";
        std::cout << "D = " << D << "\nD.position() = " << D.position() << "\n\n";

        // Move cursors and perform operations to match the output
        A.moveBack();
        B.moveBack();
        C.moveFront();
        D.moveFront();

        std::cout << "A = " << A << "\nA.position() = " << A.position() << "\n";
        std::cout << "B = " << B << "\nB.position() = " << B.position() << "\n";
        std::cout << "C = " << C << "\nC.position() = " << C.position() << "\n";
        std::cout << "D = " << D << "\nD.position() = " << D.position() << "\n\n";

        // Perform comparison operations
        std::cout << "A==B is " << (A == B ? "true" : "false") << "\n";
        std::cout << "B==C is " << (B == C ? "true" : "false") << "\n";
        std::cout << "C==D is " << (C == D ? "true" : "false") << "\n";
        std::cout << "D==A is " << (D == A ? "true" : "false") << "\n\n";

        // Test list operations and handle exceptions
        try {
            A.peekPrev();
        } catch (std::length_error &e) {
            std::cout << "List: peekPrev(): cursor at front\n   continuing without interruption\n";
        }

        try {
            A.movePrev();
        } catch (std::length_error &e) {
            std::cout << "List: movePrev(): cursor at front\n   continuing without interruption\n";
        }

        try {
            A.setBefore(100);
        } catch (std::length_error &e) {
            std::cout << "List: setBefore(): cursor at front\n   continuing without interruption\n";
        }

        try {
            A.eraseBefore();
        } catch (std::length_error &e) {
            std::cout << "List: eraseBefore(): cursor at front\n   continuing without interruption\n";
        }

        try {
            A.peekNext();
        } catch (std::length_error &e) {
            std::cout << "List: peekNext(): cursor at back\n   continuing without interruption\n";
        }

        try {
            A.moveNext();
        } catch (std::length_error &e) {
            std::cout << "List: moveNext(): cursor at back\n   continuing without interruption\n";
        }

        try {
            A.setAfter(200);
        } catch (std::length_error &e) {
            std::cout << "List: setAfter(): cursor at back\n   continuing without interruption\n";
        }

        try {
            A.eraseAfter();
        } catch (std::length_error &e) {
            std::cout << "List: eraseAfter(): cursor at back\n   continuing without interruption\n";
        }

        // Final state of list A for verification
        std::cout << "A = " << A << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
