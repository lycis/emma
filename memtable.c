#define _EMMA_MEMTABLE_SRC_
#include "memtable.h"
#include "emma.h"

#include <string.h>
#include <stdio.h>

void init_memory_table(size_t blkSize)
{
    int base;
    
    base = emma_log2(blkSize) + 1;
    
    if(memory_table == 0) {
        // init list
        memory_table = (memory_page**) calloc(base, sizeof(memory_page*));
    } else if(memory_table_len < base) {
        // enlarge list
        memory_table = (memory_page**) realloc(memory_table, base*sizeof(memory_page*));
        memset(memory_table+(memory_table_len+1), 
               0, 
               (base-memory_table_len)*sizeof(memory_page*));
    }
    
    memory_table_len = base;
}

memory_block* find_free_block(memory_page *start)
{
    memory_page *page;

    // position on a page with free blocks
    page = start;
    while(page->numFree == 0 && page->next != 0)
    {
        page = page->next;
    }

    /*if(page == 0)
    {
        // initialise new additional page of memory
        page = init_memory_page(start->blksize);
        if(prevPage != 0)
          prevPage->next = page;
    }*/
    
    if(page == 0)
        return 0;

    if(page->numFree == 0)
        return 0;

    return page->freeblk[0];
}

memory_page* init_memory_page(size_t blksize)
{
    size_t       extBlkSize = blksize+(2*EMMA_SG_LEN);
    memory_page  *p = (memory_page*) calloc(1, sizeof(memory_page));
    int i;
   
    printf("init_memory_page(%zu)\n", blksize); 
    
    p->size = 10*extBlkSize; // TODO configurable blocks per page
    
    // allocate data area for the page
    p->data = calloc(1, p->size);
    
    // initialise memory block meta information
    p->blocks = (memory_block**) calloc(10, sizeof(memory_block*));
    for(i=0; i<10; ++i)
    {
        char *dataBegin = ((char*) p->data) + (i*extBlkSize);
        memory_block *b =  *(p->blocks + i);

        b = (memory_block*) malloc(sizeof(memory_block)); 

        b->page = p;
        b->sgPre  = dataBegin;
        b->data   = dataBegin + EMMA_SG_LEN;
        b->sgPost = dataBegin + EMMA_SG_LEN + blksize;
        b->allocStatus = FREE;
    }
    
    // store record of all free blocks
    p->freeblk = (memory_block**) calloc(10, sizeof(memory_block*));
    p->numFree = 10;
    
    // add all blocks to the list of free blocks
    for(i=0; i<10; ++i)
        *(p->freeblk) = *(p->blocks+i);

    return p;
}
