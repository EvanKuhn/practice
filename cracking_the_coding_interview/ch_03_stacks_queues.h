#include "common.h"

//==============================================================================
// Problems and solutions
//==============================================================================

const string CHAPTER_03_QUESTION_01 =
"Describe how you could use a single array to implement three stacks.";

void test_chapter_03_question_01() {
  cout << "Divide the array in 3 equal parts, allow each stack to grow within\n"
       << "its space. If we need to realloc, we can do that and double the size\n"
       << "of the stack that needs more space (and maybe double the sizes of\n"
       << "any stack that's close to full, to avoid to many realloc's).\n";
}

//------------------------------------------------------------------------------

const string CHAPTER_03_QUESTION_02 =
"How would you design a stack which, in addition to push and pop, also has a\n"
"function min which returns the minimum element? Push, pop and min should all\n"
"operate in O(1) time.";

void test_chapter_03_question_02() {
  cout << "Add `min` to each stack element, and set it each time you add an element\n";
}

//------------------------------------------------------------------------------

const string CHAPTER_03_QUESTION_03 =
"Imagine a (literal) stack of plates. If the stack gets too high, it might topple.\n"
"Therefore, in real life, we would likely start a new stack when the previous\n"
"stack exceeds some threshold. Implement a data structure SetOfStacks that mimics\n"
"this SetOfStacks should be composed of several stacks, and should create a new\n"
"stack once the previous one exceeds capacity. SetOfStacks.push() and\n"
"SetOfStacks.pop() should behave identically to a single stack (that is, pop()\n"
"should return the same values as it would if there were just a single stack).\n"
"FOLLOW UP\n"
"Implement a function popAt(int index) which performs a pop operation on a\n"
"specific sub-stack";

template <typename T>
class SetOfStacks {
public:
  // Max size of a single stack in the set
  static const size_t MAX_STACK_SIZE = 10;

  SetOfStacks()
    : m_size(0)
    , m_max_stack_size(MAX_STACK_SIZE)
  { }

  explicit SetOfStacks(size_t max_stack_size)
    : m_size(0)
    , m_max_stack_size(max_stack_size)
  { }

  // Get the total number of elements in the set of stacks
  size_t size() const { return m_size; }

  // Get the number of internal stacks
  size_t num_stacks() const { return m_stacks.size(); }

  // Push a value onto the stack
  void push(const T& value);

  // Remove the top value in the stack
  void pop();

  // Return a reference to the top value in the stack
  T&       top()       { return m_stacks.back().top(); }
  const T& top() const { return m_stacks.back().top(); }

private:
  // Data members
  size_t m_size;
  size_t m_max_stack_size;
  std::list<std::stack<T> > m_stacks;
};

template <typename T>
void SetOfStacks<T>::push(const T& value) {
  // Create a new stack if the list of stacks is empty
  if(m_stacks.empty()) {
    m_stacks.resize(1);
  }
  // ... or if the last (topmost) stack is full
  else if(m_stacks.back().size() > m_max_stack_size) {
    m_stacks.resize(m_stacks.size() + 1);
  }
  // Push the new value
  m_stacks.back().push(value);
  ++m_size;
}

template <typename T>
void SetOfStacks<T>::pop() {
  // Pop the top value, and delete the stack if it becomes empty
  m_stacks.back().pop();
  if(m_stacks.back().empty()) {
    m_stacks.pop_back();
  }
  --m_size;
}

void test_chapter_03_question_03() {
  cout << "Creating SetOfStacks with max stack size of 4" << endl;
  SetOfStacks<int> sos(4);

  cout << "Adding values 10 to 20" << endl;
  for(int i = 10; i <= 20; ++i) {
    sos.push(i);
  }
  cout << "sos.size = " << sos.size() << endl;
  cout << "sos.num_stacks = " << sos.num_stacks() << endl;

  cout << "Pop all values: ";
  while(sos.size() > 0) {
    cout << sos.top() << ' ';
    sos.pop();
  }
  cout << endl;
  cout << "sos.size = " << sos.size() << endl;
  cout << "sos.num_stacks = " << sos.num_stacks() << endl;
}

