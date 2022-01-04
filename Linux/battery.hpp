#ifndef DWMSTATUS_LINUX_BATTERY_HPP
#define DWMSTATUS_LINUX_BATTERY_HPP

#include "pfile.hpp"
#include "status.hpp"

namespace dwmstatus {

class battery_status : public basic_status
{
public:
    battery_status();

    battery_status(const battery_status&) = delete;

    battery_status&
    operator=(const battery_status&) = delete;

    virtual string
    update(system_clock::time_point t) override;

private:
    vector<pfile> status;
    vector<pfile> capacity;
};

} // namespace dwmstatus

#endif  // DWMSTATUS_LINUX_BATTERY_HPP
