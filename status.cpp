#include "status.hpp"

namespace dwmstatus {

periodic::periodic(status_ptr status, seconds period)
    : status_ { move(status) }
    , period_ { period }
{
}

optional<string> periodic::update(system_clock::time_point t)
{
    if (t > t0_ && (t - t0_) < period_) {
        return nullopt;
    }
    t0_ = t;
    if (!status_) {
        return nullopt;
    }
    return status_->update(t);
}

//----------------------------------------------------------------------------

bar::bar(vector<status_ptr> items, string_view sep, string_view prefix, string_view suffix)
    : items_ { move(items) }
    , str_ { items_.size() }
    , sep_ { sep }
    , prefix_ { prefix }
    , suffix_ { suffix }
{
}

optional<string> bar::update(system_clock::time_point t)
{
    bool changed = false;

    for (unsigned i = 0; i < items_.size(); ++i) {
        if (!items_[i]) {
            continue;
        }
        if (const auto str = items_[i]->update(t); str) {
            changed = true;
            str_[i] = str.value();
        }
    }

    if (changed) {
        string ans = prefix_;
        for (unsigned i = 0; i < str_.size(); ++i) {
            if (i != 0) {
                ans += sep_;
            }
            ans += str_[i];
        }
        return ans + suffix_;
    }

    return nullopt;
}

} // namespace dwmstatus
