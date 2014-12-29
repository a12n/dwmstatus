#ifndef __TIME_H_INCLUDED__
#define __TIME_H_INCLUDED__

#include "status.h"

#define MAKE_TIME(_interval, _format)                       \
    MAKE_STATUS((_interval), (_format), NULL, time_update)

void
time_update(void* state, time_t now, char* buf, size_t buf_sz)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __TIME_H_INCLUDED__ */
