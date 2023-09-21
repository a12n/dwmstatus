#ifndef DWMSTATUS_COLOR_HPP
#define DWMSTATUS_COLOR_HPP

// https://dwm.suckless.org/patches/sgrstatus/

namespace dwmstatus {
namespace color {

#ifdef DWMSTATUS_WITH_COLOR

#define CODE(name, code) \
    constexpr auto name = "\033[" code "m"

#else // DWMSTATUS_WITH_COLOR

#define CODE(name, code) \
    constexpr auto name = ""

#endif // DWMSTATUS_WITH_COLOR

#define BRIGHT(name, code) \
    CODE(bright_##name, "1;" code)

#define FGBG(name, num)     \
    namespace fg {          \
    CODE(name, "3" #num);   \
    BRIGHT(name, "3" #num); \
    }                       \
    namespace bg {          \
    CODE(name, "4" #num);   \
    }

FGBG(black, 0);
FGBG(red, 1);
FGBG(green, 2);
FGBG(yellow, 3);
FGBG(blue, 4);
FGBG(magenta, 5);
FGBG(cyan, 6);
FGBG(white, 7);

CODE(reset, "0");

#undef FGBG
#undef BRIGHT
#undef CODE

} // namespace color
} // namespace dwmstatus

#endif // DWMSTATUS_COLOR_HPP
