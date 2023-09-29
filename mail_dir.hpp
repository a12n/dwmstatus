#ifndef DWMSTATUS_MAIL_DIR_HPP
#define DWMSTATUS_MAIL_DIR_HPP

#include "status.hpp"

namespace dwmstatus {

struct mail_dir : abstract_status {
    mail_dir(const set<string>& dirs = {});
    virtual optional<string> update(system_clock::time_point);

private:
    vector<string> dirs_;
};

} // namespace dwmstatus

#endif // DWMSTATUS_MAIL_DIR_HPP
