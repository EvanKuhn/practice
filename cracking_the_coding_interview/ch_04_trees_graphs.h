#include "common.h"

//==============================================================================
// Problems and solutions
//==============================================================================

const string CHAPTER_04_QUESTION_01 =
"Implement a function to check if a tree is balanced. For the purposes of this\n"
"question, a balanced tree is defined to be a tree such that no two leaf nodes\n"
"differ in distance from the root by more than one.";

struct TreeNode {
  explicit TreeNode(int value = 0, TreeNode* left = NULL, TreeNode* right = NULL)
    : value(value)
    , left (left)
    , right(right)
  { }

  ~TreeNode() {
    delete left;
    delete right;
    left = right = NULL;
  }

  bool is_leaf() const {
    return !left && !right;
  }

  // Data members
  int       value;
  TreeNode* left;
  TreeNode* right;
};

// Build a balanced tree and return a pointer to the root node
TreeNode* _build_balanced_tree() {
  return new TreeNode(1,
    new TreeNode(2,
      new TreeNode(3),
      new TreeNode(4)
    ),
    new TreeNode(5,
      new TreeNode(6),
      new TreeNode(7)
    )
  );
}

// Iterative function to check if a tree is balanced (ie. all leaf nodes have
// the same height).
bool tree_is_balanced_i(TreeNode* root) {
  queue<pair<TreeNode*,int> > nodes;
  nodes.push(make_pair(root, 0));
  int expected_depth = -1;

  while(!nodes.empty()) {
    // Get the next node and its depth
    TreeNode* node = nodes.front().first;
    int depth = nodes.front().second;
    nodes.pop();

    // If the node is a leaf, check that it is at the expected depth
    if(node->is_leaf()) {
      if(expected_depth == -1) {
        expected_depth = depth;
      }
      if(depth != expected_depth) {
        return false;
      }
    }
    // Check children's depth
    else {
      if(node->left)  nodes.push(make_pair(node->left,  depth + 1));
      if(node->right) nodes.push(make_pair(node->right, depth + 1));
    }
  }

  return true;
}

// Recursive helper function to check node depth
static bool _check_node_depth(TreeNode* node, int depth, int& expected_depth) {
  // If the node is a leaf, return true if the depth is the same as the expected
  // depth, false otherwise. If expected_depth is uninitialized (-1), init it.
  if(node->is_leaf()) {
    if(expected_depth == -1) {
      expected_depth = depth;
    }
    return expected_depth == depth;
  }
  // Node is not a leaf. Check all children.
  else {
    if(node->left && !_check_node_depth(node->left, depth+1, expected_depth)) {
      return false;
    }
    if(node->right && !_check_node_depth(node->right, depth+1, expected_depth)) {
      return false;
    }
  }
  return true;
}

// Recursive function to check if a tree is balanced (ie. all leaf nodes have
// the same height).
bool tree_is_balanced_r(TreeNode* root) {
  int leaf_depth = -1;
  return _check_node_depth(root, 0, leaf_depth);
}

void test_chapter_04_question_01() {
  TreeNode* tree = _build_balanced_tree();

  // Check for a balanced tree with our iterative and recursive functions
  if(tree_is_balanced_i(tree)) {
    cout << "Success, tree_is_balanced_i() detected a balanced tree" << endl;
  }
  else {
    cout << "Error, tree_is_balanced_i() didn't detect a balanced tree" << endl;
  }
  if(tree_is_balanced_r(tree)) {
    cout << "Success, tree_is_balanced_r() detected a balanced tree" << endl;
  }
  else {
    cout << "Error, tree_is_balanced_r() didn't detect a balanced tree" << endl;
  }

  // Add a new node to make the tree unbalanced
  tree->right->right->right = new TreeNode(100);

  // Recheck the now-unbalanced tree
  if(tree_is_balanced_i(tree)) {
    cout << "Error, tree_is_balanced_i() didn't detect an unbalanced tree" << endl;
  }
  else {
    cout << "Success, tree_is_balanced_i() detected an unbalanced tree" << endl;
  }
  if(tree_is_balanced_r(tree)) {
    cout << "Error, tree_is_balanced_r() didn't detect an unbalanced tree" << endl;
  }
  else {
    cout << "Success, tree_is_balanced_r() detected an unbalanced tree" << endl;
  }

  delete tree;
}

//------------------------------------------------------------------------------

const string CHAPTER_04_QUESTION_02 =
"Given a directed graph, design an algorithm to find out whether there is a\n"
"route between two nodes.";

// Simple directed graph class implemented using an adjacency matrix
class DirectedGraph {
public:
  // Construct the DirectedGraph given the number of nodes in the graph
  explicit DirectedGraph(size_t num_nodes = 0) {
    resize(num_nodes);
  }

  // Clear the graph
  void clear() { m_edges.clear(); }

  // Resize the graph to contain N nodes
  void resize(size_t num_nodes) {
    m_edges.clear();
    m_edges.resize(num_nodes);
    for(size_t i = 0; i < num_nodes; ++i) {
      m_edges[i].resize(num_nodes);
    }
  }

  // Get the number of nodes in the graph
  size_t size() const { return m_edges.size(); }

  // Get adjacent nodes by number
  void get_adjacent(int n, vector<int>& adj) const;

  // Add, delete, or check existence of edge A -> B.
  // Edges are numbered from 0 to size-1.
  void add_edge(size_t a, size_t b)       { m_edges[a][b] = true; }
  void del_edge(size_t a, size_t b)       { m_edges[a][b] = false; }
  bool has_edge(size_t a, size_t b) const { return m_edges[a][b]; }

