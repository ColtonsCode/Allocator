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

/**
 * @brief Reallocates memory on the heap.
 * @param ptr Pointer to the memory to reallocate.
 * @param size New size in bytes.
 * @return Pointer to the reallocated memory, or NULL on failure.
 * @note The memory must have been allocated with @ref cc_malloc. 
 */
void *cc_realloc(void *ptr, size_t size);

/**
 * @brief Allocated memory on the heap and clears it.
 * @param nelem Number of elements.
 * @param elsize Size of each element in bytes.
 * @return Pointer to the allocated memory, or NULL on failure.
 * @note This function initializes the allocated memory to zero.
 */
void *cc_calloc(size_t nelem, size_t elsize);

#endif