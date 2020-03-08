#include "status.hpp"

namespace dwmstatus {

status::status(const seconds& dt, basic_status* raw) :
    interval{s},
    last_t{system_clock::from_time_t(0)},
    impl{raw}
{
    if (! impl) {
        throw runtime_error("basic status must be non-null");
    }
}

optional<string>
status::update(const system_clock::time_point& t)
{
    if ((t - last_t) >= interval || t < last_t) {
        last_t = t;
        return impl->update(t);
    } else {
        return nullopt;
    }
}

} // namespace dwmstatus
