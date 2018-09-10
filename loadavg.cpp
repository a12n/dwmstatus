#include <cstdlib>

#include "loadavg.hpp"

namespace dwmstatus {

using std::ios_base;

string
loadavg_status::update(const system_clock::time_point&)
{
    double ans[3] = { 0.0, 0.0, 0.0 };
    getloadavg(ans, 3);
    ostringstream out;
    out.precision(2);
    out.setf(ios_base::fixed);
    out << ans[0] << ' ' << ans[1] << ' ' << ans[2];
    return out.str();
}

} // namespace dwmstatus
