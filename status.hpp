#ifndef DWMSTATUS_STATUS_HPP
#define DWMSTATUS_STATUS_HPP

#include "decl.hpp"

namespace dwmstatus {

class status_impl {
public:
    virtual ~status_impl() = default;

    virtual string update(system_clock::time_point t) = 0;
};

unique_ptr<status_impl> make_status_impl(const string& id, istream& conf);

//----------------------------------------------------------------------------

class status {
public:
    status(seconds period, unique_ptr<status_impl> impl);

    bool update(system_clock::time_point t);

    inline operator const string&() const
    {
        return str;
    }

private:
    seconds period;
    unique_ptr<status_impl> impl;
    system_clock::time_point t0;
    string str;
};

unique_ptr<status> make_status(istream& conf);

//----------------------------------------------------------------------------

using status_list = vector<unique_ptr<status>>;

status_list make_status_list(istream& conf);

bool update_status_list(status_list& list, system_clock::time_point t);

string format_status_list(const status_list& list, const char* sep);

} // namespace dwmstatus

#endif // DWMSTATUS_STATUS_HPP
