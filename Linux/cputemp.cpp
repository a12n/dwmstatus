#include "cputemp.hpp"

namespace dwmstatus {

cputemp_status::cputemp_status() :
    hwmon{"/sys/class/hwmon/hwmon0/temp1_input"}
{
}

string
cputemp_status::update(system_clock::time_point)
{
    return to_string(static_cast<int>(hwmon.read<double>() / 1000.0)) + " °C";
}

} // namespace dwmstatus
