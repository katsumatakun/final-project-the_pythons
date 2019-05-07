#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for getopt
#include "disk.h"
#include "findFreeSpace.h"
#include "loadDirectory.h"
#include "cmp_extension.h"
#include "copy_from_disks.h"


int main(int argc, char* argv[]){

  int num_of_blocks[2] = {244, 2040};
  /* 77 - 2 * 26 / 8  for floppy*/
  /* 255 * 128 / 16  for hard drive */
  /* number of tracks * sectors per tract / sectors per block */

  int blocks_per_dir[2] = {8,16};


  if (argc < 5) {
    printf("usage: program name, disk format, function format, disk name, filename \n");
    return -1;
  }
  char* fname = argv[3];
  if(!contain(".dsk", fname) ){
    printf("The extension of the file must be .dsk\n");
    return -1;
  }
  char format=' ';

  char opt = getopt(argc, argv, "FHpd-:");
    switch(opt){
    case 'F':
      disk_type = FLOPPY;
      break;
    case 'H':
      disk_type = HARD;
      break;
    case 'p': //from pc to disk
      format = 'p';
      break;
    case 'd': //from disk to pc
      format = 'd';
      break;
    default:
      printf("usage: program name, disk format, function format, disk name, file name \n");
      return -1;
    }
  if(format == 'd'){
    copy_from_disks( argc, argv);
  }
  else{
  nodePtr head = loadDirectory(fname, opt);

  int* allocated_blocks = findFreeSpace(head);
}

  return 0;
}
