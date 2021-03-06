#include "binary_tree.h"
#include <iostream>

using namespace std;

void print_node(const BinaryTree::Node* node) {
  cout << node->value << " ";
}

void print_node_and_level(const BinaryTree::Node* node, int level) {
  cout << "  level " << level << ": " << node->value << endl;
}

int main(int argc, char** argv) {
  BinaryTree tree;

  cout << "Adding values: ";
  for(int i=0; i<10; ++i) {
    int value = rand() % 100;
    cout << value << " ";
    tree.add(value);
  }
  cout << endl;
  cout << "Tree size: " << tree.size() << endl;

  cout << "Tree in-order: ";
  tree.visit_in_order(print_node);
  cout << endl;

  cout << "Tree pre-order: ";
  tree.visit_pre_order(print_node);
  cout << endl;

  cout << "Tree post-order: ";
  tree.visit_post_order(print_node);
  cout << endl;

  cout << "Tree by level:" << endl;
  tree.visit_by_level(print_node_and_level);

  cout << "DFS(44): ";
  cout << (tree.depth_first_search(44) ? "found!" : "not found") << endl;

  cout << "BFS(44): ";
  cout << (tree.breadth_first_search(44) ? "found!" : "not found") << endl;
}
