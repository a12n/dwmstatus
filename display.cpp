#include "display.hpp"

#include <cstdio>

namespace dwmstatus {

void term_display::set_status(string_view str)
{
    cout << str << endl;
}

#ifdef DWMSTATUS_WITH_X11

//----------------------------------------------------------------------------

x11_display::x11_display()
    : conn_(xcb_connect(nullptr, nullptr), xcb_disconnect)
{
    if (xcb_connection_has_error(conn_.get())) {
        throw runtime_error("couldn't connect to X server");
    }
    root_ = xcb_setup_roots_iterator(xcb_get_setup(conn_.get())).data->root;
}

void x11_display::set_status(string_view str)
{
    xcb_change_property(conn_.get(), XCB_PROP_MODE_REPLACE, root_,
        XCB_ATOM_WM_NAME, XCB_ATOM_STRING,
        8, str.size(), str.data());
    xcb_flush(conn_.get());
}

#endif // DWMSTATUS_WITH_X11

} // namespace dwmstatus
