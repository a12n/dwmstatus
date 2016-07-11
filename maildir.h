/* License: WTFPL (http://www.wtfpl.net/) */

#ifndef __MAILDIR_H_INCLUDED__
#define __MAILDIR_H_INCLUDED__

#include "status.h"

struct status
maildir_status(double interval, const char* path)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __MAILDIR_H_INCLUDED__ */
