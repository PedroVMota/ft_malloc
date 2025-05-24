#include <stdint.h>
#include <sys/mman.h>
#include "Core.h"
#include "Metadata.h"



static void *map(unsigned int len){
  void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  return ptr;
}


// struct heap_chunck_t *allocate(unsigned int _aligned_size){
//   if(_aligned_size <= 0)
//     return NULL;
//   struct heap_chunck_t *chunk = (struct heap_chunck_t *)map(_aligned_size);
//   return chunk;

