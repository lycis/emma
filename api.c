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

    printf("blksize=%zu\n", blksize);

    // get matching list
    base = emma_log2(blksize);
    printf("index=%d\n", base);

    if(memory_table_len < (base + 1))
    {
        printf("init_memory_table\n");
        init_memory_table(blksize);
    }

    printf("checking first page init\n");
    // initialise first page of memory if not yet done
    if(memory_table[base] == 0) 
    {
        printf("init first page\n");
        memory_table[base] = init_memory_page(blksize);
    }

    list = memory_table[base];
    printf("memory page=%p\n", (void*) list);

    // get a free block of the according size
    block = find_free_block(list); // TODO not working..
    printf("memory block = %p\n", (void*) block);

    // allocate a new page of memory if necessary
    if(block == 0)
    {
	memory_page *pNewPage, *currPage;
        printf("allocate new page\n");
        pNewPage = init_memory_page(blksize);
	printf("memory page initialised = %p\n", (void*) pNewPage);

        // add new page to the memory list
        currPage = list;
	printf("currPage=%p\n next=%p", (void*) currPage, (void*) currPage->next);
        while(currPage->next != 0)
        {
	    printf("paging...\n");
            currPage = currPage->next;
	    printf("currPage=%p\n", (void*) currPage);
        }

        currPage->next = pNewPage;
        block = find_free_block(pNewPage); // get a free block on the new page
    }

    // safeguard memory
    memcpy(block->sgPre, EMMA_SG, EMMA_SG_LEN);
    memcpy(block->sgPost, EMMA_SG, EMMA_SG_LEN);

    return block->data;
}

