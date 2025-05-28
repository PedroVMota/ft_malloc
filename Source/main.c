#include <ft_malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Modified main for leak testing
int main() {
    int *ptr = ft_malloc(sizeof(int) * 1024);
    printf("Int Ptr: %p\n", ptr);
    *ptr = 42;
    printf("Int Val: %d\n", *ptr);
    
    return 0;
}
