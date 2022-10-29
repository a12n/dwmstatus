#include "file.hpp"

namespace dwmstatus {
namespace {

ifstream& unbuf(ifstream& f)
{
    f.rdbuf()->pubsetbuf(nullptr, 0);
    return f;
}

} // namespace

ifstream open_unbuf(const string& filename)
{
    ifstream f { filename };
    if (!f.is_open()) {
        throw std::ios_base::failure("couldn't open file");
    }
    return move(unbuf(f));
}

istream& rewind(istream& f)
{
    f.clear();
    f.seekg(0);
    return f;
}

//----------------------------------------------------------------------------

optional<string> read_line(istream& f)
{
    string ans;
    if (getline(f, ans)) {
        return ans;
    } else {
        return nullopt;
    }
}

template <>
optional<string> read_value(istream& f)
{
    string ans;
    if (f >> quoted(ans)) {
        return ans;
    } else {
        return nullopt;
    }
}

istream& skip_line(istream& f, unsigned n)
{
    while (n-- && read_line(f)) {
        // Skip
    }
    return f;
}

} // namespace dwmstatus
