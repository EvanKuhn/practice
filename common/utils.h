#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace Utils {

// Fill a vector with `size` random integer values between `minval` and `maxval`
void fill_vector_randomly(vector<int>& v, int minval, int maxval, size_t size) {
  int range = maxval - minval;
  v.resize(size);
  for(size_t i = 0; i < size; ++i) {
    v[i] = (rand() % range) + minval;
  }
}

// Print a vector of values, comma-separated, in one line. No newline printed.
template <typename T>
void print_vector_horizontal(const vector<T>& v) {
  for(size_t i = 0; i < v.size(); ++i) {
    cout << v[i];
    if(i < v.size() - 1) {
      cout << ", ";
    }
  }
}

// Print a vector of values, one per line
template <typename T>
void print_vector_vertical(const vector<T>& v) {
  for(size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << endl;
  }
}

// Return a boolean indicating if the array is sorted in increasing order
template <typename T>
bool array_is_sorted(const vector<T>& v)
{
  for(size_t i = 1; i < v.size(); ++i) {
    if(v[i-1] > v[i]) {
      return false;
    }
  }
  return true;
}

} // namespace Utils

// Print an array to an output stream
template <typename T>
inline ostream& operator<<(ostream& out, const vector<T>& values) {
  const size_t size = values.size();
  for(size_t i = 0; i < size; i++) {
    out << values[i];
    if(i < size - 1) out << " ";
  }
  return out;
}
