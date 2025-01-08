/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
ListTest.cpp
Test file for testing function of List.cpp
*/
#include <iostream>
#include <cassert>
#include "BigInteger.h"

void testAdd() {
    BigInteger a, b, result;

    // Test adding two positive numbers
    a = BigInteger("12345");
    b = BigInteger("6789");
    result = a.add(b);
    assert(result.to_string() == "19134");

    // Test adding a positive and a negative number
    a = BigInteger("12345");
    b = BigInteger("-6789");
    result = a.add(b);
    assert(result.to_string() == "5556");

    // Test adding two negative numbers
    a = BigInteger("-12345");
    b = BigInteger("-6789");
    result = a.add(b);
    assert(result.to_string() == "-19134");

    // Test adding a positive and a negative number resulting in zero
    a = BigInteger("12345");
    b = BigInteger("-12345");
    result = a.add(b);
    assert(result.to_string() == "0");
}

void testSub() {
    BigInteger a, b, result;

    // Test subtracting two positive numbers
    a = BigInteger("12345");
    b = BigInteger("6789");
    result = a.sub(b);
    assert(result.to_string() == "5556");

    // Test subtracting a positive and a negative number
    a = BigInteger("12345");
    b = BigInteger("-6789");
    result = a.sub(b);
    assert(result.to_string() == "19134");

    // Test subtracting two negative numbers
    a = BigInteger("-12345");
    b = BigInteger("-6789");
    result = a.sub(b);
    assert(result.to_string() == "-5556");

    // Test subtracting two equal numbers
    a = BigInteger("12345");
    b = BigInteger("12345");
    result = a.sub(b);
    assert(result.to_string() == "0");
}

void testMult() {
    BigInteger a, b, result;

    // Test multiplying two positive numbers
    a = BigInteger("123");
    b = BigInteger("456");
    result = a.mult(b);
    assert(result.to_string() == "56088");

    // Test multiplying a positive and a negative number
    a = BigInteger("123");
    b = BigInteger("-456");
    result = a.mult(b);
    assert(result.to_string() == "-56088");

    // Test multiplying two negative numbers
    a = BigInteger("-123");
    b = BigInteger("-456");
    result = a.mult(b);
    assert(result.to_string() == "56088");

    // Test multiplying by zero
    a = BigInteger("0");
    b = BigInteger("456");
    result = a.mult(b);
    assert(result.to_string() == "0");
}

void testCompare() {
    BigInteger a, b;

    // Test comparing two positive numbers
    a = BigInteger("12345");
    b = BigInteger("6789");
    assert(a.compare(b) > 0);

    // Test comparing a positive and a negative number
    a = BigInteger("12345");
    b = BigInteger("-6789");
    assert(a.compare(b) > 0);

    // Test comparing two negative numbers
    a = BigInteger("-12345");
    b = BigInteger("-6789");
    assert(a.compare(b) < 0);

    // Test comparing two equal numbers
    a = BigInteger("12345");
    b = BigInteger("12345");
    assert(a.compare(b) == 0);

    // Test comparing zero with a positive number
    a = BigInteger("0");
    b = BigInteger("12345");
    assert(a.compare(b) < 0);

    // Test comparing zero with a negative number
    a = BigInteger("0");
    b = BigInteger("-12345");
    assert(a.compare(b) > 0);
}

void testToString() {
    BigInteger a;

    // Test string representation of positive numbers
    a = BigInteger("12345");
    assert(a.to_string() == "12345");

    // Test string representation of negative numbers
    a = BigInteger("-12345");
    assert(a.to_string() == "-12345");

    // Test string representation of zero
    a = BigInteger("0");
    assert(a.to_string() == "0");
}

int main() {
    testAdd();
    testSub();
    testMult();
    testCompare();
    testToString();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
