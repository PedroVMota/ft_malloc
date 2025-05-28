#include "Chunk.h"

// Implementation for Chunk
//
//
//
/*
 * addr it will be the heap point that will be used to store the chunk (header of the heap) + plus the requested memory.
 * _ofsset it will be the starting point where the user can use to store the variables values;
 * nbytes is a security in order to no exceed the memory byte
*/
void *mapchunk(void **addr, void **_offset, size_t nbytes){
    if (sizeof(t_chunk) >= nbytes)
        return NULL;
    t_chunk *ptr = (t_chunk *)(*addr);
    ptr->size = nbytes;  // nbytes is the data size for this chunk
    ptr->next = NULL;
    ptr->prev = NULL;
    ptr->region = (char *)(*addr) + sizeof(t_chunk);
    *_offset = ptr->region;
    return ((*addr) + nbytes);
}
