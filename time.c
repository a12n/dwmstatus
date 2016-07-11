/* License: WTFPL (http://www.wtfpl.net/) */

#include <stdlib.h>
#include <string.h>

#include "time.h"

void
time_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    const char* format = (const char*)opaque;

    strftime(buf, buf_sz, format, localtime(&now));
}

struct status
time_make(double interval, const char* format)
{
    return status_make(interval, strdup(format), free, time_update);
}
