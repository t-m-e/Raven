#ifndef RAVENSH_DEBUG_DEBUG
#define RAVENSH_DEBUG_DEBUG

#include <stdio.h>

#define DEBUG_ACTIVE
#ifdef DEBUG_ACTIVE
    #define DEBUG(x, ...) printf("[debug] "#x"\n", ##__VA_ARGS__)
#else
    #define DEBUG(x, ...) 
#endif

#endif
