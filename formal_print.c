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

  nodePtr current = p;
  if(disk_type = 'F'){
  int count=0;
  char copy_name[12];
  char copy_name_current[12];
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
          int recs= current->ptr->rc;
          int bytes= recs*128;
          current = current->next;
          if(current!=NULL){
            strcpy(copy_name_current, current->ptr->name);
            copy_name_current[11] = '\0';
          }
        }
        printf("%5dK %5d               ", bytes/1000+1, recs);
        recs=0;
        bytes=0;
        count++;
        if(count % 2 == 0)
          printf("\n");
      }
  }
}

}
