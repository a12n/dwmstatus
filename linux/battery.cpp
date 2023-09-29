#include "battery.hpp"

#include "blocks.hpp"
#include "color.hpp"
#include "file.hpp"
#include "icons.hpp"

#include <cmath>

namespace dwmstatus {

using std::ios_base;

battery::files::files(const string& dir_path)
    : status_ { open_unbuf(dir_path + "/status") }
    , capacity_ { open_unbuf(dir_path + "/capacity") }
{
}

double battery::files::capacity()
{
    return reread_value<double>(capacity_).value_or(0.0);
}

int battery::files::charging()
{
    const auto s = reread_value<string>(status_).value_or("");
    if (s == "Discharging") {
        return -1;
    } else if (s == "Charging") {
        return 1;
    } else {
        return 0;
    }
}

battery::battery()
{
    try {
        for (int i = 0;; ++i) {
            bats_.emplace_back("/sys/class/power_supply/BAT" + to_string(i));
        }
    } catch (const ios_base::failure&) {
        // No more batteries.
    }
}

optional<string> battery::update(system_clock::time_point)
{
    double total_cap = 0.0;
    int net_charg = 0;

    for (auto& b : bats_) {
        total_cap += b.capacity();
        net_charg += b.charging();
    }

    const auto pct = total_cap / (100.0 * bats_.size());

    ostringstream out;

    if (pct < 0.15) {
        out << color::fg::red;
    } else if (net_charg > 0) {
        out << color::fg::green;
    } else if (net_charg < 0) {
        out << color::fg::yellow;
    }
    out << blocks::choose(icons::awesome::battery, pct) << ' '
        << static_cast<int>(round(100 * pct)) << " %"
        << color::reset;

    return out.str();
}

} // namespace dwmstatus
