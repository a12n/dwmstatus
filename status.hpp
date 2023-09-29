#ifndef DWMSTATUS_STATUS_HPP
#define DWMSTATUS_STATUS_HPP

#include "decl.hpp"

namespace dwmstatus {

class status_impl {
public:
    virtual ~status_impl() = default;

    virtual string update(system_clock::time_point t) = 0;
};

unique_ptr<status_impl> make_status_impl(string_view id, istream& conf);

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

using status_bar = vector<unique_ptr<status>>;

status_bar make_status_bar(istream& conf);

bool update_status_bar(status_bar& bar, system_clock::time_point t);

string format_status_bar(const status_bar& bar, string_view sep);

} // namespace dwmstatus

//----------------------------------------------------------------------------

namespace dwmstatus {

struct abstract_status {
    virtual ~abstract_status() = default;
    virtual optional<string> update(system_clock::time_point t) = 0;
};

using status_ptr = unique_ptr<abstract_status>;

struct periodic : abstract_status {
    periodic(status_ptr status, seconds period);
    virtual optional<string> update(system_clock::time_point) override;

private:
    status_ptr status_;
    seconds period_;
    system_clock::time_point t0_;
};

struct bar : abstract_status {
    bar(vector<status_ptr> items, string_view sep = " • ", string_view prefix = "", string_view suffix = "");
    virtual optional<string> update(system_clock::time_point t) override;

private:
    vector<status_ptr> items_;
    vector<string> str_;
    string sep_;
    string prefix_;
    string suffix_;
};

} // namespace dwmstatus

#endif // DWMSTATUS_STATUS_HPP
