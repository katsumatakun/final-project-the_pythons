#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "loadDirectory.h"
#include "dir_ent.h"


int main(int argc, char* argv[]){

    if(argc < 4){
      printf("usage: program name, disk format, disk name, file to be deleted \n");
      return -1;
    }

    FILE *fptr;
    if((fptr = fopen(argv[2],"rb+"))==NULL){   //rb+ Allows to read and write but if there is no file it will equal null
      printf("File cannot be opened \n");
      return -1;
    }
    char opt;
    if((opt = getopt(argc, argv, "FH-:")) == -1){
      printf("must flag with F or H to indicate floppy or hard disk");
      return -1;
    }
    int loop = argc-1;
    int trav_cnt=0;       //count the string length of the entry minus .extension
    int cnt[argc];        //hold the length of the input file minus the .extension
    int choice = 0;       //if =0,1 then multiple files can be input and deleted, if = 2 then that means *.extesion is inputed and special case is executed

    while (loop!=2) {                                           //used to convert all characters to uppercase
      trav_cnt = 0;
      for(int i=0;i<strlen(argv[loop]);i++){
        if(argv[loop][i] == 42&&trav_cnt<1){
          choice = 2;
          i++;
        }
        if(argv[loop][i]<91 && argv[loop][i]!=46){              //if char are lowercase converts to upper, but if the char is not equal to "."
          trav_cnt++;
        }
        else if(argv[loop][i]==46){                      //if the char =".", then it replaces it with a space
          cnt[loop+1] = trav_cnt-1;
          argv[loop][i] = 32;
          if(argv[loop][i+1] == 42){
            choice = 1;
          }
        }
        else if(argv[loop][i]>91) {
          argv[loop][i] =argv[loop][i]-32;
          trav_cnt++;

        }
      }
      loop--;
    }

    loop = argc-1;                                  //reset num entries
    int boot_tracks, num_entries, skew, rem_bytes;
    switch(opt){
      case 'F':                               //Floppy drive
        boot_tracks = 128 * 26 * 2;
        num_entries = 64;
        break;
      case 'H':                                 //hard drive
        boot_tracks = 0;
        num_entries = 1024;
        break;
      default:
        printf("usage: program name, disk format, disk name \n");
        return -1;
      }

      char *finames[256];                       //holds the the filename to be deleted
      nodePtr p = loadDirectory(argv[2],opt);
      int con = 0;                            //count for number of files to be deleted
      int co;
      if(choice == 2){
        while(p!=NULL){
          co=0;                             //used to increment the hold for the filenames that are = extension
          for(int d = 4;d!=1;d--){
            if(p->ptr->extension[d-2] == argv[3][d]){                   //When extension is the same as inputed
              co++;
            }
            if(co == 3){
              finames[con]= p->ptr->name;
              con++;
            }
          }
          p = p->next;
        }
      }

      fseek(fptr,boot_tracks,SEEK_SET);                                     //set the file to be read from the start of the directory entries
      entPtr q;
      q = (entPtr) malloc(sizeof(struct directory_entry));
      int entry_size = sizeof(struct directory_entry);
      int run_count=0;
      char write[0];
      write[0]=229;
      int a = 0;
      int run = 0;                                         //counter used to parse through the .dsk filename


      while(fread(q,entry_size,1,fptr)){                            //reads the file one line at a time
        if(choice<2){
          for(int j=(argc-1);j!=2;j--){
            if(q->status == 0 && q->name){
              a=0;
              run_count = 0;
              for(int l=0; l < strlen(argv[j])-1;l++){      //count for the length of the file to be removed.
                if(q->name[a] == argv[j][l]){             //reads the file and input one char at a time to see if =
                  run_count++;
                  a++;
                }
                if(q->name[a] == 32 && run_count>1&&choice!=1){         //if the filename is equal to the input, adds spaces to counter and sets next counter to the start of the extension
                  while(q->name[a] == 32){
                    a++;
                  }
                }
                if(run_count == strlen(argv[j])-2){         //if the whole filenaem is equal then writes the e5
                  fseek(fptr,-entry_size,SEEK_CUR);             //sets seek to begining of line to prime for write
                  fwrite(write,1,1,fptr);
                  fseek(fptr,-1,SEEK_CUR);                    //sets the seek -1 to compensate for replaced 00
                  run++;
                }
              }
            }
          }
        }
        else if(choice==2){                             //if the input is *.extensions
          if(q->status == 0){
            for(int j=con-1;j!=-1;j--){
              a=0;
              run_count = 0;
              for(int l=0; l < strlen(finames[j])-1;l++){      //counts for the length of the file to be removed.
                if(q->name[a] == finames[j][a]){
                  run_count++;
                  a++;
                }
                }
                if(run_count == strlen(finames[j])-1){
                  fseek(fptr,-entry_size,SEEK_CUR);
                  fwrite(write,1,1,fptr);
                  fseek(fptr,-1,SEEK_CUR);
                  run++;
                }
              }
            }
          }
        }
      fclose(fptr);
      if(run==0){
        printf("file was not found within file\n");
      }
    }
