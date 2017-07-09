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
    if(str[i-1] == str[i]) return false;
  }
  return true;
}

static void _test_unique(const string& str) {
  cout << "\"" << str << "\": ";
  cout << (string_has_unique_chars(str) ? "unique" : "duplicate") << " chars" << endl;
}

void test_chapter_01_question_01() {
  _test_unique("hello");
  _test_unique("world");
}

//------------------------------------------------------------------------------

const string CHAPTER_01_QUESTION_02 =
  "Write code to reverse a C-Style String (C-String means that “abcd” is\n"
  "represented as five characters, including the null character).";

char* reverse_string(char* str) {
  const size_t len = strlen(str);
  for(size_t i = 0, j = len - 1; i < j; ++i, --j) {
    std::swap(str[i], str[j]);
  }
  return str;
}

static void _test_reverse(const char* str) {
  char* buf = strdup(str);
  cout << "\"" << str << "\" --> \"" << reverse_string(buf) << "\"" << endl;
  delete buf;
}

void test_chapter_01_question_02() {
  _test_reverse("hello");
  _test_reverse("san francisco");
}

//------------------------------------------------------------------------------

const string CHAPTER_01_QUESTION_03 =
  "Design an algorithm and write code to remove the duplicate characters in a\n"
  "string without using any additional buffer. NOTE: One or two additional\n"
  "variables are fine; an extra copy of the array is not.\n"
  "FOLLOW UP: Write the test cases for this method.";

void remove_dup_chars(char* str) {
  // Table of flags indicating which chars we've seen
  bool chars_seen[128] = {0};

  // As we examine the string, we'll read from one location and write to another
  size_t i_read = 0;
  size_t i_write = 0;
  const size_t len = strlen(str);

  while(i_read < len) {
    // If we've seen this char before, skip it
    if(chars_seen[str[i_read]]) {
      ++i_read;
      continue;
    }

    // We haven't seen the char before, so copy it. (We can skip copying if
    // the read and write indexes are the same).
    if(i_read != i_write) {
      str[i_write] = str[i_read];
    }

    // Record that we've seen this char
    chars_seen[str[i_read]] = true;

    // Move on
    ++i_read;
    ++i_write;
  }

  // Terminate the string
  str[i_write] = '\0';
}

static void _test_rm_dups(const char* str) {
  char buf[128] = {0};
  strcpy(buf, str);
  remove_dup_chars(buf);
  cout << "\"" << str << "\" --> \"" << buf << "\"" << endl;
}

void test_chapter_01_question_03() {
  _test_rm_dups("");
  _test_rm_dups("a");
  _test_rm_dups("ab");
  _test_rm_dups("aab");
  _test_rm_dups("aaabbb");
  _test_rm_dups("ababab");
  _test_rm_dups("hello world");
}

//------------------------------------------------------------------------------

const string CHAPTER_01_QUESTION_04 =
  "Write a method to decide if two strings are anagrams or not.";

bool strings_are_anagrams(const string& a, const string& b) {
  string a_sorted = a;
  string b_sorted = b;
  std::sort(a_sorted.begin(), a_sorted.end());
  std::sort(b_sorted.begin(), b_sorted.end());
  return (a_sorted == b_sorted);
}

static void _test_anagrams(const string& a, const string& b) {
  cout << '"' << a << "\" and \"" << b << "\": ";
  cout << (strings_are_anagrams(a, b) ? "" : "NOT ") << "anagrams" << endl;
}

void test_chapter_01_question_04() {
  _test_anagrams("hello", "lleho");
  _test_anagrams("hello", "lleHo");
  _test_anagrams("san", "francisco");
}

//------------------------------------------------------------------------------

const string CHAPTER_01_QUESTION_05 =
  "Write a method to replace all spaces in a string with ‘%20’.";

void encode_spaces(string& str) {
  string buf;
  size_t num_spaces = 0;

  // Count all the spaces
  for(size_t i = 0; i < str.size(); ++i) {
    if(str[i] == ' ') {
      ++num_spaces;
    }
  }

  // Compute required size of new string
  size_t newsize = str.size() + (num_spaces * 2);

  // Construct the new string
  buf.resize(newsize);
  for(size_t i = 0, j = 0; i < str.size(); ++i) {
    if(str[i] == ' ') {
      buf[j++] = '%';
      buf[j++] = '2';
      buf[j++] = '0';
    }
    else {
      buf[j++] = str[i];
    }
  }

  // Set 'str' to the new value
  std::swap(str, buf);
}

static void _test_spaces(const char* str) {
  string encoded = str;
  encode_spaces(encoded);
  cout << "\"" << str << "\" --> \"" << encoded << "\"" << endl;
}

void test_chapter_01_question_05() {
  _test_spaces("hello");
  _test_spaces("hello there how are you");
}

//------------------------------------------------------------------------------

const string CHAPTER_01_QUESTION_06 =
  "Given an image represented by an NxN matrix, where each pixel in the image is 4\n"
  "bytes, write a method to rotate the image by 90 degrees. Can you do this in place?";

typedef vector<vector<uint32_t> > image_t;

struct Point {
  Point(size_t x, size_t y, const image_t& image)
  : x(x), y(y), value(image[x][y])
  { }
  size_t x, y;
  uint32_t value;
};

