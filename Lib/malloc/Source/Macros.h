/* Architecture detection for memory alignment */
#ifndef MACROS_H
#define MACROS_H



#if defined(__LP64__) || defined(_WIN64) || defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__)
    #define ARCH_64BIT
    #define WORD_SIZE 8
    #define ALIGNMENT 16      /* 16-byte alignment for 64-bit (standard for malloc) */
    #define ALIGNMENT_MASK 15 /* 0x0F - for masking lower 4 bits */
#else
    #define ARCH_32BIT
    #define WORD_SIZE 4
    #define ALIGNMENT 8      /* 8-byte alignment for 32-bit (for long long/double) */
    #define ALIGNMENT_MASK 7 /* 0x07 - for masking lower 3 bits */
#endif

    #define ALIGN_UP(size) (((size) + ALIGNMENT - 1) & ~ALIGNMENT_MASK)
    #define ALIGN_DOWN(ptr) ((void *)((uintptr_t)(ptr) & ~ALIGNMENT_MASK))
    #define IS_ALIGNED(ptr) (((uintptr_t)(ptr) & ALIGNMENT_MASK) == 0)
    #define IS_POWER_OF_2(x) ((x) && !((x) & ((x) - 1)))
#endif