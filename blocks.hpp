#ifndef DWMSTATUS_BLOCKS_HPP
#define DWMSTATUS_BLOCKS_HPP

#include "decl.hpp"

namespace dwmstatus {

extern const vector<string> horiz_blocks;
extern const vector<string> shade_blocks;
extern const vector<string> vert_blocks;

string
choose_block(const vector<string>& table, double pct);

} // namespace dwmstatus

#endif  // DWMSTATUS_BLOCKS_HPP
