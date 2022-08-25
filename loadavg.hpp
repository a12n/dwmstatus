#ifndef DWMSTATUS_LOADAVG_HPP
#define DWMSTATUS_LOADAVG_HPP

#include "status.hpp"

namespace dwmstatus {

class loadavg_status : public status_impl
{
public:
    virtual string
    update(system_clock::time_point t) override;
};

} // namespace dwmstatus

#endif  // DWMSTATUS_LOADAVG_HPP
