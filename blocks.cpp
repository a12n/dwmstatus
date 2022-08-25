#include "blocks.hpp"

namespace dwmstatus {

const vector<string> horiz_blocks { " ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█" };
const vector<string> shade_blocks { " ", "░", "▒", "▓", "█" };
const vector<string> vert_blocks { " ", "▁", "▂", "▃", "▅", "▆", "▇", "█" };

string choose_block(const vector<string>& table, double pct)
{
    if (pct < 0.0) {
        pct = 0.0;
    } else if (pct > 1.0) {
        pct = 1.0;
    }
    return table[pct * (table.size() - 1) + 0.5];
}

} // namespace dwmstatus
