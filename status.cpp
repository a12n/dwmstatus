#include "status.hpp"

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

unique_ptr<status_impl> make_status_impl(string_view id, istream& conf)
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
    else if (id == "wlan") {
        return make_unique<wlan_status>(conf);
    } else {
        throw runtime_error("unknown status identifier");
    }
}

//----------------------------------------------------------------------------

status::status(seconds period, unique_ptr<status_impl> impl)
    : period { period }
    , impl { move(impl) }
{
    if (!this->impl) {
        throw runtime_error("basic status must be non-null");
    }
}

bool status::update(system_clock::time_point t)
{
    if ((t - t0) >= period || t < t0) {
        str = impl->update(t);
        t0 = t;
        return true;
    } else {
        return false;
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

//----------------------------------------------------------------------------

status_bar make_status_bar(istream& conf)
{
    string line;
    status_bar bar;
    while (getline(conf, line)) {
        istringstream line_conf { line };
        bar.push_back(make_status(line_conf));
    }
    return bar;
}

bool update_status_bar(status_bar& bar, system_clock::time_point t)
{
    bool changed = false;
    for (auto& s : bar) {
        if (s->update(t)) {
            changed = true;
        }
    }
    return changed;
}

string format_status_bar(const status_bar& bar, string_view sep)
{
    string ans;
    for (const auto& s : bar) {
        if (!ans.empty()) {
            ans += sep;
        }
        ans += *s;
    }
    return ans;
}

//----------------------------------------------------------------------------

periodic::periodic(status_ptr status, seconds period)
    : status_ { move(status) }
    , period_ { period }
{
}

optional<string> periodic::update(system_clock::time_point t)
{
    if (t > t0_ && (t - t0_) < period_) {
        return nullopt;
    }
    t0_ = t;
    if (!status_) {
        return nullopt;
    }
    return status_->update(t);
}

} // namespace dwmstatus
