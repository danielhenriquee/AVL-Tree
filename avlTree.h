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
int height(AVL_TBinaryNode<T>* node) {
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
void AVL_updateBalanceFactor (AVL_TBinaryNode<T>* node) {
    if (!node) // If nullptr
        return;
    int hl = height(node->left); // Calculates left subtree height
    int hr = height(node->right); // Calculates right subtree height
    node->balance = hl - hr; // Balance factor = left height - right height 
}

// Balance case: Left-Left
template <typename T>
void LL (AVL_TBinaryNode<T> *&r) {
    AVL_TBinaryNode<T> *b = r; // B became sub-tree's root
    AVL_TBinaryNode<T> *a = b->left; // A became left side of sub-tree's root
    b->left = a->right; // Root->left points a->right
    a->right = b; // a->right points to root
    r = a;
    AVL_updateBalanceFactor(a);
    AVL_updateBalanceFactor(b);
}

// Balance case: Right-Right
template <typename T>
void RR (AVL_TBinaryNode<T> *&r) {
    AVL_TBinaryNode<T> *b = r; // B became sub-tree's root
    AVL_TBinaryNode<T> *a = b->right; // A became right side of sub-tree's root
    b->right = a->left; // Root->right points a->left
    a->left = b; // a->right points to root
    r = a;
    AVL_updateBalanceFactor(a);
    AVL_updateBalanceFactor(b);
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
    }  
    
    // Navigate to correct position
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
T AVL_searchData(AVL_TBinaryNode<T> *node, int key) {
    if (!node)
        throw std::out_of_range("Error: key not found.");
    if (key == node->key)
        return node->data;
    if (key < node->key)
        return AVL_searchData(node->left, key);
    else
        return AVL_searchData(node->right, key);
}

// AVL_remove node
template <typename T>
void AVL_remove(AVL_TBinaryNode<T>* &node, int key) {
    if (!node) // Empty subtree
        return; 

    if (key < node->key) { // Remove from left subtree
        AVL_remove(node->left, key);
    } else if (key > node->key) { // Remove from right subtree
        AVL_remove(node->right, key);
    } else { // Node found
        if (!node->left) { // No left child, replace with right child
            AVL_TBinaryNode<T>* temp = node;
            node = node->right;
            delete temp;
        } else if (!node->right) { // No right child, replace with left child
            AVL_TBinaryNode<T>* temp = node;
            node = node->left;
            delete temp;
        } else { // Node has two children: find the largest in left subtree
            AVL_TBinaryNode<T>* pred = node->left;
            AVL_TBinaryNode<T>* predParent = node;
            while (pred->right) {
                predParent = pred;
                pred = pred->right;
            } // Copy predecessor key/data to current node
            node->key = pred->key;
            node->data = pred->data;
    
            if (predParent->right == pred) // Remove predecessor node
                predParent->right = pred->left;
            else
                predParent->left = pred->left;
            delete pred;
        }
    }

    if (node) // Rebalance subtree
        AVL_rebalance(node);
}

// Print tree (ascending by key)
template <typename T>
void AVL_printTree(AVL_TBinaryNode<T> *node) {
    if (node != nullptr) {
        AVL_printTree (node->left); // Navigate to the lowest element (most left)
        cout << node->key<<" "; // Print element
        AVL_printTree (node->right);
    }
}

// Print node with indentation
template <typename T>
void AVL_printNode(T k, int b) {
    for (int i = 0; i < b; i++)
        cout << "   ";
    cout << k << endl;
}

// Print tree (sideways visualization)
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

// Delete tree
template <typename T>
void AVL_destroyTree(AVL_TBinaryNode<T>* &node) {
    if (!node)
        return;
    AVL_destroyTree(node->left);
    AVL_destroyTree(node->right);
    delete node;
    node = nullptr;
}

// Min node
template <typename T>
AVL_TBinaryNode<T>* AVL_min(AVL_TBinaryNode<T>* node) {
    if (!node) 
        return nullptr;
    while (node->left)
        node = node->left;
    return node;
}

// Max node
template <typename T>
AVL_TBinaryNode<T>* AVL_max(AVL_TBinaryNode<T>* node) {
    if (!node) 
        return nullptr;
    while (node->right)
        node = node->right;
    return node;
}

// Check if tree contains key
template <typename T>
bool AVL_contains(AVL_TBinaryNode<T>* node, int key) {
    if (!node) 
        return false;
    if (key == node->key) 
        return true;
    if (key < node->key) 
        return AVL_contains(node->left, key);
    return AVL_contains(node->right, key);
}

// Return tree size
template <typename T>
int AVL_size(AVL_TBinaryNode<T>* node) {
    if (!node) 
        return 0;
    return 1 + AVL_size(node->left) + AVL_size(node->right);
}

#endif // AVL_TREE_H
