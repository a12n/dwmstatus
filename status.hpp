#pragma once

#include "decl.hpp"

namespace dwmstatus {

class basic_status
{
public:
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