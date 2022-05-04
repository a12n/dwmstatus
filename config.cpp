#include "battery.hpp"
#include "config.hpp"
#include "cputemp.hpp"
#include "loadavg.hpp"
#include "maildir.hpp"
#include "time.hpp"
#ifdef DWMSTATUS_WITH_UTIME
#include "utime.hpp"
#endif  // DWMSTATUS_WITH_UTIME

namespace dwmstatus {
namespace {

unique_ptr<basic_status>
make_basic_status(const string& id, istream& config)
{
    if (id == "battery") { return make_unique<battery_status>(); }
    else if (id == "cputemp") { return make_unique<cputemp_status>(); }
    else if (id == "loadavg") { return make_unique<loadavg_status>(); }
    else if (id == "maildir") { return make_unique<maildir_status>(config); }
    else if (id == "time") { return make_unique<time_status>(config); }
#ifdef DWMSTATUS_WITH_UTIME
    else if (id == "utime") { return make_unique<utime_status>(config); }
#endif  // DWMSTATUS_WITH_UTIME
    else { throw runtime_error("unknown status identifier"); }
}

unique_ptr<status>
make_status(istream& config)
{
    string id;

    if (! (config >> quoted(id))) {
        throw runtime_error("a line in config must start with status identifier");
    }

    unsigned int interval;

    if (! (config >> interval)) {
        throw runtime_error("update interval required in config");
    }

    return make_unique<status>(seconds(interval), make_basic_status(id, config));
}

} // namespace

vector<unique_ptr<status>>
read_config(istream& config)
{
    string line;
    vector<unique_ptr<status>> ans;
    while (getline(config, line)) {
        istringstream line_config{line};
        ans.emplace_back(make_status(line_config));
    }
    return ans;
}

template <>
optional<string>
read_value(istream& config)
{
    string ans;
    if (config >> quoted(ans)) {
        return ans;
    } else {
        return nullopt;
    }
}

} // namespace dwmstatus
