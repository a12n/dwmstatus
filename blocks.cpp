#include "blocks.hpp"

namespace dwmstatus {
namespace blocks {

const vector<string> horiz { " ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█" };
const vector<string> shade { " ", "░", "▒", "▓", "█" };
const vector<string> vert { " ", "▁", "▂", "▃", "▅", "▆", "▇", "█" };

string choose(const vector<string>& table, double pct)
{
    if (pct < 0.0) {
        pct = 0.0;
    } else if (pct > 1.0) {
        pct = 1.0;
    }
    return table[pct * (table.size() - 1) + 0.5];
}

} // namespace blocks
} // namespace dwmstatus
