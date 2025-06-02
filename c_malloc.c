#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include "c_malloc.h"

// The size of a block_meta struct.
#define CC_META_SIZE sizeof(cc_block_meta)

// Internal head for linked list.
static void *cc_global_base = NULL;

// Internal metadata header for each allocation block.
// Used by cc_malloc/cc_free to track size and free status.
typedef struct cc_block_meta 
{
    size_t size;
    struct cc_block_meta *next;
    bool free;
    int magic; // For debugging only. TODO: Remove this in non-debug mode.
} cc_block_meta;

cc_block_meta *cc_find_free_block(cc_block_meta **last, size_t size)
{
    cc_block_meta *current = cc_global_base;

    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }

    return current;
}

cc_block_meta *cc_request_space(cc_block_meta *last, size_t size)
{
    cc_block_meta *block;
    block = sbrk(0);

    void *request = sbrk(size + CC_META_SIZE);
    assert((void*)block == request); // Not thread safe.
    if (request == (void*) -1)
    {
        return NULL; // sbrk failed.
    }

    if (last) // NULL on first request.
    {
        last->next = block;
    }

    block->size = size;
    block->next = NULL;
    block->free = false;
    block->magic = 0x12345678;
    return block;
}

cc_block_meta *cc_get_block_ptr(void *ptr)
{
    return (cc_block_meta*)ptr - 1;
}

void *cc_malloc(size_t size)
{
    cc_block_meta *block;

    if (size <= 0)
    {
        return NULL;
    }

    if (!cc_global_base) // First call.
    {
        block = cc_request_space(NULL, size);
        if (!block)
        {
            return NULL;
        }
        cc_global_base = block;

        // +1 increments the address by one sizeof(struct cc_block_meta).
        return block + 1;
    }

    cc_block_meta *last = cc_global_base;
    block = cc_find_free_block(&last, size);
    if (!block) // Failed to find a suitable free block
    {
        block = cc_request_space(last, size);
        if (!block)
        {
            return NULL;
        }

        return block + 1;
    }

    // Found a free block
    block->free = 0;
    block->magic = 0x77777777;

    return (block+1);
}

void cc_free(void *ptr)
{
    if (!ptr)
    {
        return;
    }

    cc_block_meta *block_ptr = cc_get_block_ptr(ptr);
    assert(block_ptr->free == 0);
    assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);

    block_ptr->free = true;
    block_ptr->magic = 0x55555555;
}

