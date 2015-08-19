/* 
 * File:   emma.h
 * Author: Daniel Eder (daniel@deder.at)
 *
 * Created on 19. August 2015, 12:26
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

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* EMMA_H */

