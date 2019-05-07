#include "disk.h"

num_of_blocks[2] = {75 * 26 / 8, 255 * 128 / 16};
/* 77 - 2 * 26 / 8  for floppy*/
/* 255 * 128 / 16  for hard drive */
/* number of tracks * sectors per tract / sectors per block */

int blocks_per_dir[2] = {8,16};
