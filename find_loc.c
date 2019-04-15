#include <stdlib.h>
#include "find_loc.h"

//It will return the starting place of the sector input;
int start_sector(int track_num){ return 128*26*track_num; }


//It will return array of int containing the starting place of allocation input;
int* start_alloc(int alloc_num){
  int sector=1; int track=2;
  for(int i=0; i<alloc_num; i++)
    { sector=sector+8;
      if(sector>26)
      { track++;
        sector = sector % 26; }
    }
  int* ary= (int*)malloc(sizeof(int)*2); ary[0]= sector; ary[1]= track;
  return ary;
}

//It will return actual locations of allocation input
int* findloc(int num_alloc, int num_data){
  int* ary = start_alloc(num_alloc);
  int ary1[8];
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


  return ary1;

}
