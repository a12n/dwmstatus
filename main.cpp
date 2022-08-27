#include "config.hpp"
#include "display.hpp"

#include <iostream>
#include <thread>

namespace this_thread = std::this_thread;
using namespace dwmstatus;
using std::cin;

int main()
{
#ifdef DWMSTATUS_WITH_X11
    x11_display display;
#else // DWMSTATUS_WITH_X11
    term_display display;
#endif // DWMSTATUS_WITH_X11

    auto& conf = cin;
    auto status = read_config(conf);

    while (true) {
        const auto t = system_clock::now();

        if (update(status, t)) {
            display.set_status(" " + format(status, " • ") + " ");
        }

        this_thread::sleep_until(t + seconds(1));
    }

    return 0;
}
