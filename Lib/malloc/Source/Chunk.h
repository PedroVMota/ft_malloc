#ifndef CHUNK_H
#define CHUNK_H
#include <stddef.h>
#include <stdint.h>
#include <Macros.h>

#define CHUNK_ALLOCATED 0x1
#define PREV_FREE 0x2

typedef struct chunk_t
{

  size_t size;
  uint8_t isbeingused;
  struct chunk_t *next;
  struct chunk_t *prev;
  void *region;
} t_chunk;

t_chunk *lastnode(t_chunk *lst);
t_chunk *available(t_chunk *lst);
t_chunk *convert_voidptr_to_chunk(void *ptr);

#endif
