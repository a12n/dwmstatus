#ifndef __LOADAVG_H_INCLUDED__
#define __LOADAVG_H_INCLUDED__

#include "status.h"

#define loadavg_make(_interval)                             \
    status_make((_interval), NULL, NULL, loadavg_update)

void
loadavg_update(void* opaque, time_t now, char* buf, size_t buf_sz)
#ifdef __GNUC__
    __attribute__((nonnull(3)))
#endif  /* __GNUC__ */
    ;

#endif  /* __LOADAVG_H_INCLUDED__ */
