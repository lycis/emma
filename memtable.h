/* 
 * File:   memtable.h
 * Author: Daniel Eder (daniel@deder.at)
 *
 * Created on 19. August 2015, 12:26
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

// holds information about a block of memory in the internal memory
typedef struct memory_block {
    int  *page;       // number of the memory page
    char *sgPre;      // safeguard placed in front of data
    char *sgPost;     // safeguard placed behind data
    void *data;       // actual data
    int  allocStatus; // indicates allocation status (0 = free, 1 = allocated)
};

// holds information for a page in the internal memory that consits of
// multiple pages that are not necessarily next to each other
typedef struct memory_page {
    struct memory_page *prev;      // previous page
    size_t size;                   // page size; end = begin + size
    struct memory_page *next;      // next page
    size_t blksize;                // size of a single block
    struct memory_block *blocks[]; // block meta information
};

#ifndef _EMMA_MEMTABLE_SRC_
extern memory_page *memory_table[];
#else
struct memory_page *memory_table[]; // holds all page lists for different sizes
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* MEMTABLE_H */

