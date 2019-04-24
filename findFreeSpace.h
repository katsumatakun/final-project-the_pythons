#include "node.h"

#define NUM_OF_BLOCKS 27
/* what is the number of blocks?*/

union AllocatedBlocks{
  int all;
  int[NUM_OF_BLOCKS] block:1;
}

AllocatedBlocks findFreeSpace(nodePtr);
/* takes an argument to give it the directory
  returns a union which represents the blocks, with a 1 indicating the block
  is allocated and a 0 indicating it is free
  */
