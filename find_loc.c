#include <stdlib.h>
#include <stdio.h>
#include "find_loc.h"

const int log_phy[27]={0, 1, 7, 13, 19, 25, 5, 11, 17, 23, 3, 9, 15, 21, 2, 8, 14, 20, 26, 6, 12, 18, 24, 4, 10, 16, 22};


//It will return the starting place of the sector input;
int start_sector(int track_num){ return 128*26*track_num; }


//It will return array of int containing the starting place of allocation input;
void start_alloc(int alloc_num, int* ary){
  int sector=1; int track=2;
  for(int i=0; i<alloc_num; i++)
    { sector=sector+8;
      if(sector>26)
      { track++;
        sector = sector % 26; }
    }
  ary[0]= sector; ary[1]= track;

}

//It will return actual locations of allocation input
void find_loc(int num_alloc, int num_data, int* ary1){
  int ary[2];
  start_alloc(num_alloc, ary);
  int num=0;
  for(int i=0; i<num_data; i++)
  { num = start_sector(ary[1]) + 128 *(log_phy[ary[0]]-1);
     ary[0]++;
     if(ary[0] > 26)
     { ary[0] = ary[0] % 26;
       ary[1]++;
     }
       ary1[i] = num;
  }
  for(int x=num_data; x<8; x++)
    ary1[x] = 0;
}

//It will return actual locations of allocation input
void find_loc_h(int num_alloc, int num_data, int* ary1){
  int start_loc = num_alloc*2048;
  printf("start %d\n", start_loc);
  for(int i=0; i<num_data; i++){
    ary1[i] = start_loc;
    start_loc+=128;
  }
  for(int x=num_data; x<16; x++){
    ary1[x] = 0;
  }

}
