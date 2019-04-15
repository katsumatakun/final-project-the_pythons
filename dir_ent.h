#ifndef _DIR_ENT_
#define _DIR_ENT_

typedef struct directly_entry* entPtr;

struct floppy_alloc {
  unsigned short alloc_1:8;
  unsigned short alloc_2:8;
};

union alloc{
  struct floppy_alloc f_alloc;
  unsigned short h_alloc;
};

struct directly_entry{
    unsigned char status;
    char name[8];
    char extension[3];
    unsigned char xl;
    unsigned char bc;
    unsigned char xh;
    unsigned char rc;
    union alloc alc1;
    union alloc alc2;
    union alloc alc3;
    union alloc alc4;
    union alloc alc5;
    union alloc alc6;
    union alloc alc7;
    union alloc alc8;
  };

#endif
