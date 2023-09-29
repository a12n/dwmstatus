#ifndef DWMSTATUS_LINUX_WLAN_HPP
#define DWMSTATUS_LINUX_WLAN_HPP

#include "status.hpp"

namespace dwmstatus {

struct wlan : abstract_status {
public:
    wlan(const string& iface = "");
    virtual optional<string> update(system_clock::time_point) override;

private:
    double quality();
    string essid();

    string iface_;
    ifstream wireless_;
    int fd_;
};

} // namespace dwmstatus

#endif // DWMSTATUS_LINUX_WLAN_HPP
