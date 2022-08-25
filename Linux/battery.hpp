#ifndef DWMSTATUS_LINUX_BATTERY_HPP
#define DWMSTATUS_LINUX_BATTERY_HPP

#include "pfile.hpp"
#include "status.hpp"

namespace dwmstatus {

class battery_status : public status_impl {
public:
    battery_status();

    battery_status(const battery_status&) = delete;

    battery_status& operator=(const battery_status&) = delete;

    virtual string update(system_clock::time_point t) override;

private:
    struct battery {
        explicit battery(const string& dir_path);

        short charging();

        pfile status;
        pfile capacity;
    };

    vector<battery> batteries;
};

} // namespace dwmstatus

#endif // DWMSTATUS_LINUX_BATTERY_HPP
