#ifndef _FIND_LOC_
#define _FIND_LOC_

const int log_phy[27]={0, 1, 7, 13, 19, 25, 5, 11, 17, 23, 3, 9, 15, 21, 2, 8, 14, 20, 26, 6, 12, 18, 24, 4, 10, 16, 22};
int start_sector(int);
int* start_alloc(int);
int* findloc(int, int);


#endif
