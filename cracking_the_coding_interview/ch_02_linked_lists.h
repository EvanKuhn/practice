#include "common.h"

//==============================================================================
// Obviously we need a linked list implementation
//==============================================================================

struct ListNode {
  explicit ListNode(int val = 0, ListNode* next = NULL)
    : value(val)
    , next(next)
  { }
  int value;
  ListNode* next;
};

class List {
public:
  // Initialize an empty list
  List() : m_head(NULL), m_tail(NULL), m_size(0) { }

  // Delete all nodes on destruction
  ~List() {
    ListNode* cur = m_head;
    while(cur) {
      ListNode* next = cur->next;
      delete cur;
      cur = next;
    }
  }

  // Get the size
  size_t size() const { return m_size; }

  // Get the head or tail nodes.
  // NOTE: an iterator would be the correct way to expose this.
  const ListNode* head() const { return m_head; }
  const ListNode* tail() const { return m_tail; }

  // Prepend a value
  void prepend(int val) {
    if(!m_head) {
      m_head = m_tail = new ListNode(val);
    }
    else {
      m_head = new ListNode(val, m_head);
    }
    ++m_size;
  }

  // Append a value
  void append(int val) {
    if(!m_head) {
      m_head = m_tail = new ListNode(val);
    }
    else {
      m_tail = m_tail->next = new ListNode(val);
    }
    ++m_size;
  }

  // Fill the list with `count` random values in the range [0,max)
  void fill(size_t count, int max) {
    for(size_t i = 0; i < count; ++i) {
      append(rand() % max);
    }
  }

  // Sort the list using an O(N^2) sorting algo
  void sort() {
    for(ListNode* start = m_head; start && start->next; start = start->next) {
      for(ListNode* cur = start; cur && cur->next; cur = cur->next) {
        if(cur->value > cur->next->value) {
          std::swap(cur->value, cur->next->value);
        }
      }
    }
  }

  // Problem 1: remove duplicates from a list
  void dedup();
  void dedup_no_extra_space();

private:
  ListNode* m_head;
  ListNode* m_tail;
  size_t    m_size;
};

// Print all list values to the stream, separated by spaces
ostream& operator<<(ostream& out, const List& list) {
  for(const ListNode* cur = list.head(); cur; cur = cur->next) {
    out << cur->value;
    if(cur->next) out << ' ';
  }
  return out;
}

//==============================================================================
// Problems and solutions
//==============================================================================

const string CHAPTER_02_QUESTION_01 =
  "Write code to remove duplicates from an unsorted linked list.\n"
  "FOLLOW UP\n"
  "How would you solve this problem if a temporary buffer is not allowed?";

void List::dedup() {
  // We could sort the list with a bubble sort or other O(N^2) algo, and then
  // look for adjacent identical numbers. However using a hashset is easier.
  unordered_set<int> nums;
  ListNode* prev = NULL;
  ListNode* curr = m_head;

  while(curr) {
    // Current value not yet encountered. Add it to the set and iterate.
    if(nums.find(curr->value) == nums.end()) {
      nums.insert(curr->value);
      prev = curr;
      curr = curr->next;
    }
    // Current value is duplicate. Delete the current node.
    else {
      prev->next = curr->next;
      delete curr;
      curr = prev->next;
      --m_size;
    }
  }
}

void test_chapter_02_question_01() {
  List list;
  list.fill(10, 8);
  cout << "Original: " << list << endl;
  list.dedup();
  cout << "Dedupped: " << list << endl;
}

//------------------------------------------------------------------------------

const string CHAPTER_02_QUESTION_02 =
  "Implement an algorithm to find the nth to last element of a singly linked list.";

void test_chapter_02_question_02() {

}

//------------------------------------------------------------------------------

const string CHAPTER_02_QUESTION_03 =
  "Implement an algorithm to delete a node in the middle of a single linked list,\n"
  "given only access to that node.\n"
  "EXAMPLE\n"
  "Input: the node ‘c’ from the linked list a->b->c->d->e\n"
  "Result: nothing is returned, but the new linked list looks like a->b->d->e";

void test_chapter_02_question_03() {

}

//------------------------------------------------------------------------------

const string CHAPTER_02_QUESTION_04 =
  "You have two numbers represented by a linked list, where each node contains a\n"
  "single digit. The digits are stored in reverse order, such that the 1’s digit\n"
  "is at the head of the list. Write a function that adds the two numbers and\n"
  "returns the sum as a linked list.\n"
  "EXAMPLE\n"
  "Input: (3 -> 1 -> 5) + (5 -> 9 -> 2)\n"
  "Output: 8 -> 0 -> 8";

void test_chapter_02_question_04() {

}

//------------------------------------------------------------------------------

const string CHAPTER_02_QUESTION_05 =
  "Given a circular linked list, implement an algorithm which returns node at the\n"
  "beginning of the loop.\n"
  "DEFINITION\n"
  "Circular linked list: A (corrupt) linked list in which a node’s next pointer\n"
  "points to an earlier node, so as to make a loop in the linked list.\n"
  "EXAMPLE\n"
  "input: A -> B -> C -> D -> E -> C [the same C as earlier]\n"
  "output: C";

void test_chapter_02_question_05() {

}

//==============================================================================
// Chapter class for printing questions and solutions
//==============================================================================

//Chapter g_chapter_02(2, "Linked Lists", g_chapter_02_exercises);

class Chapter02 : public Chapter {
public:
  Chapter02()
    : Chapter(2, "Linked Lists")
  { }

protected:
  virtual void init_exercises() {
    add_exercise(1, CHAPTER_02_QUESTION_01, test_chapter_02_question_01);
    add_exercise(2, CHAPTER_02_QUESTION_02, test_chapter_02_question_02);
    add_exercise(3, CHAPTER_02_QUESTION_03, test_chapter_02_question_03);
    add_exercise(4, CHAPTER_02_QUESTION_04, test_chapter_02_question_04);
    add_exercise(5, CHAPTER_02_QUESTION_05, test_chapter_02_question_05);
  }
};
