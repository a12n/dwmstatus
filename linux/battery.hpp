#ifndef DWMSTATUS_LINUX_BATTERY_HPP
#define DWMSTATUS_LINUX_BATTERY_HPP

#include "status.hpp"

namespace dwmstatus {

struct battery : abstract_status {
    battery();
    virtual optional<string> update(system_clock::time_point) override;

private:
    struct files {
        files(const string& dir_path);

        double capacity();
        int charging();

        ifstream status_;
        ifstream capacity_;
    };

    vector<files> bats_;
};

} // namespace dwmstatus

#endif // DWMSTATUS_LINUX_BATTERY_HPP
