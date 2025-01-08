/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
List.cpp
Implementation file for List 
*/
#include<iostream>
#include<string>
#include<stdexcept>
#include "List.h"

List::Node::Node(ListElement x){
    data = x; 
    next = nullptr; 
    prev = nullptr; 
}

List::List(){
    frontDummy = new Node(0); 
    backDummy = new Node(0); 
    
    frontDummy->next = backDummy; 
    backDummy->prev = frontDummy; 
    beforeCursor = frontDummy; 
    afterCursor = backDummy; 
    pos_cursor = 0; 
    num_elements = 0; 
}

List::List(const List& L) : List() {
    Node* N = L.frontDummy->next; 
    while (N != L.backDummy) {
        insertBefore(N->data); 
        N = N->next; 
    }
    moveFront(); 
}

List::~List(){
    clear(); 
    delete frontDummy; 
    delete backDummy; 
}

int List::length() const {
    return num_elements; 
}

ListElement List::front() const {
    if (num_elements == 0)  { 
        throw std::length_error("List: front() called on empty List");
    }
    return frontDummy->next->data; 
}

ListElement List::back() const {
    if (num_elements == 0)  { 
        throw std::length_error("List: back() called on empty List");
    }
    return backDummy->prev->data; 
}

int List::position() const {
    return pos_cursor; 
}

ListElement List::peekNext() const {
    if (pos_cursor >= num_elements) {
        throw std::length_error("List: peekNext() called on end of list");
    }
    return afterCursor->data; 
}

ListElement List::peekPrev() const {
    if (pos_cursor == 0) {
        throw std::length_error("List: peekPrev() called on beginning of list");
    }
    return beforeCursor->data; 
}

void List::clear() {
    moveFront(); 
    while (num_elements > 0) {
        eraseAfter(); 
    }
}

void List::moveFront() {
    beforeCursor = frontDummy; 
    afterCursor = frontDummy->next;
    pos_cursor = 0; 
}

void List::moveBack() {
    beforeCursor = backDummy->prev; 
    afterCursor = backDummy; 
    pos_cursor = num_elements; 
}

ListElement List::moveNext() {
    if (pos_cursor >= num_elements) {
        throw std::length_error("List: moveNext() called on end of list");
    }
    beforeCursor = afterCursor; 
    afterCursor = afterCursor->next; 
    pos_cursor += 1;
    return beforeCursor->data; 
}

ListElement List::movePrev() {
    if (pos_cursor == 0) {
        throw std::length_error("List: movePrev() called on beginning of list");
    }
    afterCursor = beforeCursor; 
    beforeCursor = beforeCursor->prev; 
    pos_cursor -= 1; 
    return afterCursor->data; 
}

void List::insertAfter(ListElement x) {
    Node* N = new Node(x); 
    N->prev = beforeCursor; 
    N->next = afterCursor; 
    beforeCursor->next = N; 
    afterCursor->prev = N; 
    afterCursor = N; 
    num_elements += 1; 
}

void List::insertBefore(ListElement x) {
    Node* N = new Node(x); 
    N->prev = beforeCursor; 
    N->next = afterCursor; 
    beforeCursor->next = N; 
    afterCursor->prev = N; 
    beforeCursor = N;
    pos_cursor += 1;
    num_elements += 1; 
}

void List::setAfter(ListElement x) {
    if (pos_cursor >= num_elements) {
        throw std::length_error("List: setAfter() called on end of list");
    }
    afterCursor->data = x; 
}

void List::setBefore(ListElement x){
    if (pos_cursor == 0) {
        throw std::length_error("List: setBefore() called on beginning of list");
    }
    beforeCursor->data = x; 
}

void List::eraseAfter() {
    if (pos_cursor >= num_elements) {
        throw std::length_error("List: eraseAfter() called on end of list");
    }
    Node* N = afterCursor; 
    beforeCursor->next = afterCursor->next; 
    afterCursor->next->prev = beforeCursor; 
    afterCursor = afterCursor->next; 
    delete N; 
    num_elements--; 
}

