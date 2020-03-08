#include <sys/types.h>

#include <dirent.h>
#include <limits.h>

#include <cstdlib>

#include "maildir.hpp"

namespace dwmstatus {
namespace {

using dir_ptr = unique_ptr<DIR, decltype(&closedir)>;

dir_ptr
open_dir(const string& path)
{
    dir_ptr ans{opendir(path.c_str()), closedir};
    if (! ans) {
        throw runtime_error("couldn't open directory \"" + path + "\"");
    }
    return ans;
}

string
resolve_path(const string& path)
{
    char ans[PATH_MAX];
    if (! realpath(path.c_str(), ans)) {
        throw runtime_error("couldn't resolve path \"" + path + "\"");
    }
    return ans;
}

unsigned int
count_files(const string& path)
{
    unsigned int ans{0};
    auto dir{open_dir(path)};
    while (const auto f{readdir(dir.get())}) {
        if (f->d_type == DT_REG) {
            ++ans;
        }
    }
    return ans;
}

string
default_dir()
{
    const char* home{getenv("HOME")};
    if (home) {
        const char* email{getenv("EMAIL")};
        if (email) {
            return string(home) + "/mail/" + email + "/INBOX";
        } else {
            return string(home) + "/Maildir";
        }
    } else {
        throw runtime_error("couldn't get default maildir path");
    }
}

set<string>
read_string_set(istream& config)
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
    for (auto& path : dirs) {
        path = resolve_path(path);
    }
    dirs.shrink_to_fit();
}

maildir_status::maildir_status(istream& config) :
    maildir_status(read_string_set(config))
{
}

string
maildir_status::update(system_clock::time_point)
{
    unsigned int n_new{0};
    for (const auto& p : dirs) {
        n_new += count_files(p + "/new");
    }
    return to_string(n_new);
}

} // namespace dwmstatus
