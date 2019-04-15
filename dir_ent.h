#ifndef _DIR_ENT_
#define _DIR_ENT_

typedef struct directory_entry* entPtr;

struct floppy_alloc {
  unsigned short alloc_1:8;
  unsigned short alloc_2:8;
};

union alloc_block{
  struct floppy_alloc f_alloc;
  unsigned short h_alloc;
};

struct directory_entry{
    unsigned char status;
    char name[8];
    char extension[3];
    unsigned char xl;
    unsigned char bc;
    unsigned char xh;
    unsigned char rc;
    union block_alloc alc1;
    union block_alloc alc2;
    union block_alloc alc3;
    union block_alloc alc4;
    union block_alloc alc5;
    union block_alloc alc6;
    union block_alloc alc7;
    union block_alloc alc8;
  };

#endif
