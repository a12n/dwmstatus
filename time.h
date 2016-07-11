/* License: WTFPL (http://www.wtfpl.net/) */

#ifndef __TIME_H_INCLUDED__
#define __TIME_H_INCLUDED__

#include "status.h"

struct status
time_make(double interval, const char* format)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

void
time_update(void* opaque, time_t now, char* buf, size_t buf_sz)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __TIME_H_INCLUDED__ */