//------------------------------------------------------------------------------

const string CHAPTER_03_QUESTION_04 =
"In the classic problem of the Towers of Hanoi, you have 3 rods and N disks of\n"
"different sizes which can slide on to any tower. The puzzle starts with disks\n"
"sorted in ascending order of size from top to bottom (eg, each disk sits on top\n"
"of an even larger one). You have the following constraints:\n"
"  (A) Only one disk can be moved at a time.\n"
"  (B) A disk is slid off the top of one rod onto the next rod.\n"
"  (C) A disk can only be placed on top of a larger disk.\n"
"Write a program to move the disks from the first rod to the last using Stacks";

class TowersOfHanoi {
public:
  // Constructor. Takes the number of disks as the `size`.
  explicit TowersOfHanoi(size_t num_disks);

  // Return the number of disks in the puzzle
  size_t num_disks() const { return m_num_disks; }

  // Solve the puzzle
  void solve();

  // Helper function to print the current game state
  void print(ostream& out) const;

private:
  // Enum identifying the left, middle, and right pegs
  enum EPeg { PEG_LEFT, PEG_MID, PEG_RIGHT };

  // Move `num` disks from one peg to another
  void _move(EPeg from, EPeg to, size_t num);

  // Move from one peg to another
  void _move(EPeg from, EPeg to);

  // Give two pegs, get the 'other' peg
  static EPeg _other_peg(EPeg a, EPeg b);

  size_t             m_num_disks;
  mutable stack<int> m_left;
  mutable stack<int> m_mid;
  mutable stack<int> m_right;
};

TowersOfHanoi::TowersOfHanoi(size_t num_disks)
  : m_num_disks(num_disks)
{
  for(size_t i = num_disks; i > 0; --i) {
    m_left.push(i);
  }
}

void TowersOfHanoi::solve() {
  _move(PEG_LEFT, PEG_RIGHT, m_num_disks);
}

TowersOfHanoi::EPeg TowersOfHanoi::_other_peg(EPeg a, EPeg b) {
  if(a != PEG_LEFT && b != PEG_LEFT) return PEG_LEFT;
  if(a != PEG_MID && b != PEG_MID) return PEG_MID;
  return PEG_RIGHT;
}

// Move a stack of N disks (N = `num`)
void TowersOfHanoi::_move(EPeg from, EPeg to, size_t num) {
  //cout << "_move(" << from << ", " << to << ", " << num << ")\n";
  if(num == 1) {
    _move(from, to);
  }
  else {
    const EPeg other = _other_peg(from, to);
    _move(from, other, num - 1);
    _move(from, to);
    _move(other, to, num - 1);
  }
}

// Move a single disk
void TowersOfHanoi::_move(EPeg from, EPeg to) {
  //cout << "_move(" << from << ", " << to << ")\n";
  if(from == to) return;

  int value = 0;
  stack<int>* src = NULL;
  stack<int>* dst = NULL;

  // Get pointers to the source and destination pegs (stacks)
  switch(from) {
    case PEG_LEFT:  src = &m_left;  break;
    case PEG_MID:   src = &m_mid;   break;
    case PEG_RIGHT: src = &m_right; break;
  }

  switch(to) {
    case PEG_LEFT:  dst = &m_left;  break;
    case PEG_MID:   dst = &m_mid;   break;
    case PEG_RIGHT: dst = &m_right; break;
  }

  // Check for errors
  if(src->empty()) {
    throw logic_error("attempting to move from an empty peg");
  }
  if(!dst->empty() && src->top() > dst->top()) {
    ostringstream ss;
    ss << "moving disk " << src->top() << " onto disk " << dst->top();
    throw logic_error(ss.str());
  }

  //cout << "Moving " << src->top() << " from " << from << " to " << to << endl;

  // Move the topmost value ('disk') from the source to dest
  dst->push(src->top());
  src->pop();
}

