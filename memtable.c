#define _EMMA_MEMTABLE_SRC_
#include "memtable.h"
#include "emma.h"

#include <string.h>
#include <stdio.h>

void init_memory_table(size_t blkSize)
{
    int base, i;

    debug_print("init_memory_table(%zu)\n", blkSize);
    
    base = emma_log2(blkSize) + 1;
    debug_print("base=%d\n", base);
    
    if(memory_table == 0) {
        // init list
        memory_table = (memory_page**) calloc(base, sizeof(memory_page*));
    } 
    
    if(memory_table_len < base) {
        // enlarge list
        memory_table = (memory_page**) realloc(memory_table, base*sizeof(memory_page*));
        /*memset(memory_table+(memory_table_len+1), 
               0, 
               (base-memory_table_len)*sizeof(memory_page*));*/
    }

    debug_print("initialisng first pages...\n");

    for(i=memory_table_len+1; i<=(base-1); ++i) {
        debug_print("fp base = %d\n", i);
        append_memory_page(init_memory_page(emma_nextp2(i)), i);
    }

    memory_table_len = base;
}

memory_block* find_free_block(const memory_page *start)
{
    const memory_page *page;

    debug_print("find_free_block(%p)\n", (void*) start);

    // position on a page with free blocks
    page = start;
    debug_print("page (%p) has %d free blocks\n", (void*) page, page->numFree);
    while(page->numFree == 0 && page != 0)
    {
	debug_print("no free block on page. next = %p\n", (void*) page->next);
        page = page->next;
    }

    if(page == 0) {
	debug_print("page = NULL\n");
        return 0;
    }
    
    if(page->numFree == 0) {
	debug_print("all blocks are used up.\n");
        return 0;
    }

    debug_print("free block: %p\n", (void*) page->freeblk[0]);
    return page->freeblk[0];
}

void mark_block_used(const memory_page *page)
{

}

memory_page* init_memory_page(size_t blksize)
{
    size_t       extBlkSize = blksize+(2*EMMA_SG_LEN);
    memory_page  *p = (memory_page*) calloc(1, sizeof(memory_page));
    int i;
   
    debug_print("init_memory_page(%zu)\n", blksize); 
    
    // size = block count * block size + size of backpointer to block for each data element
    p->size = 10*extBlkSize + sizeof(memory_block*); // TODO configurable blocks per page
    debug_print("p->size = %zu\n", p->size);
    
    // allocate data area for the page
    p->data = calloc(1, p->size);
    
    // initialise memory block meta information
    p->blocks = (memory_block**) calloc(10, sizeof(memory_block*));
    for(i=0; i<10; ++i)
    {
        char *dataBegin = ((char*) p->data) + (i*extBlkSize);
        memory_block *b = (memory_block*) malloc(sizeof(memory_block)); 

        b->page = p;
        b->sgPre  = dataBegin + sizeof(memory_block*);
        b->data   = dataBegin + EMMA_SG_LEN;
        b->sgPost = dataBegin + EMMA_SG_LEN + blksize;
        b->allocStatus = FREE;

        memcpy(dataBegin, &b, sizeof(memory_block*)); // save back reference

	    p->blocks[i] = b;
    }
    
    // store record of all free blocks
    p->freeblk = (memory_block**) calloc(10, sizeof(memory_block*));
    p->numFree = 10;
    
    // add all blocks to the list of free blocks
    for(i=0; i<10; ++i) {
	    debug_print("p->freeblk[%d] = %p\n", i, (void*) p->blocks[i]) ;
        p->freeblk[i] = p->blocks[i];
    }
    
    debug_print("init_memory_page(%zu) = %p\n", blksize, (void*) p);
    debug_print("p->next = %p\n", (void*) p->next);
    return p;
}

memory_page* get_last_memory_page(size_t blksize)
{
    memory_page* cp = memory_table[blksize];
    if(cp == 0) 
    {
	    return 0;
    }

    while(cp->next != 0)
    {
        cp = cp->next;
    }

    return cp;
}

void append_memory_page(const memory_page *page, size_t blksize)
{
    memory_page *last = 0;

    debug_print("append_memory_page(%p, %zu)\n", (void*) page, blksize);

    last = get_last_memory_page(blksize);
    if(last == 0)
    {
	debug_print("setting first page: memory_table[%zu] = %p\n", blksize, (void*) page);
        memory_table[blksize] = (memory_page*) page;
    }
    else
    {
        last->next = (memory_page*) page;
    }
}
