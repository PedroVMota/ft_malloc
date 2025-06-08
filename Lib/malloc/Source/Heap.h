#ifndef HEAP_H
#define HEAP_H

#define _GNU_SOURCE

#include <stddef.h>
#include <sys/mman.h>
#include <Chunk.h>

#define MIN_BIN_SIZE 16
#define MAX_BIN_SIZE 512
#define NUM_BINS 6




static const size_t bin_sizes[NUM_BINS] = {
    16,
    32,
    64,
    128,
    256,
    512,
};

typedef struct pool_t
{
  t_chunk *chunks;
  size_t maxsize;
  size_t availsize;
} t_pool;

typedef struct heap_t
{
  t_pool bins[NUM_BINS];
  t_chunk *bchunks;

  size_t totalalloc;
  size_t totalfrees;
  size_t peakusage;

} t_heap;

extern t_heap heap;

void *alloc_heap(size_t size);
void *alloc_small(size_t binsize, int binselection);

#endif
