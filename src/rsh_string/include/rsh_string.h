#ifndef RAVENSH_RSH_STRING
#define RAVENSH_RSH_STRING

#include <stddef.h>

/* strcmp enum */
enum {
    RSH_STRCMP_LT = -1,
    RSH_STRCMP_EQ = 0,
    RSH_STRCMP_GT = 1,
    RSH_STRCMP_ERR = -2
};

/* string length */
size_t rsh_strlen(
    char* data,
    size_t size
);

/* string comparison 
 * @return
 *      RSH_STRCMP_LT == a < b
 *      RSH_STRCMP_EQ == a = b
 *      RSH_STRCMP_GT == a > b
 *      RSH_STRCMP_ERR == size = 0
 */
int rsh_strcmp(
    char* a,
    char* b,
    size_t size
);

/* string copy */ 
void rsh_strcpy(
    char* a, 
    char* b,
    size_t size
);

/* string set */
void rsh_strset(
    char* str,
    size_t count,
    char c
);

#endif
