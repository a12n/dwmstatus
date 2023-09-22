#ifndef DWMSTATUS_BLOCKS_HPP
#define DWMSTATUS_BLOCKS_HPP

#include "decl.hpp"

namespace dwmstatus {
namespace blocks {

extern const vector<string_view> horiz;
extern const vector<string_view> shade;
extern const vector<string_view> vert;

string choose(const vector<string_view>& table, double pct);

} // namespace blocks
} // namespace dwmstatus

#endif // DWMSTATUS_BLOCKS_HPP
