/* License: WTFPL (http://www.wtfpl.net/) */

#ifndef __TIME_H_INCLUDED__
#define __TIME_H_INCLUDED__

#include <stdlib.h>
#include <string.h>

#include "status.h"

#define time_make(_interval, _format)                               \
    status_make((_interval), strdup(_format), free, time_update)

void
time_update(void* opaque, time_t now, char* buf, size_t buf_sz)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __TIME_H_INCLUDED__ */
