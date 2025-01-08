/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
DictionaryTest.cpp
Test file for testing function of Dictionary.cpp
*/
#include <iostream>
#include <cassert>
#include "Dictionary.h"

void testInsertionAndSize() {
    Dictionary dict;
    dict.setValue("a", 10);
    dict.setValue("b", 20);
    dict.setValue("c", 30);

    assert(dict.size() == 3);
    std::cout << "Test Insertion and Size: PASSED\n";
}

void testTraversal() {
    Dictionary dict;
    dict.setValue("a", 10);
    dict.setValue("c", 30);
    dict.setValue("b", 20);

    // Test forward traversal
    dict.begin();
    assert(dict.currentKey() == "a");
    assert(dict.currentVal() == 10);
    dict.next();
    assert(dict.currentKey() == "b");
    assert(dict.currentVal() == 20);
    dict.next();
    assert(dict.currentKey() == "c");
    assert(dict.currentVal() == 30);

    // Test backward traversal
    dict.end();
    assert(dict.currentKey() == "c");
    assert(dict.currentVal() == 30);
    dict.prev();
    assert(dict.currentKey() == "b");
    assert(dict.currentVal() == 20);
    dict.prev();
    assert(dict.currentKey() == "a");
    assert(dict.currentVal() == 10);

    std::cout << "Test Traversal: PASSED\n";
}

void testSearch() {
    Dictionary dict;
    dict.setValue("x", 100);
    dict.setValue("y", 200);

    assert(dict.contains("x"));
    assert(dict.contains("y"));
    assert(!dict.contains("z"));

    assert(dict.getValue("x") == 100);
    assert(dict.getValue("y") == 200);

    std::cout << "Test Search: PASSED\n";
}

void testRemoval() {
    Dictionary dict;
    dict.setValue("a", 10);
    dict.setValue("b", 20);
    dict.setValue("c", 30);

    dict.remove("b");
    assert(dict.size() == 2);
    assert(!dict.contains("b"));
    assert(dict.contains("a"));
    assert(dict.contains("c"));

    dict.remove("a");
    assert(dict.size() == 1);
    assert(!dict.contains("a"));
    assert(dict.contains("c"));

    std::cout << "Test Removal: PASSED\n";
}

void testEquality() {
    Dictionary dict1, dict2;

    dict1.setValue("key1", 100);
    dict1.setValue("key2", 200);

    dict2.setValue("key1", 100);
    dict2.setValue("key2", 200);

    assert(dict1 == dict2);

    dict2.setValue("key2", 300);
    assert(!(dict1 == dict2));

    std::cout << "Test Equality: PASSED\n";
}

void testClear() {
    Dictionary dict;
    dict.setValue("a", 10);
    dict.setValue("b", 20);
    dict.setValue("c", 30);

    dict.clear();
    assert(dict.size() == 0);
    assert(!dict.contains("a"));
    assert(!dict.contains("b"));
    assert(!dict.contains("c"));

    std::cout << "Test Clear: PASSED\n";
}

void testExceptions() {
    Dictionary dict;

    try {
        dict.currentKey();
        assert(false); // Should not reach here
    } catch (const std::logic_error& e) {
        std::cout << "Caught exception as expected: " << e.what() << "\n";
    }

    try {
        dict.getValue("nonexistent");
        assert(false); // Should not reach here
    } catch (const std::logic_error& e) {
        std::cout << "Caught exception as expected: " << e.what() << "\n";
    }

    try {
        dict.next();
        assert(false); // Should not reach here
    } catch (const std::logic_error& e) {
        std::cout << "Caught exception as expected: " << e.what() << "\n";
    }

    std::cout << "Test Exceptions: PASSED\n";
}

int main() {
    testInsertionAndSize();
    testTraversal();
    testSearch();
    testRemoval();
    testEquality();
    testClear();
    testExceptions();

    std::cout << "All tests PASSED.\n";
    return 0;
}
