#include "status/load_avg.hpp"

#include <cstdlib>

namespace dwmstatus {

optional<string> load_avg::update(system_clock::time_point)
{
    double load[3];

    getloadavg(load, 3);

    return (ostringstream()
        << setprecision(2) << fixed
        << load[0] << ' ' << load[1] << ' ' << load[2])
        .str();
}

} // namespace dwmstatus
