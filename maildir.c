/* License: WTFPL (http://www.wtfpl.net/) */

#include <sys/types.h>

#include <dirent.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "maildir.h"

struct maildir_state
{
    DIR* cur_dirp;
    DIR* new_dirp;
};

static size_t
count_files(DIR* dirp)
{
    size_t n = 0;

    rewinddir(dirp);
    while (1) {
        struct dirent* dp;

        dp = readdir(dirp);
        if (dp == NULL) {
            break;
        }

        if (dp->d_type == DT_REG) {
            ++n;
        }
    }

    return n;
}

static DIR*
open_subdir(const char* base, const char* sub)
{
    char path[256];

    /* TODO: Check for buf is of enough size */
    snprintf(path, sizeof(path), "%s/%s", base, sub);

    return opendir(path);
}

static void*
maildir_alloc(const char* path)
{
    struct maildir_state* state;

    state = calloc(1, sizeof(struct maildir_state));
    if (state == NULL) {
        err(1, "maildir: couldn't allocate state");
    }

    state->cur_dirp = open_subdir(path, "cur");
    state->new_dirp = open_subdir(path, "new");
    if (state->cur_dirp == NULL ||
        state->new_dirp == NULL)
    {
        errx(1, "maildir: path \"%s\" doesn't look like a maildir", path);
    }

    return state;
}

static void
maildir_free(void* opaque)
{
    struct maildir_state* state = (struct maildir_state*)opaque;

    closedir(state->new_dirp);
    closedir(state->cur_dirp);
    free(state);
}

static void
maildir_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    struct maildir_state* state = (struct maildir_state*)opaque;

    size_t n_cur;
    size_t n_new;

    (void)now;

    n_cur = count_files(state->cur_dirp);
    n_new = count_files(state->new_dirp);

    snprintf(buf, buf_sz, "%zu/%zu", n_new, n_new + n_cur);
}

static const char*
maildir_default_path(void)
{
    static char path[256];

    const char* email;
    const char* home;

    home = getenv("HOME");
    if (home != NULL) {
        email = getenv("EMAIL");
        if (email != NULL) {
            snprintf(path, sizeof(path), "%s/mail/%s/INBOX", home, email);
        } else {
            snprintf(path, sizeof(path), "%s/Maildir", home);
        }
        return path;
    } else {
        return NULL;
    }
}

struct status
maildir_status(double interval, const char* path)
{
    if (path == NULL) {
        path = maildir_default_path();
    }
    return status_make(
        interval, maildir_alloc(path), maildir_free, maildir_update);
}
