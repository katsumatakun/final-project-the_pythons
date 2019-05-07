#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "find_loc.h"
#include "cmp_extension.h"
#include "dir_ent.h"
#include "loadDirectory.h"

struct node_files {
  struct node_files* pre;
  struct node_files* nxt;
  char* pt;
};

typedef struct node_files *filePtr;

filePtr insert(char* file_name, filePtr head_ptr){

  filePtr new_node_p;
  filePtr front_node_p;
  filePtr behind_node_p;
  filePtr new_Head_p = head_ptr;

  //allocation failure will finish function execution with null return
  new_node_p = (nodePtr) malloc(sizeof(struct node_files));
  new_node_p->pt = file_name
  behind_node_p = head_ptr;
  front_node_p = NULL;

  //Finding insertion point
  while(behind_node_p != NULL && strcmp((behind_node_p->pt), (new_node_p->pt<0))){
    front_node_p = behind_node_p;
    behind_node_p = behind_node_p->nxt;
  }

 //insert very first of the linked list
 if (front_node_p == NULL){
    new_node_p->prev = NULL;
    new_node_p->next  = behind_node_p;
    new_Head_p = new_node_p;
    if(behind_node_p != NULL){
      behind_node_p -> prev = new_node_p;
    }
  }

  //insert between node pointed to by front_node_p and one pointed to by behind_node_p
  //(or very end if behind_node_p == NULL)
  else{
    front_node_p->next = new_node_p;
    new_node_p->prev = front_node_p;
    new_node_p->next = behind_node_p;
    if(behind_node_p != NULL){
      behind_node_p->prev = new_node_p;
    }
    return new_Head_p;
}


}

//return o if no wildcard return 1 if before, return 2 if after, return 3 if both
int wildcards(char* fname){
  int dot=0;
  int before=0
  int after = 0;

  for(int x=0; x<strlen(fname); x++){
    if(fname[x] == '*'){
      if(dot==0)
        before = 1;
      else
        after = 2;
    }
    if(fname[x] == '.' ){
      dot = 1;
    }
  }

    return before+after;

}

int find(char* st, char c){
  for(int i=0; i<strlen(st); i++){
    if(char[i] == c){
      return i;
    }
  }
  return -1;
}

int pre(char* st1, char* st2, int num){
  convertToUpperCase(st1);
  convertToUpperCase(st2);
  for(int i=0; i<num; i++){
    if(st1[i]!=st2[i])
      return 0;
  }
  return 1;
}

int post(char* st1, char* st2, int num){
  convertToUpperCase(st1);
  convertToUpperCase(st2);
  int len = strlen(st1);
  for(int i=st1-len; i<len; i++){
    if(st1[i]!=st2[i])
      return 0;
  }
  return 1;
}

void conc(char* st1, char* st2, char* new_str){
  int size1 = strlen(st1);
  int size2 = strlen(st2);

  int x = 0;
  int y;
  for(int i=0; i<size1; i++)
  {
    //printf("i = %d\n", i);
    if(st1[i]==' '){
      x = i;
      break;
    }
    new_str[i] = st1[i];
  }
  //printf("x = %d\n", x);
  if(x==0)
    x = size1;
  new_str[x] = '.';
  x++;

  for(y=0; y<size2; y++){
    if(st2[y]==' ')
      break;
    new_str[x+y] = st2[y];
  }
  new_str[x+y] = '\0';
  //printf("%s\n", new_str);
}

void convertToUpperCase(char *sPtr)
{
      for (int i=0; i< strlen(sPtr); i++)
        sPtr[i] = toupper(sPtr[i]);

}


/* The purpose of cpmdir is to read all of the directory entries and print them in the alphabetical order */

