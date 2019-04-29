#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
    char buff[12];
    int total_files = 0;
    int loop = argc-1;                   //Converts the filename to all uppercase
    int len = strlen(argv[loop]);
    int trav_cnt=0;
    int cnt[1];

    while (loop!=2) {
      trav_cnt = 0;
      for(int i=0;i<len;i++){
        if(argv[loop][i]<=91 && argv[loop][i]!=46){
          //printf("%c .\n",argv[loop][i]);
          trav_cnt++;
        }
        else if (argv[loop][i]==46){
          cnt[1] = trav_cnt-1;
          argv[loop][i]= 32;
          //printf("%c .+\n",argv[loop][i]);

        }
        else if(argv[loop][i]>91) {
          argv[loop][i] =argv[loop][i]-32;
          //printf("%c .\n",argv[loop][i]);
          trav_cnt++;
        }
      }
      loop--;
      total_files++;
    }
    loop = argc-1;

    //printf("\n%s}\n",argv[3]);

    int boot_tracks, num_entries, skew, rem_bytes;
    char opt;

    if((opt = getopt(argc, argv, "FH-:")) == -1){
      printf("must flag with F or H to indicate floppy or hard disk");
      return -1;
    }


    switch(opt){
      case 'F':
        boot_tracks = 128 * 26 * 2; // should bootTracks be just tracks? A floppy disk only has two boot tracks
        num_entries = 64;
        rem_bytes = 128 * 26 * 75;
        skew = 6;
        //border = 9984;
        printf("Floppy \n");
        break;
      case 'H':
        boot_tracks = 0; //should bootTracks be just tracks? A floppy disk only has two boot tracks
        num_entries = 1024;
        rem_bytes = 128 * 128 * 255;
        skew = 1;
        //border = 32768;
        break;
      default:
        printf("usage: program name, disk format, disk name \n");
        return -1;
      }


      fseek(fptr,boot_tracks,SEEK_SET);
      entPtr q;
      q = (entPtr) malloc(sizeof(struct directly_entry));
      int entry_size = sizeof(struct directly_entry);
      //printf("%i ::::::\n",entry_size );

      int run_count=0;
      char write[0];
      write[0]=229;
      int k = sizeof(write[0]);
      //printf("%i \n", k);
      while(fread(q,entry_size,1,fptr)){
        for(int j=loop;j!=2;j--){
          if(q->status == 0){
            for(int l=0; l < 6 ;l++){
              if(q->name[l] == argv[j][l])
              {
                run_count++;
              }
              else{
                break;
              }
              if(run_count == strlen(argv[j])){
                fseek(fptr,-entry_size,SEEK_CUR);
                printf("%d \n",q->status);
                printf("%s :\n",q->name);
                fwrite(write,1,1,fptr);
                fseek(fptr,-1,SEEK_CUR);
                fread(q,entry_size,1,fptr);
                printf("%d \n",q->status);
                printf("%s :\n",q->name);
                run_count = 0;
              }
            }
          }
        }
      }

      fclose(fptr);
    }
