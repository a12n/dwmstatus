#include "cputemp.hpp"

#include "config.hpp"

namespace dwmstatus {

cputemp_status::cputemp_status(unsigned int i)
    : hwmon { "/sys/class/hwmon/hwmon" + to_string(i) + "/temp1_input" }
{
}

cputemp_status::cputemp_status(istream& config)
    : cputemp_status(read_value<unsigned int>(config).value_or(0))
{
}

string cputemp_status::update(system_clock::time_point)
{
    return to_string(static_cast<int>(hwmon.reread_value<double>().value_or(0.0) / 1000.0)) + " °C";
}

} // namespace dwmstatus
