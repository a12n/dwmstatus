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
    update(const system_clock::time_point& t) = 0;
};

//----------------------------------------------------------------------------

class status
{
public:
    explicit
    status(const seconds& dt, basic_status* raw);

    optional<string>
    update(const system_clock::time_point& t);

private:
    const seconds dt;
    system_clock::time_point last_t;
    unique_ptr<basic_status> raw;
};

} // namespace dwmstatus

#endif  // DWMSTATUS_STATUS_HPP
