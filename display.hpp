#ifndef DWMSTATUS_DISPLAY_HPP
#define DWMSTATUS_DISPLAY_HPP

#include "decl.hpp"

namespace dwmstatus {

struct display {
    virtual ~display() = default;
    virtual void set_status(string_view) = 0;
};

//----------------------------------------------------------------------------

struct term_display : display {
    virtual void set_status(string_view) override;
};

} // namespace dwmstatus

#ifdef DWMSTATUS_WITH_X11

#include <xcb/xcb.h>
#include <xcb/xproto.h>

namespace dwmstatus {

struct x11_display : display {
    x11_display();
    virtual void set_status(string_view) override;

private:
    unique_ptr<xcb_connection_t, decltype(&xcb_disconnect)> conn;
    xcb_window_t root;
};

} // namespace dwmstatus

#endif // DWMSTATUS_WITH_X11

#endif // DWMSTATUS_DISPLAY_HPP
