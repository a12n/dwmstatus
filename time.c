#include <stdlib.h>

#include "time.h"

void
time_update(void* state, time_t now, char* buf, size_t buf_sz)
{
    const char* format = (const char*)state;

    strftime(buf, buf_sz, format, localtime(&now));
}
