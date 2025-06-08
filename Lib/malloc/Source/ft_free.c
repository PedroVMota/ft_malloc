#include "Chunk.h"
#include "Core.h" 
#include "Heap.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>


/// @brief 
/// @param ptr start region where the user uses the memory. 
void ft_free(void *ptr){
    printf("____ FT FREE ___ \n");
    t_chunk *begging = (ptr - sizeof(t_chunk));
    printf("ptr: %p\n", begging);
    printf("Meta data: %d %d\n", begging->isbeingused, begging->size);
 
}