#pragma once

#include "status.hpp"

namespace dwmstatus {

vector<unique_ptr<status> >
read_config(istream& config);

} // namespace dwmstatus
