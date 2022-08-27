#include "config.hpp"

namespace dwmstatus {

template <>
optional<string> read_value(istream& conf)
{
    string ans;
    if (conf >> quoted(ans)) {
        return ans;
    } else {
        return nullopt;
    }
}

} // namespace dwmstatus
