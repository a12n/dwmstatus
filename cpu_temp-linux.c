/* License: WTFPL (http://www.wtfpl.net/) */

#include <stdio.h>

#include "cpu_temp.h"

void
cpu_temp_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    (void)opaque;
    (void)now;

    /* TODO */

    snprintf(buf, buf_sz, "N/A");
}
