#include "findFreeSpace.h"
#include "disk.h"

int* findFreeSpace(nodePtr head){
  int* all_blocks = malloc(); //allocate space for the array representing the blocks
  for(int i = 0; i < num_of_blocks; i++){
    /* initialize all blocks to empty */
    all_blocks[i] = 0;
  }

  block_alloc ba;
  int location;


  while(head->next != NULL){
    ba = head->ptr->blocks;

    for(int i = 0; i < blocks_per_dir[disk_type]; i++){
      if(disk_type == FLOPPY)
        location = ba.floppy_block[i];
      else
        location = ba.hard_block[i];
      if(location == 0) /* if the end of file has been reached */
        i = blocks_per_dir[disk_type]; /* end the loop */
      else
        all_blocks[location] = 1;
    }

    head = head->next;
  }

}
