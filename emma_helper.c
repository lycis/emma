#include "emma_helper.h"

size_t nextp2(size_t v)
{
    if(v == 0)
    {
        return 1;
    }
    
    if(v && !(v & (v - 1)))
    {
        return v;
    }
    
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    
    return v;
}
