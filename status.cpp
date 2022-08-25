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

} // namespace dwmstatus
