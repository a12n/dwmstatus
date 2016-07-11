/* License: WTFPL (http://www.wtfpl.net/) */

#ifndef __MAILDIR_H_INCLUDED__
#define __MAILDIR_H_INCLUDED__

#include "status.h"

struct status
maildir_make(double interval, const char* path)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

void*
maildir_alloc(const char* path)
#ifdef __GNUC__
    __attribute__((malloc, nonnull, warn_unused_result))
#endif  /* __GNUC__ */
    ;

void
maildir_free(void* opaque)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

void
maildir_update(void* opaque, time_t now, char* buf, size_t buf_sz)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __MAILDIR_H_INCLUDED__ */
