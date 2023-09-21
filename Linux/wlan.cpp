#include "wlan.hpp"

#include "blocks.hpp"
#include "color.hpp"
#include "file.hpp"
#include "icons.hpp"

#include <cmath>
#include <cstring>

#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/wireless.h>

namespace dwmstatus {

wlan_status::wlan_status(const string& iface)
    : iface { iface }
    , wireless { open_unbuf("/proc/net/wireless") }
    , iwreq_fd { socket(AF_INET, SOCK_DGRAM, 0) }
{
    if (iwreq_fd < 0) {
        throw runtime_error("couldn't open socket");
    }
}

wlan_status::wlan_status(istream& conf)
    : wlan_status(read_value<string>(conf).value_or(""))
{
}

string wlan_status::update(system_clock::time_point)
{
    const double pct = quality();

    ostringstream output;

    if (pct < 0) {
        output << color::fg::white;
    } else if (pct < 0.25) {
        output << color::fg::red;
    } else if (pct < 0.50) {
        output << color::fg::yellow;
    }
    output << icons::awesome::wifi << ' ';
    if (pct < 0) {
        output << "---";
    } else {
        output.width(3);
        output << static_cast<int>(round(100 * pct));
    }
    output << " %"
           << color::reset;

    // if (pct < 0) {
    //     output << icons::material::wifi_off << " ------";
    // } else {
    //     auto id = essid();
    //     if (id.size() > 6) {
    //         id.resize(5);
    //         id += "…";
    //     }
    //     output << blocks::choose(icons::material::wifi, pct) << ' ' << id;
    // }
    // output << color::reset;

    return output.str();
}

double wlan_status::quality()
{
    rewind(wireless);
    skip_line(wireless, 2);

    while (const auto line_opt = read_line(wireless)) {
        istringstream line { line_opt.value() };

        auto name = read_value<string>(line).value_or(":");
        name.pop_back(); // Trim ':' at the end of interface name.

        if (iface.empty()) {
            // Interface wasn't specified, use the first one.
            iface = name;
        }

        if (iface == name) {
            // Found entry for the interface.
            skip_value<int>(line);
            return read_value<double>(line).value_or(0.0) / 70;
        }
    }

    return -1;
}

string wlan_status::essid()
{
    if (iface.empty()) {
        return "";
    } else if (iface.size() > (IFNAMSIZ - 1)) {
        throw runtime_error("bad interface name \"" + iface + "\"");
    }

    iwreq req;

    memset(&req, 0, sizeof(iwreq));
    memcpy(req.ifr_name, iface.data(), iface.size());

    char buf[IW_ESSID_MAX_SIZE + 1];

    req.u.essid.length = sizeof(buf);
    req.u.essid.pointer = buf;

    if (ioctl(iwreq_fd, SIOCGIWESSID, &req) < 0) {
        throw runtime_error("ioctl");
    }

    return buf;
}

} // namespace dwmstatus
