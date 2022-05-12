#include <cmath>

#include "battery.hpp"
#include "blocks.hpp"

namespace dwmstatus {

using std::ios_base;

battery_status::battery::battery(const string& dir_path) :
    status{dir_path + "/status"},
    capacity{dir_path + "/capacity"}
{
}

short
battery_status::battery::charging()
{
    const auto s{status.reread_value<string>().value_or("")};
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
        for (int i{0}; ; ++i) {
            batteries.emplace_back("/sys/class/power_supply/BAT" + to_string(i));
        }
    } catch (const ios_base::failure&) {
        // No more batteries
    }
}

string
battery_status::update(system_clock::time_point)
{
    auto charging{0};
    auto capacity{0.0};

    for (auto& b : batteries) {
        charging += b.charging();
        capacity += b.capacity.reread_value<double>().value_or(0.0);
    }

    const auto pct{capacity / (100.0 * batteries.size())};

    ostringstream out;

#ifdef DWMSTATUS_WITH_COLOR
    if (pct < 0.15) {
        out << "\033[31m";
    } else if (charging > 0) {
        out << "\033[32m";
    } else if (charging < 0) {
        out << "\033[33m";
    }
#endif  // DWMSTATUS_WITH_COLOR

    out << choose_block({ "", "", "", "", "" }, pct);

#ifdef DWMSTATUS_WITH_COLOR
    out << "\033[0m";
#endif  // DWMSTATUS_WITH_COLOR

    return out.str();
}

} // namespace dwmstatus
