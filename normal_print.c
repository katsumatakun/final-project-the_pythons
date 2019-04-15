#include <stdio.h>
#include "dir_ent.h"
#include "node.h"
#include "normal_print.h"

void normal_print(nodePtr p){

  nodePtr current = p;
  int count=0;
  while(current!=NULL){
    if(current->ptr->status != 229 && current->ptr->xl == 0) /*if the entry isn't empty*/
      {
        printf(": %10s ", current->ptr->name);
        count++;
        if(count % 4 == 0)
          printf("\n");
      }
    current = current->next;
  }

}
