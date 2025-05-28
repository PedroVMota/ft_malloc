#include "Heap.h"
#include <stdio.h>

// Implementation for Heap
void *alloc_heap(size_t size){
    return mmap(NULL, size,PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,0);    
}
