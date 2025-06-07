#include "Heap.h"
#include <stdio.h>

// Implementation for Heap
void *alloc_heap(size_t size){
    return mmap(NULL, size,PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,0);    
}





void *alloc_small(size_t size, t_pool **bin, size_t binsize){    
    printf("Total Size allocated: %lu\n", (*bin)->maxsize);
    printf("Available memory: %lu\n", (*bin)->availsize);
    return NULL;
}
