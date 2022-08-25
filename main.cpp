#include <iostream>
#include <thread>

#include "config.hpp"
#include "display.hpp"

namespace this_thread = std::this_thread;
using namespace dwmstatus;
using std::cin;

namespace {

string
join(const vector<string>& strs, const string& sep)
{
    string ans;
    for (const auto& s : strs) {
        if (! ans.empty()) {
            ans += sep;
        }
        ans += s;
    }
    return ans;
}

} // namespace

int
main(void)
{
#ifdef DWMSTATUS_WITH_X11
    x11_display display;
#else  // DWMSTATUS_WITH_X11
    term_display display;
#endif  // DWMSTATUS_WITH_X11

    auto status{read_config(cin)};
    vector<string> status_str(status.size());

    while (true) {
        const auto t{system_clock::now()};
        bool changed{false};
        for (size_t i{0}; i < status.size(); ++i) {
            const auto s{status[i]->update(t)};
            if (s) {
                status_str[i] = *s;
                changed = true;
            }
        }
        if (changed) {
            display.set_status(" " + join(status_str, " • ") + " ");
        }
        this_thread::sleep_until(t + seconds(1));
    }
    return 0;
}
