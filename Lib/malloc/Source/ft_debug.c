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
}

void check_bins(){
    for (int i = 0; i < NUM_BINS; i++){
        printf("\tSelecting bin: %d\n", bin_sizes[i]);
        t_chunk *bin = heap.bins[i].chunks;
        printf("\tAvailable: %d\n", heap.bins[i].availsize);
        while(bin){
            if(!bin->isbeingused)
                debug_chunk(bin);
            bin = bin->next;
        }
    }
}

void ft_debug(){
    check_bins();
}