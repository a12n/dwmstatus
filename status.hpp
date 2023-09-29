#ifndef DWMSTATUS_STATUS_HPP
#define DWMSTATUS_STATUS_HPP

#include "decl.hpp"

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
    static constexpr auto default_sep = " • ";

    bar(vector<status_ptr> items, string_view sep = default_sep, string_view prefix = "", string_view suffix = "");
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