int main(int argc, char* argv[]) {

  if (argc<4) {
    printf("usage: program name, disk format, disk name, file name \n");
    return -1;
  }

  int num_files = argc-3;
  char* dname = argv[2];

  if(!contain(".dsk", dname) ){
    printf("The extension of the file must be .dsk\n");
    return -1;
  }

  FILE *fpr;
  if((fpr = fopen(dname, "rb")) == NULL ) {
    printf("Input file not open\n");
    return -1;
  }


  char opt;
  char opt_disk=' ';
  int opt_format=0;
  int num_128_per_block;
  int block_size;
  int num_alloc_per_ent;
  while((opt = getopt(argc, argv, "FH-:")) != -1){
    switch(opt){
    case 'F':
      opt_disk = 'F';
      num_128_per_block = 8;
      num_alloc_per_ent = 16;
      block_size = 1024;
      break;
    case 'H':
      opt_disk = 'H';
      num_128_per_block = 16;
      num_alloc_per_ent = 8;
      break;
    default:
      printf("usage: program name, disk format, disk name, file name \n");
      return -1;
    }
  }
  if(opt_disk==' '){
    printf("usage: program name, disk format, disk name, file name \n");
    return -1;
  }

  nodePtr p = loadDirectory(dname, opt_disk);
  nodePtr current = p;
  filePtr pf = NULL;
  char* files[5000];
  int length = 0;
  int actual_num_files=0;
  for(int i=0; i<num_files; i++){
    if(wildcard(argc[i+3])==0){
      pf = insert(argc[i+3], pf);
      actual_num_files++;
    }
    else if(wildcard(argc[i+3])==1){
      while(current != NULL){
        strcpy(copy_name, current->ptr->name);
        copy_name[8] = '\0';
        strcpy(copy_extension, current->ptr->extension);
        copy_extension[3] = '\0';
        conc(copy_name, copy_extension, current_file_name);
        int dot = find_loc(argc[i+3], '.');
        if(pre(current_file_name,argc[i+3], dot+1){
          pf = insert(argc[i+3], pf);
          actual_num_files++;
        }
        current=current->next;
      }
    }
    else if(wildcard(argc[i+3])==2){
      while(current != NULL){
        strcpy(copy_name, current->ptr->name);
        copy_name[8] = '\0';
        strcpy(copy_extension, current->ptr->extension);
        copy_extension[3] = '\0';
        conc(copy_name, copy_extension, current_file_name);
        int dot = find_loc(argc[i+3], '.');
        if(post(current_file_name,argc[i+3], dot+1){
          pf = insert(argc[i+3], pf);
          actual_num_files++;
        }
        current=current->next;
      }
    }
    else{
      while(current != NULL){
        pf = insert(argc[i+3], pf);
        current = current->next;
        actual_num_files++;
      }
    }
    current = p;
  }

  filePtr cur = pf;
  FILE* fpw;
  char* file_name;
  int file_loc = 3;
  char copy_name[9];
  char copy_extension[4];
  char current_file_name[12];
  int block_loc[num_128_per_block];
  char content[128];
  while(actual_num_files){
    file_name = argv[file_loc];
    if((fpw = fopen(file_name, "wb")) == NULL ) {
      printf("Output file not open\n");
      return -1;
    }

    printf(" before %s\n", file_name);
    convertToUpperCase(file_name);
    printf(" after %s\n", file_name);
    while(current!=NULL){
      strcpy(copy_name, current->ptr->name);
      copy_name[8] = '\0';
      strcpy(copy_extension, current->ptr->extension);
      copy_extension[3] = '\0';
      //printf("%s\n", copy_extension);
      conc(copy_name, copy_extension, current_file_name);
      //printf("%s\n", current_file_name);
      if(wildcard(file_name)==0){
      if(!strcmp(current_file_name, file_name)){
        int num128 = current->ptr->rc;
        for(int j=0; j<num_alloc_per_ent; j++){
          if(num128 >= num_128_per_block) //num_128_per_block == num 128 per blok
          {
            num128-= num_128_per_block;
            //printf("%d\n",current->ptr->blocks.floppy_block[j] );
            if(opt_disk == 'F'){
              find_loc(current->ptr->blocks.floppy_block[j], num_128_per_block, block_loc);
            }
            else{
              char ary[4];
              printf("%d\n",hextodec(ary) );
              find_loc_h(current->ptr->blocks.hard_block[j], num_128_per_block, block_loc);
            }
            printf("alloc  %d\n", block_loc[0]);
            for(int k=0; k<num_128_per_block; k++){
              if(block_loc[k]==0){
                break;
              }
              fseek(fpr, block_loc[k], SEEK_SET);
              fread(&content, 128, 1, fpr);
              printf("%s\n", content);
              fwrite(&content, 128, 1, fpw);
            }
          }
          else if(num128==0){
            break;
          }
          else{
            find_loc(current->ptr->blocks.floppy_block[j], num128, block_loc);
            break;
        }
      }
      current = current->next;
      }
    }
  }
  fclose(fpw);
  num_files--;
}
return 0;
}
