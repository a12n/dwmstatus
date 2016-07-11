#pragma once

#ifndef __CONFIG_H_INCLUDED__
#define __CONFIG_H_INCLUDED__

#include "status.h"

void
config_parse(FILE* file, struct status* status, size_t* n_status)
#ifdef __GNUC__
    __attribute__((nonnull))
#endif  /* __GNUC__ */
    ;

#endif  /* __CONFIG_H_INCLUDED__ */
