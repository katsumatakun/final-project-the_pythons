#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmp_extension.h"
#include "dir_ent.h"
#include "loadDirectory.h"
#include "normal_print.h"
#include "formal_print.h"

/* The purpose of cpmdir is to read all of the directory entries and print them in the alphabetical order */

int main(int argc, char* argv[]) {

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


  char opt;
  char opt_disk=' ';
  int opt_format=0;
  while((opt = getopt(argc, argv, "lFH-:")) != -1){
    switch(opt){
    case 'F':
      opt_disk = 'F';
      break;
    case 'H':
      opt_disk = 'H';
      break;
    case 'l':
      opt_format = 1;
      break;
    default:
      printf("usage: program name, disk format, print format, disk name \n");
      return -1;
    }
  }

  nodePtr p = loadDirectory(fname, opt_disk);
  if(!opt_format){
    normal_print(p);
  }
  else{
    formal_print(p, opt_format);
  }

  return 0;
}
