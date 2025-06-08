#include "Chunk.h"
#include "Core.h" 
#include "Heap.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>




// Helper function to find which bin a chunk belongs to
int find_bin_for_size(size_t size) {
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


void ft_free(void *ptr) {
    if (!ptr) {
        printf("ft_free: NULL pointer passed\n");
        return;
    }
    
    printf("____ FT FREE ___ \n");
    printf("User ptr: %p\n", ptr);
    
    // Get the chunk header from the user pointer
    t_chunk *chunk = get_chunk_from_ptr(ptr);
    printf("Chunk ptr: %p\n", chunk);
    
    // Validate the chunk
    if (!is_valid_chunk(chunk)) {
        printf("ft_free: Invalid chunk detected\n");
        printf("Chunk size: %zu\n", chunk ? chunk->size : 0);
        printf("Chunk region: %p\n", chunk ? chunk->region : NULL);
        return;
    }
    
    printf("Chunk metadata: size=%zu, used=%d\n", chunk->size, chunk->isbeingused);
    
    // Check if chunk is already free
    if (!chunk->isbeingused) {
        printf("ft_free: Double free detected!\n");
        return;
    }
    
    // Calculate the original allocation size (includes chunk header)
    size_t total_size = ALIGN_UP(ALIGN_UP(chunk->size) + ALIGN_UP(sizeof(t_chunk)));
    printf("Size requested -> %d\n", (int)chunk->size);
    
    // Determine if this is a small chunk or large chunk
    if (total_size <= MAX_BIN_SIZE) {
        // Small chunk - return to appropriate bin
        int bin_index = find_bin_for_size(total_size);
        if (bin_index >= 0) {
            printf("Freeing small chunk to bin %d (size %zu)\n", bin_index, bin_sizes[bin_index]);
            chunk->isbeingused = 0;
            heap.bins[bin_index].availsize += bin_sizes[bin_index];
            heap.totalfrees++;
            
            printf("Bin %d now has %zu bytes available\n", bin_index, heap.bins[bin_index].availsize);
        } else {
            printf("ft_free: Could not find appropriate bin for size %zu\n", total_size);
        }
    } else {
        // Large chunk - find in bchunks list and mark as free
        printf("Freeing large chunk (size %zu)\n", chunk->size);
        
        // Verify this chunk exists in our bchunks list
        t_chunk *current = heap.bchunks;
        int found = 0;
        while (current) {
            if (current == chunk) {
                found = 1;
                break;
            }
            current = current->next;
        }
        
        if (found) {
            chunk->isbeingused = 0;
            heap.totalfrees++;
            printf("Large chunk marked as free\n");
        } else {
            printf("ft_free: Large chunk not found in heap.bchunks list\n");
        }
    }
    
    printf("ft_free completed successfully\n");
}