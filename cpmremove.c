#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmp_extension.h"


int main(int argc, char* argv[]){

    if(argc != 3){
      printf("usage: program name, disk format, disk name \n");
      return -1;
    }

    if(!contain(".dsk", argv[2])){
      printf("The extension of the file must be .dsk\n");
      return -1;
    }
    FILE *fptr;

    if((fptr = fopen(argv[2],"rb+"))==NULL){  //rb+ Allows to read and write but if there is no file it will equal null
      printf("File cannot be opened");
      return -1;
    }

}
