#ifndef DWMSTATUS_DECL_HPP
#define DWMSTATUS_DECL_HPP

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace dwmstatus {

using std::clamp;
using std::cout;
using std::endl;
using std::fixed;
using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::istream;
using std::istringstream;
using std::make_unique;
using std::move;
using std::nullopt;
using std::optional;
using std::ostringstream;
using std::put_time;
using std::quoted;
using std::runtime_error;
using std::set;
using std::setprecision;
using std::setw;
using std::string;
using std::string_view;
using std::to_string;
using std::unique_ptr;
using std::vector;
using std::chrono::seconds;
using std::chrono::system_clock;

} // namespace dwmstatus

#endif // DWMSTATUS_DECL_HPP
