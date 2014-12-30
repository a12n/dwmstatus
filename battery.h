#ifndef __BATTERY_H_INCLUDED__
#define __BATTERY_H_INCLUDED__

#include "status.h"

#define MAKE_BATTERY(_interval)                                         \
    MAKE_STATUS((_interval), battery_make(), battery_free, battery_update)

void
battery_free(void* opaque)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

void*
battery_make(void)
#ifdef __GNUC__
    __attribute__((malloc, warn_unused_result))
#endif  /* __GNUC__ */
    ;

void
battery_update(void* opaque, time_t now, char* buf, size_t buf_sz)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __BATTERY_H_INCLUDED__ */