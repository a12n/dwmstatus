#ifndef DWMSTATUS_STATUS_HPP
#define DWMSTATUS_STATUS_HPP

#include "decl.hpp"

namespace dwmstatus {

class status_impl {
public:
    virtual ~status_impl() = default;

    virtual string update(system_clock::time_point t) = 0;
};

//----------------------------------------------------------------------------

class status {
public:
    status(seconds period, unique_ptr<status_impl> impl);

    optional<string> update(system_clock::time_point t);

private:
    const seconds period;
    const unique_ptr<status_impl> impl;
    system_clock::time_point t0;
};

} // namespace dwmstatus

#endif // DWMSTATUS_STATUS_HPP
