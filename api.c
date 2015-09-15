#include "emma.h"
#include "memtable.h"

#include <string.h>

void* emma_malloc(size_t size)
{
    memory_page* list;
    int          base;
    size_t       blksize;
    memory_block *block;

    blksize = emma_nextp2(size);

    // get matching list
    base = emma_log2(blksize);
    if(memory_table_len < (base + 1))
    {
        init_memory_table(blksize);
    }

    // initialise first page of memory if not yet done
    if(memory_table[base] == 0) 
    {
        memory_table[base] = init_memory_page(blksize);
    }

    list = memory_table[base];

    // get a free block of the according size
    block = find_free_block(list); // TODO not working...

    // allocate a new page of memory if necessary
    if(block == 0)
    {
        memory_page *pNewPage, *currPage;
        pNewPage = init_memory_page(blksize);

        // add new page to the memory list
        currPage = list;
        while(currPage->next != 0)
        {
            currPage = currPage->next;
        }

        currPage->next = pNewPage;
        block = find_free_block(pNewPage); // get a free block on the new page
    }

    // safeguard memory
    memcpy(block->sgPre, EMMA_SG, EMMA_SG_LEN);
    memcpy(block->sgPost, EMMA_SG, EMMA_SG_LEN);

    return block->data;
}