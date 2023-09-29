#ifndef DWMSTATUS_DISPLAY_HPP
#define DWMSTATUS_DISPLAY_HPP

#include "decl.hpp"

namespace dwmstatus {

struct abstract_display {
    virtual ~abstract_display() = default;
    virtual void set_status(string_view str) = 0;
};

using display_ptr = unique_ptr<abstract_display>;

//----------------------------------------------------------------------------

struct term_display : abstract_display {
    virtual void set_status(string_view) override;
};

} // namespace dwmstatus

#ifdef DWMSTATUS_WITH_X11

#include <xcb/xcb.h>
#include <xcb/xproto.h>

namespace dwmstatus {

struct x11_display : abstract_display {
    x11_display();
    virtual void set_status(string_view) override;

private:
    unique_ptr<xcb_connection_t, decltype(&xcb_disconnect)> conn_;
    xcb_window_t root_;
};

} // namespace dwmstatus

#endif // DWMSTATUS_WITH_X11

#endif // DWMSTATUS_DISPLAY_HPP
