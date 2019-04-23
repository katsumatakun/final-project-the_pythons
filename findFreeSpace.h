#include "node.h"

const int NUM_OF_BLOCKS = ;

union AllocatedBlocks{
  int all;
  int[NUM_OF_BLOCKS] block:1;
}

AllocatedBlocks findFreeSpace(nodePtr);
