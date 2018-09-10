#include "status.hpp"

namespace dwmstatus {

status::status(const seconds& dt, basic_status* raw) :
    dt(dt),
    last_t(system_clock::from_time_t(0)),
    raw(raw)
{
    if (! raw) {
        throw runtime_error("basic status must be non-null");
    }
}

optional<string>
status::update(const system_clock::time_point& t)
{
    if ((t - last_t) >= dt || t < last_t) {
        last_t = t;
        return raw->update(t);
    } else {
        return nullopt;
    }
}

} // namespace dwmstatus
