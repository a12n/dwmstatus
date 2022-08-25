#ifndef DWMSTATUS_MAILDIR_HPP
#define DWMSTATUS_MAILDIR_HPP

#include "status.hpp"

namespace dwmstatus {

class maildir_status : public status_impl {
public:
    explicit maildir_status(const set<string>& dir_set);

    explicit maildir_status(istream& config);

    virtual string update(system_clock::time_point t);

private:
    vector<string> dirs;
};

} // namespace dwmstatus

#endif // DWMSTATUS_MAILDIR_HPP
