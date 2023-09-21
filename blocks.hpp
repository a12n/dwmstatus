#ifndef DWMSTATUS_BLOCKS_HPP
#define DWMSTATUS_BLOCKS_HPP

#include "decl.hpp"

namespace dwmstatus {
namespace blocks {

extern const vector<string> horiz;
extern const vector<string> shade;
extern const vector<string> vert;

string choose(const vector<string>& table, double pct);

} // namespace blocks
} // namespace dwmstatus

#endif // DWMSTATUS_BLOCKS_HPP
