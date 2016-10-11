/* License: WTFPL (http://www.wtfpl.net/) */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu_temp.h"

struct cpu_temp_state
{
    FILE* temp;
};

static void*
cpu_temp_alloc(void)
{
    struct cpu_temp_state* state;

    state = calloc(1, sizeof(struct cpu_temp_state));
    if (state == NULL) err(1, "cpu_temp: couldn't allocate state");

    state->temp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (state->temp == NULL) err(1, "cpu_temp: couldn't open temp file");

    setvbuf(state->temp, NULL, _IONBF, 0);

    return state;
}

static void
cpu_temp_free(void* opaque)
{
    struct cpu_temp_state* state = (struct cpu_temp_state*)opaque;

    fclose(state->temp);
    free(state);
}

static void
cpu_temp_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    struct cpu_temp_state* state = (struct cpu_temp_state*)opaque;
    float temp = 0.0f;

    (void)now;

    rewind(state->temp);
    fscanf(state->temp, "%f", &temp);
    snprintf(buf, buf_sz, "%2.0f °C", temp / 1000.0f);
}

struct status
cpu_temp_status(double interval)
{
    return status_make(interval, cpu_temp_alloc(), cpu_temp_free, cpu_temp_update);
}
