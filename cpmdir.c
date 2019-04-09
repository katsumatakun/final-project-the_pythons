#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmp_extension.h"
#include "dir_ent.h"
#include "node.h"
#include "insert.h"

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

  FILE *fpr;
  if((fpr = fopen(argv[2], "rb")) == NULL ) {
    printf("Input file not open\n");
    return -1;
  }

  int bootTracks, numEntries, skew, border, current, opt;
  while((opt = getopt(argc, argv, "FH-:")) != -1){
    switch(opt){
    case 'F':
      bootTracks = 128 * 26 * 2;
      numEntries = 64;
      skew = 6;
      border = 9984;
      break;
    case 'H':
      bootTracks = 0;
      numEntries = 1024;
      skew = 1;
      border = 32768; //maybe 16384
      break;
    default:
      printf("usage: program name, disk format, disk name \n");
      return -1;
      }
      break;
  }

  current = bootTracks;
  nodePtr head_ptr = NULL;

  entPtr q;
  q = (entPtr) malloc(sizeof(struct directly_entry));
  if(q == NULL){
    printf("No more memory space available \n");
    return -1;
  }

  fseek(fpr, bootTracks, SEEK_SET);
  int entry_size = sizeof(struct directly_entry);

  for(int i=0; i<numEntries/4; i++ ){

    for(int x=0; x<4; x++){
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
    current = current + 128*skew;
    if(current>=border){
      current = current-border+bootTracks;
      if(current == bootTracks){
        current = current+128;
      }
    }
    //printf("%x\n",current );
    fseek(fpr, current, SEEK_SET);
  }

  nodePtr p = head_ptr;
  while(p!=NULL){
    //229==e5
    if(p->ptr->status != 229 && p->ptr->xl == 0)
      printf("%s \n", p->ptr->name);
    p = p->next;
  }

  fclose(fpr);

  return 0;
}
