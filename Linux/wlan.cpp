#include "wlan.hpp"

#include "blocks.hpp"
#include "color.hpp"
#include "file.hpp"
#include "icons.hpp"

#include <cmath>

namespace dwmstatus {

wlan_status::wlan_status(const string& iface)
    : iface { iface }
    , wireless { open_unbuf("/proc/net/wireless") }
{
}

wlan_status::wlan_status(istream& conf)
    : wlan_status(read_value<string>(conf).value_or(""))
{
}

string wlan_status::update(system_clock::time_point)
{
    double quality = -1;

    rewind(wireless);
    skip_line(wireless, 2);

    while (const auto line_opt = read_line(wireless)) {
        istringstream line { line_opt.value() };

        auto name = read_value<string>(line).value_or(":");
        name.pop_back();     // Trim ':' at the end of interface name.

        if (iface.empty()) {
            // Interface wasn't specified, use the first one.
            iface = name;
        }

        if (iface == name) {
            // Found entry for the interface.
            skip_value<int>(line);
            quality = read_value<double>(line).value_or(0.0) / 70;
            break;
        }
    }

    ostringstream output;

    if (quality < 0) {
        output << color::fg::white;
    } else if (quality < 0.25) {
        output << color::fg::red;
    } else if (quality < 0.50) {
        output << color::fg::yellow;
    }
    output << icons::awesome::wifi << ' ';
    if (quality < 0) {
        output << "---";
    } else {
        output.width(3);
        output << static_cast<int>(round(100 * quality));
    }
    output << " %"
           << color::reset;

    return output.str();
}

} // namespace dwmstatus
