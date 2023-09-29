#include "status/unicode_time.hpp"

#include <unicode/unistr.h>

namespace dwmstatus {

unicode_time::unicode_time(string_view pattern)
{
    UErrorCode err = U_ZERO_ERROR;
    fmt_ = make_unique<icu::SimpleDateFormat>(icu::UnicodeString::fromUTF8(pattern), err);
    if (U_FAILURE(err)) {
        throw runtime_error("unicode_time: " + string(u_errorName(err)));
    }
}

optional<string> unicode_time::update(system_clock::time_point t)
{
    icu::UnicodeString ustr;
    string str;
    const auto t2 = system_clock::to_time_t(t);
    const UDate t3 = 1E3 * static_cast<UDate>(t2);
    return fmt_->format(t3, ustr).toUTF8String(str);
}

} // namespace dwmstatus
