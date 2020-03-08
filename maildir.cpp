#include <filesystem>

#include "maildir.hpp"

namespace fs = std::filesystem;

namespace dwmstatus {
namespace {

unsigned int
count_files(const fs::path& dir)
{
    unsigned int ans{0};
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
    const char* home{getenv("HOME")};
    if (home) {
        const char* email{getenv("EMAIL")};
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
        ans.emplace(dir);
    }
    return ans;
}

} // namespace

maildir_status::maildir_status(const set<string>& dir_set) :
    dirs(cbegin(dir_set), cend(dir_set))
{
    if (dirs.empty()) {
        dirs.emplace_back(default_dir());
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
    unsigned int n_new{0};
    for (const auto& p : dirs) {
        n_new += count_files(fs::path(p) / "new");
    }
    return to_string(n_new);
}

} // namespace dwmstatus
