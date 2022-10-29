#ifndef DWMSTATUS_FILE_HPP
#define DWMSTATUS_FILE_HPP

#include "decl.hpp"

namespace dwmstatus {

ifstream open_unbuf(const string& filename);

istream& rewind(istream& f);

//----------------------------------------------------------------------------

optional<string> read_line(istream& f);

template <typename T>
optional<T> read_value(istream& f)
{
    T ans;
    if (f >> ans) {
        return ans;
    } else {
        return nullopt;
    }
}

template <>
optional<string> read_value(istream& f);

istream& skip_line(istream& f, unsigned n = 1);

template <typename T>
istream& skip_value(istream& f, unsigned n = 1)
{
    while (n-- && read_value<T>(f)) {
        // Skip
    }
    return f;
}

//----------------------------------------------------------------------------

template <typename T>
optional<T> reread_value(istream& f)
{
    return read_value<T>(rewind(f));
}

} // namespace dwmstatus

#endif // DWMSTATUS_FILE_HPP
