/* License: WTFPL (http://www.wtfpl.net/) */

#include <stdio.h>
#include <stdlib.h>

#include "loadavg.h"

static void
loadavg_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    double loadavg[3];

    (void)opaque;
    (void)now;

    getloadavg(loadavg, 3);
    snprintf(buf, buf_sz, "%.2f %.2f %.2f",
             loadavg[0], loadavg[1], loadavg[2]);
}

struct status
loadavg_make(double interval)
{
    return status_make(interval, NULL, NULL, loadavg_update);
}
