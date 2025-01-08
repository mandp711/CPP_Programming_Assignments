/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
Dictionary.cpp
Implementation file for Dictionary
*/
#include "Dictionary.h"
#include <stdexcept>
#include <iostream>

// Node constructor
Dictionary::Node::Node(keyType k, valType v)
   : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr) {
   }

Dictionary::Dictionary() {
   nil = new Node("", 0);
   nil->left = nil;
   nil->right = nil;
   nil->parent = nil;
   root = nil;
   num_pairs = 0;
}


// Copy constructor
Dictionary::Dictionary(const Dictionary& D) {
   nil = new Node("", 0);
   root = nil;
   current = nil;
   num_pairs = 0;
   preOrderCopy(D.root, nil);
}


// Destructor
Dictionary::~Dictionary() {
   postOrderDelete(root);
   delete nil;
}

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R->key != N->key) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
    else {
        return; 
    }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || k == R->key) {
        return R;
    }
    if (k < R->key) {
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R != nil) {
        while (R->left != nil) {
            R = R->left; 
        }
    } 
    return R; 
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R != nil) {
        while (R->right != nil) {
            R = R->right; 
        }
    }
    return R; 
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nil) {
        return nil; 
    }
    if (N->right != nil) {
        return findMin(N->right); 
    }
    Node* P = N->parent; 
    while (P != nil && N == P->right) {
        N = P; 
        P = P->parent; 
    } 
    return P; 
}

// findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nil) {
        return nil; 
    }
    if (N->left != nil) {
        return findMax(N->left); 
    }
    Node* P = N->parent; 
    while (P != nil && N == P->left) {
        N = P; 
        P = P->parent; 
    } 
    return P; 
}

// Access Functions -----------------------------------------------------------

// size()
// Returns the size of this Dictionary
int Dictionary::size() const {
    return num_pairs; 
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil; 
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    Node* N = search(root, k); 
    if (N == nil) {
        throw std::logic_error("Dictionary: getValue(): key not found"); 
    }
    return N->val; 
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    return current != nil; 
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (!(hasCurrent())) {
        throw std::logic_error("Dictionary: currentKey(): current undefined"); 
    }   
    return current->key; 
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (!(hasCurrent())) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val; 
}

// Manipulation Procedures ----------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root); 
    root = nil; 
    current = nil; 
    num_pairs = 0; 
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    Node* current = root;
    Node* parent = nil;

    while (current != nil && current->key != k) {
        parent = current;
        if (k < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current != nil) {
        current->val = v;
    } else {
        Node* newNode = new Node(k, v);
        newNode->left = newNode->right = nil;

        if (parent == nil) {
            root = newNode;
        } else if (k < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        newNode->parent = parent;
        num_pairs++;
    }
}


 // remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).

void Dictionary::remove(keyType k) {
    Node* nodeDel = search(root, k);
    if (nodeDel == nil) {
        throw std::invalid_argument("Dictionary: remove(): key \"" + k + "\" does not exist");
    }

    if (nodeDel->left != nil && nodeDel->right != nil) {
        Node* successor = findMin(nodeDel->right);
        nodeDel->key = successor->key;
        nodeDel->val = successor->val;
        nodeDel = successor;
    }

    Node* replacement = (nodeDel->left != nil) ? nodeDel->left : nodeDel->right;

    if (nodeDel->parent == nil) {
        root = replacement;
    } else if (nodeDel == nodeDel->parent->left) {
        nodeDel->parent->left = replacement;
    } else {
        nodeDel->parent->right = replacement;
    }

    if (replacement != nil) {
        replacement->parent = nodeDel->parent;
    }

    if (current == nodeDel) {
        current = nil;
    }

    delete nodeDel;
    num_pairs--;
}



// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    current = findMin(root); 
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    current = findMax(root); 
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current undefined"); 
    }
    current = findPrev(current); 
}

// Other Functions ------------------------------------------------------------

std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    return to_string() == D.to_string();
}

// Overloaded Operators -------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        clear();
        if (D.root != D.nil) {
            preOrderCopy(D.root, D.nil);
        }
    }
    return *this;
}