#ifndef DWMSTATUS_ICONS_HPP
#define DWMSTATUS_ICONS_HPP

#include "decl.hpp"

namespace dwmstatus {
namespace icons {

namespace awesome { // Font Awesome

extern const vector<string> battery;
extern const vector<string> hourglass;
extern const vector<string> thermometer;

constexpr auto envelope = "";
constexpr auto microchip = "";
constexpr auto wifi = "";

} // namespace awesome

namespace material { // Material Icons

extern const vector<string> battery;
extern const vector<string> network_wifi;
extern const vector<string> wifi;

constexpr auto battery_alert = "";
constexpr auto battery_charging_full = "";
constexpr auto battery_saver = "";
constexpr auto network_wifi_off = "";
constexpr auto wifi_off = "";

} // namespace material

} // namespace icons
} // namespace dwmstatus

#endif // DWMSTATUS_ICONS_HPP
