#include "loadavg.hpp"

#include <cstdlib>

namespace dwmstatus {

using std::ios_base;

string loadavg_status::update(system_clock::time_point)
{
    double loadavg[3] { 0.0, 0.0, 0.0 };
    getloadavg(loadavg, 3);
    ostringstream out;
    out.precision(2);
    out.setf(ios_base::fixed);
    out << loadavg[0] << ' ' << loadavg[1] << ' ' << loadavg[2];
    return out.str();
}

} // namespace dwmstatus
