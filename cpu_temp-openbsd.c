/* License: WTFPL (http://www.wtfpl.net/) */

#include <stdio.h>

#include "cpu_temp.h"

static void
cpu_temp_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    FILE* pipe;

    (void)opaque;
    (void)now;

    pipe = popen("sysctl hw.sensors.cpu0", "r");
    if (pipe != NULL) {
        float temp;

        if (fscanf(pipe, "hw.sensors.cpu0.temp0=%f degC", &temp) == 1) {
            snprintf(buf, buf_sz, "%2.0f °C", temp);
        }
        pclose(pipe);
    }
}

struct status
cpu_temp_status(double interval)
{
    return status_make(interval, NULL, NULL, cpu_temp_update);
}
