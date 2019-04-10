#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmp_extension.h"
#include "dir_ent.h"
#include "node.h"
#include "insert.h"
#include "loadDirectory.h"

/* The purpose of cpmdir is to read all of the directory entries and print them in the alphabetical order */

int main(int argc, char* argv[]) {

  if (argc != 3) {
    printf("usage: program name, disk format, disk name \n");
    return -1;
  }

  if(!contain(".dsk", argv[2])){
    printf("The extension of the file must be .dsk\n");
    return -1;
  }

  char opt;
  if((opt = getopt(argc, argv, "FH-:")) == -1){
    printf("must flag with F or H to indicate floppy or hard disk");
    return -1;
  }


  nodePtr p = loadDirectory(argv[2], opt);
  while(p!=NULL){
    //229==e5
    if(p->ptr->status != 229 && p->ptr->xl == 0) /*if the entry isn't empty*/
      printf("%s \n", p->ptr->name);
    p = p->next;
  }

  return 0;
}
