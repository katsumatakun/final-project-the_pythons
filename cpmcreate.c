#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmp_extension.h"


int main(int argc, char* argv[]) {

  if (argc != 3) {
    printf("usage: program name, disk format, disk name \n");
    return -1;
  }

  if(!contain(".dsk", argv[2])){
    printf("The extension of the file must be .dsk\n");
    return -1;
  }

  FILE *fpw;
  if((fpw = fopen(argv[2], "wb")) == NULL ) {
    printf("Output file not open\n");
    return -1;
  }
  int flag = 0;
  int total_bytes, opt; //byte per sec * sec per track * tracks
  while((opt = getopt(argc, argv, "FH-:")) != -1){
    switch(opt){
    case 'F':
      total_bytes = 128 * 26 * 77;
      break;
    case 'H':
      total_bytes = 128 * 128 * 255;
      break;
    default:
      //total_bytes = 128 * 26 * 77;
      printf("usage: program name, disk format, disk name \n");
      return -1;
      }
      break;
  }

  unsigned char* E5s = (unsigned char*)malloc(total_bytes);
  for(int i=0; i<total_bytes; i++)
    E5s[i] = 0xE5;
  fwrite(E5s, total_bytes, 1, fpw);
  fclose(fpw);

  return 0;
}
