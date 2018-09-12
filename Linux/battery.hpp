#pragma once

#include "pfile.hpp"
#include "status.hpp"

namespace dwmstatus {

class battery_status : public basic_status
{
public:
    battery_status();

    battery_status(const battery_status&) = delete;

    battery_status&
    operator=(const battery_status&) = delete;

    virtual string
    update(const system_clock::time_point& t) override;

private:
    vector<pfile> status;
    vector<pfile> capacity;
    bool show_disch;
};

} // namespace dwmstatus
