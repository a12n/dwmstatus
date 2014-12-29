#include <err.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include "loadavg.h"
#include "status.h"

int
main(void)
{
    Display* display;

    struct status status[] = {
        MAKE_LOADAVG(3.0)
    };
    const size_t n_status = sizeof(status) / sizeof(status[0]);

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        errx(1, "Couldn't open display");
    }

    while (1) {
        if (status_update_all(status, n_status, time(NULL))) {
            char buf[4096] = "\0";

            status_concat_all(status, n_status, buf, sizeof(buf), " • ");

            XStoreName(display, DefaultRootWindow(display), buf);
            XSync(display, False);
        }
        sleep(1);
    }

    return 0;
}
