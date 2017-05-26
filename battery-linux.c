/* License: WTFPL (http://www.wtfpl.net/) */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "battery.h"

#define CAPACITY_PATH "/sys/class/power_supply/BAT0/capacity"

struct battery_state
{
    FILE* capacity;
};

static void*
battery_alloc(void)
{
    struct battery_state* state;

    state = calloc(1, sizeof(struct battery_state));
    if (state == NULL) {
        err(1, "battery: couldn't allocate state");
    }

    state->capacity = fopen(CAPACITY_PATH, "r");
    if (state->capacity == NULL) {
        err(1, "battery: couldn't open capacity file for BAT0");
    }

    setvbuf(state->capacity, NULL, _IONBF, 0);

    return state;
}

static void
battery_free(void* opaque)
{
    struct battery_state* state = (struct battery_state*)opaque;

    fclose(state->capacity);
    free(state);
}

static void
battery_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    struct battery_state* state = (struct battery_state*)opaque;
    int capacity = 0;

    (void)now;

    state->capacity = freopen(CAPACITY_PATH, "r", state->capacity);
    fscanf(state->capacity, "%d", &capacity);
    snprintf(buf, buf_sz, "%3d %%", capacity);
}

struct status
battery_status(double interval)
{
    return status_make(interval, battery_alloc(), battery_free, battery_update);
}
