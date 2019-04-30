#include "node.h"

#define NUM_OF_BLOCKS (77 * 26 / 8)
/* 77 * 26 / 8 */
/* number of tracks * sectors per tract / sectors per block */

union AllocatedBlocks{
  int all;
  int[NUM_OF_BLOCKS] block:1;
}

AllocatedBlocks findFreeSpace(nodePtr);
/* takes an argument to give it the directory
  returns a union which represents the blocks, with a 1 indicating the block
  is allocated and a 0 indicating it is free
  */
