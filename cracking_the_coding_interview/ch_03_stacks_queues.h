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

void test_chapter_03_question_03() { }

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

void test_chapter_03_question_04() { }

//------------------------------------------------------------------------------

const string CHAPTER_03_QUESTION_05 =
"Implement a MyQueue class which implements a queue using two stacks.";

void test_chapter_03_question_05() { }

//------------------------------------------------------------------------------

const string CHAPTER_03_QUESTION_06 =
"Write a program to sort a stack in ascending order. You should not make any\n"
"assumptions about how the stack is implemented. The following are the only\n"
"functions that should be used to write this program: push | pop | peek | isEmpty.";

void test_chapter_03_question_06() { }

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
