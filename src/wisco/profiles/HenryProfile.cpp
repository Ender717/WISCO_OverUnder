#include "wisco/profiles/HenryProfile.hpp"

namespace wisco
{
namespace profiles
{
std::string HenryProfile::getName()
{
    return PROFILE_NAME;
}

int HenryProfile::getControlMode(user::EControlType control_type) const
{
    int mode{};
    if (CONTROL_MODE_MAP.contains(control_type))
        mode = CONTROL_MODE_MAP.at(control_type);
    return mode;
}

void HenryProfile::setControlMode(user::EControlType control_type, int control_mode)
{
    CONTROL_MODE_MAP[control_type] = control_mode;
}

user::EControllerAnalog HenryProfile::getAnalogControlMapping(user::EControl control) const
{
    user::EControllerAnalog analog{user::EControllerAnalog::NONE};
    if (ANALOG_CONTROL_MAP.contains(control))
        analog = ANALOG_CONTROL_MAP.at(control);
    return analog;
}

user::EControllerDigital HenryProfile::getDigitalControlMapping(user::EControl control) const
{
    user::EControllerDigital digital{user::EControllerDigital::NONE};
    if (DIGITAL_CONTROL_MAP.contains(control))
        digital = DIGITAL_CONTROL_MAP.at(control);
    return digital;
}
}
}