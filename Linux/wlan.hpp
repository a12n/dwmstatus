#ifndef DWMSTATUS_WLAN_HPP
#define DWMSTATUS_WLAN_HPP

#include "status.hpp"

namespace dwmstatus {

class wlan_status : public status_impl {
public:
    explicit wlan_status(const string& iface = "");

    explicit wlan_status(istream& conf);

    virtual string update(system_clock::time_point t) override;

private:
    string iface;
    ifstream wireless;
};

} // namespace dwmstatus

#endif // DWMSTATUS_WLAN_HPP
