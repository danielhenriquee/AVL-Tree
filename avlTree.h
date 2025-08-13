// Daniel Henrique da Silva

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <stdexcept>

using namespace std;

// Generic element
template <typename T>
struct AVL_TBinaryNode {
    T data;
    int key;
    int balance; // Balance factor = height(left) - height(right)
    AVL_TBinaryNode<T> *right; // Points to right child
    AVL_TBinaryNode<T> *left; // Points to left child
};

// Points to the root of the Generic Binary Tree
template <typename T>
struct AVL_TBinaryTree {
    AVL_TBinaryNode<T> *root;
};

// Boot Generic AVL Tree
template <typename T>
void AVL_boot(AVL_TBinaryTree<T> &tree) {
    tree.root = nullptr;
};

// Returns AVL tree height
template <typename T>
int height(TBinaryNode<T>* node) {
    if (!node) // If nullptr
        return 0;
    int hl = height(node->left); 
    int hr = height(node->right);
    if (hl > hr) // If left height is greater
        return hl + 1;
    else // If right height is greater or equal
        return hr + 1;
}

// Update node's balance factor
template <typename T>
void updateBalanceFactor (TBinaryNode<T>* node) {
    if (!node) // If nullptr
        return;
    int hl = height(node->left); // Calculates left subtree height
    int hr = height(node->right); // Calculates right subtree height
    n->balance = hl - hr // Balance factor = left height - right height 
}

// Balance case: Left-Left
template <typename T>
void LL (AVL_TBinaryNode<T> *&r) {
    AVL_TBinaryNode<T> *b = r; // B became sub-tree's root
    AVL_TBinaryNode<T> *a = b->left; // A became left side of sub-tree's root
    b->left = a->right; // Root->left points a->right
    a->right = b; // a->right points to root
    r = a;
    updateBalanceFactor(a);
    updateBalanceFactor(b);
}

// Balance case: Right-Right
template <typename T>
void RR (AVL_TBinaryNode<T> *&r) {
    AVL_TBinaryNode<T> *b = r; // B became sub-tree's root
    AVL_TBinaryNode<T> *a = b->right; // A became right side of sub-tree's root
    b->right = a->left; // Root->right points a->left
    a->left = b; // a->right points to root
    r = a;
    updateBalanceFactor(a);
    updateBalanceFactor(b);
}

// Balance case: Left-Right
template <typename T>
void LR (AVL_TBinaryNode<T> *&r) {
    AVL_TBinaryNode<T> *b = r; // B became sub-tree's root
    AVL_TBinaryNode<T> *a = b->left; // A became left side of sub-tree's root
    b->left = a->right->right;
    r = a->right;
    a->right = r->left;
    r->left = a;
    r->right = b;
    switch (r->balance) {
        case -1:
            a->balance = 0;
            b->balance = 1;
            break;
        case 0:
            a->balance = 0;
            b->balance = 0;
            break;
        case 1:
            a->balance = -1;
            b->balance = 0;
            break;
    }
}

// Balance case: Right-Left
template <typename T>
void RL (AVL_TBinaryNode<T> *&r) {
    AVL_TBinaryNode<T> *b = r; // B became sub-tree's root
    AVL_TBinaryNode<T> *a = b->right; // A became right side of sub-tree's root
    r = a->left;
    a->left = a->left->right;
    b->right = r->left;
    r->left = b;
    r->right = a;
    switch (r->balance) {
        case -1:
            a->balance = 1;
            b->balance = 0;
            break;
        case 0:
            a->balance = 0;
            b->balance = 0;
            break;
        case 1:
            a->balance = 0;
            b->balance = -1;
            break;
    }
}

