#include <iostream>
#include <cstdlib>
#include "AVL_TREE.h"

int main() {
  bool menu = true;
  int choice;
  int value;
  int key;
  AVL_TBinaryTree<int> tree;
  AVL_boot(tree);

  while(menu) {
      system("CLS");  /*CodeBlocks*/
      
      cout << "\n====== AVL Binary Tree ======" << endl;
      cout << "1 - Insert" << endl;
      cout << "2 - Remove" << endl;
      cout << "3 - Search Data" << endl;
      cout << "4 - Print Tree In-Order" << endl;
      cout << "5 - Tree Size" << endl;
      cout << "6 - Check if Key Exists" << endl;
      cout << "7 - Reset Tree" << endl;
      cout << "8 - Quit" << endl;
      cout << "=============================" << endl;

      cout << "Enter your choice: ";
      cin >> choice;
      switch (choice) {
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
          case 3: // Search data
              cout << "Enter a key to search: ";
              cin >> key;
              try {
                  value = AVL_searchData(tree.root, key);
                  cout << "Value: " << value << endl;
              } catch (const out_of_range &e) {
                  cout << e.what() << endl;
              }
              system("PAUSE");
              break;
          case 4: // Print in-order
              cout << "Tree in-order: ";
              AVL_printTree(tree.root);
              cout << endl;
              system("PAUSE");
              break;
          case 5: // Tree size
              cout << "Tree size: " << AVL_size(tree.root) << endl;
              system("PAUSE");
              break;
          case 6: // Check if key exists
              cout << "Enter a key to check: ";
              cin >> key;
              if (AVL_contains(tree.root, key))
                  cout << "Key exists in the tree." << endl;
              else
                  cout << "Key does not exist." << endl;
              system("PAUSE");
              break;
          case 7: // Reset
              AVL_destroyTree(tree.root);
              AVL_boot(tree);
              cout << "Tree reset successfully." << endl;
              system("PAUSE");
              break;
          case 8: // Quit
              menu = false;
              break;
          default:
              cout << "Invalid choice!" << endl;
              system("PAUSE");
              break;
      }
  }
  AVL_destroyTree(tree.root);
  return 0;
}
