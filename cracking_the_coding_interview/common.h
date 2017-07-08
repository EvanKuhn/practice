#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <unordered_map>
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
// A Chapter object holds a set of exercises. It can be extended to add specific
// exercises per chapter.
// TODO: we could probably replace all of this with an ExerciseRegistry, and
// allow Exercise objects to be sorted.
//==============================================================================

class Chapter {
public:
  Chapter(int number, const string& title)
    : m_number(number)
    , m_title(title)
  { }

  // Get the chapter number
  int number() const { return m_number; }

  // Get the chapter title
  const string& title() const { return m_title; }

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
    initialize();
    cout << bold_on;
    cout << SEP << endl;
    cout << "Chapter " << number() << ": " << title() << endl;
    cout << SEP << "\n\n";
    cout << bold_off;
    for(int i = 1; i <= num_exercises(); ++i) {
      cout << exercise(i) << endl;
      // TODO: run the 'answer' function
    }
  }

protected:
  // Initialize questions and answers. Override in base classes!
  virtual void init_exercises() = 0;

  // Initialize the exercises if not already done
  void initialize() {
    if(m_exercises.empty()) {
      init_exercises();
    }
  }

  // Add an exercise.
  // - This will check the exercise's number against the expected number and
  //   raise a std::logic_error if they don't match.
  void add_exercise(int expected, const string& question, answer_func_ptr answer)
  {
    const int ch_number = m_number;
    const int ex_number = m_exercises.size() + 1;
    if(ex_number != expected) {
      ostringstream buf;
      buf << "Added exercise " << ex_number << ", expected " << expected;
      throw logic_error(buf.str());
    }
    m_exercises[ex_number] = Exercise(ch_number, ex_number, question, answer);
  }

private:
  // Data members
  int m_number;
  string m_title;
  unordered_map<int,Exercise> m_exercises;
};
