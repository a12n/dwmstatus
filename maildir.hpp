#pragma once

#include "status.hpp"

namespace dwmstatus {

class maildir_status : public basic_status
{
public:
    explicit
    maildir_status(const set<string>& dir_set);

    explicit
    maildir_status(istream& config);

    virtual string
    update(const system_clock::time_point& t);

private:
    vector<string> dirs;
};

} // namespace dwmstatus
