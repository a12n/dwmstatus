#include <err.h>
#include <stdio.h>

#include "battery.h"
#include "config.h"
#include "cputemp.h"
#include "loadavg.h"
#include "maildir.h"
#include "time.h"
#ifdef _WITH_UTIME
#   include "utime.h"
#endif  /* _WITH_UTIME */

size_t
config_parse(FILE* file, struct status* status, size_t max_n_status)
{
    char line[384];
    size_t n = 0;

    while (n < max_n_status && fgets(line, sizeof(line), file) != NULL) {
        char s[256];
        double f;

        if (sscanf(line, " battery %lf ", &f) == 1) {
            status[n++] = battery_status(f);
        } else if (sscanf(line, " cputemp %lf ", &f) == 1) {
            status[n++] = cputemp_status(f);
        } else if (sscanf(line, " loadavg %lf ", &f) == 1) {
            status[n++] = loadavg_status(f);
        } else if (sscanf(line, " maildir %lf %255[ -~] ", &f, s) == 2) {
            status[n++] = maildir_status(f, s);
        } else if (sscanf(line, " maildir %lf ", &f) == 1) {
            status[n++] = maildir_status(f, NULL);
        } else if (sscanf(line, " time %lf %255[ -~] ", &f, s) == 2) {
            status[n++] = time_status(f, s);
        } else if (sscanf(line, " time %lf ", &f) == 1) {
            status[n++] = time_status(f, NULL);
#ifdef _WITH_UTIME
        } else if (sscanf(line, " utime %lf %255[ -~] ", &f, s) == 2) {
            status[n++] = utime_status(f, s);
        } else if (sscanf(line, " utime %lf ", &f) == 1) {
            status[n++] = utime_status(f, NULL);
#endif  /* _WITH_UTIME */
        } else {
            warnx("Invalid status descr \"%s\"", line);
        }
    }

    if (ferror(file)) {
        err(1, "Couldn't read config file");
    }

    return n;
}
