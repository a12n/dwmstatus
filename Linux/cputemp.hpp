#ifndef DWMSTATUS_LINUX_CPUTEMP_HPP
#define DWMSTATUS_LINUX_CPUTEMP_HPP

#include "status.hpp"

namespace dwmstatus {

class cputemp_status : public status_impl {
public:
    explicit cputemp_status(int i = 0);

    explicit cputemp_status(istream& config);

    virtual string update(system_clock::time_point t) override;

private:
    ifstream hwmon;
};

} // namespace dwmstatus

#endif // DWMSTATUS_LINUX_CPUTEMP_HPP