  // Check if a route exists between two nodes A and B
  bool has_route(size_t src, size_t dst) const;

private:
  // Adjacency matrix. m_edges[i][j] == true indicates edge I -> J exists.
  vector<vector<bool> > m_edges;
};

void DirectedGraph::get_adjacent(int node, vector<int>& adj) const {
  adj.clear();
  for(int i = 0; i < size(); ++i) {
    if(has_edge(node, i)) {
      adj.push_back(i);
    }
  }
}

bool DirectedGraph::has_route(size_t src, size_t dst) const {
  queue<int> horizon;
  horizon.push(src);
  unordered_set<int> visited;

  while(!horizon.empty()) {
    // Get next node in horizon
    int next = horizon.front();
    horizon.pop();

    // Mark the node as visited
    visited.insert(next);

    // Get all nodes adjacent to the node
    vector<int> adj;
    get_adjacent(next, adj);

    // Check each adjacent node
    for(size_t i = 0; i < adj.size(); ++i) {
      int adj_node = adj[i];
      // If the adjacent node is the destination, return true!
      if(adj_node == dst) {
        return true;
      }
      // Else if the adjacent node has not been visited, add it to the horizon
      if(visited.find(adj_node) == visited.end()) {
        horizon.push(adj_node);
      }
    }
  }
  return false;
}

static void _construct_test_graph(DirectedGraph& g) {
  // Graph:
  //  1 -> 2 -> 3 -> 4 ->5
  //            ^
  //            |
  //  6 -> 7 -- +
  // So there's a path from 1 -> 5, and 6 -> 5, but not 1 -> 6.
  g.resize(8);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 5);
  g.add_edge(6, 7);
  g.add_edge(7, 3);
}

static void _check_route_exists(const DirectedGraph& graph, size_t a, size_t b,
  bool expected)
{
  const bool has_route = graph.has_route(a, b);
  const char* answer = (has_route ? "true" : "false");
  const char* status = (has_route == expected ? "OK" : "FAIL");
  printf("graph.has_route(%lu,%lu) returned %s (%s)\n", a, b, answer, status);
}

void test_chapter_04_question_02() {
  // Construct test graph
  DirectedGraph graph;
  _construct_test_graph(graph);

  // Check that routes exist
  _check_route_exists(graph, 1, 2, true);
  _check_route_exists(graph, 1, 3, true);
  _check_route_exists(graph, 1, 4, true);
  _check_route_exists(graph, 1, 5, true);

  _check_route_exists(graph, 6, 7, true);
  _check_route_exists(graph, 6, 3, true);
  _check_route_exists(graph, 6, 4, true);
  _check_route_exists(graph, 6, 5, true);

  _check_route_exists(graph, 6, 1, false);
  _check_route_exists(graph, 6, 2, false);
}

//------------------------------------------------------------------------------

const string CHAPTER_04_QUESTION_03 =
"Given a sorted (increasing order) array, write an algorithm to create a binary\n"
"tree with minimal height.";

void test_chapter_04_question_03() { }

//------------------------------------------------------------------------------

const string CHAPTER_04_QUESTION_04 =
"Given a binary search tree, design an algorithm which creates a linked list of\n"
"all the nodes at each depth (i.e., if you have a tree with depth D, you’ll have\n"
"D linked lists).";

void test_chapter_04_question_04() { }

//------------------------------------------------------------------------------

const string CHAPTER_04_QUESTION_05 =
"Write an algorithm to find the ‘next’ node (i.e., in-order successor) of a\n"
"given node in a binary search tree where each node has a link to its parent.";

void test_chapter_04_question_05() { }

//------------------------------------------------------------------------------

const string CHAPTER_04_QUESTION_06 =
"Design an algorithm and write code to find the first common ancestor of two\n"
"nodes in a binary tree. Avoid storing additional nodes in a data structure.\n"
"NOTE: This is not necessarily a binary search tree.";

void test_chapter_04_question_06() { }

//------------------------------------------------------------------------------

const string CHAPTER_04_QUESTION_07 =
"You have two very large binary trees: T1, with millions of nodes, and T2,\n"
"with hundreds of nodes. Create an algorithm to decide if T2 is a subtree of T1.";

void test_chapter_04_question_07() { }

//------------------------------------------------------------------------------

const string CHAPTER_04_QUESTION_08 =
"You are given a binary tree in which each node contains a value. Design an\n"
"algorithm to print all paths which sum up to that value. Note that it can be\n"
"any path in the tree - it does not have to start at the root.";

void test_chapter_04_question_08() { }

//==============================================================================
// Chapter class for printing questions and solutions
//==============================================================================

Exercise CHAPTER_04_EXERCISES[] = {
  Exercise(4, 1, CHAPTER_04_QUESTION_01, test_chapter_04_question_01),
  Exercise(4, 2, CHAPTER_04_QUESTION_02, test_chapter_04_question_02),
  Exercise(4, 3, CHAPTER_04_QUESTION_03, test_chapter_04_question_03),
  Exercise(4, 4, CHAPTER_04_QUESTION_04, test_chapter_04_question_04),
  Exercise(4, 5, CHAPTER_04_QUESTION_05, test_chapter_04_question_05),
  Exercise(4, 6, CHAPTER_04_QUESTION_06, test_chapter_04_question_06),
  Exercise(4, 7, CHAPTER_04_QUESTION_07, test_chapter_04_question_07),
  Exercise(4, 8, CHAPTER_04_QUESTION_08, test_chapter_04_question_08),
};

Chapter g_chapter_04(4, "Stacks and Queues", CHAPTER_04_EXERCISES,
  array_length(CHAPTER_04_EXERCISES));
