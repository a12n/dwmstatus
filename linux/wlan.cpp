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

wlan::wlan(const string& iface)
    : iface_ { iface }
    , wireless_ { open_unbuf("/proc/net/wireless") }
    // , fd_ { socket(AF_INET, SOCK_DGRAM, 0) }
{
    // if (fd_ < 0) {
    //     throw runtime_error("wlan: couldn't open socket");
    // }
}

optional<string> wlan::update(system_clock::time_point)
{
    const auto pct = quality();

    ostringstream out;

    if (pct < 0) {
        out << color::fg::white;
    } else if (pct < 0.25) {
        out << color::fg::red;
    } else if (pct < 0.50) {
        out << color::fg::yellow;
    }
    out << icons::awesome::wifi << ' ';
    if (pct < 0) {
        out << "---";
    } else {
        out << setw(3) << static_cast<int>(round(100 * pct));
    }
    out << " %"
        << color::reset;

    // if (pct < 0) {
    //     out << icons::material::wifi_off << " ------";
    // } else {
    //     auto id = essid();
    //     if (id.size() > 6) {
    //         id.resize(5);
    //         id += "…";
    //     }
    //     out << blocks::choose(icons::material::wifi, pct) << ' ' << id;
    // }
    // out << color::reset;

    return out.str();
}

double wlan::quality()
{
    rewind(wireless_);
    skip_line(wireless_, 2);

    while (const auto line_opt = read_line(wireless_)) {
        istringstream line { line_opt.value() };

        auto name = read_value<string>(line).value_or(":");
        name.pop_back(); // Trim ':' at the end of interface name.

        if (iface_.empty()) {
            // Interface wasn't specified, use the first one.
            iface_ = name;
        }

        if (iface_ == name) {
            // Found entry for the interface.
            skip_value<int>(line);
            return read_value<double>(line).value_or(0.0) / 70;
        }
    }

    return -1;
}

string wlan::essid()
{
    if (iface_.empty()) {
        return "";
    } else if (iface_.size() > (IFNAMSIZ - 1)) {
        throw runtime_error("wlan: bad interface name \"" + iface_ + "\"");
    }

    iwreq req;

    memset(&req, 0, sizeof(iwreq));
    memcpy(req.ifr_name, iface_.data(), iface_.size());

    char buf[IW_ESSID_MAX_SIZE + 1];

    req.u.essid.length = sizeof(buf);
    req.u.essid.pointer = buf;

    if (ioctl(fd_, SIOCGIWESSID, &req) < 0) {
        throw runtime_error("wlan: ioctl");
    }

    return buf;
}

} // namespace dwmstatus
