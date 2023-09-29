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

// stdout prints status string to standard output, for spectrwm and
// other WMs reading bar's output.
struct stdout : abstract_display {
    virtual void set_status(string_view str) override;
};

} // namespace dwmstatus

#ifdef DWMSTATUS_WITH_X11

#include <xcb/xcb.h>
#include <xcb/xproto.h>

namespace dwmstatus {

// window_property writes status string to WM_NAME property of X root
// window, for DWM.
struct window_property : abstract_display {
    window_property();
    virtual void set_status(string_view str) override;

private:
    unique_ptr<xcb_connection_t, decltype(&xcb_disconnect)> conn_;
    xcb_window_t root_;
};

} // namespace dwmstatus

#endif // DWMSTATUS_WITH_X11

#endif // DWMSTATUS_DISPLAY_HPP
