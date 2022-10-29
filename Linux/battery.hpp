#ifndef DWMSTATUS_LINUX_BATTERY_HPP
#define DWMSTATUS_LINUX_BATTERY_HPP

#include "status.hpp"

namespace dwmstatus {

class battery_status : public status_impl {
public:
    battery_status();

    virtual string update(system_clock::time_point t) override;

private:
    struct battery {
        explicit battery(const string& dir_path);

        short charging();

        ifstream status;
        ifstream capacity;
    };

    vector<battery> batteries;
};

} // namespace dwmstatus

#endif // DWMSTATUS_LINUX_BATTERY_HPP
