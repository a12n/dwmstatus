#include "status.hpp"

namespace dwmstatus {

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
