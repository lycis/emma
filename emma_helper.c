#include "emma_helper.h"
#include <stdio.h>

size_t emma_nextp2(size_t v) {
    if (v == 0) {
        return 1;
    }

    if (v && !(v & (v - 1))) {
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

size_t emma_log2(size_t v) {
    size_t r; // result goes here

#if __i386__
    static const int MultiplyDeBruijnBitPosition[32] = {
          0,  9,  1, 10, 13, 21,  2, 29,
         11, 14, 16, 18, 22, 25,  3, 30,
          8, 12, 20, 28, 15, 17, 24,  7,
         19, 27, 23,  6, 26,  5,  4, 3
    }
#elif __x86_64__
    static const int MultiplyDeBruijnBitPosition[64] = {
        63,  0, 58,  1, 59, 47, 53,  2,
        60, 39, 48, 27, 54, 33, 42,  3,
	61, 51, 37, 40, 49, 18, 28, 20,
	55, 30, 34, 11, 43, 14, 22,  4,
	62, 57, 46, 52, 38, 26, 32, 41,
	50, 36, 17, 19, 29, 10, 13, 21,
	56, 45, 25, 31, 35, 16,  9, 12,
	44, 24, 15,  8, 23,  7,  6,  5
# else
#error arch not supported
#endif
    };

    v |= v >> 1; // first round down to one less than a power of 2 
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
#ifdef __x86_64__
    v |= v >> 32;
#endif

#ifdef __i486__
    r = MultiplyDeBruijnBitPosition[(size_t) (v * 0x07C4ACDD) >> 27];
#elif __x86_64__
    r = MultiplyDeBruijnBitPosition[((size_t)((v - (v >> 1))*0x07EDD5E59A4E28C2)) >> 58];
#endif

    return r;
}
