#include <iostream>
#include "ch_01_arrays_strings.h"
#include "ch_02_linked_lists.h"
#include "ch_03_stacks_queues.h"
#include "ch_04_trees_graphs.h"

//==============================================================================
// Chapters
//==============================================================================

Chapter CHAPTERS[] = {
  g_chapter_01,
  g_chapter_02,
  g_chapter_03,
  g_chapter_04,
};

const size_t NUM_CHAPTERS = array_length(CHAPTERS);

//==============================================================================
// Main
//==============================================================================

int main(int argc, char** argv) {
  seed_rand();

  // Run a particular chapter
  if(argc > 1) {
    int chapter = atoi(argv[1]);
    if(chapter < 1 || chapter > NUM_CHAPTERS) {
      cerr << "Unknown chapter '" << argv[1] << "'" << endl;
      return 1;
    }
    CHAPTERS[chapter-1].run();
  }
  // Run all chapters
  else {
    for(size_t i = 0; i < NUM_CHAPTERS; ++i) {
      CHAPTERS[i].run();
    }
  }
}
