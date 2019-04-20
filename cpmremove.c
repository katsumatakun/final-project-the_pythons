#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "string.h"
#include "loadDirectory.h"
#include "dir_ent.h"


int main(int argc, char* argv[]){

    if(argc < 4){
      printf("usage: program name, disk format, File to be deleted, disk name \n");
      return -1;
    }

    FILE *fptr;
    if((fptr = fopen(argv[2],"rb+"))==NULL){  //rb+ Allows to read and write but if there is no file it will equal null
      printf("File cannot be opened");
      return -1;
    }
    int total_files = 0;
    int loop = argc-1;                   //Converts the filename to all uppercase
    int len = strlen(argv[loop]);
    while (loop!=2) {
      for(int i=0;i<len;i++){
        if(argv[loop][i]<=91){
          printf("%c \n",argv[loop][i]);
        }
        else if(argv[loop][i]!= 46){
          argv[loop][i]=argv[loop][i]-32;
          printf("%c \n",argv[loop][i]);
        }
      }
      loop--;
      int len=strlen(argv[loop]);
      total_files++;
    }
    printf("%s \n", argv[3]);


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
      entPtr q;
      q = (entPtr) malloc(sizeof(struct directly_entry));
      int entry_size = sizeof(struct directly_entry);
      int x=1;
      while(total_files!=0){
        while(fread(q, entry_size,1,fptr)){
        if(q->status == 0){
          printf("%s \n",q->name);
        }
      }
    }

    }

/*
      nodePtr head_ptr = NULL;
      entPtr q;
      q = (entPtr) malloc(sizeof(struct directly_entry));
      fseek(fptr,boot_tracks,SEEK_SET);
      int entry_size = sizeof(struct directly_entry);

      for(int x=0; x<4; x++){
        fread(q, entry_size, 1, fptr);
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
        current = current-border+boot_tracks;
        if(current == boot_tracks){
          current = current+128;
        }
      }
      printf("%x\n",current );
      fseek(fptr, current, SEEK_SET);
    }*/