// Helper function for printing
void _print_helper(stack<int>& from, stack<int>& to, size_t size) {
  if(from.size() == size) {
    printf("%3d", from.top());
    to.push(from.top());
    from.pop();
  }
  else {
    cout << "   ";
  }
}

void TowersOfHanoi::print(ostream& out) const {
  stack<int> temp_left, temp_mid, temp_right;
  const size_t max_size = max(max(m_left.size(), m_mid.size()), m_right.size());

  // Print each disk. This will pop values off the stacks and place them on
  // the temp stacks.
  for(size_t s = max_size; s > 0; --s) {
    _print_helper(m_left, temp_left, s);
    cout << "     ";
    _print_helper(m_mid, temp_mid, s);
    cout << "     ";
    _print_helper(m_right, temp_right, s);
    cout << endl;
  }
  cout << "left      mid     right";

  // Move the values back from the temp stacks to the original stacks
  while(!temp_left.empty()) {
    m_left.push(temp_left.top());
    temp_left.pop();
  }
  while(!temp_mid.empty()) {
    m_mid.push(temp_mid.top());
    temp_mid.pop();
  }
  while(!temp_right.empty()) {
    m_right.push(temp_right.top());
    temp_right.pop();
  }
}

// Print a representation of the current state of the TowersOfHanoi object
ostream& operator<<(ostream& out, const TowersOfHanoi& obj) {
  obj.print(out);
  return out;
}

void test_chapter_03_question_04() {
  TowersOfHanoi towers(5);
  cout << "\nStart state:" << endl;
  cout << towers << endl;

  towers.solve();
  cout << "\nSolved state:" << endl;
  cout << towers << endl;
}

//------------------------------------------------------------------------------

const string CHAPTER_03_QUESTION_05 =
"Implement a MyQueue class which implements a queue using two stacks.";

template <typename T>
class MyQueue {
public:
  // Get the queue size
  size_t size() const;

  // Push a value to the back of the queue
  void push(const T& value);

  // Remove the value from the front of the queue
  void pop();

  // Access the front value
  T&       front();
  const T& front() const;

  // Access the front value
  T&       back();
  const T& back() const;

private:
  // Utility functions to move all values between the push and pop stacks
  void _move_all_to_push_stack();
  void _move_all_to_pop_stack();

  // Data members
  mutable stack<T> m_push_stack;
  mutable stack<T> m_pop_stack;
};

template <typename T>
size_t MyQueue<T>::size() const {
  return m_push_stack.size() + m_pop_stack.size();
}

template <typename T>
void MyQueue<T>::push(const T& value) {
  _move_all_to_push_stack();
  m_push_stack.push(value);
}

template <typename T>
void MyQueue<T>::pop() {
  _move_all_to_pop_stack();
  m_pop_stack.pop();
}

template <typename T>
T& MyQueue<T>::front() {
  _move_all_to_pop_stack();
  return m_pop_stack.top();
}

template <typename T>
const T& MyQueue<T>::front() const {
  _move_all_to_pop_stack();
  return m_pop_stack.top();
}

template <typename T>
T& MyQueue<T>::back() {
  _move_all_to_push_stack();
  return m_push_stack.top();
}

template <typename T>
const T& MyQueue<T>::back() const {
  _move_all_to_push_stack();
  return m_push_stack.top();
}

template <typename T>
void MyQueue<T>::_move_all_to_push_stack() {
  while(!m_pop_stack.empty()) {
    m_push_stack.push(m_pop_stack.top());
    m_pop_stack.pop();
  }
}

template <typename T>
void MyQueue<T>::_move_all_to_pop_stack() {
  while(!m_push_stack.empty()) {
    m_pop_stack.push(m_push_stack.top());
    m_push_stack.pop();
  }
}

