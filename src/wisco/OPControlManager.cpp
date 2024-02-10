#include "wisco/OPControlManager.hpp"

namespace wisco
{
void OPControlManager::setProfile(std::unique_ptr<IProfile>& profile)
{
    m_profile = std::move(profile);
}

void OPControlManager::initializeOpcontrol(std::shared_ptr<robot::Robot> robot)
{

}

void OPControlManager::runOpcontrol(std::shared_ptr<robot::Robot> robot)
{

}
}