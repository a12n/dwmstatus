/* License: WTFPL (http://www.wtfpl.net/) */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "battery.h"

struct battery_state
{
    /* TODO */
};

void*
battery_alloc(void)
{
    struct battery_state* state;

    state = calloc(1, sizeof(struct battery_state));
    if (state == NULL) {
        err(1, "battery: couldn't allocate state");
    }

    /* TODO */

    return state;
}

void
battery_free(void* opaque)
{
    struct battery_state* state = (struct battery_state*)opaque;

    /* TODO */

    free(state);
}

void
battery_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    /* TODO */
    (void)opaque;
    (void)now;

    snprintf(buf, buf_sz, "N/A");
}
