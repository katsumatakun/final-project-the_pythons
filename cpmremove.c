#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "loadDirectory.h"
#include "dir_ent.h"

void slice_str(const char * str, char * buffer, size_t start, size_t end)
{
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

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
    int cnt[1];
    int trav_cnt=0;

    while (loop!=2) {
      trav_cnt = 0;
      for(int i=0;i<len;i++){
        if(argv[loop][i]<=91 && argv[loop][i]!=46){
          printf("%c .\n",argv[loop][i]);
          trav_cnt++;
        }
        else if (argv[loop][i]==46){
          cnt[1] = trav_cnt-1;
          argv[loop][i]= 32;
          printf("%c .+\n",argv[loop][i]);
          ///argv[loop][i]= 32;
        }
        else if(argv[loop][i]>91) {
          argv[loop][i] =argv[loop][i]-32;
          printf("%c .\n",argv[loop][i]);
          trav_cnt++;
        }
      }
      //argv[loop] = buff;
      loop--;
      total_files++;
    }
    loop = argc-1;
    //slice_str(argv[loop],argv[loop],0,cnt[loop]);
    printf("%i \n", cnt[loop-2]);
    printf("\n%s}\n",argv[3]);

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
        printf("Floppy \n");
        break;
      case 'H':
        boot_tracks = 0; //should bootTracks be just tracks? A floppy disk only has two boot tracks
        num_entries = 1024;
        rem_bytes = 128 * 128 * 255;
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
      int x=120;

      loop = argc-1;
      int dir_count = 0;
      nodePtr p = loadDirectory(argv[2],opt);
      while(p!=NULL){
        //229==e5
        //printf("%s   : ", p->ptr->name);
        //printf("%d \n", p->ptr->status);
        if(p->ptr->status != 229 && p->ptr->xl == 0){ //if the entry isn't empty
          if(p->ptr->status == 0){
            dir_count++;
          }
        }
        p = p->next;
      }
      //printf("%i \n", dir_count);
      //  printf("%s \n", p->ptr->name)
      dir_count = 0;
      int run_count=0;
      while(total_files!=0){
        while(x!=0){
          fread(q, entry_size,1,fptr);
          dir_count++;
          //printf("%s:",q->name);
          if(q->status == 0){
            for(int l=0; l < 3 ;l++){
              if(q->name[l] == argv[loop][l])
              {
                run_count++;
                printf("%li \n",strlen(argv[loop])-5);
              }
              if(run_count == strlen(argv[loop])-5){
                printf("%s :",q->name);
                entry_size = entry_size+(sizeof(struct directly_entry)*run_count);
                fseek(fptr,entry_size,SEEK_SET);
                q->status = 255;
                //fwrite(q,)
                printf("%d \n",q->status);
              }
            }
            run_count = 0;
            //printf("%s :",q->name)
          }
            //printf("%d ,",q->xl);
            //printf("%d ,",q->bc);
            //printf("%d \n",q->rc);
            x--;
          }
          total_files--;
        }
      //printf("%i \n",dir_count);
    }
