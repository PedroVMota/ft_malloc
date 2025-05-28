#ifndef CHUNK_H
#define CHUNK_H
#include <stddef.h>
#include <stdint.h>



#define CHUNK_ALLOCATED  0x1   // Bit 0: chunk is allocated
#define PREV_FREE       0x2   // Bit 1: previous chunk is free 


typedef struct chunk_t{
  //Header Part
  size_t size; 
  uint8_t isbeingused;
  struct chunk_t *next;
  struct chunk_t *prev;  // Fixed the typo here
  //Address part
  void *region;
} t_chunk;

void *mapchunk(void **addr, void **offset, size_t nbytes);

#endif
