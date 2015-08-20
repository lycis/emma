/* 
 * File:   emma_helper.h
 * Author: Daniel Eder (daniel@deder.at)
 *
 * Created on 19. August 2015, 13:48
 * 
 * !!! INTERNAL ONLY !!!
 * 
 * contains helper functions for the lib
 * 
 * this code is usually not exposed to public
 * 
 */

#ifndef EMMA_HELPER_H
#define	EMMA_HELPER_H

#include <stdlib.h>
#include "emma.h"

#ifdef	__cplusplus
extern "C" {
#endif

// provide the next greater power of 2 or n if n == power of 2
size_t EMMA_API emma_nextp2(size_t);

// find the log 2 base of a number
int EMMA_API emma_log2(size_t);


#ifdef	__cplusplus
}
#endif

#endif	/* EMMA_HELPER_H */

