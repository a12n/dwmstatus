/* License: WTFPL (http://www.wtfpl.net/) */

#ifndef __CPU_TEMP_H_INCLUDED__
#define __CPU_TEMP_H_INCLUDED__

#include "status.h"

#define cpu_temp_make(_interval)                            \
    status_make((_interval), NULL, NULL, cpu_temp_update)

void
cpu_temp_update(void* opaque, time_t now, char* buf, size_t buf_sz)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __CPU_TEMP_H_INCLUDED__ */
