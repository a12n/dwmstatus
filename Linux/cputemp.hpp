#ifndef DWMSTATUS_LINUX_CPUTEMP_HPP
#define DWMSTATUS_LINUX_CPUTEMP_HPP

#include "pfile.hpp"
#include "status.hpp"

namespace dwmstatus {

class cputemp_status : public status_impl
{
public:
    explicit
    cputemp_status(unsigned int i = 0);

    explicit
    cputemp_status(istream& config);

    cputemp_status(const cputemp_status&) = delete;

    cputemp_status&
    operator=(const cputemp_status&) = delete;

    virtual string
    update(system_clock::time_point t) override;

private:
    pfile hwmon;
};

} // namespace dwmstatus

#endif  // DWMSTATUS_LINUX_CPUTEMP_HPP
