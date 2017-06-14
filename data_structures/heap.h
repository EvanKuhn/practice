//==============================================================================
// Heap data structure in C++
//==============================================================================
#pragma once

#include <vector>

template <typename T>
class Heap
{
public:
  Heap();
  Heap(const std::vector<T>& items);
  Heap(const Heap& other);
  Heap& operator=(const Heap& other);
  ~Heap();

  // Get the number of elements in the heap
  size_t size() const;

  // Check if the heap is empty
  bool empty() const;

  // Insert a value into the heap
  void insert(const T& value);

  // Remove and return the next value
  T extract();

  // Return the next value, but do not remove it
  T peek();

private:
  // Functions to get the parent or child of a given node (by index)
  size_t heap_parent(size_t i) { return (i - 1) / 2; }
  size_t heap_left  (size_t i) { return (i * 2) + 1; }
  size_t heap_right (size_t i) { return (i * 2) + 2; }

  // Data members
  std::vector<T> m_items;
};

// Heapsort algorithm
template <typename T>
void heapsort(std::vector<T>& items);

//==============================================================================
// Implementation
//==============================================================================

template <typename T>
Heap<T>::Heap() { }

template <typename T>
Heap<T>::Heap(const std::vector<T>& items) {
  for(size_t i=0; i<items.size(); i++) {
    insert(items[i]);
  }
}

template <typename T>
Heap<T>::Heap(const Heap& other) {
  Heap h;
  h = other;
  return h;
}

template <typename T>
Heap<T>& Heap<T>::operator=(const Heap& other) {
  m_items = other.m_items;
}

template <typename T>
Heap<T>::~Heap() { }

template <typename T>
size_t Heap<T>::size() const {
  return m_items.size();
}

template <typename T>
bool Heap<T>::empty() const {
  return m_items.empty();
}

template <typename T>
void Heap<T>::insert(const T& value) {
  // Append the new value to the items array. Then continually swap the value
  // with its parent until the heap property is satisfied.
  m_items.push_back(value);
  size_t i = m_items.size() - 1;

  while(i > 0) {
    // Compute the parent node index
    size_t i_parent = heap_parent(i);

    // Stop swapping if the parent is smaller
    if(m_items[i_parent] <= m_items[i])
      break;

    // Otherwise, swap parent and child
    std::swap(m_items[i_parent], m_items[i]);
    i = i_parent;
  }
}

template <typename T>
T Heap<T>::extract() {
  // Save the root node's value, and move the last node to the root
  T retval = m_items[0];
  m_items[0] = m_items.back();
  m_items.pop_back();
  size_t i = 0;

  // Swap the root node down the tree until the heap property is satisfied
  while(true) {
    size_t i_left  = heap_left(i);
    size_t i_right = heap_right(i);

    bool left_child_exists  = (i_left  < m_items.size());
    bool right_child_exists = (i_right < m_items.size());

    // Break if there are no children
    if(!left_child_exists)
      break;

    // Figure out which child is smaller
    size_t i_smallest = i_left;
    if(right_child_exists && m_items[i_right] < m_items[i_left])
      i_smallest = i_right;

    // Swap the current node with the smaller child
    if(m_items[i] > m_items[i_smallest]) {
      std::swap(m_items[i], m_items[i_smallest]);
      i = i_smallest;
    }
    else {
      break;
    }
  }

  // Return the top value we stored previously
  return retval;
}

template <typename T>
T Heap<T>::peek() {
  return m_items[0];
}

template <typename T>
void heapsort(std::vector<T>& items) {
  Heap<T> heap(items);
  items.clear();
  while(!heap.empty()) {
    items.push_back(heap.extract());
  }
}
