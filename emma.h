/* 
 * File:   emma.h
 * Author: Daniel Eder (daniel@deder.at)
 *
 * 
 * Default header file for external interfaces of Emma.
 * 
 */

#ifndef EMMA_H
#define	EMMA_H

// API export
#ifdef _WIN32
  #ifdef EMMA_LIB_EXPORT
    #define EMMA_API __declspec(dllexport)
  #else
    #define EMMA_API __declspec(dllimport)
  #endif
#else
  #define EMMA_API
#endif

#define debug_print(...) \
	do { if (EMMA_DEBUG) fprintf(stderr,  __VA_ARGS__); } while (0)

#include "emma_helper.h"

#define EMMA_SG_LEN 16 // length of the safeguard for memory
#define EMMA_SG "\xba\x5e\xba\x11\xde\xad\xbe\xa7\xba\x5e\xba\x11\xde\xad\xbe\xa7" // TODO make configurable

#ifdef	__cplusplus
extern "C" {
#endif

// allocate new memory. works just like malloc(size_t) but uses
// the internal memory for allocation
EMMA_API void* emma_malloc(size_t size);


#ifdef	__cplusplus
}
#endif

#endif	/* EMMA_H */