void rotate_image(image_t& image) {
  const size_t dim = image.size();
  for(size_t level = 0; level < (dim / 2); ++level) {
    for(size_t i = level; i < dim - 1 - level; ++i) {
      // Get four points to rotate
      Point p1(level,               i + level,            image);
      Point p2(i + level,           dim - 1 - level,      image);
      Point p3(dim - 1 - level,     dim - 1 - level - i,  image);
      Point p4(dim - 1 - level - i, level,                image);

      // Rotate the points by copying values
      image[p1.x][p1.y] = p4.value;
      image[p2.x][p2.y] = p1.value;
      image[p3.x][p3.y] = p2.value;
      image[p4.x][p4.y] = p3.value;
    }
  }
}

static void _init_image(image_t& image, size_t dim) {
  image.resize(dim);
  uint32_t val = 1;
  for(size_t i = 0; i < dim; ++i) {
    image[i].resize(dim, val++);
  }
}

static void _print_image(const image_t& image) {
  const size_t dim = image.size();
  for(size_t i = 0; i < dim; ++i) {
    for(size_t j = 0; j < dim; ++j) {
      cout << image[i][j] << ' ';
    }
    cout << endl;
  }
}

void test_chapter_01_question_06() {
  image_t image;
  size_t dim = 5;
  _init_image(image, dim);
  cout << "\nOriginal:\n";
  _print_image(image);
  rotate_image(image);
  cout << "\nRotated:\n";
  _print_image(image);
}

//------------------------------------------------------------------------------

const string CHAPTER_01_QUESTION_07 =
  "Write an algorithm such that if an element in an MxN matrix is 0, its entire\n"
  "row and column is set to 0.";


class Matrix {
public:
  // Constructors
  Matrix()                    { }
  explicit Matrix(size_t dim) { resize(dim, dim); }
  Matrix(size_t m, size_t n)  { resize(m, n); }

  // Sizes
  size_t m() const { return m_data.size(); }
  size_t n() const { return m_data.empty() ? 0 : m_data[0].size(); }

  // Access data
  // NOTE: this exposes the internals (vectors) which isn't great
  vector<uint32_t>&       operator[](size_t i)       { return m_data[i]; }
  const vector<uint32_t>& operator[](size_t i) const { return m_data[i]; }

  // Clear the matrix
  void clear() { m_data.clear(); }

  // Resize to M x N
  Matrix& resize(size_t m, size_t n) {
    m_data.resize(m);
    for(size_t i = 0; i < m; ++i) { m_data[i].resize(n); }
    return *this;
  }

  // Assign each element a random value in the range [0,max).
  void fill(uint32_t max = 100) {
    const size_t M = m();
    const size_t N = n();
    for(size_t i = 0; i < M; ++i) {
      for(size_t j = 0; j < N; ++j) {
        m_data[i][j] = rand() % max;
      }
    }
  }

  // For any zero value, extend it to all cells in the same row and column
  void extend_zeroes() {
    const size_t M = m();
    const size_t N = n();

    // Collect the set of rows  and columns to zero out
    unordered_set<size_t> rows;
    unordered_set<size_t> cols;

    for(size_t i = 0; i < M; ++i) {
      for(size_t j = 0; j < N; ++j) {
        if(m_data[i][j] == 0) {
          rows.insert(i);
          cols.insert(j);
        }
      }
    }

    // Zero out the rows and columns
    typedef unordered_set<size_t>::const_iterator set_iter;

    for(set_iter it = rows.begin(); it != rows.end(); ++it) {
      for(int col = 0; col < N; ++col) {
        m_data[*it][col] = 0;
      }
    }

    for(set_iter it = cols.begin(); it != cols.end(); ++it) {
      for(int row = 0; row < M; ++row) {
        m_data[row][*it] = 0;
      }
    }
  }

private:
  vector<vector<uint32_t> > m_data;
};

// Print a matrix to the stream
ostream& operator<<(ostream& out, const Matrix& matrix) {
  const size_t M = matrix.m();
  const size_t N = matrix.n();
  char buf[32] = {0};
  for(size_t i = 0; i < M; ++i) {
    for(size_t j = 0; j < N; ++j) {
      sprintf(buf, "%2d", matrix[i][j]);
      out << buf;
      if(j < N - 1) out << ' ';
    }
    if(i < M - 1) out << "\n";
  }
  return out;
}

void array_expand_zero(Matrix& matrix) {
  //TODO
}

void test_chapter_01_question_07() {
  seed_rand();
  Matrix matrix(6,12);

  matrix.fill(50);
  cout << "\nOriginal:\n" << matrix << endl;
  matrix.extend_zeroes();
  cout << "\nZeroed-out:\n" << matrix << endl;
}

//------------------------------------------------------------------------------

const string CHAPTER_01_QUESTION_08 =
  "Assume you have a method isSubstring which checks if one word is a substring of\n"
  "another. Given two strings, s1 and s2, write code to check if s2 is a rotation\n"
  "of s1 using only one call to isSubstring.\n"
  "(eg: “waterbottle” is a rotation of “erbottlewat”).";

bool is_substring(const string& str, const string& substr) {
  return str.find(substr) != string::npos;
}

bool strings_are_rotations(const string& s1, const string& s2) {
  // The trick is to append s1 to itself, so then s2 WILL be a substring of s1.
  // Also of course, s1 and s2 must be the same size.
  return s1.size() == s2.size() && is_substring(s1 + s1, s2);
}

static void _check_rotation(const string& s1, const string& s2) {
  cout << '"' << s1 << "\", \"" << s2 << "\": rotations? ";
  cout << (strings_are_rotations(s1, s2) ? "YES" : "NO") << endl;
}

void test_chapter_01_question_08() {
  _check_rotation("", "");
  _check_rotation("a", "a");
  _check_rotation("cycle", "ecycl");
  _check_rotation("blah", "blahblah");
}

//==============================================================================
// Chapter class for printing questions and solutions
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
