#include "wisco/AutonomousManager.hpp"

namespace wisco
{

void AutonomousManager::setAutonomous(std::unique_ptr<IAutonomous>& autonomous)
{
    m_autonomous = std::move(autonomous);
}

void AutonomousManager::initializeAutonomous(std::shared_ptr<robot::Robot> robot)
{

}

void AutonomousManager::runAutonomous(std::shared_ptr<robot::Robot> robot)
{

}
}