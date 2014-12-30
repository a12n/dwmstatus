/* License: WTFPL (http://www.wtfpl.net/) */

#ifndef __STATUS_H_INCLUDED__
#define __STATUS_H_INCLUDED__

#include <time.h>

struct status
{
    double interval;

    void* state;

    void (*free)(void*);
    void (*update)(void*, time_t, char*, size_t);

    time_t last;
    char buf[256];
};

#define status_make(_interval, _state, _free, _update)      \
    { (_interval), (_state), (_free), (_update), 0, "" }

char*
status_concat_all(const struct status* status, size_t n_status,
                  char* ans, size_t ans_sz, const char* sep)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

void
status_free(struct status* status);

void
status_free_all(struct status* status, size_t n_status)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

int
status_update(struct status* status, time_t now)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

int
status_update_all(struct status* status, size_t n_status, time_t now)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __STATUS_H_INCLUDED__ */
