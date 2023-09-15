#include "display.hpp"
#include "status.hpp"

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

    auto s = make_status_bar(cin);

    while (true) {
        const auto t = system_clock::now();

        if (update_status_bar(s, t)) {
            dpy.set_status(" " + format_status_bar(s, " • ") + " ");
        }

        this_thread::sleep_until(t + seconds(1));
    }

    return 0;
}
