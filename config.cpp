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

using std::getline;

namespace {

unique_ptr<status>
read_status(istream& config)
{
    string id;
    size_t dt;

    if (! (config >> quoted(id))) {
        throw runtime_error("a line in config must start with status identifier");
    }

    if (! (config >> dt)) {
        throw runtime_error("update interval required in config");
    }

    basic_status* raw_status = nullptr;

    if (id == "battery") { raw_status = new battery_status; }
    else if (id == "cputemp") { raw_status = new cputemp_status; }
    else if (id == "loadavg") { raw_status = new loadavg_status; }
    else if (id == "maildir") { raw_status = new maildir_status(config); }
    else if (id == "time") { raw_status = new time_status(config); }
#ifdef DWMSTATUS_WITH_UTIME
    else if (id == "utime") { raw_status = new utime_status(config); }
#endif  // DWMSTATUS_WITH_UTIME
    else { throw runtime_error("unknown status identifier"); }

    return make_unique<status>(seconds(dt), raw_status);
}

} // namespace

vector<unique_ptr<status>>
read_config(istream& config)
{
    string line;
    vector<unique_ptr<status>> ans;
    while (getline(config, line)) {
        istringstream line_config(line);
        ans.push_back(read_status(line_config));
    }
    return ans;
}

} // namespace dwmstatus
