#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "dir_ent.h"

/*
  This function will accept the head pointer pointing to
  the first node of the linked list
  and a pointer to entPtr that points to a directly entry.
  Then the entry being pointed by q is going to be stored in a new node
  of the linked List so that the list can have file names in decending
  alphabetical order.
  Finally return the pointer to the new head node after sorting.
*/

nodePtr insertData(nodePtr head_ptr, entPtr q){
  nodePtr new_node_p;
  nodePtr front_node_p;
  nodePtr behind_node_p;
  nodePtr new_Head_p = head_ptr;

  //allocation failure will finish function execution with null return
  new_node_p = (nodePtr) malloc(sizeof(struct node));
  if(new_node_p == NULL){
    new_Head_p = NULL;
    return new_Head_p;
  }

  new_node_p->ptr = q;
  behind_node_p = head_ptr;
  front_node_p = NULL;

  //Finding insertion point
  while(behind_node_p != NULL && strcmp((behind_node_p->ptr)->name, (new_node_p->ptr)->name)<0){
    front_node_p = behind_node_p;
    behind_node_p = behind_node_p->next;
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
}

  return new_Head_p;
}
