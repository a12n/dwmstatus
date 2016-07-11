/* License: WTFPL (http://www.wtfpl.net/) */

#include <string.h>

#include "status.h"

struct status
status_make(double interval, void* state, void (*free)(void*),
            void (*update)(void*, time_t, char*, size_t))
{
    struct status ans = { interval, state, free, update, 0, "" };
    return ans;
}

char*
status_concat_all(const struct status* status, size_t n_status,
                  char* ans, size_t ans_sz, const char* sep)
{
    size_t i;

    /* TODO: Check ans_sz */
    (void)ans_sz;

    for (i = 0; i < n_status; i++) {
        if (i != 0) {
            strcat(ans, sep);
        }
        strcat(ans, status[i].buf);
    }
    return ans;
}

void
status_free(struct status* status)
{
    if (status->free != NULL) {
        status->free(status->state);
        status->state = NULL;
    }
}

void
status_free_all(struct status* status, size_t n_status)
{
    size_t i;

    for (i = 0; i < n_status; i++) {
        status_free(&status[i]);
    }
}

int
status_update(struct status* status, time_t now)
{
    if (difftime(now, status->last) >= status->interval) {
        if (status->update != NULL) {
            status->update(status->state, now, status->buf, sizeof(status->buf));
        }
        status->last = now;
        return 1;
    }
    return 0;
}

int
status_update_all(struct status* status, size_t n_status, time_t now)
{
    int changed = 0;
    size_t i;

    for (i = 0; i < n_status; i++) {
        if (status_update(&status[i], now)) {
            changed = 1;
        }
    }
    return changed;
}
