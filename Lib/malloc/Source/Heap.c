#include "Heap.h"
#include <stdio.h>

void *alloc_heap(size_t size){
    return mmap(NULL, size,PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,0);    
}



t_chunk *newlst(size_t binsize) {
    // Calculate total size needed for each chunk (header + aligned data)
    size_t chunk_total_size = ALIGN_UP(sizeof(t_chunk)) + ALIGN_UP(binsize);
    
    // Calculate total memory needed for 1024 chunks
    size_t total_memory = chunk_total_size * 1024;
    printf("[REQUESTING] >> Requesting %zu bytes for %zu chunks of size %zu\n", 
           total_memory, (size_t)1024, binsize);
    // Allocate the large memory block
    void *memory_block = alloc_heap(total_memory);
    if (!memory_block) {
        printf("[ERROR] Failed to allocate memory block\n");
        return NULL;
    }
    t_chunk *head = NULL;
    t_chunk *current = NULL;
    char *current_addr = (char *)memory_block;
    for (int i = 0; i < 1024; i++) {
        t_chunk *new_chunk = (t_chunk *)current_addr;
        new_chunk->size = binsize;  // Store the data size (not total size)
        new_chunk->isbeingused = 0; // Mark as free
        new_chunk->next = NULL;
        new_chunk->prev = NULL;
        new_chunk->region = current_addr + ALIGN_UP(sizeof(t_chunk));
        if (!head) {
            head = new_chunk;
            current = head;
        } else {
            current->next = new_chunk;
            new_chunk->prev = current;
            current = new_chunk;
        }
        current_addr += chunk_total_size;
    }
    return head;
}



void *alloc_small(size_t size, t_pool *bin, size_t binsize){    
    printf("Total Size allocated: %lu\n", (bin)->maxsize);
    printf("Available memory: %lu\n", (bin)->availsize);
    t_chunk *slot = bin->chunks;
    while(slot){
        printf("\t[SEARCH] -> Analizing this %p\n", slot);
        if(!slot->isbeingused)
            break;
        slot = slot->next;
    }

    if(!slot){
        printf("[REQUESTIONS] -> Requesting binsize * 1024\n");
        t_chunk *nlst = newlst(binsize);
        if(!nlst){
            printf("New List is null\n");
            return NULL;
        }
        bin->maxsize += (binsize * 1024);
        bin->availsize += (binsize * 1024);
        slot = bin->chunks;
        if(slot){
            while(slot->next)
                slot = slot->next;
            slot->next = nlst;
            nlst->prev = nlst;
        }
        else{
            bin->chunks = nlst;
        }
        printf("[REQUEST] Calling the recursive \n");
        return alloc_small(size, bin, binsize);
    }

    slot->isbeingused = 1;
    bin->availsize -= binsize;
    return (slot + sizeof(t_chunk));
}
