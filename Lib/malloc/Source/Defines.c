#include "Defines.h"
#include <stddef.h>

#include <stdio.h>

// Implementation for Defines
void print_bits(const void *var, size_t size) {
    const unsigned char *ptr = (const unsigned char*)var;
    
    // Print bits from most significant byte to least significant
    for (size_t byte = 0; byte < size; byte++) {
        unsigned char current_byte = ptr[size - 1 - byte];
        
        // Print each bit in the byte (MSB first)
        for (int bit = 7; bit >= 0; bit--) {
            printf("%c", ('0' + ((current_byte >> bit) & 1)));
        }
        
        // Add space between bytes (except after last byte)
        if (byte < size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}
