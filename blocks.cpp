#include "blocks.hpp"

namespace dwmstatus {
namespace blocks {

const vector<string_view> horiz { " ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█" };
const vector<string_view> shade { " ", "░", "▒", "▓", "█" };
const vector<string_view> vert { " ", "▁", "▂", "▃", "▅", "▆", "▇", "█" };

string choose(const vector<string_view>& table, double pct)
{
    if (pct < 0.0) {
        pct = 0.0;
    } else if (pct > 1.0) {
        pct = 1.0;
    }
    return string(table[pct * (table.size() - 1) + 0.5]);
}

} // namespace blocks
} // namespace dwmstatus
