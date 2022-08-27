#ifndef DWMSTATUS_CONFIG_HPP
#define DWMSTATUS_CONFIG_HPP

#include "decl.hpp"

namespace dwmstatus {

template <typename T>
optional<T> read_value(istream& conf)
{
    T ans;
    if (conf >> ans) {
        return ans;
    } else {
        return nullopt;
    }
}

template <>
optional<string> read_value(istream& conf);

} // namespace dwmstatus

#endif // DWMSTATUS_CONFIG_HPP
