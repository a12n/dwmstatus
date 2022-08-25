#include "config.hpp"

#include "battery.hpp"
#include "cputemp.hpp"
#include "loadavg.hpp"
#include "maildir.hpp"
#include "time.hpp"
#ifdef DWMSTATUS_WITH_UTIME
#include "utime.hpp"
#endif // DWMSTATUS_WITH_UTIME
#include "wlan.hpp"

namespace dwmstatus {
namespace {

unique_ptr<status_impl> make_status_impl(const string& id, istream& conf)
{
    if (id == "battery") {
        return make_unique<battery_status>();
    } else if (id == "cputemp") {
        return make_unique<cputemp_status>(conf);
    } else if (id == "loadavg") {
        return make_unique<loadavg_status>();
    } else if (id == "maildir") {
        return make_unique<maildir_status>(conf);
    } else if (id == "time") {
        return make_unique<time_status>(conf);
    }
#ifdef DWMSTATUS_WITH_UTIME
    else if (id == "utime") {
        return make_unique<utime_status>(conf);
    }
#endif // DWMSTATUS_WITH_UTIME
    else {
        throw runtime_error("unknown status identifier");
    }
}

unique_ptr<status> make_status(istream& conf)
{
    string id;

    if (!(conf >> quoted(id))) {
        throw runtime_error("line in config must start with status identifier");
    }

    int period;

    if (!(conf >> period) || period < 1) {
        throw runtime_error("invalid or missing period in config");
    }

    return make_unique<status>(seconds(period), make_status_impl(id, conf));
}

} // namespace

vector<unique_ptr<status>> read_config(istream& conf)
{
    string line;
    vector<unique_ptr<status>> ans;
    while (getline(conf, line)) {
        istringstream line_conf { line };
        ans.emplace_back(make_status(line_conf));
    }
    return ans;
}

template <>
optional<string> read_value(istream& conf)
{
    string ans;
    if (conf >> quoted(ans)) {
        return ans;
    } else {
        return nullopt;
    }
}

} // namespace dwmstatus
