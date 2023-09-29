#include "cpu_temp.hpp"

#include "blocks.hpp"
#include "color.hpp"
#include "file.hpp"
#include "icons.hpp"

namespace dwmstatus {

cpu_temp::cpu_temp(const string& hwmon_path)
    : hwmon_ { open_unbuf(hwmon_path) }
{
}

optional<string> cpu_temp::update(system_clock::time_point)
{
    const auto temp = (reread_value<int>(hwmon_).value_or(0) + 500) / 1000;

    ostringstream out;

    if (temp > 80) {
        out << color::fg::red;
    }
    out << blocks::choose(icons::awesome::thermometer, temp / 80.0) << ' '
        << temp << " °C"
        << color::reset;

    return out.str();
}

} // namespace dwmstatus
