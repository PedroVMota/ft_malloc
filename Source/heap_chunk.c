#include "Metadata.h"


void add(chunk_t *ptr){
  chunk_t *start = global.chunk;
  if(!start){
    global.chunk = ptr;
    return;
  }
  while(start->next)
    start = start->next;
  start->next = ptr;
  ptr->prev = start;
  return;
}
