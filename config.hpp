#ifndef DWMSTATUS_CONFIG_HPP
#define DWMSTATUS_CONFIG_HPP

#include "status.hpp"

namespace dwmstatus {

vector<unique_ptr<status>>
read_config(istream& config);

} // namespace dwmstatus

#endif  // DWMSTATUS_CONFIG_HPP
