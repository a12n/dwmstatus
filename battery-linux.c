/* License: WTFPL (http://www.wtfpl.net/) */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "battery.h"

struct battery_state
{
    FILE* capacity;
};

void*
battery_alloc(void)
{
    struct battery_state* state;

    state = calloc(1, sizeof(struct battery_state));
    if (state == NULL) {
        err(1, "battery: couldn't allocate state");
    }

    state->capacity = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    if (state->capacity == NULL) {
        err(1, "battery: couldn't open capacity file for BAT0");
    }

    setvbuf(state->capacity, NULL, _IONBF, 0);

    return state;
}

void
battery_free(void* opaque)
{
    struct battery_state* state = (struct battery_state*)opaque;

    fclose(state->capacity);
    free(state);
}

void
battery_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    struct battery_state* state = (struct battery_state*)opaque;
    int capacity = 0;

    (void)now;

    rewind(state->capacity);
    fscanf(state->capacity, "%d", &capacity);
    snprintf(buf, buf_sz, "%3d %%", capacity);
}
