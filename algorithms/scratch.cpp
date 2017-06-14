#include <iostream>
#include <vector>

using namespace std;


void how_to_collect_runtime() {
  // ...

  auto start_time = std::chrono::high_resolution_clock::now();
  bubble_sort(items);
  auto end_time = std::chrono::high_resolution_clock::now();

  // Figure out that whole time thing
  auto duration = end_time - start_time;
  std::chrono::nanoseconds nanosec(duration);
  //double millisec = nanosec.count() / 1000000.0;

  // Check array, print run time
  cout << "Sort status: " << (Utils::array_is_sorted(items) ? "ok" : "fail") << endl;
  cout << "Run time: " << nanosec.count() << " ns" << endl;
}



/*
Bubble Sort
- sorting, array size: 10,   status: ok,   time: 2345 ms
- sorting, array size: 100,  status: fail, time: 2345 ms
- sorting, array size: 1000, status: ok,   time: 2345 ms
*/
