#include "wisco/profiles/JohnProfile.hpp"

namespace wisco
{
namespace profiles
{
std::string JohnProfile::getName()
{
    return PROFILE_NAME;
}


int JohnProfile::getControlMode(user::EControlType control_type) const
{
    int mode{};
    if (CONTROL_MODE_MAP.contains(control_type))
        mode = CONTROL_MODE_MAP.at(control_type);
    return mode;
}

user::EControllerAnalog JohnProfile::getAnalogControlMapping(user::EControl control) const
{
    user::EControllerAnalog analog{user::EControllerAnalog::NONE};
    if (ANALOG_CONTROL_MAP.contains(control))
        analog = ANALOG_CONTROL_MAP.at(control);
    return analog;
}

user::EControllerDigital JohnProfile::getDigitalControlMapping(user::EControl control) const
{
    user::EControllerDigital digital{user::EControllerDigital::NONE};
    if (DIGITAL_CONTROL_MAP.contains(control))
        digital = DIGITAL_CONTROL_MAP.at(control);
    return digital;
}
}
}