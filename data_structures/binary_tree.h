#pragma #once
#include <stddef.h>

//==============================================================================
// Binary search tree implementation
//==============================================================================


class BinaryTree {
public:
  // Node structure for the tree
  struct Node {
    Node() : value(0), right(NULL), left(NULL) { }
    explicit Node(int value) : value(value), right(NULL), left(NULL) { }
    int value;
    Node* right;
    Node* left;
  };

  // Constructor, destructor
  BinaryTree();
  ~BinaryTree();

  // Get the number of nodes in the tree
  size_t size() const;

  // Remove all nodes from the tree
  void clear();

  // Add a value to the tree. Returns true if added, false if already present.
  bool add(int value);

  // Delete a value from the tree. Returns true if deleted, false if not found.
  bool del(int value);

  // Check whether the current value exists in the tree
  bool has(int value) const;

  // Typedef for taking action on nodes in one of the visit* functions
  typedef void (*node_visit_func_t)(BinaryTree::Node* node);

  // Visit nodes in order, pre-order, or post-order
  void visit_in_order(node_visit_func_t func) const;
  void visit_pre_order(node_visit_func_t func) const;
  void visit_post_order(node_visit_func_t func) const;

  // Depth-first and breadth-first search
  bool depth_first_search(int target) const;
  bool breadth_first_search(int target) const;

private:
  // Data members
  Node*  m_root;
  size_t m_size;
};
