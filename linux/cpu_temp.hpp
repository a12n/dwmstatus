#ifndef DWMSTATUS_LINUX_CPU_TEMP_HPP
#define DWMSTATUS_LINUX_CPU_TEMP_HPP

#include "status.hpp"

namespace dwmstatus {

struct cpu_temp : abstract_status {
    cpu_temp(const string& hwmon_path = "/sys/class/hwmon/hwmon0/temp1_input");
    virtual optional<string> update(system_clock::time_point) override;

private:
    ifstream hwmon_;
};

} // namespace dwmstatus

#endif // DWMSTATUS_LINUX_CPU_TEMP_HPP
