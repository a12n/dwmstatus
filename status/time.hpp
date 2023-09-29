#ifndef DWMSTATUS_STATUS_TIME_HPP
#define DWMSTATUS_STATUS_TIME_HPP

#include "status.hpp"

namespace dwmstatus {

struct time : abstract_status {
    static constexpr auto default_pattern = "%a, %d %b %Y %T %Z";

    time(string_view pattern = default_pattern);
    virtual optional<string> update(system_clock::time_point t) override;

private:
    string fmt_;
};

} // namespace dwmstatus

#endif // DWMSTATUS_STATUS_TIME_HPP
