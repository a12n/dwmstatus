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

int main()
{
    using namespace dwmstatus;
    using namespace std::chrono;
    using namespace std;

    try {
        display_ptr display = make_unique<dwmstatus::stdout>();
        status_ptr status = make_unique<dwmstatus::time>();

        {
#include "config.inc"
        }

        if (!display) {
            throw invalid_argument("unspecified display in configuration");
        }
        if (!status) {
            throw invalid_argument("unspecified status in configuration");
        }

        while (true) {
            const auto t = system_clock::now();

            if (const auto s = status->update(t); s) {
                display->set_status(s.value());
            }

            this_thread::sleep_until(t + seconds(1));
        }
    } catch (const exception& err) {
        cerr << err.what() << endl;
        return 1;
    }

    return 0;
}
