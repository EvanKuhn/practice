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

  // Fill a list with `count` random values in the range [0,max)
  List(size_t count, int max)
    : m_head(NULL), m_tail(NULL), m_size(0)
  {
    fill(count, max);
  }

  // Delete all nodes on destruction
  ~List() { clear(); }

  // Delete all nodes in the list
  void clear() {
    ListNode* cur = m_head;
    while(cur) {
      ListNode* next = cur->next;
      delete cur;
      cur = next;
    }
    m_size = 0;
    m_head = m_tail = NULL;
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

  // Fill the list with `count` random values in the range [0,max).
  // Will clear any existing values first.
  void fill(size_t count, int max) {
    clear();
    for(size_t i = 0; i < count; ++i) {
      append(rand() % max);
    }
  }

  // Sort the list using an O(N^2) sorting algo
  void sort() {
    ListNode* smallest = NULL;
    for(ListNode* start = m_head; start; start = start->next) {
      ListNode* smallest = start;
      for(ListNode* cur = start; cur; cur = cur->next) {
        if(cur->value < smallest->value) {
          smallest = cur;
        }
      }
      if(smallest != start) {
        std::swap(start->value, smallest->value);
      }
    }
  }

  // Problem 1: remove duplicates from a list
  void dedup();
  void dedup_no_extra_space();

  // Problem 2: return the Nth-to-last node
  ListNode*       nth_to_last(size_t n);
  const ListNode* nth_to_last(size_t n) const;

  // Problem 3: delete a node from the middle of the list
  void delete_middle_node(ListNode* node);

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

void List::dedup_no_extra_space() {
  sort();
  ListNode* curr = m_head;

  while(curr && curr->next) {
    // If the next node has the same value as the current one, delete it
    if(curr->next->value == curr->value) {
      ListNode* next = curr->next;
      curr->next = curr->next->next;
      delete next;
      --m_size;
    }
    // Next node has a different value. Move ahead.
    else {
      curr = curr->next;
    }
  }
}

void test_chapter_02_question_01() {
  List list;

  cout << "\nWith extra space:" << endl;
  list.fill(10, 8);
  cout << "- Original: " << list << endl;
  list.dedup();
  cout << "- Dedupped: " << list << endl;

  cout << "\nNo extra space:" << endl;
  list.clear();
  list.fill(10, 8);
  cout << "- Original: " << list << endl;
  list.dedup_no_extra_space();
  cout << "- Dedupped: " << list << endl;
}

//------------------------------------------------------------------------------

const string CHAPTER_02_QUESTION_02 =
  "Implement an algorithm to find the nth to last element of a singly linked list.";

ListNode* List::nth_to_last(size_t n) {
  ListNode* front = m_head;
  ListNode* back = NULL;

  // Move the `front` and `back` pointers along the list. Move `front` forward
  // N times, then init `back to the head, then move both until `front` is null.
  // At that point, return the `back` node.
  for(size_t i = 0; i < n; ++i) {
    if(!front) return NULL;
    front = front->next;
  }
  back = m_head;

  // Move both pointers
  while(front) {
    front = front->next;
    back = back->next;
  }
  return back;
}

const ListNode* List::nth_to_last(size_t n) const {
  return const_cast<List*>(this)->nth_to_last(n);
}

static string _node_value(const ListNode* node) {
  ostringstream ss;
  if(node)
    ss << node->value;
  else
    ss << "(null)";
  return ss.str();
}

void test_chapter_02_question_02() {
  List list;
  list.fill(10, 100);
  cout << "List: " << list << endl;
  cout << "1st to last: " << _node_value(list.nth_to_last(1)) << endl;
  cout << "2nd to last: " << _node_value(list.nth_to_last(2)) << endl;
  cout << "3rd to last: " << _node_value(list.nth_to_last(3)) << endl;
  cout << "4th to last: " << _node_value(list.nth_to_last(4)) << endl;
  cout << "10th to last: " << _node_value(list.nth_to_last(10)) << endl;
  cout << "11th to last: " << _node_value(list.nth_to_last(11)) << endl;
}

//------------------------------------------------------------------------------

const string CHAPTER_02_QUESTION_03 =
  "Implement an algorithm to delete a node in the middle of a single linked list,\n"
  "given only access to that node.\n"
  "EXAMPLE\n"
  "Input: the node ‘c’ from the linked list a->b->c->d->e\n"
  "Result: nothing is returned, but the new linked list looks like a->b->d->e";

// This question requires a dumb trick: swap this node's value with the next
// node, and then delete the next node.
void List::delete_middle_node(ListNode* node) {
  std::swap(node->value, node->next->value);
  ListNode* temp = node->next;
  node->next = node->next->next;
  delete temp;
  --m_size;
}

void test_chapter_02_question_03() {
  List list;
  list.fill(5, 10);
  cout << "Original: " << list << endl;
  ListNode* rm = list.nth_to_last(3);
  list.delete_middle_node(rm);
  cout << "Remove 3rd from last: " << list << endl;
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

// Operator to add two list and produce a third list representing the sum
List operator+(const List& a, const List& b) {
  List result;
  const ListNode* cur_a = a.head();
  const ListNode* cur_b = b.head();
  int carry = 0;

  while(cur_a || cur_b) {
    const int val_a = (cur_a ? cur_a->value : 0);
    const int val_b = (cur_b ? cur_b->value : 0);
    const int sum = val_a + val_b + carry;
    const int digit = sum % 10;
    carry = sum / 10;
    result.append(digit);
    if(cur_a) cur_a = cur_a->next;
    if(cur_b) cur_b = cur_b->next;
  }

  if(carry) {
    result.append(carry);
  }

  return result;
}

void test_chapter_02_question_04() {
  List a(3, 10);
  List b(3, 10);
  cout << endl;
  cout << "A:   " << a << endl;
  cout << "B:   " << b << endl;
  cout << "A+B: " << (a + b) << endl;

  a.fill(2,10);
  b.fill(4,10);
  cout << endl;
  cout << "A:   " << a << endl;
  cout << "B:   " << b << endl;
  cout << "A+B: " << (a + b) << endl;
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

Exercise CHAPTER_02_EXERCISES[] = {
  Exercise(2, 1, CHAPTER_02_QUESTION_01, test_chapter_02_question_01),
  Exercise(2, 2, CHAPTER_02_QUESTION_02, test_chapter_02_question_02),
  Exercise(2, 3, CHAPTER_02_QUESTION_03, test_chapter_02_question_03),
  Exercise(2, 4, CHAPTER_02_QUESTION_04, test_chapter_02_question_04),
  Exercise(2, 5, CHAPTER_02_QUESTION_05, test_chapter_02_question_05),
};

Chapter g_chapter_02(2, "Linked Lists", CHAPTER_02_EXERCISES,
  array_length(CHAPTER_02_EXERCISES));
