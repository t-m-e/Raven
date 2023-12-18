#include "rsh_string.h"

/* string length */
size_t rsh_strlen(
    char* data,
    size_t size
) {
    if (size == 0) return 0;

    size_t len = 0;
    while (data[len] != 0) {
        if (len >= size) break;
        len++;
    }

    return len;
}

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
) {
    if (size == 0) return RSH_STRCMP_ERR;

    for (size_t i = 0; i < size; i++) {
        if (i >= size) break;
        if (a[i] < b[i]) return RSH_STRCMP_LT;
        if (a[i] > b[i]) return RSH_STRCMP_GT;
    }

    return RSH_STRCMP_EQ;
}

/* string copy */
void rsh_strcpy(
    char* a, 
    char* b,
    size_t size
) {
    if (size == 0) return;

    for (size_t i = 0; i < size; i++) {
        a[i] = b[i];
    }
}

/* string set */
void rsh_strset(
    char* str,
    size_t count,
    char c
) {
    if (count == 0) return;

    for (size_t i = 0; i < count; i++) {
        str[i] = c;
    }
}
