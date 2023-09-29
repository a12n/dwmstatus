#ifndef DWMSTATUS_STATUS_UNICODE_TIME_HPP
#define DWMSTATUS_STATUS_UNICODE_TIME_HPP

#include "status.hpp"

#include <unicode/smpdtfmt.h>

namespace dwmstatus {

struct unicode_time : abstract_status {
    static constexpr auto default_pattern = "EEEE, d MMMM yyyy HH:mm:ss Z";

    unicode_time(string_view pattern = default_pattern);
    virtual optional<string> update(system_clock::time_point t) override;

private:
    unique_ptr<icu::SimpleDateFormat> fmt_;
};

} // namespace dwmstatus

#endif // DWMSTATUS_STATUS_UNICODE_TIME_HPP
