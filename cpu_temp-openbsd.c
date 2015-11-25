/* License: WTFPL (http://www.wtfpl.net/) */

#include <stdio.h>

#include "cpu_temp.h"

void
cpu_temp_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    FILE* pipe;

    pipe = popen("sysctl hw.sensors.cpu0", "r");
    if (pipe != NULL) {
        float temp;

        if (fscanf(pipe, "hw.sensors.cpu0.temp0=%f degC", &temp) == 1) {
            snprintf(buf, buf_sz, "%2.0f °", temp);
        }
        pclose(pipe);
    }
}
