#ifndef DWMSTATUS_DECL_HPP
#define DWMSTATUS_DECL_HPP

#include <chrono>
#include <fstream>
#include <iomanip>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace dwmstatus {

using std::cbegin;
using std::cend;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::make_unique;
using std::move;
using std::nullopt;
using std::optional;
using std::ostringstream;
using std::quoted;
using std::runtime_error;
using std::set;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

} // namespace dwmstatus

#endif  // DWMSTATUS_DECL_HPP
