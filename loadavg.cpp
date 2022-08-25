#include "loadavg.hpp"

#include <cstdlib>

namespace dwmstatus {

using std::ios_base;

string loadavg_status::update(system_clock::time_point)
{
    double loadavg[3] = { 0.0, 0.0, 0.0 };

    getloadavg(loadavg, 3);

    ostringstream output;

    output.precision(2);
    output.setf(ios_base::fixed);
    output << loadavg[0] << ' ' << loadavg[1] << ' ' << loadavg[2];

    return output.str();
}

} // namespace dwmstatus
