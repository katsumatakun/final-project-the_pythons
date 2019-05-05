#ifndef DISK
#define DISK

#define FLOPPY 0
#define HARD 1

extern int disk_type;


int[2] num_of_blocks = {77 * 26 / 8, };
/* 77 * 26 / 8  for floppy*/
/* number of tracks - boot tracks * sectors per tract / sectors per block */




#endif
