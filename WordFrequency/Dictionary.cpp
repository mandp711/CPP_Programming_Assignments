/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
Dictionary.cpp
Implementation file for Dictionary
*/
#include "Dictionary.h"

#define black 0
#define red 1

// node constructor
Dictionary::Node::Node(keyType k, valType v): key(k), val(v), parent(nullptr), 
left(nullptr), right(nullptr), color(black) { 

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
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    postOrderDelete(root); 
    delete(nil); 
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right); 
    }
}

/*PreOrderTreeWalk(x)
   if x != NIL
      print(x.key)
      PreOrderTreeWalk(x.left)
      PreOrderTreeWalk(x.right)
// Appends a string representation of the tree rooted at R to s. The appended
   // string will consist of keys only, with the order determined by a pre-order
   // tree walk. The keys stored in black Nodes will be appended as "key\n", and
   // the keys stored in red Nodes will be appended as "key (RED)\n". The output 
   // of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
*/
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key; 
        if (R->color == red) {
            s += " (RED)"; 
        }
        s += "\n"; 
        preOrderString(s, R->left); 
        preOrderString(s, R->right); 
    }
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
void Dictionary::BST_insert(Node* M) {
    Node* y = nil; 
    Node* x = root; 
    while (x != nil) {
        y = x; 
        if (M->key < x->key) {
            x = x->left; 
        }
        else {
            x = x->right; 
        }
    }
    M->parent = y; 
    if (y == nil) {
        root = M; 
    }
    else if (M->key < y->key) {
        y->left = M; 
    }
    else {
        y->right = M; 
    }
    M->left = nil;
    M->right = nil;
    M->color = red; 
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
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

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left); 
        postOrderDelete(R->right); 
        delete R; 
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || k == R->key) {
        return R; 
    }
    else if (k < R->key) {
        return search(R->left, k);
    } 
    else {
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
// Node, or is nil, returns nil
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) {
        return findMin(N->right); 
    }
    Node* y = N->parent; 
    while (y != nil && N == y->right) {
        N = y;
        y = y->parent; 
    } 
    return y; 
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {
        return findMax(N->left); 
    }
    Node* y = N->parent; 
    while (y != nil && N == y->left) {
        N = y; 
        y = y->parent; 
    }
    return y; 
}

// RBT Helper Functions

// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    Node* y = N->right;

    N->right = y->left; 
    if (y->left != nil) {
        y->left->parent = N; 
    }

    y->parent = N->parent; 
    if (N->parent == nil) {
        root = y;
    }
    else if (N == N->parent->left) {
        N->parent->left = y; 
    }
    else {
        N->parent->right = y;
    }

    y->left = N; 
    N->parent = y; 
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
    Node* y = N->left; 
    
    N->left = y->right; 
    if (y->right != nil) {
        y->right->parent = N;
    }

    y->parent = N->parent; 
    if (N->parent == nil) {
        root = y; 
    }
    else if (N == N->parent->right) {
        N->parent->right = y; 
    }
    else {
        N->parent->left = y; 
    }

    y->right = N; 
    N->parent = y; 
}

