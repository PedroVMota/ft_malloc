#ifndef MALLOC_H
#define MALLOC_H


#include <stddef.h>

void *ft_malloc(size_t size);




void *debugchunks();
void print_bits(const void *var, size_t size);


#endif
