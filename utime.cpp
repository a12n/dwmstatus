#include "utime.hpp"

#include "config.hpp"

#include <unicode/unistr.h>

#include <stdexcept>

namespace dwmstatus {

utime_status::utime_status(const string& pattern)
{
    UErrorCode err { U_ZERO_ERROR };
    fmt = make_unique<icu::SimpleDateFormat>(icu::UnicodeString::fromUTF8(pattern), err);
    if (U_FAILURE(err)) {
        throw runtime_error(u_errorName(err));
    }
}

utime_status::utime_status(istream& config)
    : utime_status(read_value<string>(config).value_or(default_pattern))
{
}

string utime_status::update(system_clock::time_point t)
{
    icu::UnicodeString ustr;
    string str;
    const auto t2 { system_clock::to_time_t(t) };
    const UDate t3 { 1E3 * static_cast<UDate>(t2) };
    return fmt->format(t3, ustr).toUTF8String(str);
}

} // namespace dwmstatus
