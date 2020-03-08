#ifndef DWMSTATUS_UTIME_HPP
#define DWMSTATUS_UTIME_HPP

#include <unicode/smpdtfmt.h>

#include "status.hpp"

namespace dwmstatus {

class utime_status : public basic_status
{
public:
    static constexpr auto default_pattern = "EEEE, d MMMM yyyy HH:mm:ss";

    explicit
    utime_status(const string& pattern = default_pattern);

    explicit
    utime_status(istream& config);

    virtual string
    update(const system_clock::time_point& t) override;

private:
    unique_ptr<icu::SimpleDateFormat> fmt;
};

} // namespace dwmstatus

#endif  // DWMSTATUS_UTIME_HPP
