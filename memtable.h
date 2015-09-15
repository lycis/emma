/* 
 * File:   memtable.h
 * Author: Daniel Eder (daniel@deder.at)
 *
 * 
 * !!! INTERNAL ONLY !!!
 * 
 * handling of internal memory
 * 
 * these functions and structures are (usually) not exposed to the user
 * 
 */

#ifndef MEMTABLE_H
#define	MEMTABLE_H

#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
/* STRUCTS */

struct memory_page;

// holds information about a block of memory in the internal memory
typedef struct memory_block {
    struct memory_page  *page;       // number of the memory page
    char         *sgPre;      // safeguard placed in front of data
    char         *sgPost;     // safeguard placed behind data
    void         *data;       // actual data
    int          allocStatus; // indicates allocation status (0 = free, 1 = allocated)
} memory_block;

// holds information for a page in the internal memory that consits of
// multiple pages that are not necessarily next to each other
typedef struct memory_page {
    struct memory_page  *prev;     // previous page
    size_t              size;      // page size; end = begin + size
    struct memory_page  *next;     // next page
    size_t              blksize;   // size of a single block
    void                *data;     // points to the memory page
    struct memory_block **blocks;  // block meta information
    struct memory_block **freeblk; // free memory blocks
    unsigned int        numFree;   // number of free blocks on this page
} memory_page;

#ifndef _EMMA_MEMTABLE_SRC_
extern memory_page **memory_table;
extern int memory_table_len;
extern const unsigned int FREE;
extern const unsigned int ALLOCATED;
#else
struct memory_page **memory_table = 0; // holds all page lists for different sizes
int memory_table_len = 0;
const unsigned int FREE      = 0;
const unsigned int ALLOCATED = 1;
#endif

/* FUNCTIONS */

// initialises the internal memory table for the given blocksize
//
// it is initiated without any pages. all not yet initialised table entries
// up to the given block size will be initialised as well
//
void init_memory_table(size_t blkSize);

// returns a pointer to the next free memory block on the given page with
// the given size. it will return 0 if no memory of that size is available.
memory_block* find_free_block(memory_page *start);

// allocates and initialises a new page of memory with the given block size
memory_page* init_memory_page(size_t blksize);

#ifdef	__cplusplus
}
#endif

#endif	/* MEMTABLE_H */

