#ifndef DEFINES_H

#define DEFINES_H
#define NULL 0


#if defined(__x86_64__) || defined(_M_X64)
    #define MALLOC_ALIGNMENT 16
    #define SIMD_ALIGNMENT 32    // AVX2
#elif defined(__i386__) || defined(_M_IX86)
    #define MALLOC_ALIGNMENT 8
    #define SIMD_ALIGNMENT 16    // SSE
#elif defined(__aarch64__)
    #define MALLOC_ALIGNMENT 16
    #define SIMD_ALIGNMENT 16    // NEON
#elif defined(__arm__)
    #define MALLOC_ALIGNMENT 8
    #define SIMD_ALIGNMENT 16    // NEON
#else
    #define MALLOC_ALIGNMENT 8   // Safe default
    #define SIMD_ALIGNMENT 16
#endif

#endif
