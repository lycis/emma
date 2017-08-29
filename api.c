#include "emma.h"
#include "memtable.h"

#include <string.h>
#include <stdio.h>

void* emma_malloc(size_t size)
{
    memory_page* list;
    int          base;
    size_t       blksize;
    memory_block *block;

    blksize = emma_nextp2(size);

    debug_print("blksize=%zu\n", blksize);

    // get matching list
    base = emma_log2(blksize);
    debug_print("index=%d\n", base);

    if(memory_table_len < (base + 1))
    {
        // extend memory table
        debug_print("init_memory_table\n");
        init_memory_table(blksize);
    }

    list = memory_table[base];
    debug_print("memory page=%p\n", (void*) list);

    // get a free block of the according size
    block = find_free_block(list); // TODO not working..
    debug_print("memory block = %p\n", (void*) block);
    debug_print("memory page = %p\n", (void*) list);

    // allocate a new page of memory if necessary
    if(block == 0)
    {
    memory_page *pNewPage, *currPage;
        debug_print("allocate new page\n");
        pNewPage = init_memory_page(blksize);
    debug_print("memory page initialised = %p\n", (void*) pNewPage);
    append_memory_page(pNewPage, base);
    list = memory_table[base];
    debug_print("listi[%d] = %p\n", base, (void*) list);
    block = find_free_block(list);
    if(block == 0)
    {
            debug_print("error: no free block\n");
        return 0;
    }

        // add new page to the memory list
        currPage = list;
        debug_print("currPage=%p\n next=%p", (void*) currPage, (void*) currPage->next);
        while(currPage->next != 0)
        {
            debug_print("paging...\n");
            currPage = currPage->next;
            debug_print("currPage=%p\n", (void*) currPage);
        }

        currPage->next = pNewPage;
        block = find_free_block(pNewPage); // get a free block on the new page
    }

    // safeguard memory
    memcpy(block->sgPre, EMMA_SG, EMMA_SG_LEN);
    memcpy(block->sgPost, EMMA_SG, EMMA_SG_LEN);

    return block->data;
}

int emma_free(memory_block* block)
{
    if(block->allocStatus != 1)
    {
//        return EMMA_FREE_NOT_ALLOCATED;
    }

return 0;
}
