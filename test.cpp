#include <iostream>
#include "avlTree.h"

using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

int main() {
    AVL_TBinaryTree<int> tree;
    AVL_boot(tree);
    bool menu = true;

    while (menu) {
        system(CLEAR);

        cout << "\n======== AVL Binary Tree =======" << endl;
        cout << "=== 1 -     Insert Node      ===" << endl;
        cout << "=== 2 -     Remove Node      ===" << endl;
        cout << "=== 3 -     Search Node      ===" << endl;
        cout << "=== 4 - Print Tree In-Order  ===" << endl;
        cout << "=== 5 - Print Tree Structure ===" << endl;
        cout << "=== 6 -      Tree Size       ===" << endl;
        cout << "=== 7 - Check if Key Exists  ===" << endl;
        cout << "=== 8 -      Reset Tree      ===" << endl;
        cout << "=== 9 -         Quit         ===" << endl;
        cout << "================================" << endl;
        cout << "Enter your choice: ";

        int key, value, choice;
        cin >> choice;
        switch(choice) {
            case 1: // Insert
                cout << "Enter a key: ";
                cin >> key;
                cout << "Enter a value: ";
                cin >> value;
                AVL_insert(tree.root, key, value);
                break;
            case 2: // Remove
                cout << "Enter a key to remove: ";
                cin >> key;
                AVL_remove(tree.root, key);
                break;
            case 3: // Search
                cout << "Enter a key to search: ";
                cin >> key;
                value = AVL_searchData(tree.root, key);
                cout << "Value found: " << value << endl;
                cout << "Type any character to return to the menu...";
                cin.ignore();
                cin.get();
                break;
            case 4: // Print in-order
                cout << "Tree in-order: ";
                AVL_printTree(tree.root);
                cout << endl;
                cout << "Type any character to return to the menu...";
                cin.ignore();
                cin.get();
                break;
            case 5: // Show tree sideways
                cout << "AVL Tree structure:\n";
                AVL_showTree(tree.root, 0);
                cout << "Type any character to return to the menu...";
                cin.ignore();
                cin.get();
                break;
            case 6: // Tree size
                cout << "Tree size: " << AVL_size(tree.root) << endl;
                cout << "Type any character to return to the menu...";
                cin.ignore();
                cin.get();
                break;
            case 7: // Check key
                cout << "Enter a key to check: ";
                cin >> key;
                if (AVL_contains(tree.root, key))
                    cout << "Key exists in the tree." << endl;
                else
                    cout << "Key does not exist." << endl;
                cout << "Type any character to return to the menu...";
                cin.ignore();
                cin.get();
                break;
            case 8: // Reset tree
                AVL_destroyTree(tree.root);
                AVL_boot(tree);
                break;
            case 9: // Quit
                menu = false;
                break;
            default:
                cout << "Invalid choice!\n";
                cout << "Type any character to return to the menu...";
                cin.ignore();
                cin.get();
                break;
        }
    }

    AVL_destroyTree(tree.root);
    return 0;
}
