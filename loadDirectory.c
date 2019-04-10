#include "loadDirectory.h"
#include <stdio.h>
#include <stdlib.h>

nodePtr loadDirectory(char* filePath, char opt){
  FILE *fpr;
  if((fpr = fopen(filePath, "rb")) == NULL ) {
    printf("Input file not open\n");
    return NULL;
  }

  int bootTracks, numEntries, skew, border, current;

    switch(opt){
    case 'F':
      bootTracks = 128 * 26 * 2; /* should bootTracks be just tracks? A floppy disk only has two boot tracks */
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
      return NULL;
      }


  current = bootTracks;
  nodePtr head_ptr = NULL;

  entPtr q;
  q = (entPtr) malloc(sizeof(struct directly_entry));
  if(q == NULL){
    printf("No more memory space available \n");
    return NULL;
  }

  fseek(fpr, bootTracks, SEEK_SET);
  int entry_size = sizeof(struct directly_entry);

  for(int i=0; i<numEntries/4; i++ ){

    for(int x=0; x<4; x++){
      fread(q, entry_size, 1, fpr);
      head_ptr = insertData(head_ptr, q);
      if(head_ptr == NULL){
        printf("No more memory space available \n");
        return NULL;
      }
      q = (entPtr) malloc(sizeof(struct directly_entry));
      if(q == NULL){
        printf("No more memory space available \n");
        return NULL;
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
  fclose(fpr);
  return head_ptr;
}
