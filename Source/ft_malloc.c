#include "Metadata.h"
#include "Core.h"

struct heap_info_t global = {null};


#include <stdio.h>

void print(){
  chunk_t *ptr = global.chunk;
  while(ptr){
    printf("|%p->%p|\n", ptr, (ptr + ptr->size));
    ptr = ptr->next;
  }
}

void append(chunk_t **ptr){
  if(!global.chunk){
    global.chunk = *ptr;
    print();
    return;
  }
  chunk_t *start = global.chunk;
  while(start->next)
    start = start->next;
  start->next = *ptr;
  (*ptr)->prev = start;
  print();
  return;
}

void *ft_malloc(unsigned int size){
  if(size <= 0)
    return NULL;
  if(global.chunk == NULL){
    chunk_t *ptr = allocate(size);
    if(!ptr)
      return NULL;
    append(&ptr);
  }
  return NULL;
}
