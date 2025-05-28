#ifndef HEAP_H
#define HEAP_H


#define _GNU_SOURCE 
#include <stddef.h>
#include <sys/mman.h>
#include <Chunk.h>

/* Architecture detection for memory alignment */
#if defined(__LP64__) || defined(_WIN64) || defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__)
    #define ARCH_64BIT
    #define WORD_SIZE 8
    #define ALIGNMENT 16       /* 16-byte alignment for 64-bit (standard for malloc) */
    #define ALIGNMENT_MASK 15  /* 0x0F - for masking lower 4 bits */
#else
    #define ARCH_32BIT
    #define WORD_SIZE 4
    #define ALIGNMENT 8        /* 8-byte alignment for 32-bit (for long long/double) */
    #define ALIGNMENT_MASK 7   /* 0x07 - for masking lower 3 bits */
#endif

#define ALIGN_UP(size) (((size) + ALIGNMENT - 1) & ~ALIGNMENT_MASK)
#define ALIGN_DOWN(ptr) ((void*)((uintptr_t)(ptr) & ~ALIGNMENT_MASK))
#define IS_ALIGNED(ptr) (((uintptr_t)(ptr) & ALIGNMENT_MASK) == 0)
#define IS_POWER_OF_2(x) ((x) && !((x) & ((x) - 1)))



#define MIN_BIN_SIZE 16        /* Minimum allocation size (aligned) */
#define MAX_BIN_SIZE 512
#define NUM_BINS 6            /* Number of bins in our system */

/* Static array of bin sizes (powers of 2) */
static const size_t bin_sizes[NUM_BINS] = {
    16,      /* Bin 0:  16 bytes */
    32,      /* Bin 1:  32 bytes */
    64,      /* Bin 2:  64 bytes */
    128,     /* Bin 3:  128 bytes */
    256,     /* Bin 4:  256 bytes */
    512,     /* Bin 5:  512 bytes */
};



typedef struct pool_t{
  t_chunk *chunks;
  void *beg;
  size_t maxsize;
  size_t availsize;
} t_pool;


typedef struct heap_t{
  t_pool bins[NUM_BINS];
  t_chunk *bchunks;
  
  size_t totalalloc;
  size_t totalfrees;
  size_t peakusage;

} t_heap;


static t_heap heap;

void *alloc_heap(size_t size);


#endif
