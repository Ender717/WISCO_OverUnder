#include "wisco/AutonomousManager.hpp"

namespace wisco
{
AutonomousManager::AutonomousManager(const std::shared_ptr<rtos::IClock>& clock, const std::unique_ptr<rtos::IDelayer>& delayer) 
    : m_clock{clock}, m_delayer{delayer->clone()}
{

}

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
        m_autonomous->run(m_clock, m_delayer, control_system, robot);
}
}