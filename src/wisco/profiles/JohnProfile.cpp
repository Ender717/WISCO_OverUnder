#include "wisco/profiles/JohnProfile.hpp"

namespace wisco
{
namespace profiles
{
std::string JohnProfile::getName()
{
    return PROFILE_NAME;
}

int JohnProfile::getControlMode(std::string control)
{
    int mode{};
    if (CONTROL_MODE_MAP.contains(control))
        mode = CONTROL_MODE_MAP.at(control);
    return mode;
}

user::EControllerAnalog JohnProfile::getAnalogControlMapping(std::string control)
{
    user::EControllerAnalog analog{user::EControllerAnalog::NONE};
    if (ANALOG_CONTROL_MAP.contains(control))
        analog = ANALOG_CONTROL_MAP.at(control);
    return analog;
}

user::EControllerDigital JohnProfile::getDigitalControlMapping(std::string control)
{
    user::EControllerDigital digital{user::EControllerDigital::NONE};
    if (DIGITAL_CONTROL_MAP.contains(control))
        digital = DIGITAL_CONTROL_MAP.at(control);
    return digital;
}
}
}