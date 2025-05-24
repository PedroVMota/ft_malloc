#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_malloc.h"

// Linux/glibc
#ifdef __linux__
#include <malloc.h>
size_t get_malloc_size(void* ptr) {
    return malloc_usable_size(ptr);
}
#endif

// macOS
#ifdef __APPLE__
#include <malloc/malloc.h>
size_t get_malloc_size(void* ptr) {
    return malloc_size(ptr);
}
#endif

// Windows (MSVC)
#ifdef _WIN32
#include <malloc.h>
size_t get_malloc_size(void* ptr) {
    return _msize(ptr);
}
#endif

// FreeBSD
#ifdef __FreeBSD__
#include <malloc_np.h>
size_t get_malloc_size(void* ptr) {
    return malloc_usable_size(ptr);
}
#endif


void print_arch_info() {
    printf("=== Architecture Detection ===\n");
    
#if defined(__x86_64__) || defined(_M_X64)
    printf("Architecture: x86-64 (64-bit)\n");
    printf("Recommended alignment: 16 bytes\n");
#elif defined(__i386__) || defined(_M_IX86)
    printf("Architecture: x86-32 (32-bit)\n");
    printf("Recommended alignment: 8 bytes\n");
#elif defined(__aarch64__)
    printf("Architecture: ARM64 (AArch64)\n");
    printf("Recommended alignment: 16 bytes\n");
#elif defined(__arm__)
    printf("Architecture: ARM32\n");
    printf("Recommended alignment: 8 bytes\n");
#elif defined(__riscv)
    printf("Architecture: RISC-V\n");
    #if __riscv_xlen == 64
        printf("RISC-V 64-bit\n");
        printf("Recommended alignment: 8 bytes\n");
    #else
        printf("RISC-V 32-bit\n");
        printf("Recommended alignment: 4 bytes\n");
    #endif
#else
    printf("Architecture: Unknown\n");
    printf("Recommended alignment: 8 bytes (safe default)\n");
#endif

    printf("Pointer size: %zu bytes\n", sizeof(void*));
    printf("long size: %zu bytes\n", sizeof(long));
    printf("double size: %zu bytes\n", sizeof(double));
}

int main(int ac, char **av){

    // print_arch_info();
    // printf("=======\n");
    unsigned int size = atoi(av[1]);
    void *ftmalloc = ft_malloc(size);
    void *mal3 = malloc(size);
    //
    // printf("[Ignore] Size of ft_malloc %lu\n", get_malloc_size(ftmalloc));
    // printf("Get Malloc Size of malloc %lu\n", get_malloc_size(mal3));
    
    
    return 0;
}
