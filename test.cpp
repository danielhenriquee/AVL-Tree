#include <iostream>
#include <limits>
#include "AVL_TREE.h"

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

// Pause console (cross-platform)
void pauseConsole() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    AVL_TBinaryTree<int> tree;
    AVL_boot(tree);
    bool menu = true;

    while (menu) {
        clearScreen();

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

        int choice;
        cin >> choice;

        if(cin.fail()) {  // Validate input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            pauseConsole();
            continue;
        }

        int key, value;

        switch(choice) {
            case 1: // Insert
                cout << "Enter a key: ";
                cin >> key;
                cout << "Enter a value: ";
                cin >> value;
                AVL_insert(tree.root, key, value);
                cout << "Node inserted successfully.\n";
                pauseConsole();
                break;

            case 2: // Remove
                cout << "Enter a key to remove: ";
                cin >> key;
                AVL_remove(tree.root, key);
                cout << "Node removed (if it existed).\n";
                pauseConsole();
                break;

            case 3: // Search
                cout << "Enter a key to search: ";
                cin >> key;
                try {
                    value = AVL_searchData(tree.root, key);
                    cout << "Value found: " << value << endl;
                } catch (const out_of_range &e) {
                    cout << e.what() << endl;
                }
                pauseConsole();
                break;

            case 4: // Print in-order
                cout << "Tree in-order: ";
                AVL_printTree(tree.root);
                cout << endl;
                pauseConsole();
                break;

            case 5: // Show tree sideways
                cout << "AVL Tree structure:\n";
                AVL_showTree(tree.root, 0);
                pauseConsole();
                break;

            case 6: // Tree size
                cout << "Tree size: " << AVL_size(tree.root) << endl;
                pauseConsole();
                break;

            case 7: // Check key
                cout << "Enter a key to check: ";
                cin >> key;
                if (AVL_contains(tree.root, key))
                    cout << "Key exists in the tree." << endl;
                else
                    cout << "Key does not exist." << endl;
                pauseConsole();
                break;

            case 8: // Reset tree
                AVL_destroyTree(tree.root);
                AVL_boot(tree);
                cout << "Tree reset successfully." << endl;
                pauseConsole();
                break;

            case 9: // Quit
                menu = false;
                break;

            default:
                cout << "Invalid choice!\n";
                pauseConsole();
                break;
        }
    }

    AVL_destroyTree(tree.root);
    return 0;
}
