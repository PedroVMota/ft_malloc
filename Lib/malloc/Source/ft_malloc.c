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
        chunk->magic = CHUNK_MAGIC;
        chunk->prev = NULL;
        chunk->next = NULL;
        chunk->size = _aligned;
        chunk->isbeingused = 1;
        chunk->region = (void*)((char *)chunk + ALIGN_UP(sizeof(t_chunk)));
        chunk->end_magic = CHUNK_MAGIC;
        
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
        return chunk->region;
    } else {
        ptr->isbeingused = 1;
        return ptr->region;
    }
}


// Updated ft_malloc with debugging
void *ft_malloc(size_t size) {
    size_t user = ALIGN_UP(ALIGN_UP(size) + ALIGN_UP(sizeof(t_chunk)));
    if (user <= MAX_BIN_SIZE) {
        size_t bin = bin_sizes[0];
        t_pool binheap;
        int binselection  = -1;
        for (int i = 0; i < NUM_BINS; i++) {
            
            if (user <= bin_sizes[i]) {
                bin = bin_sizes[i];
                binselection = i;
                binheap = (heap.bins[i]);
                break;
            }
        }
        return alloc_small(bin, binselection);
    } else {
        return big_chunk_operation(user);
    }
}
