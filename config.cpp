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

basic_status*
make_basic_status(const string& id, istream& config)
{
    if (id == "battery") { return new battery_status; }
    else if (id == "cputemp") { return new cputemp_status; }
    else if (id == "loadavg") { return new loadavg_status; }
    else if (id == "maildir") { return new maildir_status(config); }
    else if (id == "time") { return new time_status(config); }
#ifdef DWMSTATUS_WITH_UTIME
    else if (id == "utime") { return new utime_status(config); }
#endif  // DWMSTATUS_WITH_UTIME
    else { throw runtime_error("unknown status identifier"); }
}

unique_ptr<status>
make_status(istream& config)
{
    string id;
    size_t dt;

    if (! (config >> quoted(id))) {
        throw runtime_error("a line in config must start with status identifier");
    }

    if (! (config >> dt)) {
        throw runtime_error("update interval required in config");
    }

    return make_unique<status>(seconds(dt), make_basic_status(id, config));
}

} // namespace

vector<unique_ptr<status>>
read_config(istream& config)
{
    string line;
    vector<unique_ptr<status>> ans;
    while (getline(config, line)) {
        istringstream line_config(line);
        ans.emplace_back(make_status(line_config));
    }
    return ans;
}

} // namespace dwmstatus
