#include <stdio.h>
#include "findFreeSpace.h"
#include "loadDirectory.h"

int main(int argc, char* argv[]){
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

  while((opt = getopt(argc, argv, "FH-:")) != -1){
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

  nodePtr head = loadDirectory(fname, disk_type);

  int* allocated_blocks = findFreeSpace(head);

  for(int i = 0; i < num_of_blocks[disk_type]; i++){
    printf("%d", allocated_blocks[i]);
  }


}
