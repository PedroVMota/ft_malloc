#include "Chunk.h"
#include "Core.h" 
#include "Heap.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>


void debug_chunk(t_chunk *ptr){
    printf("\tChunk: %p\n", ptr);
    printf("\t\tMagic: %X\n", ptr->magic);
    printf("\t\tEnd magic: %X\n", ptr->end_magic);
    printf("\n\t\tSize: %lu\n", ptr->size);
    printf("\t\tNext: %p\n", ptr->next);
    printf("\t\tPrev: %p\n", ptr->prev);
    printf("\t\tRegion: %p\n", ptr->region);
    printf("\t\tIs being used: %d\n", ptr->isbeingused);
}

void check_bins(){
    for (int i = 0; i < NUM_BINS; i++){
        printf("\tSelecting bin: %zu\n", bin_sizes[i]);  // Use %zu for size_t
        t_chunk *bin = heap.bins[i].chunks;
        printf("\tAvailable: %zu\n", heap.bins[i].availsize);  // Use %zu for size_t
        while(bin){
            if(bin->isbeingused)
                debug_chunk(bin);
            bin = bin->next;
        }
    }
}

void ft_debug(){
    check_bins();
}