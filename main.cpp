#include "battery.hpp"
#include "cpu_temp.hpp"
#include "display.hpp"
#include "file.hpp"
#include "load_avg.hpp"
#include "mail_dir.hpp"
#include "status.hpp"
#include "time.hpp"
#include "unicode_time.hpp"
#include "wlan.hpp"

#include <iostream>
#include <thread>

namespace this_thread = std::this_thread;
using namespace dwmstatus;
using std::cin;

int main()
{
#ifdef DWMSTATUS_WITH_X11
    x11_display dpy;
#else // DWMSTATUS_WITH_X11
    term_display dpy;
#endif // DWMSTATUS_WITH_X11

    auto bar = make_status_bar(cin);

    while (true) {
        const auto t = system_clock::now();

        if (update_status_bar(bar, t)) {
            dpy.set_status(" " + format_status_bar(bar, " • ") + " ");
        }

        this_thread::sleep_until(t + seconds(1));
    }

    return 0;
}
