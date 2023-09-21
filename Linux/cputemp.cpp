#include "cputemp.hpp"

#include "blocks.hpp"
#include "color.hpp"
#include "file.hpp"
#include "icons.hpp"

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
    const auto temp = (reread_value<int>(hwmon).value_or(0) + 500) / 1000;

    ostringstream output;

    if (temp > 80) {
        output << color::fg::red;
    }
    output << blocks::choose(icons::awesome::thermometer, temp / 80.0) << ' '
           << temp << " °C"
           << color::reset;

    return output.str();
}

} // namespace dwmstatus
