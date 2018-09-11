#include <experimental/filesystem>

#include "maildir.hpp"

namespace fs = std::experimental::filesystem;

namespace dwmstatus {

using std::getenv;

namespace {

size_t
count_files(const fs::path& dir)
{
    size_t ans = 0;
    for (const auto& f : fs::directory_iterator(dir)) {
        if (f.status().type() == fs::file_type::regular) {
            ++ans;
        }
    }
    return ans;
}

fs::path
default_dir()
{
    const char* home = getenv("HOME");
    if (home) {
        const char* email = getenv("EMAIL");
        if (email) {
            return fs::path(home) / "mail" / email / "INBOX";
        } else {
            return fs::path(home) / "Maildir";
        }
    } else {
        throw runtime_error("couldn't get default maildir path");
    }
}

set<string>
read_dir_set(istream& config)
{
    set<string> ans;
    string dir;
    while (config >> quoted(dir)) {
        ans.insert(dir);
    }
    return ans;
}

} // namespace

maildir_status::maildir_status(const set<string>& dir_set) :
    dirs(dir_set.begin(), dir_set.end())
{
    if (dirs.empty()) {
        dirs.push_back(default_dir());
    }
    dirs.shrink_to_fit();
}

maildir_status::maildir_status(istream& config) :
    maildir_status(read_dir_set(config))
{
}

string
maildir_status::update(const system_clock::time_point&)
{
    size_t n_cur = 0;
    size_t n_new = 0;
    for (const auto& p : dirs) {
        n_cur += count_files(fs::path(p) / "cur");
        n_new += count_files(fs::path(p) / "new");
    }
    ostringstream out;
    out << n_new << "/" << (n_new + n_cur);
    return out.str();
}

} // namespace dwmstatus
