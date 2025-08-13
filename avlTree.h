#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

// Generic element
template <typename T>
struct TBinaryNode {
    T data;
    int key;
    int balance;
    TBinaryNode<T> *right;
    TBinaryNode<T> *left;
};

// Points to the root of the Generic Binary Tree
template <typename T>
struct TBinaryTree {
    TBinaryNode<T> *root;
};

// Boot Generic Tree
template <typename T>
void BootBinaryTree(TBinaryTree<T> &tree) {
    tree.root = NULL;
};

// Print
template <typename T>
void printTree(TBinaryNode<T> *node) {
    if (node != NULL) {
        printTree (node->left); // Navigate to the lowest element (most left)
        cout << node->key<<" "; // Print element
        printTree (node->right);
    }
}

// Insert (with balancing)
template <typename T>
int insert(TBinaryNode<T> *&node, int key, T data) {
    if (node == NULL) {
        node = new TBinaryNode<T>;
        node->key = key;
        node->data = data;
        node->balance = 0;
        node->right = NULL;
        node->left = NULL;
        return 1;
    } else {
        if (key > node->key) { // If key > node->key // insert in the right side
            int n = insert(node->right, key, data);
            node->balance = node->balance + n;
            if (node->balance > 1) { // Check if should be balanced
                if (node->right->key > key)
                    RL(node);
                else
                    RR(node);
                return 0;
            } else {
                if (node->balance == 0)
                    return 0;
                else
                    return 1;
            }
        } else {
            if (key < node->key) { // If key < node->key // insert in the left side
                int n = insert(node->
                    left, key, data);
                node->balance = node->balance - n;
                if (node->balance < -1) {
                    if (node->left->key > key)
                        LL(node);
                    else
                        LR(node);
                    return 0;
                } else {
                    if (node->balance == 0)
                        return 0;
                    else
                        return 1;
                }
            }
        }
    }
    return 0;
}

// Search to return data
template <typename T>
T searchData(TBinaryNode<T> *&node, int key) {
    if (node != NULL) {
        if (node->key == key) {
            return node->data;
        } else {
            if (key > node->key)
                searchData(node->right, key);
            else {
                if (key < node->key)
                    searchData(node->left, key);
            }
        }
    }
}

// Remove node
template <typename T>
void remove (TBinaryNode<T> *&node) {
    TBinaryNode<T> *exclude; // Pointer which is gonna be the node removed
    TBinaryNode<T> *greater = node->left; // Saves left element of node that gonna be removed
    if (greater == NULL) { // Check if there isn't node in the left
        exclude = node;
        node = node->right;
        delete exclude;
        return;
    }
    TBinaryNode<T> *parent = NULL; // Pointer which saves parent node
    while (greater->right != NULL) { // Navigate until reaches most right element of the left side of the node which is gonna be removed
        parent = greater; // Saves parente o greater node
        greater = greater->right;
    }
    greater->right = node->right; // Gets the right side of the node which is gonna be removed
    if (parent != NULL) { // Check if there is parent node
        parent->right = greater->left; // Parent gets left side of the node which is gonna substitute the node which is gonna be removed
        greater->left = node->left; // Greater gets left side of the node which is gonna be removed
    }
    exclude = node;
    node = greater; // Node gets substituted by greater
    delete exclude; // Node is removed
}

// Search to remove
template <typename T>
void searchRemove(TBinaryNode<T> *&node, int key) {
    if (node != NULL) {
        if (node->key == key) {
            remove(node);
        } else {
            if (key > node->key)
                searchRemove(node->right, key);
            else {
                if (key < node->key)
                    searchRemove(node->left, key);
            }
        }
    }
}

// Balance case: Left-Left
template <typename T>
void LL (TBinaryNode<T> *&r) {
  TBinaryNode<T> *b = r; // B became sub-tree's root
  TBinaryNode<T> *a = b->left; // A became left side of sub-tree's root
  b->left = a->right; // Root->left points a->right
  a->right = b; // a->right points to root
  a->balance = 0;
  b->balance = 0;
  r = a;
}

// Balance case: Right-Right
template <typename T>
void RR (TBinaryNode<T> *&r) {
  TBinaryNode<T> *b = r; // B became sub-tree's root
  TBinaryNode<T> *a = b->right; // A became right side of sub-tree's root
  b->right = a->left; // Root->right points a->left
  a->left = b; // a->right points to root
  a->balance = 0;
  b->balance = 0;
  r = a;
}

// Balance case: Left-Right
template <typename T>
void LR (TBinaryNode<T> *&r) {
  TBinaryNode<T> *b = r; // B became sub-tree's root
  TBinaryNode<T> *a = b->left; // A became left side of sub-tree's root
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
void RL (TBinaryNode<T> *&r) {
  TBinaryNode<T> *b = r; // B became sub-tree's root
  TBinaryNode<T> *a = b->right; // A became right side of sub-tree's root
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

// Print
template <typename T>
void printNode(T k, int b) {
  for (int i = 0; i < b; i++)
    cout << "   ";
  cout << k << endl;
}

// Print
template <typename T>
void showTree(TBinaryNode<T> *node, int b) {
  if (node == NULL) {
    printNode(0, b);
    return;
  }
  showTree(node->right, b+2);
  printNode(node->key, b);
  showTree(node->left, b+2);
}
