#include "wisco/profiles/HenryProfile.hpp"

namespace wisco
{
namespace profiles
{
std::string HenryProfile::getName()
{
    return PROFILE_NAME;
}

user::EChassisControlMode HenryProfile::getChassisControlMode()
{
    return CHASSIS_CONTROL_MODE;
}

user::EControllerAnalog HenryProfile::getAnalogControlMapping(std::string control)
{
    user::EControllerAnalog analog{user::EControllerAnalog::NONE};
    if (ANALOG_CONTROL_MAP.contains(control))
        analog = ANALOG_CONTROL_MAP.at(control);
    return analog;
}

user::EControllerDigital HenryProfile::getDigitalControlMapping(std::string control)
{
    user::EControllerDigital digital{user::EControllerDigital::NONE};
    if (DIGITAL_CONTROL_MAP.contains(control))
        digital = DIGITAL_CONTROL_MAP.at(control);
    return digital;
}
}
}