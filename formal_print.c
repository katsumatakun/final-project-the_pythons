#include <stdio.h>
#include <string.h>
#include "dir_ent.h"
#include "node.h"
#include "formal_print.h"


/*
  It will print the name, size(bytes), and the number of record (128bytes each) of directory entries, i.e. "sdir"
*/

void formal_print(nodePtr p, char disk_type){

  printf("   Name      Bytes   Recs   Attributes     Name      Bytes   Recs   Attributes\n" );
  printf("------------ ------ ------ ------------ ------------ ------ ------ ------------\n" );
  int total_bytes =0;
  int total_recs =0;
  nodePtr current = p;
  int count=0;
  int entries_occupied=0;
  char copy_name[12];
  char copy_name_current[12];
  int one_block;
  int max_entry;
  if(disk_type = 'F'){
    one_block = 1024;
    max_entry = 64;
  }
  else{
    one_block = 2048;
    max_entry = 1024;
  }
  while(current!=NULL){
    if(current->ptr->xl == 0) /*if the entry isn't empty*/{
        strcpy(copy_name, current->ptr->name);
        copy_name[11] = '\0';
        printf("%12s ", copy_name);
        int recs= current->ptr->rc;
        int bytes= recs*128;
        current = current->next;
        strcpy(copy_name_current, current->ptr->name);
        copy_name_current[11] = '\0';
        while(current!=NULL && !(strcmp(copy_name, copy_name_current))){
          entries_occupied++;
          recs+= current->ptr->rc;
          bytes= recs*128;
          current = current->next;
          if(current!=NULL){
            strcpy(copy_name_current, current->ptr->name);
            copy_name_current[11] = '\0';
          }
        }
        int k = (bytes%one_block == 0)? (bytes/one_block) : (bytes/one_block+1);
        total_bytes+= k;
        total_recs+=recs;
        printf("%5dK %5d   Dir RW       ", k, recs);
        recs=0;
        bytes=0;
        count++;
        entries_occupied++;
        if(count % 2 == 0)
          printf("\n");
      }
  }
  printf("\n");
  printf(" Total Bytes = %8dK  Total Records = %8d Files Found = %5d\n", total_bytes, total_recs, count);
  printf(" Total %dK Block = %8d Used/Max Dir Entries for this disk = %4d/  %d\n",one_block/1000, total_bytes, entries_occupied, max_entry);
}