void List::eraseBefore() {
    if (pos_cursor == 0) {
        throw std::length_error("List: eraseBefore() called on beginning of list");
    }
    Node* N = beforeCursor; 
    afterCursor->prev = beforeCursor->prev; 
    beforeCursor->prev->next = afterCursor; 
    beforeCursor = beforeCursor->prev; 
    delete N;
    num_elements--; 
    pos_cursor--; 
}

int List::findNext(ListElement x) {
    Node* curr = afterCursor; 
    int currPos = pos_cursor; 
    while (curr != backDummy) {
        if (curr->data == x) {
            beforeCursor = curr; 
            afterCursor = curr->next;
            pos_cursor = currPos + 1; 
            return pos_cursor; 
        }
        curr = curr->next; 
        currPos++; 
    }
    moveBack(); 
    return -1; 
}


int List::findPrev(ListElement x) {
    Node* curr = beforeCursor; 
    int currPos = pos_cursor - 1; 
    
    // Search backwards from beforeCursor
    while (curr != frontDummy) {
        if (curr->data == x) {
            // Set the cursor position to just before the found element
            afterCursor = curr;
            beforeCursor = curr->prev;
            pos_cursor = currPos;
            return pos_cursor;
        }
        // Move one node back and update position
        curr = curr->prev;
        currPos--;
    }
    
    // If not found, set cursor to front and return -1
    moveFront();
    return -1;
}


void List::cleanup() {
    Node* temp = frontDummy->next;
    int outer = 0;

    while (temp != backDummy) {
        Node* check = temp->next;
        int inner = outer + 1;

        while (check != backDummy) {
            if (check->data == temp->data) {
                Node* toDelete = check;
                check = check->next;

                if (toDelete == beforeCursor) {
                    beforeCursor = beforeCursor->prev;
                } else if (toDelete == afterCursor) {
                    afterCursor = afterCursor->next;
                }

                toDelete->prev->next = toDelete->next;
                toDelete->next->prev = toDelete->prev;
                delete toDelete;
                num_elements--;

                // Adjust pos_cursor if necessary
                if (inner < pos_cursor) {
                    pos_cursor--;
                }
            } else {
                check = check->next;
                inner++;
            }
        }
        temp = temp->next;
        outer++;
    }
}



List List::concat(const List& L) const {
    List result; 

    // Insert elements from this list
    Node* temp = frontDummy->next;
    while (temp != backDummy) {
        result.insertBefore(temp->data);
        temp = temp->next;
    }
    temp = L.frontDummy->next;
    while (temp != L.backDummy) {
        result.insertBefore(temp->data);
        temp = temp->next;
    }    

    // Insert elements from the second list (L)
    result.moveFront(); 

    // Return the concatenated list (cursor position doesn't need to be moved)
    return result;
}
// output: (3, 2, 1, 5, 4)

std::string List::to_string() const {
    std::string result = "(";
    Node* temp = frontDummy->next;
    while (temp != backDummy) {
        result += std::to_string(temp->data);
        if (temp->next != backDummy) {
            result += ", ";
        }
        temp = temp->next;
    }
    result += ")";
    return result;
}


bool List::equals(const List& R) const {
    if (num_elements != R.num_elements) {
        return false;
    }

    Node* temp = frontDummy->next; 
    Node* tempR = R.frontDummy->next; 

    while (temp != backDummy && temp != backDummy) {
        if (temp->data != tempR->data) {
            return false; 
        }

        temp = temp->next; 
        tempR = tempR->next; 
    }
    return true; 
}

std::ostream& operator<<( std::ostream& stream, const List& L ) {
    stream << L.to_string();
    return stream;
}

bool operator==( const List& A, const List& B ) {
    return A.equals(B);
}

List& List::operator=(const List& L)  {
    if (this != &L) { // Avoid self-assignment
        clear(); // Remove existing elements

        // Copy elements from L
        Node* temp = L.frontDummy->next;
        while (temp != L.backDummy) {
            insertBefore(temp->data);
            temp = temp->next;
        }
        moveFront();
    }
    return *this;

}











