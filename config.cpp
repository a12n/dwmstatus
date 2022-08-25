#include "config.hpp"

namespace dwmstatus {
namespace {

unique_ptr<status> make_status(istream& conf)
{
    string id;

    if (!(conf >> quoted(id))) {
        throw runtime_error("line in config must start with status identifier");
    }

    int period;

    if (!(conf >> period) || period < 1) {
        throw runtime_error("invalid or missing period in config");
    }

    return make_unique<status>(seconds(period), make_status_impl(id, conf));
}

} // namespace

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
