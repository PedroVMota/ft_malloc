#include <stdlib.h>
#include <stdio.h>

int main() {
    printf("Before malloc\n");
    void *ptr = malloc(100);
    printf("Malloc returned: %p\n", ptr);
    free(ptr);
    printf("After free\n");
    return 0;
}
