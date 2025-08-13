# AVL-Tree
AVL Tree implementation created at Data Structures - 2024/1

This repository contains a generic (template-based) implementation of an AVL Tree — a self-balancing binary search tree that maintains a height difference of at most one between its subtrees.
Its main goal is to serve as educational material for studying balanced tree structures, as well as a reusable base for academic projects that require efficient insertion, removal, and search operations.

**Contents**
- avlTree.h — AVL Tree definition and implementation
- test.cpp - main testing all features implementeds

**Features**
- Generic (template) support for storing data of any type
- Automatic rebalancing after insertion and deletion to maintain AVL properties
- Support for key–value association (key used for ordering, data for storage)
- Height calculation and balance factor tracking for each node
- Rotation cases: LL, RR, LR, RL
- Search operations (AVL_searchData, AVL_contains)
- Traversal and printing methods (AVL_printTree, AVL_showTree)
- Utility functions: AVL_size, AVL_min, AVL_max
- Memory management (AVL_destroyTree)

**Usage**
Include the header file in your C++ project and create an AVL_TBinaryTree<T> object with your desired type T.
You can then use the provided functions to insert, remove, search, and display tree contents while ensuring automatic balancing.

**Notes**
- Keys (int key) define the ordering; duplicate keys overwrite existing data
- The implementation prioritizes clarity over extreme optimization, making it suitable for learning and academic contexts
- Exception handling is provided for invalid search operations
- Printing methods are intended for debugging and visualization rather than structured output formatting
