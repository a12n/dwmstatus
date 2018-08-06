#include <err.h>

#include "pfile.h"

FILE*
pfile_open(const char* pathname)
{
    FILE* ans;
    ans = fopen(pathname, "r");
    if (ans != NULL) {
        setvbuf(ans, NULL, _IONBF, 0);
    }
    return ans;
}

FILE*
pfile_open_err(const char* pathname)
{
    FILE* ans;
    ans = pfile_open(pathname);
    if (ans == NULL) {
        err(1, "pfile: couldn't open \"%s\"", pathname);
    }
    return ans;
}

void
pfile_close(FILE* pf)
{
    if (pf != NULL) {
        fclose(pf);
    }
}

static void
pfile_read(FILE* pf, const char* fmt, void* ans)
{
    rewind(pf);
    if (fscanf(pf, fmt, ans) != 1) {
        err(1, "pfile: couldn't read according to format \"%s\"", fmt);
    }
}

double
pfile_read_double(FILE* pf)
{
    double ans;
    pfile_read(pf, "%lf", &ans);
    return ans;
}

long
pfile_read_long(FILE* pf)
{
    long ans;
    pfile_read(pf, "%ld", &ans);
    return ans;
}
