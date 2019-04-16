#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmp_extension.h"
#include "node.h"



int main(int argc, char* argv[]){

    if(argc != 4){
      printf("usage: program name, disk format, File to be deleted, disk name \n");
      return -1;
    }

    if(!contain(".dsk", argv[3])){
      printf("The extension of the file must be .dsk\n");
      return -1;
    }

    FILE *fptr;
    if((fptr = fopen(argv[3],"rb+"))==NULL){  //rb+ Allows to read and write but if there is no file it will equal null
      printf("File cannot be opened");
      return -1;
    }

    int boot_tracks, num_entries, skew, border, current;
    char opt;

    if((opt = getopt(argc, argv, "FH-:")) == -1){
      printf("must flag with F or H to indicate floppy or hard disk");
      return -1;
    }

    switch(opt){
      case 'F':
        boot_tracks = 128 * 26 * 2; /* should bootTracks be just tracks? A floppy disk only has two boot tracks */
        num_entries = 64;
        skew = 6;
        printf("Floppy \n");
        break;
      case 'H':
        boot_tracks = 0; /* should bootTracks be just tracks? A floppy disk only has two boot tracks */
        num_entries = 1024;
        skew = 1;
        break;
      default:
        printf("usage: program name, disk format, disk name \n");
        return -1;
      }

      fseek(fptr,boot_tracks,SEEK_SET);
      for(int i = 0; i<15;i++){

      }


}
