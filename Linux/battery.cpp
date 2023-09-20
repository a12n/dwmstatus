#include "battery.hpp"

#include "blocks.hpp"
#include "color.hpp"
#include "file.hpp"

#include <cmath>

namespace dwmstatus {

using std::ios_base;
using std::setw;

battery_status::battery::battery(const string& dir_path)
    : status { open_unbuf(dir_path + "/status") }
    , capacity { open_unbuf(dir_path + "/capacity") }
{
}

short battery_status::battery::charging()
{
    const auto s = reread_value<string>(status).value_or("");
    if (s == "Discharging") {
        return -1;
    } else if (s == "Charging") {
        return 1;
    } else {
        return 0;
    }
}

battery_status::battery_status()
{
    try {
        for (int i = 0;; ++i) {
            batteries.emplace_back("/sys/class/power_supply/BAT" + to_string(i));
        }
    } catch (const ios_base::failure&) {
        // No more batteries
    }
}

string battery_status::update(system_clock::time_point)
{
    auto charging = 0;
    auto capacity = 0.0;

    for (auto& b : batteries) {
        charging += b.charging();
        capacity += reread_value<double>(b.capacity).value_or(0.0);
    }

    const auto pct = capacity / (100.0 * batteries.size());

    ostringstream output;

    if (pct < 0.15) {
        output << color::fg::red;
    } else if (charging > 0) {
        output << color::fg::green;
    } else if (charging < 0) {
        output << color::fg::yellow;
    }

    output << setw(3) << static_cast<int>(round(100.0 * pct)) << " %";

    output << color::reset;

    return output.str();
}

} // namespace dwmstatus
