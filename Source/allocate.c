#include "./Core.h"
#include "Defines.h"
#include "Metadata.h"
#include "sys/mman.h"

#include <stdio.h>



static void *map(unsigned int len){
  void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  return ptr;
}

struct heap_chunck_t *allocate(unsigned int _request_size)
{
  
  unsigned int s_len = sizeof(struct heap_chunck_t);
  unsigned int u_allocate = (_request_size + SIMD_ALIGNMENT - 1) & ~(SIMD_ALIGNMENT - 1);
  unsigned int final = ((s_len + u_allocate) + SIMD_ALIGNMENT - 1) & ~(SIMD_ALIGNMENT - 1);
  printf("SIMD_ALIGNMENT: %d\n", SIMD_ALIGNMENT);
  printf("Size of the head meta data:\t%lu\n", (unsigned long)s_len);
  printf("Size of the request: %lu\n", (unsigned long)_request_size);
  printf("Request memory aligned: %lu\n", (unsigned long)u_allocate);
  printf("Final: %lu\n", (unsigned long)final);
  chunk_t *ptr = NULL;
  ptr = map(final);
  ptr->is_being_used = 1;
  ptr->size = final;
  ptr->next = NULL;
  ptr->prev = NULL;
  printf("Memory address allocated: %p\n", ptr);
  return ptr;
}
