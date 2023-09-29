#include "status/time.hpp"

#include <ctime>

namespace dwmstatus {

time::time(string_view pattern)
    : pattern { pattern }
{
}

optional<string> time::update(system_clock::time_point t)
{
    const auto t2 = system_clock::to_time_t(t);
    return (ostringstream() << put_time(localtime(&t2), pattern.c_str())).str();
}

} // namespace dwmstatus
