/* License: WTFPL (http://www.wtfpl.net/) */

#include <stdio.h>
#include <stdlib.h>

#include "cputemp.h"
#include "mem.h"
#include "pfile.h"

struct cputemp_state
{
    FILE* temp;
};

static void*
cputemp_alloc(void)
{
    struct cputemp_state* state;

    state = calloc_err(1, sizeof(struct cputemp_state));
    state->temp = pfile_open_err("/sys/class/hwmon/hwmon0/temp1_input");

    return state;
}

static void
cputemp_free(void* opaque)
{
    struct cputemp_state* state = (struct cputemp_state*)opaque;

    pfile_close(state->temp);
    free(state);
}

static void
cputemp_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    struct cputemp_state* state = (struct cputemp_state*)opaque;

    (void)now;

    snprintf(buf, buf_sz, "%2.0lf °C", pfile_read_double(state->temp) / 1000.0);
}

struct status
cputemp_status(double interval)
{
    return status_make(interval, cputemp_alloc(), cputemp_free, cputemp_update);
}
