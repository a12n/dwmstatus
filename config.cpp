#include "config.hpp"

namespace dwmstatus {

status_list read_config(istream& conf)
{
    string line;
    status_list ans;
    while (getline(conf, line)) {
        istringstream line_conf { line };
        ans.emplace_back(make_status(line_conf));
    }
    return ans;
}

template <>
optional<string> read_value(istream& conf)
{
    string ans;
    if (conf >> quoted(ans)) {
        return ans;
    } else {
        return nullopt;
    }
}

} // namespace dwmstatus
