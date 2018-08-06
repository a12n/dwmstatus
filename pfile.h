#pragma once

#ifndef __PFILE_H_INCLUDED__
#define __PFILE_H_INCLUDED__

#include <stdio.h>

FILE*
pfile_open(const char* pathname)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

FILE*
pfile_open_err(const char* pathname)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

void
pfile_close(FILE* pf);

double
pfile_read_double(FILE* pf)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

long
pfile_read_long(FILE* pf)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __PFILE_H_INCLUDED__ */
