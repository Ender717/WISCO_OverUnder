#include "wisco/configs/BlueConfiguration.hpp"

namespace wisco
{
namespace configs
{
std::string BlueConfiguration::getName()
{
    return CONFIGURATION_NAME;
}

std::shared_ptr<robot::Robot> BlueConfiguration::buildRobot()
{
    return std::shared_ptr<robot::Robot>{};
}
}
}