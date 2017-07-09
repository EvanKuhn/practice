#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const char* SEP =
  "================================================================================";

// Typedef for answer function
typedef void (*answer_func_ptr)();

// Stream manipulators for bold fonts
std::ostream& bold_on(std::ostream& os) {
  return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os) {
  return os << "\e[0m";
}

// Seed the random number generator
void seed_rand() {
  time_t t;
  srand((unsigned) time(&t));
}

// Compute a C array length
#define array_length(array) (sizeof(array) / sizeof(array[0]))

//==============================================================================
// Exercise struct to hold an exercise's number, question text, and answer
// function. Also include a function to print an excercise to a stream.
//==============================================================================

class Exercise {
public:
  Exercise()
    : chapter(0)
    , number(0)
    , question("")
    , answer(NULL)
  { }

  Exercise(int chapter, int number, const string& question, answer_func_ptr answer)
    : chapter(chapter)
    , number(number)
    , question(question)
    , answer(answer)
  { }

  // Public data structures
  int chapter;
  int number;
  string question;
  answer_func_ptr answer;
};

// Print an exercise to a stream
ostream& operator<<(ostream& out, const Exercise& x) {
  out << bold_on << "QUESTION " << x.chapter << '.' << x.number << endl;
  out << "------------" << bold_off << endl;
  out << x.question << endl;
  out << "\nANSWER:" << endl;
  x.answer();
  return out;
}

//==============================================================================
// A Chapter object holds a set of exercises.
//==============================================================================

class Chapter {
public:
  Chapter(int number, const string& title)
    : m_number(number)
    , m_title(title)
  { }

  Chapter(int number, const string& title, const Exercise* exercises, size_t num_ex)
    : m_number(number)
    , m_title(title)
  {
    for(size_t i = 0; i < num_ex; ++i) {
      add_exercise(exercises[i]);
    }
  }

  // Get the chapter number
  int number() const { return m_number; }

  // Get the chapter title
  const string& title() const { return m_title; }

  // Add an exercise. Will raise a std::logic_error if the chapter number
  // doesn't match this chapter.
  void add_exercise(const Exercise& ex) {
    if(ex.chapter != m_number) {
      ostringstream buf;
      buf << "Added exercise " << ex.number << " to chapter " << m_number;
      throw logic_error(buf.str());
    }
    m_exercises[ex.number] = ex;
  }

  // Get the number of exercises in this chapter
  int num_exercises() const {
    return static_cast<int>(m_exercises.size());
  }

  // Get an exercise by number
  const Exercise& exercise(int num) const {
    return m_exercises.at(num);
  }

  // Run all exercises
  void run() {
    cout << bold_on;
    cout << SEP << endl;
    cout << "Chapter " << number() << ": " << title() << endl;
    cout << SEP << "\n\n";
    cout << bold_off;
    for(int i = 1; i <= num_exercises(); ++i) {
      cout << exercise(i) << endl;
    }
  }

private:
  // Data members
  int m_number;
  string m_title;
  unordered_map<int,Exercise> m_exercises;
};
