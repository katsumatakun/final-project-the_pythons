#ifndef NODE
#define NODE

#include "dir_ent.h"

struct node {
  struct node* prev;
  struct node* next;
  struct directly_entry* ptr;
};
typedef struct node *nodePtr;

/* node function headers */

nodePtr insertData(nodePtr, entPtr);
/*
  This function will accept the head pointer pointing to
  the first node of the linked list
  and a pointer to entPtr that points to a directly entry.
  Then the entry being pointed by q is going to be stored in a new node
  of the linked List so that the list can have file names in decending
  alphabetical order.
  Finally return the pointer to the new head node after sorting.
*/

#endif
