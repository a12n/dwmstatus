/* License: WTFPL (http://www.wtfpl.net/) */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "cputemp.h"

struct cputemp_state
{
    FILE* temp;
};

static void*
cputemp_alloc(void)
{
    struct cputemp_state* state;

    state = calloc(1, sizeof(struct cputemp_state));
    if (state == NULL) err(1, "cputemp: couldn't allocate state");

    state->temp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (state->temp == NULL) err(1, "cputemp: couldn't open temp file");

    setvbuf(state->temp, NULL, _IONBF, 0);

    return state;
}

static void
cputemp_free(void* opaque)
{
    struct cputemp_state* state = (struct cputemp_state*)opaque;

    fclose(state->temp);
    free(state);
}

static void
cputemp_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    struct cputemp_state* state = (struct cputemp_state*)opaque;
    float temp = 0.0f;

    (void)now;

    rewind(state->temp);
    fscanf(state->temp, "%f", &temp);
    snprintf(buf, buf_sz, "%2.0f °C", temp / 1000.0f);
}

struct status
cputemp_status(double interval)
{
    return status_make(interval, cputemp_alloc(), cputemp_free, cputemp_update);
}
