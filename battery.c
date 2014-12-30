#include <sys/ioctl.h>
#include <sys/param.h>

#include <machine/apmvar.h>

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "battery.h"

struct battery_state
{
    int apm_fd;
};

void*
battery_alloc(void)
{
    struct battery_state* state;

    state = calloc(1, sizeof(struct battery_state));
    if (state == NULL) {
        err(1, "battery: couldn't allocate state");
    }

    state->apm_fd = open("/dev/apm", O_RDONLY);
    if (state->apm_fd == -1) {
        err(1, "battery: couldn't open APM device");
    }

    return state;
}

void
battery_free(void* opaque)
{
    struct battery_state* state = (struct battery_state*)opaque;

    close(state->apm_fd);
    free(state);
}

void
battery_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    struct apm_power_info reply;
    struct battery_state* state = (struct battery_state*)opaque;

    if (ioctl(state->apm_fd, APM_IOC_GETPOWER, &reply) == 0) {
        if (reply.minutes_left != -1) {
            snprintf(buf, buf_sz, "%3d min", reply.minutes_left);
        } else {
            snprintf(buf, buf_sz, "%5d %%", reply.battery_life);
        }
    }

}
