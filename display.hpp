#ifndef DWMSTATUS_DISPLAY_HPP
#define DWMSTATUS_DISPLAY_HPP

#include "decl.hpp"

namespace dwmstatus {

class display {
public:
    virtual ~display() = default;

    virtual void set_status(const string&) = 0;
};

//----------------------------------------------------------------------------

class term_display : public display {
public:
    virtual void set_status(const string& s) override;
};

} // namespace dwmstatus

#ifdef DWMSTATUS_WITH_X11

#include <xcb/xcb.h>
#include <xcb/xproto.h>

namespace dwmstatus {

class x11_display : public display {
public:
    x11_display();

    virtual void set_status(const string& s) override;

private:
    unique_ptr<xcb_connection_t, decltype(&xcb_disconnect)> conn;
    xcb_window_t root;
};

} // namespace dwmstatus

#endif // DWMSTATUS_WITH_X11

#endif // DWMSTATUS_DISPLAY_HPP
