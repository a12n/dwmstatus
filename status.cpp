#include "status.hpp"

namespace dwmstatus {

status::status(seconds period, unique_ptr<status_impl> impl)
    : period { period }
    , impl { move(impl) }
    , t0 { system_clock::from_time_t(0) }
{
    if (!this->impl) {
        throw runtime_error("basic status must be non-null");
    }
}

optional<string> status::update(system_clock::time_point t)
{
    if ((t - t0) >= period || t < t0) {
        t0 = t;
        return impl->update(t);
    } else {
        return nullopt;
    }
}

} // namespace dwmstatus
