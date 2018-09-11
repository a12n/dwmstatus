#pragma once

#include <chrono>
#include <experimental/optional>
#include <fstream>
#include <iomanip>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace dwmstatus {

using std::chrono::seconds;
using std::chrono::system_clock;
using std::experimental::nullopt;
using std::experimental::optional;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::make_unique;
using std::ostringstream;
using std::quoted;
using std::runtime_error;
using std::set;
using std::string;
using std::unique_ptr;
using std::vector;

} // namespace dwmstatus