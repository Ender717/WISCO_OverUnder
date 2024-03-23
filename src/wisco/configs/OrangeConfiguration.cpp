#include "wisco/configs/OrangeConfiguration.hpp"

namespace wisco
{
namespace configs
{
std::string OrangeConfiguration::getName()
{
    return CONFIGURATION_NAME;
}

std::shared_ptr<user::IController> OrangeConfiguration::buildController()
{
    return std::shared_ptr<user::IController>{};
}

std::shared_ptr<robot::Robot> OrangeConfiguration::buildRobot()
{
    return std::shared_ptr<robot::Robot>{};
}
}
}