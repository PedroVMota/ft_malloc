#include "Chunk.h"

typedef t_chunk *t_chunkptr;

t_chunk *lastnode(t_chunkptr lst)
{
    while (lst->next)
        lst = lst->next;
    return (t_chunk *)lst;
}

t_chunk *available(t_chunkptr lst)
{
    while (lst->next)
    {
        if (!lst->isbeingused)
            return (t_chunk *)lst;
        lst = lst->next;
    }
    return NULL;
}


t_chunk *convert_voidptr_to_chunk_with_size(void *addr, size_t data_size) {
    if (!addr)
        return NULL;
    
    // Cast the memory address to a chunk pointer
    t_chunk *chunk = (t_chunk *)addr;
    
    // Initialize the chunk structure at this memory location
    chunk->size = data_size;   // Set the data size
    chunk->isbeingused = 0;    // Initially free
    chunk->next = NULL;        // No next chunk initially
    chunk->prev = NULL;        // No previous chunk initially
    
    // Set the region pointer to after the chunk header
    chunk->region = (char *)addr + ALIGN_UP(sizeof(t_chunk));
    
    return chunk;
}