void test_chapter_03_question_05() {
  MyQueue<int> q;
  cout << "Adding 10 values to queue" << endl;
  for(int i = 1; i <= 10; ++i) {
    q.push(i);
  }
  cout << "q.size() = " << q.size() << endl;
  cout << "q.front() = " << q.front() << endl;
  cout << "q.back() = " << q.back() << endl;
  cout << "values: ";
  while(q.size() > 0) {
    cout << q.front() << ' ';
    q.pop();
  }
  cout << endl;
  cout << "q.size() = " << q.size() << endl;
}

//------------------------------------------------------------------------------

const string CHAPTER_03_QUESTION_06 =
"Write a program to sort a stack in ascending order. You should not make any\n"
"assumptions about how the stack is implemented. The following are the only\n"
"functions that should be used to write this program: push | pop | peek | isEmpty.";

// TODO: I assume they want use to ONLY USE STACKS to solve this. In that case,
// create a second stack. Call the stacks A and B. Pop values from A onto B as
// long as they are decreasing.  If they are increasing, move the values back
// from B to A, then place the current value back on A.  Then continue moving
// from A to B.  Do this until you can move all values to B.  Then move all
// values back to A, so they'll be in ascending order.

void sort_stack_with_stacks(stack<int>& a) {
  stack<int> b;

  while(!a.empty()) {
    // Get the next value
    int val = a.top();
    a.pop();

    // Place the value on stack B if B is empty or if the value is smaller
    if(b.empty() || val <= b.top()) {
      b.push(val);
    }
    // Otherwise, move all values from B to A. Add the value to A at the
    // proper time to maintain the sort order.
    else {
      bool pushed = false;
      while(!b.empty()) {
        a.push(b.top());
        b.pop();

        if(!pushed) {
          if(val >= a.top() && (b.empty() || val <= b.top())) {
            a.push(val);
            pushed = true;
          }
        }
      }
    }
  }

  // Move all values back from B to A
  while(!b.empty()) {
    a.push(b.top());
    b.pop();
  }
}

ostream& operator<<(ostream& out, const stack<int>& s) {
  stack<int> temp = s;
  while(!temp.empty()) {
    out << temp.top();
    temp.pop();
    if(!temp.empty()) out << ' ';
  }
  return out;
}

void test_chapter_03_question_06() {
  // Try a stack with duplicates (probably)
  stack<int> a;
  for(int i = 0; i < 10; ++i) {
    a.push(rand() % 10);
  }

  // Print the stack before and after sorting
  cout << "\nBefore: " << a << endl;
  sort_stack_with_stacks(a);
  cout << "After:  " << a << endl;

  // Try a stack with no duplicates (probably)
  stack<int> b;
  for(int i = 0; i < 10; ++i) {
    b.push(rand() % 100);
  }

  // Print the stack before and after sorting
  cout << "\nBefore: " << b << endl;
  sort_stack_with_stacks(b);
  cout << "After:  " << b << endl;
}

//==============================================================================
// Chapter class for printing questions and solutions
//==============================================================================

Exercise CHAPTER_03_EXERCISES[] = {
  Exercise(3, 1, CHAPTER_03_QUESTION_01, test_chapter_03_question_01),
  Exercise(3, 2, CHAPTER_03_QUESTION_02, test_chapter_03_question_02),
  Exercise(3, 3, CHAPTER_03_QUESTION_03, test_chapter_03_question_03),
  Exercise(3, 4, CHAPTER_03_QUESTION_04, test_chapter_03_question_04),
  Exercise(3, 5, CHAPTER_03_QUESTION_05, test_chapter_03_question_05),
  Exercise(3, 6, CHAPTER_03_QUESTION_06, test_chapter_03_question_06),
};

Chapter g_chapter_03(3, "Stacks and Queues", CHAPTER_03_EXERCISES,
  array_length(CHAPTER_03_EXERCISES));
