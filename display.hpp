#ifndef DWMSTATUS_DISPLAY_HPP
#define DWMSTATUS_DISPLAY_HPP

#include "decl.hpp"

namespace dwmstatus {

class display
{
public:
    virtual void
    set_status(const string&) = 0;
};

//----------------------------------------------------------------------------

class term_display : public display
{
public:
    virtual void
    set_status(const string& s) override;
};

} // namespace dwmstatus

#ifdef DWMSTATUS_WITH_X11

#include <X11/Xlib.h>

namespace dwmstatus {

class x_display : public display
{
public:
    x_display();

    virtual void
    set_status(const string& s) override;

private:
    unique_ptr<Display, decltype(&XCloseDisplay)> dpy;
};

} // namespace dwmstatus

#endif  // DWMSTATUS_WITH_X11

#endif  // DWMSTATUS_DISPLAY_HPP
