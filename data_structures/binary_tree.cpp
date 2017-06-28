#include "binary_tree.h"
#include <stack>
#include <queue>
#include <vector>
#include <iostream>

//==============================================================================
// Utility functions
//==============================================================================

// Recursive function to delete the given node an all of its children
static void _free_node_recursize(BinaryTree::Node* node) {
  if(node == NULL) {
    return;
  }
  if(node->left) {
    _free_node_recursize(node->left);
  }
  if(node->right) {
    _free_node_recursize(node->right);
  }
  delete node;
}

// Starting at the root, locate the node with a given value.
// - If found, set the `node_current` and `node_parent` pointer values,
//   and return true. Otherwise, return false.
static bool _find_node(BinaryTree::Node* root,
                       int value,
                       BinaryTree::Node** node_current = NULL,
                       BinaryTree::Node** node_parent = NULL)
{
  BinaryTree::Node* parent = NULL;
  BinaryTree::Node* cur = root;

  while(cur != NULL) {
    if(cur->value == value) {
      if(node_current) *node_current = cur;
      if(node_parent) *node_parent = parent;
      return true;
    }
    else if(value < cur->value) {
      parent = cur;
      cur = cur->left;
    }
    else {
      parent = cur;
      cur = cur->right;
    }
  }
  return false;
}

// Unset the parent's pointer to the child. Parent pointer may be null.
static void _unset_parent_pointer_to_child(BinaryTree::Node* parent,
                                           BinaryTree::Node* child)
{
  if(parent) {
    if(parent->left == child) {
      parent->left = NULL;
    }
    else if(parent->right == child) {
      parent->right = NULL;
    }
  }
}

enum EVisitOrder {
  IN_ORDER,
  PRE_ORDER,
  POST_ORDER
};

// Helper function for visit() functions
static void _visit(EVisitOrder order,
                   BinaryTree::Node* node,
                   BinaryTree::node_visit_func_t func)
{
  if(!node) {
    return;
  }
  if(order == PRE_ORDER) {
    func(node);
  }
  if(node->left) {
    _visit(order, node->left, func);
  }
  if(order == IN_ORDER) {
    func(node);
  }
  if(node->right) {
    _visit(order, node->right, func);
  }
  if(order == POST_ORDER) {
    func(node);
  }
}

//==============================================================================
// BinaryTree Implementation
//==============================================================================

BinaryTree::BinaryTree()
  : m_root(NULL)
  , m_size(0)
{ }

BinaryTree::~BinaryTree() {
  clear();
}

size_t BinaryTree::size() const {
  return m_size;
}

void BinaryTree::clear() {
  _free_node_recursize(m_root);
  m_root = NULL;
  m_size = 0;
}

bool BinaryTree::add(int value) {
  // If the tree is empty, just add a new node
  if(!m_root) {
    m_root = new Node(value);
    m_size++;
    return true;
  }

  // Tree is not empty. Search for the insertion point.
  Node* cur = m_root;
  while(true) {
    // If the current node contains the value, we can't add the new value
    if(cur->value == value) {
      return false;
    }
    // If value is less than current, search left
    if(value < cur->value) {
      if(cur->left) {
        cur = cur->left;
      }
      else {
        cur->left = new Node(value);
        m_size++;
        return true;
      }
    }
    // Else if value is greater, search right
    else {
      if(cur->right) {
        cur = cur->right;
      }
      else {
        cur->right = new Node(value);
        m_size++;
        return true;
      }
    }
  }
}

bool BinaryTree::del(int value) {
  // Find the node with the given value
  Node* cur;
  Node* parent;
  if(!_find_node(m_root, value, &cur, &parent))
    return false;

  // No children exist. Unset the parent's pointer to the current node.
  if(!cur->left && !cur->right) {
    _unset_parent_pointer_to_child(parent, cur);
    delete cur;
    m_size--;
  }
  // Only one child exists. Take its children and delete it.
  else if((cur->left && !cur->right) || (cur->right && !cur->left)) {
    Node* child = (cur->left ? cur->left : cur->right);
    cur->value = child->value;
    cur->left = child->left;
    cur->right = child->right;
    delete child;
    m_size--;
  }
  // Both left and right exist. We need to copy one child's values up.
  else if(cur->left && cur->right) {
    while(true) {
      if(cur->left) {
        cur->value = cur->left->value;
        parent = cur;
        cur = cur->left;
      }
      else if(cur->right) {
        cur->value = cur->right->value;
        parent = cur;
        cur = cur->right;
      }
      else {
        // Delete the current node and unset the parent's pointer to it
        _unset_parent_pointer_to_child(parent, cur);
        delete cur;
        m_size--;
        break;
      }
    }
  }

  return true;
}

bool BinaryTree::has(int value) const {
  return _find_node(m_root, value);
}

void BinaryTree::visit_in_order(node_visit_func_t func) const {
  _visit(IN_ORDER, m_root, func);
}

void BinaryTree::visit_pre_order(node_visit_func_t func) const {
  _visit(PRE_ORDER, m_root, func);
}

void BinaryTree::visit_post_order(node_visit_func_t func) const {
  _visit(POST_ORDER, m_root, func);
}

void BinaryTree::visit_by_level(node_visit_level_func_t func) const {
  if(!m_root) return;
  std::vector<const Node*> nodes, children;
  nodes.push_back(m_root);

  for(int level = 1; nodes.size() > 0; ++level) {
    // Apply the visit-function to each node, and also record their children
    for(size_t i = 0; i < nodes.size(); ++i) {
      const Node* cur = nodes[i];
      func(cur, level);
      if(cur->left) children.push_back(cur->left);
      if(cur->right) children.push_back(cur->right);
    }

    // Use the children as the new set of nodes
    nodes.swap(children);
    children.clear();
  }
}

bool BinaryTree::depth_first_search(int target) const {
  if(!m_root) return false;

  // Initialize a stack with the root node
  std::stack<const Node*> nodes;
  nodes.push(m_root);

  // While the stack is not empty, search
  while(nodes.size() > 0) {
    const Node* cur = nodes.top();
    nodes.pop();
    std::cout << cur->value << " "; //TODO
    if(cur->value == target) {
      return true;
    }
    if(cur->left) {
      nodes.push(cur->left);
    }
    if(cur->right) {
      nodes.push(cur->right);
    }
  }
  return false;
}

bool BinaryTree::breadth_first_search(int target) const {
  if(!m_root) return false;

  // Initialize a queue with the root node
  std::queue<const Node*> nodes;
  nodes.push(m_root);

  // While the queue is not empty, search
  while(nodes.size() > 0) {
    const Node* cur = nodes.front();
    nodes.pop();
    std::cout << cur->value << " "; //TODO
    if(cur->value == target) {
      return true;
    }
    if(cur->left) {
      nodes.push(cur->left);
    }
    if(cur->right) {
      nodes.push(cur->right);
    }
  }
  return false;
}
