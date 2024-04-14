#include "wisco/AutonomousManager.hpp"

namespace wisco
{

void AutonomousManager::setAutonomous(std::unique_ptr<IAutonomous>& autonomous)
{
    m_autonomous = std::move(autonomous);
}

void AutonomousManager::initializeAutonomous(std::shared_ptr<control::ControlSystem> control_system,
                                             std::shared_ptr<robot::Robot> robot)
{
    if (m_autonomous)
        m_autonomous->initialize(control_system, robot);
}

void AutonomousManager::runAutonomous(std::shared_ptr<control::ControlSystem> control_system,
                                      std::shared_ptr<robot::Robot> robot)
{
    if (m_autonomous)
        m_autonomous->run(control_system, robot);
}
}