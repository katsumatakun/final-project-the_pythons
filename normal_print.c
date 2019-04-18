#include <stdio.h>
#include <string.h>
#include "dir_ent.h"
#include "node.h"
#include "normal_print.h"

/*
  It will just print the name of directory entries, i.e. "dir"
*/

void normal_print(nodePtr p){

  nodePtr current = p;
  int count=0;
  while(current!=NULL){
    if(current->ptr->xl == 0) /*if the entry isn't empty*/
      {
        char copy_name[12];
        strcpy(copy_name, current->ptr->name);
        copy_name[11];
        printf(": %10s ", copy_name);
        count++;
        if(count % 4 == 0)
          printf("\n");
      }
    current = current->next;
  }

}
