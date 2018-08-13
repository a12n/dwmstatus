/* License: WTFPL (http://www.wtfpl.net/) */

#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "battery.h"
#include "mem.h"
#include "pfile.h"

#define N_BAT 4
#define CAPACITY_PATH "/sys/class/power_supply/BAT?/capacity"
#define ONLINE_PATH "/sys/class/power_supply/AC/online"

struct battery_state
{
    FILE* capacity[N_BAT];
    FILE* online;
    int anim_frame;
};

static void*
battery_alloc(void)
{
    struct battery_state* state;

    state = calloc_err(1, sizeof(struct battery_state));

    state->online = pfile_open_err(ONLINE_PATH);

    int ok = 0;
    for (int i = 0; i < N_BAT; ++i) {
        char path[] = CAPACITY_PATH;
        *strchr(path, '?') = '0' + i;
        state->capacity[i] = pfile_open(path);
        ok = ok || (state->capacity[i] != NULL);
    }
    if (! ok) {
        err(1, "battery: couldn't open capacity file for a battery");
    }

    return state;
}

static void
battery_free(void* opaque)
{
    struct battery_state* state = (struct battery_state*)opaque;

    for (int i = 0; i < N_BAT; ++i) {
        pfile_close(state->capacity[i]);
    }
    pfile_close(state->online);
    free(state);
}

static void
battery_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    struct battery_state* state = (struct battery_state*)opaque;

    (void)now;

    if (! pfile_read_long(state->online)) {
        state->anim_frame = (state->anim_frame + 1) % 2;
        if (state->anim_frame == 0) {
            snprintf(buf, buf_sz, "▼▼▼ %%");
            return;
        }
    }

    long capacity = 0;
    long total = 0;
    for (int i = 0; i < N_BAT; ++i) {
        if (state->capacity[i] != NULL) {
            capacity += pfile_read_long(state->capacity[i]);
            total += 100;
        }
    }
    snprintf(buf, buf_sz, "%3ld %%", (long)round(100.0 * (double)capacity / (double)total));
}

struct status
battery_status(double interval)
{
    return status_make(interval, battery_alloc(), battery_free, battery_update);
}
