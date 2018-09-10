#include "config.hpp"
#include "time.hpp"

namespace dwmstatus {

using std::getline;

namespace {

unique_ptr<status>
read_status(istream& config)
{
    string id;
    size_t dt;

    if (! (config >> quoted(id))) {
        throw runtime_error("a line in config must start with status identifier");
    }

    if (! (config >> dt)) {
        throw runtime_error("update interval required in config");
    }

    basic_status* raw_status = nullptr;

    if (id == "time") { raw_status = new time_status(config); }
    else { throw runtime_error("unknown status identifier"); }

    return make_unique<status>(seconds(dt), raw_status);
}

} // namespace

vector<unique_ptr<status> >
read_config(istream& config)
{
    string line;
    vector<unique_ptr<status> > ans;
    while (getline(config, line)) {
        istringstream line_config(line);
        ans.push_back(read_status(line_config));
    }
    return ans;
}

} // namespace dwmstatus
