#ifndef __MAILDIR_H_INCLUDED__
#define __MAILDIR_H_INCLUDED__

#include "status.h"

#define MAKE_MAILDIR(_interval, _path)                                  \
    status_make((_interval), maildir_alloc(_path), maildir_free, maildir_update)

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
