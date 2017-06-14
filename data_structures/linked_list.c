//==============================================================================
// Linked list implementation
//
// Compile:  gcc --std=c99 linked_list.c -o linked_list
//==============================================================================
#include <stdio.h>
#include <stdlib.h>

//==============================================================================
// List structs
//==============================================================================

struct node {
  int data;
  struct node* next;
};

struct list {
  struct node* head;
};

//==============================================================================
// List methods
//==============================================================================

// Create and return a new list node
struct node* node__new(int data)
{
  struct node* node = malloc(sizeof(struct node));
  node->data = data;
  node->next = NULL;
  return node;
}

// Create and return a new list
struct list* list__new()
{
  struct list* list = malloc(sizeof(struct list));
  list->head = NULL;
  return list;
}

// Free each node, and then free the list itself
void list__free(struct list* self)
{
  struct node* cur = self->head;
  struct node* next;
  while(cur) {
    next = cur->next;
    free(cur);
    cur = next;
  }
  free(self);
}

// Prepend the integer to the list
void list__prepend(struct list* self, int x)
{
  struct node* new = node__new(x);
  new->next = self->head;
  self->head = new;
}

// Append the integer to the list
void list__append(struct list* self, int x)
{
  struct node* new = node__new(x);
  if(self->head) {
    // Find the last node, then set last->next = new
    struct node* cur = self->head;
    while (cur && cur->next) {
      cur = cur->next;
    }
    cur->next = new;
  }
  else {
    self->head = new;
  }
}

// Get the list length. Runtime O(n).
size_t list__length(struct list* self)
{
  size_t count = 0;
  for(struct node* cur = self->head; cur; cur = cur->next) {
    count++;
  }
  return count;
}

// Find and return the first node containing the target integer value.
// Returns null if no such node is found.
struct node* list__find(struct list* self, int target)
{
  for(struct node* cur = self->head; cur; cur = cur->next) {
    if(cur->data == target)
      return cur;
  }
  return NULL;
}

// Reverse the list
void list__reverse(struct list* self)
{
  struct node* prev = NULL;
  struct node* curr = self->head;
  struct node* next = NULL;

  while(curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  self->head = prev;
}

// Print the list as comma-separated values
void list__print(struct list* self)
{
  for(struct node* cur = self->head; cur; cur = cur->next) {
    if(cur != self->head)
      printf(", ");
    printf("%d", cur->data);
  }
  printf("\n");
}

//==============================================================================
// Main
//==============================================================================

int main(int argc, char** argv)
{
  printf("hey man\n");
  struct list* l = list__new();

  list__append(l, 2);
  list__append(l, 3);
  list__append(l, 4);
  list__append(l, 5);
  list__print(l);

  list__prepend(l, 1);
  list__print(l);

  list__reverse(l);
  list__print(l);

  list__free(l);
}
