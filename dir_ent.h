#ifndef _DIR_ENT_
#define _DIR_ENT_

typedef struct directory_entry* entPtr;

union block_alloc{
  unsigned short hard_block[8];
  unsigned char floppy_block[16];
};

struct directory_entry{
    unsigned char status;
    char name[8];
    char extension[3];
    unsigned char xl;
    unsigned char bc;
    unsigned char xh;
    unsigned char rc;
    union block_alloc blocks;
  };

#endif
