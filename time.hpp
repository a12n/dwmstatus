#pragma once

#include "status.hpp"

namespace dwmstatus {

class time_status : public basic_status
{
public:
    static constexpr auto default_pattern = "%a, %d %b %Y %T %Z";

    explicit
    time_status(const string& pattern = default_pattern);

    explicit
    time_status(istream& config);

    virtual string
    update(const system_clock::time_point& t) override;

private:
    string pattern;
};

} // namespace dwmstatus
