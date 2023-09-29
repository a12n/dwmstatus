#include "mail_dir.hpp"

#include "color.hpp"
#include "icons.hpp"

#include <cstdlib>

#include <dirent.h>
#include <limits.h>

#include <sys/types.h>

namespace dwmstatus {
namespace {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
using dir_ptr = unique_ptr<DIR, decltype(&closedir)>;
#pragma GCC diagnostic pop

dir_ptr open_dir(const string& path)
{
    dir_ptr ans { opendir(path.c_str()), closedir };
    if (!ans) {
        throw runtime_error("mail_dir: couldn't open directory \"" + path + "\"");
    }
    return ans;
}

string resolve_path(const string& path)
{
    char ans[PATH_MAX];
    if (!realpath(path.c_str(), ans)) {
        throw runtime_error("mail_dir: couldn't resolve path \"" + path + "\"");
    }
    return ans;
}

unsigned count_files(const string& path)
{
    auto dir = open_dir(path);
    unsigned n = 0;
    while (const auto f = readdir(dir.get())) {
        if (f->d_type == DT_REG) {
            ++n;
        }
    }
    return n;
}

string default_dir()
{
    if (const char* home = getenv("HOME")) {
        return string(home) + "/Maildir";
    } else {
        throw runtime_error("mail_dir: couldn't get default maildir path");
    }
}

} // namespace

mail_dir::mail_dir(const set<string>& dirs)
    : dirs_ { dirs.begin(), dirs.end() }
{
    if (dirs_.empty()) {
        dirs_.push_back(default_dir());
    }
    for (auto& path : dirs_) {
        path = resolve_path(path);
    }
    dirs_.shrink_to_fit();
}

optional<string> mail_dir::update(system_clock::time_point)
{
    unsigned n_new = 0;

    for (const auto& p : dirs_) {
        n_new += count_files(p + "/new");
    }

    ostringstream out;

    if (n_new > 0) {
        out << color::fg::green;
    }
    out << icons::awesome::envelope << ' ' << n_new
        << color::reset;

    return out.str();
}

} // namespace dwmstatus
