#ifndef DWMSTATUS_UTIME_HPP
#define DWMSTATUS_UTIME_HPP

#include "status.hpp"

#include <unicode/smpdtfmt.h>

namespace dwmstatus {

class utime_status : public status_impl {
public:
    static constexpr auto default_pattern = "EEEE, d MMMM yyyy HH:mm:ss Z";

    explicit utime_status(const string& pattern = default_pattern);

    explicit utime_status(istream& conf);

    virtual string update(system_clock::time_point t) override;

private:
    unique_ptr<icu::SimpleDateFormat> fmt;
};

} // namespace dwmstatus

#endif // DWMSTATUS_UTIME_HPP