void Dictionary::RB_Insert(Node* N) {
    Node* y = nil; 
    Node* x = root; 

    while (x != nil) {
        y = x; 
        if (N->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right; 
        }
        N->parent = y; 
        if (y == nil) {
            root = N; 
        } else if (N->key < y->key) {
            y->left = N; 
        } else {
            y->right = N; 
        }
        N->left = nil; 
        N->right = nil; 
        N->color = red; 
        RB_InsertFixUp(N); 
    }
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == red) {
        if (N->parent == N->parent->parent->left) {
            Node* y = N->parent->parent->right; 
            if (y->color == red) {
                N->parent->color = black; 
                y->color = black; 
                N->parent->parent->color = red; 
                N = N->parent->parent; 
            }
            else {
                if (N == N->parent->right) {
                    N = N->parent; 
                    LeftRotate(N); 
                }
                N->parent->color = black; 
                N->parent->parent->color = red; 
                RightRotate(N->parent->parent); 
            }
        }
        else {
            Node* y = N->parent->parent->left; 
            if (y->color == red) {
                N->parent->color = black; 
                y->color = black; 
                N->parent->parent->color = red;
                N = N->parent->parent; 
            }
            else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N); 
                }
                N->parent->color = black; 
                N->parent->parent->color = red; 
                LeftRotate(N->parent->parent); 
            }
        }
    }
    root->color = black; 
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v; 
    }
    else {
        u->parent->right = v; 
    }
    v->parent = u->parent; 
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
    Node* y = N; 
    Node* x; 
    int y_original_color = y->color; 
    if (N->left == nil) {
        x = N->right; 
        RB_Transplant(N, N->right); 
    }
    else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);   
    }
    else {
        y = findMin(N->right); 
        y_original_color = y->color; 
        x = y->right; 
        if (y->parent == N) {
            x->parent = y; 
        }
        else {
            RB_Transplant(y, y->right); 
            y->right = N->right; 
            y->right->parent = y; 
        }
        RB_Transplant(N, y); 
        y->left = N->left; 
        y->left->parent = y; 
        y->color = N->color; 
    }
    if (y_original_color == black) {
        RB_DeleteFixUp(x); 
    }
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    Node* w; 
    while (N != root && N->color == black) {
        if (N == N->parent->left) {
            w = N->parent->right; 
            if (w->color == red) {
                w->color = black; 
                N->parent->color = red; 
                LeftRotate(N->parent); 
                w = N->parent->right; 
            }
            if (w->left->color == black && w->right->color == black) {
                w->color = red;
                N = N->parent; 
            }
            else {
                if (w->right->color == black) {
                    w->left->color = black; 
                    w->color = red; 
                    RightRotate(w); 
                    w = N->parent->right; 
                }
                w->color = N->parent->color; 
                N->parent->color = black; 
                w->right->color = black; 
                LeftRotate(N->parent);
                N = root; 
            }
        }
        else {
            w = N->parent->left; 
            if (w->color == red) {
                w->color = black; 
                N->parent->color = red; 
                RightRotate(N->parent); 
                w = N->parent->left; 
            }
            if (w->right->color == black and w->left->color == black) {
                w->color = red; 
                N = N->parent; 
            }
            else {
                if (w->left->color == black) {
                    w->right->color = black; 
                    w->color = red; 
                    LeftRotate(w); 
                    w = N->parent->left; 
                }
                w->color = N->parent->color; 
                N->parent->color = black; 
                w->left->color = black; 
                RightRotate(N->parent); 
                N = root; 
            }
        }
    }
    N->color = black; 
}



// Access Functions

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
    Node* currentNode = root;
    Node* parent = nil;
    
    while (currentNode != nil) {
        parent = currentNode;
        if (k == currentNode->key) {
            currentNode->val = v;
            return;
        }
        currentNode = (k < currentNode->key) ? currentNode->left : currentNode->right;
    }

    Node* newNode = new Node(k, v);
    newNode->color = red; 
    newNode->left = nil;
    newNode->right = nil;
    newNode->parent = parent;

    if (parent == nil) {
        root = newNode;
    } else if (k < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    RB_InsertFixUp(newNode);

    num_pairs++;
}




 // remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType key) {
    Node* target = search(root, key);
    if (target == nil) {
        throw std::invalid_argument("Dictionary: remove(): key \"" + key + "\" does not exist");
    }

    Node* deleteNode = target;
    Node* childNode;
    int nodeColor = deleteNode->color;

    if (deleteNode->left == nil) {
        childNode = deleteNode->right;
        RB_Transplant(deleteNode, deleteNode->right);
    }
    else if (deleteNode->right == nil) {
        childNode = deleteNode->left;
        RB_Transplant(deleteNode, deleteNode->left);
    }
    else {
        deleteNode = findMin(deleteNode->right);
        nodeColor = deleteNode->color;
        childNode = deleteNode->right;
        if (deleteNode->parent == target) {
            childNode->parent = deleteNode;
        }
        else {
            RB_Transplant(deleteNode, deleteNode->right);
            deleteNode->right = target->right;
            deleteNode->right->parent = deleteNode;
        }
        RB_Transplant(target, deleteNode);
        deleteNode->left = target->left;
        deleteNode->left->parent = deleteNode;
        deleteNode->color = target->color;
    }

    if (current == target) {
        current = nil;
    }

    delete target;
    if (nodeColor == black) {
        RB_DeleteFixUp(childNode);
    }

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




