/* 
 * File:   main.c
 * Author: edd
 *
 * Created on 20. August 2015, 21:28
 */

#include <stdio.h>
#include <stdlib.h>
#include "emma.h"

#define TEST(x) total++; \
                printf("%-30s", #x); \
                if(!x()) { \
                  ok++; \
                  printf("ok\n"); \
                } else { \
                  nok++; \
                  printf("failed\n"); \
                }

#define RET_TEST_OK   0
#define RET_TEST_FAIL 1

#define TEST_CASE_BEGIN(x) int x() {
#define TEST_CASE_END }

int total, ok, nok;

// get next power of 2 for 0
TEST_CASE_BEGIN(emma_nextp2_0)
if(emma_nextp2(0) != 1) return RET_TEST_FAIL;
return RET_TEST_OK;
TEST_CASE_END

// get next power of 2 for 1        
TEST_CASE_BEGIN(emma_nextp2_1)
if(emma_nextp2(1) != 1) return RET_TEST_FAIL;
return RET_TEST_OK;
TEST_CASE_END
        
// get next power of 2 for 100000        
TEST_CASE_BEGIN(emma_nextp2_100000)
if(emma_nextp2(100000) != 131072) return RET_TEST_FAIL;
return RET_TEST_OK;
TEST_CASE_END
        

/*
 * 
 */
int main(int argc, char** argv) {    
    total = 0;
    ok = 0;
    nok = 0;
    
    // place tests here
    TEST(emma_nextp2_0);
    TEST(emma_nextp2_1);
    TEST(emma_nextp2_100000);
    
    // print statistics
    printf("Total: %i Success: %i Failed: %i\n", total, ok, nok);
    
    if(nok == 0)
        return (EXIT_SUCCESS);
    
    return EXIT_FAILURE;
}