// Rebalance node after insert ou remove
template <typename T>
void AVL_rebalance(AVL_TBinaryNode<T>* &node) {
    if (!node) // If nullptr
        return;

    AVL_updateBalanceFactor(node); // Firstly update balance factor
    
    if (node->balance > 1) { // If tree is left heavy (balance > 1)
        AVL_updateBalanceFactor(node->left); // Check left child balance to decide LL or LR
        if (node->left->balance >= 0) // LL case
            LL(node);
        else // LR case
            LR(node);
    } else if (node->balance < -1) {  // If tree is right heavy (balance < -1)
        AVL_updateBalanceFactor(node->right); // Check right child balance to decide RR or RL
        if (node->right->balance <= 0) // RR case
            RR(node);
        else // RL case
            RL(node);
    }
}

// AVL_insert (with balancing)
template <typename T>
bool AVL_insert(AVL_TBinaryNode<T> *&node, int key, T data) {
    if (node == nullptr) {
        node = new AVL_TBinaryNode<T>;
        node->key = key;
        node->data = data;
        node->balance = 0;
        node->right = nullptr;
        node->left = nullptr;
        return true;
        
    if (key < node->key) {
        if (!AVL_insert(node->left, key, data))
            return false;
    } else if (key > node->key) {
        if (!AVL_insert(node->right, key, data))
            return false;
    } else {
        node->data = data;  // Duplicated key: overwrite data
        return true;
    }

    // After insertion, rebalance current node
    AVL_rebalance(node);
    return true;
}

// Search to return data
template <typename T>
T AVL_searchData(AVL_TBinaryNode<T> *&node, int key) {
    if (node != nullptr) {
        if (node->key == key) {
            return node->data;
        } else {
            if (key > node->key)
                AVL_searchData(node->right, key);
            else {
                if (key < node->key)
                    AVL_searchData(node->left, key);
            }
        }
    }
    throw std::underflow_error("Error: empty stack.");
}

// AVL_remove node
template <typename T>
void AVL_remove (AVL_TBinaryNode<T> *&node) {
    AVL_TBinaryNode<T> *exclude; // Pointer which is gonna be the node AVL_removed
    AVL_TBinaryNode<T> *greater = node->left; // Saves left element of node that gonna be AVL_removed
    if (greater == nullptr) { // Check if there isn't node in the left
        exclude = node;
        node = node->right;
        delete exclude;
        return;
    }
    AVL_TBinaryNode<T> *parent = nullptr; // Pointer which saves parent node
    while (greater->right != nullptr) { // Navigate until reaches most right element of the left side of the node which is gonna be AVL_removed
        parent = greater; // Saves parente o greater node
        greater = greater->right;
    }
    greater->right = node->right; // Gets the right side of the node which is gonna be AVL_removed
    if (parent != nullptr) { // Check if there is parent node
        parent->right = greater->left; // Parent gets left side of the node which is gonna substitute the node which is gonna be AVL_removed
        greater->left = node->left; // Greater gets left side of the node which is gonna be AVL_removed
    }
    exclude = node;
    node = greater; // Node gets substituted by greater
    delete exclude; // Node is AVL_removed
}

// Search to AVL_remove
template <typename T>
void AVL_searchRemove(AVL_TBinaryNode<T> *&node, int key) {
    if (node != nullptr) {
        if (node->key == key) {
            AVL_remove(node);
        } else {
            if (key > node->key)
                AVL_searchRemove(node->right, key);
            else {
                if (key < node->key)
                    AVL_searchRemove(node->left, key);
            }
        }
    }
}

// Print
template <typename T>
void AVL_printTree(AVL_TBinaryNode<T> *node) {
    if (node != nullptr) {
        AVL_printTree (node->left); // Navigate to the lowest element (most left)
        cout << node->key<<" "; // Print element
        AVL_printTree (node->right);
    }
}


// Print
template <typename T>
void AVL_printNode(T k, int b) {
    for (int i = 0; i < b; i++)
        cout << "   ";
    cout << k << endl;
}

// Print
template <typename T>
void AVL_showTree(AVL_TBinaryNode<T> *node, int b) {
    if (node == nullptr) {
        AVL_printNode(0, b);
        return;
    }
    AVL_showTree(node->right, b+2);
    AVL_printNode(node->key, b);
    AVL_showTree(node->left, b+2);
}
