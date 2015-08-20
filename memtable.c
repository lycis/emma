#define _EMMA_MEMTABLE_SRC_
#include "memtable.h"
#include "emma_helper.h"

#include <string.h>

void init_memory_table(size_t blkSize)
{
    int base;
    
    base = emma_log2(blkSize);
    
    if(memory_table == 0) {
        // init list
        memory_table = calloc(base, sizeof(memory_page*));
    } else if(memory_table_len < base) {
        // enlarge list
        memory_table = realloc(memory_table, base*sizeof(memory_page*));
        memset(memory_table+(memory_table_len+1), 
               0, 
               (base-memory_table_len)*sizeof(memory_page*));
    }
    
    memory_table_len = base;
}