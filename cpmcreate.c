#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmp_extension.h"

/* The purpose of cpmcreate is to make a file filled with all E5, the size of files are different between floppy and HD, it tke flag taking */

int main(int argc, char* argv[]) {

  if (argc != 3) {
    printf("usage: program name, disk format, disk name \n");
    return -1;
  }

  for(int d=0;d<strlen(argv[2])-3;d++){
    if(argv[2][d] == 46){
      if(argv[2][d+1] == 68 || argv[2][d+1] == 100){
        if(argv[2][d+2] == 83 || argv[2][d+2] == 115){
          if(argv[2][d+3] == 75 || argv[2][d+3] == 107){
            break;
          }
          else{
            printf("The extension of the file must be .dsk\n");
            return -1;
          }
        }
        else{
          printf("The extension of the file must be .dsk\n");
          return -1;
        }
      }
      else{
        printf("The extension of the file must be .dsk\n");
        return -1;
      }
    }
  }

  FILE *fpw;
  if((fpw = fopen(argv[2], "wb")) == NULL ) {
    printf("Output file not open\n");
    return -1;
  }

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
