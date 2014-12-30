#include <stdlib.h>

#include "time.h"

void
time_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    const char* format = (const char*)opaque;

    strftime(buf, buf_sz, format, localtime(&now));
}
