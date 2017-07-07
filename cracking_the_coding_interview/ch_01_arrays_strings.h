#include "common.h"

//==============================================================================
// Problems and solutions
//==============================================================================

const string CHAPTER_01_QUESTION_01 =
  "Implement an algorithm to determine if a string has all unique characters.\n"
  "What if you can not use additional data structures?";

// Without using extra space, we sort the characters in the string and search
// for two of the same characters next to each other.
// If we could use extra space / extra data structures, we'd throw each char
// in a hashtable or hashset and see if we encounter a character twice.
bool string_has_unique_chars(string str) {
  std::sort(str.begin(), str.end());
  for(size_t i = 1; i < str.size(); ++i) {
    if(str[i-1] == str[1]) return false;
  }
  return true;
}

void _test_unique(const string& str) {
  cout << str << ": ";
  cout << (string_has_unique_chars(str) ? "unique" : "duplicates") << endl;
}

void test_chapter_01_question_01() {
  _test_unique("hello");
  _test_unique("world");
}

const string CHAPTER_01_QUESTION_02 =
  "Write code to reverse a C-Style String (C-String means that “abcd” is\n"
  "represented as five characters, including the null character).";

void reverse_string(char* str) {
  //TODO
}

void test_chapter_01_question_02() {
  //TODO
}

const string CHAPTER_01_QUESTION_03 =
  "Design an algorithm and write code to remove the duplicate characters in a string\n"
  "without using any additional buffer. NOTE: One or two additional variables are\n"
  "fine; an extra copy of the array is not.\n"
  "FOLLOW UP: Write the test cases for this method.";

void remove_dup_chars(char* str) {
  //TODO
}

void test_chapter_01_question_03() {
  //TODO
}

const string CHAPTER_01_QUESTION_04 =
  "Write a method to decide if two strings are anagrams or not.";

bool strings_are_anagrams(const string& a, const string& b) {
  return false; //TODO
}

void test_chapter_01_question_04() {
  //TODO
}

const string CHAPTER_01_QUESTION_05 =
  "Write a method to replace all spaces in a string with ‘%20’.";

void encode_spaces(string& str) {
  //TODO
}

void test_chapter_01_question_05() {
  //TODO
}

const string CHAPTER_01_QUESTION_06 =
  "Given an image represented by an NxN matrix, where each pixel in the image is 4\n"
  "bytes, write a method to rotate the image by 90 degrees. Can you do this in place?";

void rotate_image(uint32_t** data, size_t dim) {
  //TODO
}

void test_chapter_01_question_06() {
  //TODO
}

const string CHAPTER_01_QUESTION_07 =
  "Write an algorithm such that if an element in an MxN matrix is 0, its entire\n"
  "row and column is set to 0.";

void array_expand_zero(int** data, size_t m, size_t n) {
  //TODO
}

void test_chapter_01_question_07() {
  //TODO
}

const string CHAPTER_01_QUESTION_08 =
  "Assume you have a method isSubstring which checks if one word is a substring of\n"
  "another. Given two strings, s1 and s2, write code to check if s2 is a rotation\n"
  "of s1 using only one call to isSubstring.\n"
  "(eg: “waterbottle” is a rotation of “erbottlewat”).";

bool strings_are_rotations(const string& a, const string& b) {
  return false;//TODO
}

void test_chapter_01_question_08() {
  //TODO
}

//==============================================================================
// Chapter class for printing questions and testing solutions
//==============================================================================

class Chapter01 : public Chapter {
public:
  Chapter01()
    : Chapter(1, "Arrays and Strings")
  { }

protected:
  virtual void init_exercises() {
    add_exercise(1, CHAPTER_01_QUESTION_01, test_chapter_01_question_01);
    add_exercise(2, CHAPTER_01_QUESTION_02, test_chapter_01_question_02);
    add_exercise(3, CHAPTER_01_QUESTION_03, test_chapter_01_question_03);
    add_exercise(4, CHAPTER_01_QUESTION_04, test_chapter_01_question_04);
    add_exercise(5, CHAPTER_01_QUESTION_05, test_chapter_01_question_05);
    add_exercise(6, CHAPTER_01_QUESTION_06, test_chapter_01_question_06);
    add_exercise(7, CHAPTER_01_QUESTION_07, test_chapter_01_question_07);
    add_exercise(8, CHAPTER_01_QUESTION_08, test_chapter_01_question_08);
  }
};
