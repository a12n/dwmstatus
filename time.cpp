#include "time.hpp"

#include "config.hpp"

#include <ctime>

namespace dwmstatus {

using std::localtime;
using std::put_time;

time_status::time_status(const string& pattern)
    : pattern(pattern)
{
}

time_status::time_status(istream& config)
    : time_status(read_value<string>(config).value_or(default_pattern))
{
}

string time_status::update(system_clock::time_point t)
{
    const auto t2 { system_clock::to_time_t(t) };
    ostringstream out;
    out << put_time(localtime(&t2), pattern.c_str());
    return out.str();
}

} // namespace dwmstatus
