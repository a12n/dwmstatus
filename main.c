/* License: WTFPL (http://www.wtfpl.net/) */

#include <err.h>
#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "loadavg.h"
#include "status.h"
#include "time.h"

#if !defined(_NO_X11)

#include <X11/Xlib.h>

Display* display;

static void
init(void)
{
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        errx(1, "Couldn't open display");
    }
}

static void
set_status(const char* str)
{
    XStoreName(display, DefaultRootWindow(display), str);
    XSync(display, False);
}

#else  /* !defined(_NO_X11) */

#include <stdio.h>

static void
init(void)
{
}

static void
set_status(const char* str)
{
    puts(str);
}

#endif /* !defined(_NO_X11) */

#ifndef MAX_N_STATUS
#   define MAX_N_STATUS 16
#endif  /* MAX_N_STATUS */

int
main(int argc, char** argv)
{
    struct status status[MAX_N_STATUS];
    size_t n_status = 0;

    if (argc > 1) {
        FILE* config;

        config = fopen(argv[1], "r");
        if (config != NULL) {
            n_status = config_parse(config, status, MAX_N_STATUS);
            fclose(config);
        } else {
            err(1, "Couldn't open config file \"%s\"", argv[1]);
        }
    } else {
        status[n_status++] = loadavg_status(3.0);
        status[n_status++] = time_status(1.0, NULL);
    }

    init();

    while (1) {
        if (status_update_all(status, n_status, time(NULL))) {
            char buf[4096] = "\0";

            status_concat_all(status, n_status, buf, sizeof(buf), " • ");

            set_status(buf);
        }
        sleep(1);
    }

    return 0;
}
