

struct node {
  struct node* prev;
  struct node* next;
  struct directly_entry* ptr;
};
typedef struct node *nodePtr;
