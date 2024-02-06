#include "wisco/profiles/HenryProfile.hpp"

namespace wisco
{
namespace profiles
{
std::string HenryProfile::getName()
{
    return PROFILE_NAME;
}

std::string HenryProfile::getChassisControlMode()
{
    return CHASSIS_CONTROL_MODE;
}

std::string HenryProfile::getControlMapping(std::string control)
{
    return CONTROL_MAP.at(control);
}
}
}