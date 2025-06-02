#include <unistd.h>
#include <stdio.h>
#include "cc_allocate.h"

// A simple program for testing my custom allocator
// Tutorial used: https://danluu.com/malloc-tutorial/

int main(void)
{
    // Current location of the program break
    void* brk_p = sbrk(0);
    printf("Start break location: %p\n", brk_p);
    
    // Allocate the memory for an int.
    int* mem_pointer = cc_malloc(sizeof(int));
    putchar('\n');

    // Print the returned memory address.
    printf("Allocated memory at: %p\n", (void*)mem_pointer);

    // Allocate the memory for another int.
    int* mem_pointer2 = cc_malloc(sizeof(int));
    putchar('\n');
    printf("Allocated memory at: %p (second int)\n", (void*)mem_pointer2);

    putchar('\n');
    printf("Difference between pointers: %ld\n", mem_pointer2 - mem_pointer);
}