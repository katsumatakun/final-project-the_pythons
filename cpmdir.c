#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmp_extension.h"
#include "dir_ent.h"
#include "node.h"
#include "insert.h"


int main(int argc, char* argv[]) {

  if (argc != 3) {
    printf("usage: program name, disk format, disk name \n");
    return -1;
  }

  if(!contain(".dsk", argv[2])){
    printf("The extension of the file must be .dsk\n");
    return -1;
  }

  FILE *fpr;
  if((fpr = fopen(argv[2], "rb")) == NULL ) {
    printf("Input file not open\n");
    return -1;
  }

  int bootTracks, numEntries, opt;
  while((opt = getopt(argc, argv, "FH-:")) != -1){
    switch(opt){
    case 'F':
      bootTracks = 128 * 26 * 2;
      numEntries = 64;
      break;
    case 'H':
      bootTracks = 0;
      numEntries = 1024;
      break;
    default:
      printf("usage: program name, disk format, disk name \n");
      return -1;
      }
      break;
  }

  nodePtr head_ptr = NULL;

  entPtr q;
  q = (entPtr) malloc(sizeof(struct directly_entry));
  if(q == NULL){
    printf("No more memory space available \n");
    return -1;
  }

  fseek(fpr, bootTracks, SEEK_SET);
  int entry_size = sizeof(struct directly_entry);
  for(int i=0; i<numEntries; i++ ){
    fread(q, entry_size, 1, fpr);
    head_ptr = insertData(head_ptr, q);
    if(head_ptr == NULL){
      printf("No more memory space available \n");
      return -1;
    }

    q = (entPtr) malloc(sizeof(struct directly_entry));
    if(q == NULL){
      printf("No more memory space available \n");
      return -1;
    }
  }

  nodePtr current = head_ptr;
  while(current!=NULL){
    //printf("%d ",current->ptr->xl);
    if(current->ptr->xl == 0)
      printf("%s \n", current->ptr->name);
      // printf("%s %s\n",current->ptr->name, current->ptr->extension );
    current = current->next;
  }
  //printf("%lu\n", sizeof(struct directly_entry));


  fclose(fpr);

  return 0;
}
