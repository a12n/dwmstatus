/* License: WTFPL (http://www.wtfpl.net/) */

#include <err.h>

#include <unicode/udat.h>
#include <unicode/ustring.h>

#include "utime.h"

#define UTIME_BUF_SZ 128

static void
utime_check_error(UErrorCode code)
{
    if (code > U_ZERO_ERROR) {
        err(1, "utime: %s", u_errorName(code));
    }
}

static void*
utime_alloc(const char* pattern)
{
    if (pattern == NULL) {
        pattern = "EEEE, d MMMM yyyy HH:mm:ss";
    }

    UChar upattern[UTIME_BUF_SZ];
    UErrorCode code = U_ZERO_ERROR;

    u_strFromUTF8(upattern, UTIME_BUF_SZ, NULL, pattern, -1, &code);
    utime_check_error(code);

    UDateFormat* fmt;

    fmt = udat_open(UDAT_PATTERN, UDAT_PATTERN, NULL, NULL, -1, upattern, -1, &code);
    utime_check_error(code);
    if (fmt == NULL) {
        utime_check_error(U_STANDARD_ERROR_LIMIT);
    }

    return fmt;
}

static void
utime_free(void* opaque)
{
    udat_close((UDateFormat*)opaque);
}

static void
utime_update(void* opaque, time_t now, char* buf, size_t buf_sz)
{
    UChar ubuf[UTIME_BUF_SZ];
    UErrorCode code = U_ZERO_ERROR;

    int32_t n;

    n = udat_format((const UDateFormat*)opaque, 1000.0 * (double)now,
                    ubuf, UTIME_BUF_SZ, NULL, &code);
    utime_check_error(code);
    if (n > UTIME_BUF_SZ) {
        utime_check_error(U_STANDARD_ERROR_LIMIT);
    }

    u_strToUTF8(buf, buf_sz, NULL, ubuf, n, &code);
    utime_check_error(code);
}

struct status
utime_status(double interval, const char* pattern)
{
    return status_make(interval, utime_alloc(pattern), utime_free, utime_update);
}
