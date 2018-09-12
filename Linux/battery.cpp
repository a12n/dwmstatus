#include <cmath>

#include "battery.hpp"

namespace dwmstatus {

using std::ios_base;

battery_status::battery_status() :
    status(),
    capacity(),
    show_disch(false)
{
    try {
        for (int i = 0; ; ++i) {
            status.push_back(
                pfile("/sys/class/power_supply/BAT" + to_string(i) + "/status"));
            capacity.push_back(
                pfile("/sys/class/power_supply/BAT" + to_string(i) + "/capacity"));
        }
    } catch (const ios_base::failure&) {
        // No more batteries
    }
}

string
battery_status::update(const system_clock::time_point& t)
{
    show_disch = ! show_disch;

    int charging = 0;
    for (auto& s : status) {
        auto c = s.read<string>();
        if (c == "Charging") {
            ++charging;
        } else if (c == "Discharging") {
            --charging;
        }
    }
    if (charging < 0 && show_disch) {
        return "▼▼▼ %";
    } else if (charging > 0 && show_disch) {
        return "▲▲▲ %";
    }

    double current = 0.0;
    double total = 0.0;

    for (auto& c : capacity) {
        current += c.read<double>();
        total += 100.0;
    }

    ostringstream out;

    out.width(3);
    out << static_cast<int>(round(100.0 * current / total)) << " %";

    return out.str();
}

} // namespace dwmstatus
