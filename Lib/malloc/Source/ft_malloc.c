#include "Chunk.h"
#include "Core.h" 
#include "Heap.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>

t_chunk *check_usable(size_t size) {
  t_chunk *chunks = heap.bchunks;
  while (chunks) {
    if (!chunks->isbeingused) {
      if (chunks->size >= size)
        return chunks;
    }
    chunks = chunks->next;
  }
  return NULL;
}

void *big_chunk_operation(size_t _aligned){
    t_chunk *ptr = check_usable(_aligned);
    if (!ptr) {
        // No reusable chunk found - allocate new one
        t_chunk *chunk = (t_chunk *)alloc_heap(_aligned);
        if (!chunk)
            return NULL;
        chunk->prev = NULL;
        chunk->next = NULL;
        chunk->size = _aligned;
        chunk->isbeingused = 1;
        chunk->region = (void*)((char *)chunk + ALIGN_UP(sizeof(t_chunk)));
        
        t_chunk *lst = heap.bchunks;
        if(!lst){
            heap.bchunks = chunk;
        } else {
            while(lst->next){
                lst = lst->next;
            }
            lst->next = chunk;
            chunk->prev = lst;
        }
        printf("Returning: %p\n", chunk->region);
        return chunk->region;
    } else {
        // Found reusable chunk - mark it as used and return it
        ptr->isbeingused = 1;
        printf("Reusing: %p\n", ptr->region);
        return ptr->region;
    }
}


void *ft_malloc(size_t size){
    (void)size;
    size_t user = ALIGN_UP(ALIGN_UP(size) + ALIGN_UP(sizeof(t_chunk)));
    printf("%lu\n", user);
    if(user <= MAX_BIN_SIZE){
    size_t bin = bin_sizes[0];
      for (int i = 0; i < NUM_BINS; i++) {
        if (user <= bin_sizes[i]) {
          bin = bin_sizes[i];
          break;
        }
      };
        printf("Small Chunk %lu\n", bin);
        return NULL;
    }else{
        printf("Large chunk %lu\n", user);
        return big_chunk_operation(user);
    }
}


void debugchunks(){
  t_chunk *ptr = heap.bchunks;
  if(!ptr)
    return;
  int chunk = 0;

  while(ptr){
    printf("Chunk %d | %lu\n", chunk, (size_t)ptr);
    printf("\tSize: %lu\n", ptr->size);
    printf("\tIs being used %d\n", ptr->isbeingused);
    printf("\tNext: %lu\n",(size_t) ptr->next);
    printf("\tPrev: %lu\n",(size_t) ptr->prev);
    printf("\tUser ptr: %lu\n", (size_t)ptr->region);
    chunk++;
    ptr = ptr->next;
  }
}

