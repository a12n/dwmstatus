#include "blocks.hpp"

namespace dwmstatus {
namespace blocks {

const vector<string_view> horiz { " ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█" };
const vector<string_view> shade { " ", "░", "▒", "▓", "█" };
const vector<string_view> vert { " ", "▁", "▂", "▃", "▅", "▆", "▇", "█" };

string choose(const vector<string_view>& table, double pct)
{
    return string(table[clamp(pct, 0.0, 1.0) * (table.size() - 1) + 0.5]);
}

} // namespace blocks
} // namespace dwmstatus
