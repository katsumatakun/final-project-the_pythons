#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for getopt
#include "disk.h"
#include "findFreeSpace.h"
#include "loadDirectory.h"
#include "cmp_extension.h"


int main(int argc, char* argv[]){
  
  const int num_of_blocks[2] = {244, 2040};
  /* 77 - 2 * 26 / 8  for floppy*/
  /* 255 * 128 / 16  for hard drive */
  /* number of tracks * sectors per tract / sectors per block */

  const int blocks_per_dir[2] = {8,16};



  if (argc != 4 && argc != 3) {
    printf("usage: program name, disk format, print format, disk name \n");
    return -1;
  }
  char* fname;
  if(argc == 3)
    fname = argv[2];
  else
    fname = argv[3];

  if(!contain(".dsk", fname) ){
    printf("The extension of the file must be .dsk\n");
    return -1;
  }

  char opt = getopt(argc, argv, "FH-:");
    switch(opt){
    case 'F':
      disk_type = FLOPPY;
      break;
    case 'H':
      disk_type = HARD;
      break;
    default:
      printf("usage: program name, disk format, print format, disk name \n");
      return -1;
    }

  nodePtr head = loadDirectory(fname, opt);

  int* allocated_blocks = findFreeSpace(head);

  for(int i = 0; i < num_of_blocks[disk_type]; i++){
    printf("%d", allocated_blocks[i]);
  }

  return 0;
}
