#ifndef __LOADAVG_H_INCLUDED__
#define __LOADAVG_H_INCLUDED__

#include "status.h"

#define MAKE_LOADAVG(_interval)                             \
    MAKE_STATUS((_interval), NULL, NULL, loadavg_update)

void
loadavg_update(void* state, time_t now, char* buf, size_t buf_sz)
#ifdef __GNUC__
    __attribute__((nonnull(3)))
#endif  /* __GNUC__ */
    ;

#endif  /* __LOADAVG_H_INCLUDED__ */
