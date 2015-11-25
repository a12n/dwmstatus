/* License: WTFPL (http://www.wtfpl.net/) */

#include <err.h>
#include <unistd.h>

#include "battery.h"
#include "loadavg.h"
#include "maildir.h"
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

int
main(void)
{
#include "config.h"
    const size_t n_status = sizeof(status) / sizeof(status[0]);

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
