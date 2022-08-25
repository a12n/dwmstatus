#include "display.hpp"

#include <cstdio>

namespace dwmstatus {

void term_display::set_status(const string& s)
{
    puts(s.c_str());
}

#ifdef DWMSTATUS_WITH_X11

//----------------------------------------------------------------------------

x11_display::x11_display()
    : dpy(XOpenDisplay(nullptr), XCloseDisplay)
{
    if (!dpy) {
        throw runtime_error("couldn't open X display");
    }
}

void x11_display::set_status(const string& s)
{
    XStoreName(dpy.get(), DefaultRootWindow(dpy.get()), s.c_str());
    XSync(dpy.get(), False);
}

#endif // DWMSTATUS_WITH_X11

} // namespace dwmstatus
