#include "wisco/profiles/JohnProfile.hpp"

namespace wisco
{
namespace profiles
{
std::string JohnProfile::getName()
{
    return PROFILE_NAME;
}

std::string JohnProfile::getChassisControlMode()
{
    return CHASSIS_CONTROL_MODE;
}

std::string JohnProfile::getControlMapping(std::string control)
{
    return CONTROL_MAP.at(control);
}
}
}