#include "Chunk.h"
#include "Core.h" 
#include "Heap.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>





// Helper function to find which bin a chunk belongs to
int find_bin_for_size(size_t size) {
    //printf("Bin Size: %d\n", size);
    for (int i = 0; i < NUM_BINS; i++) {
        if (size <= bin_sizes[i]) {
            return i;
        }
    }
    return -1; // Not a small chunk
}

// Helper function to get chunk from user pointer
t_chunk *get_chunk_from_ptr(void *ptr) {
    if (!ptr) return NULL;
    
    // The chunk header is located just before the user data
    // ptr points to the user data region, so we need to go back
    // by the aligned size of the chunk header
    return (t_chunk *)((char *)ptr - ALIGN_UP(sizeof(t_chunk)));
}

// Helper function to validate chunk
int is_valid_chunk(t_chunk *chunk) {
    if (!chunk) return 0;
    
    // Check magic number
    if (chunk->magic != CHUNK_MAGIC) {
        printf("Invalid magic: expected 0x%X, got 0x%X\n", CHUNK_MAGIC, chunk->magic);
        return 0;
    }
    
    // Check end magic (if you're using it)
    if (chunk->end_magic != CHUNK_MAGIC) {
        printf("End magic corrupted: expected 0x%X, got 0x%X\n", CHUNK_MAGIC, chunk->end_magic);
        return 0;
    }
    
    // Other validation...
    if (chunk->size == 0) return 0;
    if (chunk->size > (1024 * 1024 * 1024)) return 0;
    
    return 1;
}

void debug_chunk(t_chunk *ptr);


void ft_free(void *ptr) {
    if (!ptr) {
        return;
    }
    
    t_chunk *chunk = get_chunk_from_ptr(ptr);

    if(chunk->size >= 512){
        debug_chunk(chunk);
    }



    if (!is_valid_chunk(chunk) || !chunk->isbeingused)
        return;

    
    size_t total_size = chunk->size;
    if (total_size <= MAX_BIN_SIZE) {
        int bin_index = find_bin_for_size(total_size);
        if (bin_index >= 0) {
            chunk->isbeingused = 0;
            heap.bins[bin_index].availsize += bin_sizes[bin_index];
            heap.totalfrees++;
        } 
    } else {
        printf("Deleting Large chunks");
        t_chunk *current = heap.bchunks;
        int found = 0;
        while (current) {
            printf("Current -> chunk: %p || %p", current, chunk);
            if (current == chunk) {
                found = 1;
                break;
            }
            current = current->next;
        }
        
        if (found) {
            chunk->isbeingused = 0;
            heap.totalfrees++;
            //printf("Large chunk marked as free\n");
        } else {
            //printf("ft_free: Large chunk not found in heap.bchunks list\n");
        }
    }
    
    //printf("ft_free completed successfully\n");
}