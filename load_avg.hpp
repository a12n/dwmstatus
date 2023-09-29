#ifndef DWMSTATUS_LOAD_AVG_HPP
#define DWMSTATUS_LOAD_AVG_HPP

#include "status.hpp"

namespace dwmstatus {

struct load_avg : abstract_status {
    virtual optional<string> update(system_clock::time_point) override;
};

} // namespace dwmstatus

#endif // DWMSTATUS_LOAD_AVG_HPP
