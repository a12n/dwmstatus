#include <err.h>

#include "mem.h"

void*
calloc_err(size_t nmemb, size_t size)
{
    void* ans;
    ans = calloc(nmemb, size);
    if (ans == NULL) {
        err(1, NULL);
    }
    return ans;
}
