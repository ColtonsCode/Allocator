/**
 * @file cc_malloc.h
 * @brief Colton's custom memory allocator
 */

#ifndef CC_MALLOC_H
#define CC_MALLOC_H

#include <stddef.h>

/**
 * @brief Allocates memory on the heap.
 * @param size Number of bytes to allocate.
 * @return Pointer the the allocated memory, or NULL on failure.
 * @note This function uses sbrk() and is not thread-safe.
 */
void* cc_malloc(size_t size);

/**
 * @brief Frees memory on the heap.
 * @param ptr Pointer to the memory to free.
 * @note The memory must have been allocated with @ref cc_malloc. 
 */
void cc_free(void *ptr);

#endif