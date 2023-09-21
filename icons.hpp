#ifndef DWMSTATUS_ICONS_HPP
#define DWMSTATUS_ICONS_HPP

#include "decl.hpp"

namespace dwmstatus {
namespace icons {

namespace awesome {             // Font Awesome

extern const vector<string> battery;
extern const vector<string> hourglass;
extern const vector<string> thermometer;

} // namespace awesome

namespace material {            // Material Icons

extern const vector<string> battery;
extern const vector<string> network_wifi;
extern const vector<string> wifi;

extern const string battery_alert;
extern const string battery_charging_full;
extern const string battery_saver;
extern const string network_wifi_off;
extern const string wifi_off;

} // namespace material

} // namespace icons
} // namespace dwmstatus

#endif // DWMSTATUS_ICONS_HPP
