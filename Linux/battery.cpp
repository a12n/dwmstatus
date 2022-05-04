#include <cmath>

#include "battery.hpp"

namespace dwmstatus {

using std::ios_base;

battery_status::battery_status()
{
    try {
        for (int i{0}; ; ++i) {
            status.emplace_back("/sys/class/power_supply/BAT" + to_string(i) + "/status");
            capacity.emplace_back("/sys/class/power_supply/BAT" + to_string(i) + "/capacity");
        }
    } catch (const ios_base::failure&) {
        // No more batteries
    }
}

string
battery_status::update(system_clock::time_point)
{
    int charging{0};
    for (auto& s : status) {
        auto c{s.rewind().read_value<string>().value_or("")};
        if (c == "Charging") {
            ++charging;
        } else if (c == "Discharging") {
            --charging;
        }
    }

    auto current{0.0};
    auto total{0.0};

    for (auto& c : capacity) {
        current += c.rewind().read_value<double>().value_or(0.0);
        total += 100.0;
    }

    const auto pct{current / total};

    ostringstream out;

    out.width(3);
    out << static_cast<int>(round(100.0 * pct)) << ' ';
    if (charging < 0) {
        out << "▼";
    } else if (charging > 0) {
        out << "▲";
    } else {
        out << '%';
    }

    return out.str();
}

} // namespace dwmstatus
