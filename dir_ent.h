#ifndef DIR_ENT
#define DIR_ENT

typedef struct directly_entry* entPtr;

struct directly_entry{
    unsigned char status;
    char name[8];
    char extension[3];
    unsigned char xl;
    unsigned char bc;
    unsigned char xh;
    unsigned char rc;
    unsigned int aloc1: 8;
    unsigned int aloc2: 8;
    unsigned int aloc3: 8;
    unsigned int aloc4: 8;
    unsigned int aloc5: 8;
    unsigned int aloc6: 8;
    unsigned int aloc7: 8;
    unsigned int aloc8: 8;
    unsigned int aloc9: 8;
    unsigned int aloc10: 8;
    unsigned int aloc11: 8;
    unsigned int aloc12: 8;
    unsigned int aloc13: 8;
    unsigned int aloc14: 8;
    unsigned int aloc15: 8;
    unsigned int aloc16: 8;
  };

#endif
