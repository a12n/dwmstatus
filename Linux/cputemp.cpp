#include "cputemp.hpp"

#include "file.hpp"

namespace dwmstatus {

cputemp_status::cputemp_status(int i)
    : hwmon { open_unbuf("/sys/class/hwmon/hwmon" + to_string(i) + "/temp1_input") }
{
}

cputemp_status::cputemp_status(istream& config)
    : cputemp_status(read_value<unsigned int>(config).value_or(0))
{
}

string cputemp_status::update(system_clock::time_point)
{
    return to_string(static_cast<int>(reread_value<double>(hwmon).value_or(0.0) / 1000.0)) + " °C";
}

} // namespace dwmstatus
