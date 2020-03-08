#ifndef DWMSTATUS_STATUS_HPP
#define DWMSTATUS_STATUS_HPP

#include "decl.hpp"

namespace dwmstatus {

class basic_status
{
public:
    virtual
    ~basic_status() = default;

    virtual string
    update(system_clock::time_point t) = 0;
};

//----------------------------------------------------------------------------

class status
{
public:
    explicit
    status(seconds interval, unique_ptr<basic_status> impl);

    optional<string>
    update(system_clock::time_point t);

private:
    const seconds interval;
    const unique_ptr<basic_status> impl;
    system_clock::time_point last_t;
};

} // namespace dwmstatus

#endif  // DWMSTATUS_STATUS_HPP
