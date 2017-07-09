#include <iostream>
#include "ch_01_arrays_strings.h"
#include "ch_02_linked_lists.h"

int main(int argc, char** argv) {
  if(argc > 1) {
    int chapter = atoi(argv[1]);
    switch(chapter) {
      case 1: Chapter01().run(); break;
      case 2: Chapter02().run(); break;
      default: cout << "Unknown chapter '" << argv[1] << "'" << endl;
    }
  }
  else {
    Chapter01().run();
    Chapter02().run();
  }
}
