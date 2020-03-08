#ifndef DWMSTATUS_LINUX_CPUTEMP_HPP
#define DWMSTATUS_LINUX_CPUTEMP_HPP

#include "pfile.hpp"
#include "status.hpp"

namespace dwmstatus {

class cputemp_status : public basic_status
{
public:
    cputemp_status();

    cputemp_status(const cputemp_status&) = delete;

    cputemp_status&
    operator=(const cputemp_status&) = delete;

    virtual string
    update(const system_clock::time_point& t) override;

private:
    pfile hwmon;
};

} // namespace dwmstatus

#endif  // DWMSTATUS_LINUX_CPUTEMP_HPP
