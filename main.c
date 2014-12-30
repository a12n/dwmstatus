#include <err.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include "battery.h"
#include "loadavg.h"
#include "maildir.h"
#include "status.h"
#include "time.h"

int
main(void)
{
    Display* display;

#include "config.h"
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
